/*
 * t38proto.cxx
 *
 * T.38 protocol handler
 *
 * Open Phone Abstraction Library
 *
 * Copyright (c) 1998-2002 Equivalence Pty. Ltd.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Open H323 Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): Vyacheslav Frolov.
 *
 */

#include <ptlib.h>

#ifdef __GNUC__
#pragma implementation "t38proto.h"
#endif

#include <t38/t38proto.h>

#if OPAL_FAX

#include <asn/t38.h>
#include <opal/patch.h>
#include <codec/opalpluginmgr.h>


/////////////////////////////////////////////////////////////////////////////

OPAL_DEFINE_MEDIA_COMMAND(OpalFaxTerminate, PLUGINCODEC_CONTROL_TERMINATE_CODEC, OpalMediaType::Fax());

#define new PNEW


static const char TIFF_File_FormatName[] = OPAL_FAX_TIFF_FILE;
const PCaselessString & OpalFaxSession::UDPTL() { return OpalFaxMediaDefinition::UDPTL(); }
PFACTORY_CREATE(OpalMediaSessionFactory, OpalFaxSession, OpalFaxMediaDefinition::UDPTL());


/////////////////////////////////////////////////////////////////////////////

OpalFaxMediaStream::OpalFaxMediaStream(OpalConnection & conn,
                                       const OpalMediaFormat & mediaFormat,
                                       unsigned sessionID,
                                       bool isSource,
                                       OpalFaxSession & session)
  : OpalMediaStream(conn, mediaFormat, sessionID, isSource)
  , m_session(session)
{
}


PBoolean OpalFaxMediaStream::Open()
{
  m_session.ApplyMediaOptions(m_mediaFormat);
  return OpalMediaStream::Open();
}


bool OpalFaxMediaStream::InternalUpdateMediaFormat(const OpalMediaFormat & mediaFormat)
{
  if (!IsOpen())
    return false;

  m_session.ApplyMediaOptions(mediaFormat);
  return OpalMediaStream::InternalUpdateMediaFormat(mediaFormat);
}


PBoolean OpalFaxMediaStream::ReadPacket(RTP_DataFrame & packet)
{
  if (!IsOpen())
    return false;

  if (!m_session.ReadData(packet))
    return false;

  m_timestamp = packet.GetTimestamp();
  return true;
}


PBoolean OpalFaxMediaStream::WritePacket(RTP_DataFrame & packet)
{
  if (!IsOpen())
    return false;

  m_timestamp = packet.GetTimestamp();
  return m_session.WriteData(packet);
}


PString OpalFaxMediaStream::GetPatchThreadName() const
{
  return PSTRSTRM((IsSource() ? 'R' : 'T') << "x " << GetMediaFormat());
}


PBoolean OpalFaxMediaStream::IsSynchronous() const
{
  return false;
}


void OpalFaxMediaStream::InternalClose()
{
  m_session.Close();
}


void OpalFaxMediaStream::GetStatistics(OpalMediaStatistics & statistics, bool fromPatch) const
{
  m_session.GetStatistics(statistics, IsSource());
  OpalMediaStream::GetStatistics(statistics, fromPatch);
}


/////////////////////////////////////////////////////////////////////////////

OpalFaxSession::OpalFaxSession(const Init & init)
  : OpalMediaSession(init)
  , m_rawUDPTL(false)
  , m_datagramSize(528)
  , m_consecutiveBadPackets(0)
  , m_awaitingGoodPacket(true)
  , m_receivedPacket(new T38_UDPTLPacket)
  , m_expectedSequenceNumber(0)
  , m_secondaryPacket(-1)
  , m_optimiseOnRetransmit(false) // not optimise udptl packets on retransmit
  , m_sentPacket(new T38_UDPTLPacket)
  , m_txBytes(0)
  , m_txPackets(0)
  , m_rxBytes(0)
  , m_rxPackets(0)
  , m_missingPackets(0)
{
  m_timerWriteDataIdle.SetNotifier(PCREATE_NOTIFIER(OnWriteDataIdle), "T38Idle");

  m_sentPacket->m_error_recovery.SetTag(T38_UDPTLPacket_error_recovery::e_secondary_ifp_packets);
  m_sentPacket->m_seq_number = (unsigned)-1;

  m_redundancy[32767] = 1;  // re-send all ifp packets 1 time
}


OpalFaxSession::~OpalFaxSession()
{
  m_timerWriteDataIdle.Stop();
  delete m_receivedPacket;
  delete m_sentPacket;
}


void OpalFaxSession::ApplyMediaOptions(const OpalMediaFormat & mediaFormat)
{
  PString option = mediaFormat.GetOptionString("UDPTL-Redundancy");
  if (!option.IsEmpty()) {
    PStringArray value = option.Tokenise(",", FALSE);
    PWaitAndSignal mutex(m_writeMutex);

    m_redundancy.clear();

    for (PINDEX i = 0 ; i < value.GetSize() ; i++) {
      PString size, redundancy;
      if (value[i].Split(':', size, redundancy, PString::SplitTrim|PString::SplitBeforeNonEmpty|PString::SplitAfterNonEmpty))
        m_redundancy[size.AsInteger()] = redundancy.AsInteger();
    }

#if PTRACING
    if (PTrace::CanTrace(3)) {
      ostream & trace = PTRACE_BEGIN(3);
      trace << "UDPTL\tUse redundancy \"";
      for (std::map<int, int>::iterator it = m_redundancy.begin() ; it != m_redundancy.end() ; it++) {
        if (it != m_redundancy.begin())
          trace << ",";
        trace << it->first << ':' << it->second;
      }
      trace << '"' << PTrace::End;
    }
#endif
  }

  int optint = mediaFormat.GetOptionInteger("UDPTL-Redundancy-Interval", m_redundancyInterval.GetSeconds());
  if (optint != m_redundancyInterval.GetSeconds()) {
    PWaitAndSignal mutex(m_writeMutex);
    m_redundancyInterval.SetInterval(0, optint);
    PTRACE(3, "UDPTL\tUse redundancy interval " << m_redundancyInterval);
  }

  optint = mediaFormat.GetOptionInteger("UDPTL-Keep-Alive-Interval", m_keepAliveInterval.GetInterval());
  if (optint != m_keepAliveInterval.GetSeconds()) {
    PWaitAndSignal mutex(m_writeMutex);
    m_keepAliveInterval.SetInterval(0, optint);
    PTRACE(3, "UDPTL\tUse keep-alive interval " << m_keepAliveInterval);
  }

  bool optbool = mediaFormat.GetOptionBoolean("UDPTL-Optimise-On-Retransmit", m_optimiseOnRetransmit);
  if (optbool != m_optimiseOnRetransmit) {
    PWaitAndSignal mutex(m_writeMutex);
    m_optimiseOnRetransmit = optbool;
    PTRACE(3, "UDPTL\tUse optimise on retransmit - " << (m_optimiseOnRetransmit ? "true" : "false"));
  }

  optbool = mediaFormat.GetOptionBoolean("UDPTL-Raw-Mode", m_rawUDPTL);
  if (optbool != m_rawUDPTL) {
    PWaitAndSignal mutex(m_writeMutex);
    m_rawUDPTL = optbool;
    PTRACE(3, "UDPTL\tSetting raw UDPTL mode to " << m_rawUDPTL);
  }

  optint = mediaFormat.GetOptionInteger("T38FaxMaxDatagram", m_datagramSize);
  if (optint != (int)m_datagramSize) {
    PWaitAndSignal mutex(m_writeMutex);
    m_datagramSize = optint;
    PTRACE(3, "UDPTL\tDatagram size set to " << m_datagramSize);
  }
}


void OpalFaxSession::AttachTransport(const OpalMediaTransportPtr & transport)
{
  m_transport = transport;
  m_transport->AddReadNotifier(PCREATE_NOTIFIER(OnReadPacket));
}


bool OpalFaxSession::Open(const PString & localInterface, const OpalTransportAddress & remoteAddress)
{
  if (IsOpen())
    return true;

  // T.38 over TCP is half baked. One day someone might want it enough for it to be finished
  if (remoteAddress.IsEmpty() || remoteAddress.GetProto(true) == OpalTransportAddress::UdpPrefix())
    m_transport = new OpalUDPMediaTransport("T.38-UDP");
  else
    m_transport = new OpalTCPMediaTransport("T.38-TCP");
  PTRACE_CONTEXT_ID_TO(m_transport);

  PIPSocket::Address localIP(localInterface);
  if (!localIP.IsValid() || !m_transport->Open(*this, 1, localIP, remoteAddress)) {
    PTRACE(2, "UDPTL\tCould listen on interface=\"" << localInterface << '"');
    return false;
  }

  if (!remoteAddress.IsEmpty() && !m_transport->SetRemoteAddress(remoteAddress.GetHostName(true))) {
    PTRACE(2, "UDPTL\tCould conect to " << remoteAddress);
    return false;
  }

  m_transport->AddReadNotifier(PCREATE_NOTIFIER(OnReadPacket));

  PTRACE(3, "UDPTL\tOpened transport to " << remoteAddress);
  return true;
}


bool OpalFaxSession::IsOpen() const
{
  return m_transport != NULL && m_transport->IsOpen();
}


bool OpalFaxSession::Close()
{
  if (m_transport == NULL)
    return false;

  m_transport->RemoveReadNotifier(this);
  m_readQueue.Close(false);
  return OpalMediaSession::Close();
}


OpalMediaStream * OpalFaxSession::CreateMediaStream(const OpalMediaFormat & mediaFormat, unsigned sessionID, bool isSource)
{
  return new OpalFaxMediaStream(m_connection, mediaFormat, sessionID, isSource, *this);
}


bool OpalFaxSession::WriteData(RTP_DataFrame & frame)
{
  if (m_transport == NULL)
    return false;

  if (m_rawUDPTL) {
    PTRACE(5, "UDPTL\tSending raw UDPTL, size=" << frame.GetPayloadSize());
    return m_transport->Write(frame.GetPayloadPtr(), frame.GetPayloadSize());
  }

  PINDEX plLen = frame.GetPayloadSize();

  if (plLen == 0) {
    PTRACE(2, "UDPTL\tInternal error - empty payload");
    return false;
  }

  PWaitAndSignal mutex(m_writeMutex);

  if (!m_sentPacketRedundancy.empty()) {
    T38_UDPTLPacket_error_recovery &recovery = m_sentPacket->m_error_recovery;

    if (recovery.GetTag() == T38_UDPTLPacket_error_recovery::e_secondary_ifp_packets) {
      // shift old primary ifp packet to secondary list

      T38_UDPTLPacket_error_recovery_secondary_ifp_packets &secondary = recovery;

      if (secondary.SetSize(secondary.GetSize() + 1)) {
        for (int i = secondary.GetSize() - 2 ; i >= 0 ; i--) {
          secondary[i + 1] = secondary[i];
          secondary[i] = T38_UDPTLPacket_error_recovery_secondary_ifp_packets_subtype();
        }

        secondary[0].SetValue(m_sentPacket->m_primary_ifp_packet.GetValue());
        m_sentPacket->m_primary_ifp_packet = T38_UDPTLPacket_primary_ifp_packet();
      }
    } else {
      PTRACE(3, "UDPTL\tNot implemented yet " << recovery.GetTagName());
    }
  }

  // calculate redundancy for new ifp packet

  int redundancy = 0;

  for (std::map<int, int>::iterator i = m_redundancy.begin() ; i != m_redundancy.end() ; i++) {
    if ((int)plLen <= i->first) {
      if (redundancy < i->second)
        redundancy = i->second;

      break;
    }
  }

  if (redundancy > 0 || !m_sentPacketRedundancy.empty())
    m_sentPacketRedundancy.insert(m_sentPacketRedundancy.begin(), redundancy + 1);

  // set new primary ifp packet

  m_sentPacket->m_seq_number = frame.GetSequenceNumber();
  m_sentPacket->m_primary_ifp_packet.SetValue(frame.GetPayloadPtr(), plLen);

  bool ok = WriteUDPTL();

  DecrementSentPacketRedundancy(true);

  if (m_sentPacketRedundancy.empty() || m_redundancyInterval <= 0)
    m_timerWriteDataIdle = m_keepAliveInterval;
  else
    m_timerWriteDataIdle = m_redundancyInterval;

  return ok;
}


void OpalFaxSession::OnWriteDataIdle(PTimer &, P_INT_PTR)
{
  PWaitAndSignal mutex(m_writeMutex);

  WriteUDPTL();

  DecrementSentPacketRedundancy(m_optimiseOnRetransmit);
}


void OpalFaxSession::DecrementSentPacketRedundancy(bool stripRedundancy)
{
  int iMax = (int)m_sentPacketRedundancy.size() - 1;

  for (int i = iMax ; i >= 0 ; i--) {
    m_sentPacketRedundancy[i]--;

    if (i == iMax && m_sentPacketRedundancy[i] <= 0)
      iMax--;
  }

  m_sentPacketRedundancy.resize(iMax + 1);

  if (stripRedundancy) {
    T38_UDPTLPacket_error_recovery & recovery = m_sentPacket->m_error_recovery;

    if (recovery.GetTag() == T38_UDPTLPacket_error_recovery::e_secondary_ifp_packets) {
      T38_UDPTLPacket_error_recovery_secondary_ifp_packets &secondary = recovery;
      secondary.SetSize(iMax > 0 ? iMax : 0);
    } else {
      PTRACE(3, "UDPTL\tNot implemented yet " << recovery.GetTagName());
    }
  }
}


bool OpalFaxSession::WriteUDPTL()
{
  if (m_transport == NULL || !m_transport->IsOpen()) {
    PTRACE(2, "UDPTL\tWrite failed, data socket not open");
    return false;
  }

  PPER_Stream rawData;
  m_sentPacket->Encode(rawData);
  rawData.CompleteEncoding();

  PTRACE(5, "UDPTL\tEncoded transmitted UDPTL data, size=" << rawData.GetSize() << " :\n  " << setprecision(2) << *m_sentPacket);

  m_txBytes += rawData.GetSize();
  ++m_txPackets;

  return m_transport->Write(rawData.GetPointer(), rawData.GetSize());
}


void OpalFaxSession::SetFrameFromIFP(RTP_DataFrame & frame, const PASN_OctetString & ifp, unsigned sequenceNumber)
{
  frame.SetPayload(ifp, ifp.GetDataLength());
  frame.SetSequenceNumber((WORD)(sequenceNumber & 0xffff));
  if (m_secondaryPacket <= 0)
    m_expectedSequenceNumber = sequenceNumber+1;
}


void OpalFaxSession::OnReadPacket(OpalMediaTransport &, PBYTEArray data)
{
  m_readQueue.Enqueue(data);
}


bool OpalFaxSession::ReadData(RTP_DataFrame & frame)
{
  PBYTEArray rawData;
  if (!m_readQueue.Dequeue(rawData))
    return false;

  if (rawData.GetSize() >= m_datagramSize) {
    PTRACE(4, "UDPTL\tProbable RTP packet");
    return true;
  }

  if (m_rawUDPTL) {
    frame.SetPayload(rawData, rawData.GetSize());
    m_rxBytes += frame.GetPayloadSize();
    ++m_rxPackets;
    PTRACE(5, "UDPTL\tRead raw UDPTL, size " << frame.GetPayloadSize());
    return true;
  }

  if (m_secondaryPacket >= 0) {
    if (m_secondaryPacket == 0)
      SetFrameFromIFP(frame, m_receivedPacket->m_primary_ifp_packet, m_receivedPacket->m_seq_number);
    else {
      T38_UDPTLPacket_error_recovery_secondary_ifp_packets & secondaryPackets = m_receivedPacket->m_error_recovery;
      SetFrameFromIFP(frame, secondaryPackets[m_secondaryPacket-1], m_receivedPacket->m_seq_number - m_secondaryPacket);
    }
    --m_secondaryPacket;
    return true;
  }

  PPER_Stream per(rawData);
  // Decode the PDU, but not if still receiving RTP
  if (  !m_receivedPacket->Decode(per) ||
         per.GetPosition() < per.GetSize() ||
        (m_awaitingGoodPacket &&
          (
            m_receivedPacket->m_primary_ifp_packet.GetSize() == 0 ||
            m_receivedPacket->m_seq_number >= 32768
          )
        )
     )
  {
    if (++m_consecutiveBadPackets > 1000) {
      PTRACE(1, "T38_UDPTL\tRaw data decode failed 1000 times, remote probably not switched from audio, aborting!");
      return false;
    }

#if PTRACING
    const unsigned Level = m_awaitingGoodPacket ? 4 : 2;
    if (PTrace::CanTrace(Level)) {
      ostream & trace = PTRACE_BEGIN(Level);
      trace << "UDPTL\t";
      if (m_awaitingGoodPacket)
        trace << "Probable RTP packet: " << rawData.GetSize() << " bytes.";
      else {
        trace << "Raw data decode failure:\n  "
              << setprecision(2) << rawData << "\n  UDPTL = "
              << setprecision(2) << m_receivedPacket;
      }
      trace << PTrace::End;
    }
#endif

    return true;
  }

  PTRACE_IF(3, m_awaitingGoodPacket, "UDPTL\tFirst decoded UDPTL packet");
  m_awaitingGoodPacket = false;
  m_consecutiveBadPackets = 0;

  PTRACE(5, "UDPTL\tDecoded UDPTL packet:\n  " << setprecision(2) << *m_receivedPacket);

  int missing = m_receivedPacket->m_seq_number - m_expectedSequenceNumber;
  if (missing > 0 && m_receivedPacket->m_error_recovery.GetTag() == T38_UDPTLPacket_error_recovery::e_secondary_ifp_packets) {
    // Packets are missing and we have redundency in the UDPTL packets
    T38_UDPTLPacket_error_recovery_secondary_ifp_packets & secondaryPackets = m_receivedPacket->m_error_recovery;
    if (secondaryPackets.GetSize() > 0) {
      PTRACE(4, "UDPTL\tUsing redundant data to reconstruct missing/out of order packet at SN=" << m_expectedSequenceNumber);
      m_secondaryPacket = missing;
      if ((PINDEX)m_secondaryPacket > secondaryPackets.GetSize())
        m_secondaryPacket = secondaryPackets.GetSize();
      SetFrameFromIFP(frame, secondaryPackets[m_secondaryPacket-1], m_receivedPacket->m_seq_number - m_secondaryPacket);
      --m_secondaryPacket;
      return true;
    }
  }

  SetFrameFromIFP(frame, m_receivedPacket->m_primary_ifp_packet, m_receivedPacket->m_seq_number);
  m_expectedSequenceNumber = m_receivedPacket->m_seq_number+1;

  m_rxBytes += rawData.GetSize();
  ++m_rxPackets;
  m_missingPackets += missing;

  return true;
}


void OpalFaxSession::GetStatistics(OpalMediaStatistics & statistics, bool receiver) const
{
  statistics.m_totalBytes = receiver ? m_rxBytes : m_txBytes;
  statistics.m_totalPackets = receiver ? m_rxPackets : m_txPackets;
  statistics.m_packetsLost = receiver ? m_missingPackets : 0;
}


/////////////////////////////////////////////////////////////////////////////

OpalFaxEndPoint::OpalFaxEndPoint(OpalManager & mgr, const char * g711Prefix, const char * t38Prefix)
  : OpalLocalEndPoint(mgr, g711Prefix, false)
  , m_t38Prefix(t38Prefix)
  , m_defaultDirectory(".")
{
  if (t38Prefix != NULL)
    mgr.AttachEndPoint(this, m_t38Prefix);

  PTRACE(3, "Fax\tCreated Fax endpoint");
}


OpalFaxEndPoint::~OpalFaxEndPoint()
{
  PTRACE(3, "Fax\tDeleted Fax endpoint.");
}


PSafePtr<OpalConnection> OpalFaxEndPoint::MakeConnection(OpalCall & call,
                                                    const PString & remoteParty,
                                                             void * userData,
                                                       unsigned int /*options*/,
                                    OpalConnection::StringOptions * stringOptions)
{
  if (!OpalMediaFormat(TIFF_File_FormatName).IsValid()) {
    PTRACE(1, "TIFF File format not valid! Missing plugin?");
    return NULL;
  }

  PINDEX prefixLength = remoteParty.Find(':');
  PStringArray tokens = remoteParty.Mid(prefixLength+1).Tokenise(";", true);
  if (tokens.IsEmpty()) {
    PTRACE(2, "Fax\tNo filename specified!");
    return NULL;
  }

  bool receiving = false;
  PString stationId = GetDefaultDisplayName();

  for (PINDEX i = 1; i < tokens.GetSize(); ++i) {
    if (tokens[i] *= "receive")
      receiving = true;
    else if (tokens[i].Left(10) *= "stationid=")
      stationId = tokens[i].Mid(10);
  }

  PFilePath filename;
  PString fileparam = tokens[0];
  PINDEX star = fileparam.Find('*');
  if (star == 0)
    filename = PFilePath("opal_fax_", m_defaultDirectory);
  else if (star != P_MAX_INDEX)
    filename = PFilePath(fileparam.Left(star), m_defaultDirectory);
  else if (PFilePath::IsAbsolutePath(fileparam))
    filename = fileparam;
  else
    filename = m_defaultDirectory + fileparam;

  if (filename.GetType().IsEmpty())
    filename.SetType(".tif");

  if (!receiving && !PFile::Exists(filename)) {
    PTRACE(2, "Fax\tCannot find filename '" << filename << "'");
    return NULL;
  }

  OpalConnection::StringOptions localOptions;
  if (stringOptions == NULL)
    stringOptions = &localOptions;

  if ((*stringOptions)(OPAL_OPT_STATION_ID).IsEmpty())
    stringOptions->SetAt(OPAL_OPT_STATION_ID, stationId);

  stringOptions->SetAt(OPAL_OPT_DISABLE_JITTER, "1");

  return AddConnection(CreateConnection(call, userData, stringOptions, filename, receiving,
                                        remoteParty.Left(prefixLength) *= GetPrefixName()));
}


bool OpalFaxEndPoint::IsAvailable() const
{
  return OpalMediaFormat(OPAL_FAX_TIFF_FILE).IsValid();
}


OpalFaxConnection * OpalFaxEndPoint::CreateConnection(OpalCall & call,
                                                      void * /*userData*/,
                                                      OpalConnection::StringOptions * stringOptions,
                                                      const PString & filename,
                                                      bool receiving,
                                                      bool disableT38)
{
  return new OpalFaxConnection(call, *this, filename, receiving, disableT38, stringOptions);
}


OpalMediaFormatList OpalFaxEndPoint::GetMediaFormats() const
{
  OpalMediaFormatList formats;
  formats += OpalT38;
  formats += TIFF_File_FormatName;
  return formats;
}


PStringList OpalFaxEndPoint::GetAvailableStringOptions() const
{
  static char const * const StringOpts[] = {
    OPAL_OPT_STATION_ID,
    OPAL_OPT_HEADER_INFO,
    OPAL_NO_G711_FAX,
    OPAL_SWITCH_ON_CED,
    OPAL_T38_SWITCH_TIME
  };

  PStringList list = OpalLocalEndPoint::GetAvailableStringOptions();
  list += PStringList(PARRAYSIZE(StringOpts), StringOpts, true);
  return list;
}


void OpalFaxEndPoint::OnFaxCompleted(OpalFaxConnection & connection, bool failed)
{
  PTRACE(3, "FAX\tFax " << (failed ? "failed" : "completed") << " on connection: " << connection);
  connection.Release(failed ? OpalConnection::EndedByMediaFailed : OpalConnection::EndedByLocalUser);
}


/////////////////////////////////////////////////////////////////////////////

OpalFaxConnection::OpalFaxConnection(OpalCall        & call,
                                     OpalFaxEndPoint & ep,
                                     const PString   & filename,
                                     bool              receiving,
                                     bool              disableT38,
                                     OpalConnection::StringOptions * stringOptions)
  : OpalLocalConnection(call, ep, NULL, 0, stringOptions, 'F')
  , m_endpoint(ep)
  , m_filename(filename)
  , m_receiving(receiving)
  , m_disableT38(disableT38)
  , m_switchTime(0)
  , m_tiffFileFormat(TIFF_File_FormatName)
  , m_completed(false)
{
  SetFaxMediaFormatOptions(m_tiffFileFormat);

  m_switchTimer.SetNotifier(PCREATE_NOTIFIER(OnSwitchTimeout), "T38Switch");

  PTRACE(3, "FAX\tCreated fax connection with token \"" << m_callToken << "\","
            " receiving=" << receiving << ","
            " disabledT38=" << disableT38 << ","
            " filename=\"" << filename << '"'
            << "\n" << setw(-1) << m_tiffFileFormat);
}


OpalFaxConnection::~OpalFaxConnection()
{
  PTRACE(3, "FAX\tDeleted FAX connection.");
}


PString OpalFaxConnection::GetPrefixName() const
{
  return m_disableT38 ? m_endpoint.GetPrefixName() : m_endpoint.GetT38Prefix();
}


OpalMediaFormatList OpalFaxConnection::GetMediaFormats() const
{
  OpalMediaFormatList formats;

  if (m_filename.IsEmpty())
    formats += OpalPCM16;
  else
    formats += m_tiffFileFormat;

  if (!m_disableT38) {
    formats += OpalRFC2833;
    formats += OpalCiscoNSE;
  }

  return formats;
}


void OpalFaxConnection::AdjustMediaFormats(bool   local,
                           const OpalConnection * otherConnection,
                            OpalMediaFormatList & mediaFormats) const
{
  // Remove everything but G.711 or fax stuff
  OpalMediaFormatList::iterator it = mediaFormats.begin();
  while (it != mediaFormats.end()) {
    if ((!m_ownerCall.IsSwitchingToT38() && it->GetMediaType() == OpalMediaType::Audio())
         || *it == OpalG711_ULAW_64K || *it == OpalG711_ALAW_64K || *it == OpalRFC2833 || *it == OpalCiscoNSE)
      ++it;
    else if (it->GetMediaType() != OpalMediaType::Fax() || (m_disableT38 && *it == OpalT38))
      mediaFormats -= *it++;
    else
      SetFaxMediaFormatOptions(*it++);
  }

  OpalLocalConnection::AdjustMediaFormats(local, otherConnection, mediaFormats);
}


void OpalFaxConnection::OnApplyStringOptions()
{
  OpalLocalConnection::OnApplyStringOptions();
  SetFaxMediaFormatOptions(m_tiffFileFormat);
  m_switchTime = m_stringOptions.GetInteger(OPAL_T38_SWITCH_TIME);
}


void OpalFaxConnection::SetFaxMediaFormatOptions(OpalMediaFormat & mediaFormat) const
{
  PTRACE_IF(3, mediaFormat.GetOptionString("TIFF-File-Name") != m_filename,
            "FAX\tSet file name to \"" << m_filename << '"');
  mediaFormat.SetOptionString("TIFF-File-Name", m_filename);

  PTRACE_IF(3, mediaFormat.GetOptionBoolean("Receiving") != m_receiving,
            "FAX\tSet to " << (m_receiving ? "receive" : "originate") << " mode");
  mediaFormat.SetOptionBoolean("Receiving", m_receiving);

  PString str = m_stringOptions(OPAL_OPT_STATION_ID);
  if (!str.IsEmpty()) {
    PTRACE_IF(3, mediaFormat.GetOptionString("Station-Identifier") != str,
              "FAX\tSet Station-Identifier to \"" << str << '"');
    mediaFormat.SetOptionString("Station-Identifier", str);
  }

  str = m_stringOptions(OPAL_OPT_HEADER_INFO);
  if (!str.IsEmpty()) {
    PTRACE_IF(3, mediaFormat.GetOptionString("Header-Info") != str,
              "FAX\tSet Header-Info to \"" << str << '"');
    mediaFormat.SetOptionString("Header-Info", str);
  }
}


void OpalFaxConnection::OnEstablished()
{
  OpalLocalConnection::OnEstablished();

  // If switched and we don't need to do CNG/CED any more, or T.38 is disabled
  // in which case the SpanDSP will deal with CNG/CED stuff.
  if (m_disableT38 || m_switchTime == 0)
    return;

  m_switchTimer.SetInterval(0, m_switchTime);
  PTRACE(3, "FAX\tStarting " << m_switchTime << " second timer for auto-switch to T.38");
}


void OpalFaxConnection::OnReleased()
{
  m_switchTimer.Stop(false);

  OpalLocalConnection::OnReleased();

  // Probably not be necessary, but just in case of race conditions
  PTRACE_IF(4, !m_mediaStreams.IsEmpty(), "FAX", "Waiting for media streams to close.");
  while (!m_mediaStreams.IsEmpty())
    PThread::Sleep(20);

  InternalOnFaxCompleted();
}


OpalMediaStream * OpalFaxConnection::CreateMediaStream(const OpalMediaFormat & mediaFormat, unsigned sessionID, bool isSource)
{
  return new OpalNullMediaStream(*this, mediaFormat, sessionID, isSource, isSource, true);
}


void OpalFaxConnection::OnClosedMediaStream(const OpalMediaStream & stream)
{
  OpalLocalConnection::OnClosedMediaStream(stream);

  if (stream.IsSink()) {
    PTRACE(4, "FAX\tTerminating fax in closed media stream id=" << stream.GetID());
    stream.ExecuteCommand(OpalFaxTerminate());

    if (m_finalStatistics.m_fax.m_result < 0) {
      stream.GetStatistics(m_finalStatistics);
      PTRACE_IF(3, m_finalStatistics.m_fax.m_result >= 0,
                "FAX\tGot final statistics: result=" << m_finalStatistics.m_fax.m_result);
    }
  }

  OpalMediaStreamPtr other = GetMediaStream(stream.GetID(), stream.IsSink());
  if (other == NULL || !other->IsOpen()) {
    if (    m_finalStatistics.m_fax.m_result == 0 /* success!*/ ||
          !(m_finalStatistics.m_fax.m_result < 0  /* in progress */ || IsReleased() || m_ownerCall.IsSwitchingT38()))
      InternalOnFaxCompleted();
    else {
      PTRACE(4, "FAX\tIgnoring switching "
              << (stream.IsSource() ? "source" : "sink")
              << " media stream id=" << stream.GetID());
      m_finalStatistics.m_fax.m_result = OpalMediaStatistics::FaxNotStarted;
    }
  }
  else {
    PTRACE(4, "FAX\tClosing " << (other->IsSource() ? "source" : "sink") << " media stream id=" << stream.GetID());
    other->Close();
  }
}


void OpalFaxConnection::OnStopMediaPatch(OpalMediaPatch & patch)
{
  OpalMediaStreamPtr src = &patch.GetSource();
  if (&src->GetConnection() == this)
    GetEndPoint().GetManager().QueueDecoupledEvent(
              new PSafeWorkArg1<OpalConnection, OpalMediaStreamPtr, bool>(this, src, &OpalConnection::CloseMediaStream));
  OpalLocalConnection::OnStopMediaPatch(patch);
}


PBoolean OpalFaxConnection::SendUserInputTone(char tone, unsigned duration)
{
  OnUserInputTone(tone, duration);
  return true;
}


void OpalFaxConnection::OnUserInputTone(char tone, unsigned /*duration*/)
{
  // Not yet switched and got a CNG/CED from the remote system, start switch
  if (m_disableT38 || IsReleased())
    return;

  if (m_receiving ? (tone == 'X')
                  : (tone == 'Y' && m_stringOptions.GetBoolean(OPAL_SWITCH_ON_CED))) {
    PTRACE(3, "FAX\tRequesting mode change in response to " << (tone == 'X' ? "CNG" : "CED"));
    SwitchFaxMediaStreams(true);
  }
}


void OpalFaxConnection::OnFaxCompleted(bool failed)
{
  m_endpoint.OnFaxCompleted(*this, failed);

  // Prevent to reuse filename
  m_filename.MakeEmpty();
}


void OpalFaxConnection::GetStatistics(OpalMediaStatistics & statistics) const
{
  if (m_finalStatistics.m_fax.m_result >= 0) {
    statistics = m_finalStatistics;
    return;
  }

  OpalMediaStreamPtr stream;
  if ((stream = GetMediaStream(OpalMediaType::Fax(), false)) == NULL &&
      (stream = GetMediaStream(OpalMediaType::Fax(), true )) == NULL) {

    PSafePtr<OpalConnection> other = GetOtherPartyConnection();
    if (other == NULL) {
      PTRACE(2, "FAX\tNo connection to get statistics.");
      return;
    }

    if ((stream = other->GetMediaStream(OpalMediaType::Fax(), false)) == NULL &&
        (stream = other->GetMediaStream(OpalMediaType::Fax(), true )) == NULL) {
      PTRACE(2, "FAX\tNo stream to get statistics.");
      return;
    }
  }

  stream->GetStatistics(statistics);
}


void OpalFaxConnection::OnSwitchTimeout(PTimer &, P_INT_PTR)
{
  if (m_disableT38 || IsReleased())
    return;

  PTRACE(2, "FAX\tDid not switch to T.38 mode, forcing switch");
  GetEndPoint().GetManager().QueueDecoupledEvent(
          new PSafeWorkNoArg<OpalFaxConnection>(this, &OpalFaxConnection::InternalOpenFaxStreams));
}


bool OpalFaxConnection::SwitchFaxMediaStreams(bool enable)
{
  if (IsReleased())
    return false;

  m_switchTime = 0;
  m_switchTimer.Stop(false);
  m_completed = false;
  PSafePtr<OpalConnection> other = GetOtherPartyConnection();
  return other != NULL && other->SwitchFaxMediaStreams(enable);
}


void OpalFaxConnection::OnSwitchedFaxMediaStreams(bool toT38, bool success)
{
  if (success) {
    m_switchTimer.Stop(false);
    m_finalStatistics.m_fax.m_result = OpalMediaStatistics::FaxNotStarted;
  }
  else {
    if (toT38 && m_stringOptions.GetBoolean(OPAL_NO_G711_FAX)) {
      PTRACE(4, "FAX\tSwitch request to fax failed, checking for fall back to G.711");
      InternalOnFaxCompleted();
    }

    m_disableT38 = true;
  }
}


bool OpalFaxConnection::OnSwitchingFaxMediaStreams(bool toT38)
{
  if (toT38 && m_disableT38) {
    PTRACE(3, "FAX\tRequest to switch to T.38 disabled");
    return false;
  }

  PTRACE(4, "FAX\tRequest to switch to T.38 allowed");
  return true;
}


void OpalFaxConnection::InternalOpenFaxStreams()
{
  if (LockReadWrite()) {
    SwitchFaxMediaStreams(true);
    UnlockReadWrite();
  }
}


void OpalFaxConnection::InternalOnFaxCompleted()
{
  if (m_completed.exchange(true))
    return;

  PTRACE(4, "FAX", "OnFaxCompleted, result=" << m_finalStatistics.m_fax.m_result);

  OnFaxCompleted(m_finalStatistics.m_fax.m_result != OpalMediaStatistics::FaxSuccessful);
}
#endif // OPAL_FAX
