//
// h46018.cxx
//
// Code automatically generated by asnparse.
//

#ifdef P_USE_PRAGMA
#pragma implementation "h46018.h"
#endif

#include <ptlib.h>
#include "h460/h46018.h"

#define new PNEW


#if ! H323_DISABLE_H46018



//
// IncomingCallIndication
//

H46018_IncomingCallIndication::H46018_IncomingCallIndication(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 0, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H46018_IncomingCallIndication::PrintOn(ostream & strm) const
{
  std::streamsize indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+24) << "callSignallingAddress = " << setprecision(indent) << m_callSignallingAddress << '\n';
  strm << setw(indent+9) << "callID = " << setprecision(indent) << m_callID << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H46018_IncomingCallIndication::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H46018_IncomingCallIndication), PInvalidCast);
#endif
  const H46018_IncomingCallIndication & other = (const H46018_IncomingCallIndication &)obj;

  Comparison result;

  if ((result = m_callSignallingAddress.Compare(other.m_callSignallingAddress)) != EqualTo)
    return result;
  if ((result = m_callID.Compare(other.m_callID)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H46018_IncomingCallIndication::GetDataLength() const
{
  PINDEX length = 0;
  length += m_callSignallingAddress.GetObjectLength();
  length += m_callID.GetObjectLength();
  return length;
}


bool H46018_IncomingCallIndication::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_callSignallingAddress.Decode(strm))
    return FALSE;
  if (!m_callID.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H46018_IncomingCallIndication::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_callSignallingAddress.Encode(strm);
  m_callID.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H46018_IncomingCallIndication::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H46018_IncomingCallIndication::Class()), PInvalidCast);
#endif
  return new H46018_IncomingCallIndication(*this);
}


//
// LRQKeepAliveData
//

H46018_LRQKeepAliveData::H46018_LRQKeepAliveData(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 0, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H46018_LRQKeepAliveData::PrintOn(ostream & strm) const
{
  std::streamsize indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+23) << "lrqKeepAliveInterval = " << setprecision(indent) << m_lrqKeepAliveInterval << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H46018_LRQKeepAliveData::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H46018_LRQKeepAliveData), PInvalidCast);
#endif
  const H46018_LRQKeepAliveData & other = (const H46018_LRQKeepAliveData &)obj;

  Comparison result;

  if ((result = m_lrqKeepAliveInterval.Compare(other.m_lrqKeepAliveInterval)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H46018_LRQKeepAliveData::GetDataLength() const
{
  PINDEX length = 0;
  length += m_lrqKeepAliveInterval.GetObjectLength();
  return length;
}


bool H46018_LRQKeepAliveData::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_lrqKeepAliveInterval.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H46018_LRQKeepAliveData::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_lrqKeepAliveInterval.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H46018_LRQKeepAliveData::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H46018_LRQKeepAliveData::Class()), PInvalidCast);
#endif
  return new H46018_LRQKeepAliveData(*this);
}


#endif // if ! H323_DISABLE_H46018


// End of h46018.cxx
