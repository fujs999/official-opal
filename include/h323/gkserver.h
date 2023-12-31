/*
 * gkserver.h
 *
 * H225 Registration Admission and Security protocol handler
 *
 * Open H323 Library
 *
 * Copyright (c) 1998-2001 Equivalence Pty. Ltd.
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
 * This code was based on original code from OpenGate of Egoboo Ltd. thanks
 * to Ashley Unitt for his efforts.
 *
 * Contributor(s): ______________________________________.
 */

#ifndef OPAL_H323_GKSERVER_H
#define OPAL_H323_GKSERVER_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <opal_config.h>

#if OPAL_H323

#include <ptlib/safecoll.h>
#include <opal/guid.h>
#include <h323/h225ras.h>
#include <h323/transaddr.h>
#include <h323/h235auth.h>
#include <h323/h323pdu.h>
#include <h323/h323trans.h>


class PASN_Sequence;
class PASN_Choice;

class H225_AliasAddress;
class H225_EndpointIdentifier;
class H225_GatekeeperIdentifier;
class H225_ArrayOf_TransportAddress;
class H225_GatekeeperIdentifier;
class H225_EndpointIdentifier;
class H225_InfoRequestResponse_perCallInfo_subtype;
class H225_RasUsageInformation;

class H323RegisteredEndPoint;
class H323GatekeeperListener;
class H323GatekeeperServer;
class H323RasPDU;

#if OPAL_H501
class H323PeerElement;
#endif

class H323GatekeeperRequest : public H323Transaction
{
    PCLASSINFO(H323GatekeeperRequest, H323Transaction);
  public:
  /**@name Construction */
  //@{
    /**Create a new gatekeeper server request.
     */
    H323GatekeeperRequest(
      H323GatekeeperListener & rasChannel,
      const H323RasPDU & pdu
    );
  //@}

    virtual H323TransactionPDU * CreateRIP(
      unsigned sequenceNumber,
      unsigned delay
    ) const;

    virtual PBoolean WritePDU(
      H323TransactionPDU & pdu
    );
    virtual bool CheckCryptoTokens();
    bool CheckGatekeeperIdentifier();
    bool GetRegisteredEndPoint();

    virtual PString GetGatekeeperIdentifier() const = 0;
    virtual unsigned GetGatekeeperRejectTag() const = 0;
    virtual PString GetEndpointIdentifier() const = 0;
    virtual unsigned GetRegisteredEndPointRejectTag() const = 0;

    H323GatekeeperListener & GetRasChannel() const { return m_rasChannel; }

    PSafePtr<H323RegisteredEndPoint> m_endpoint;

  protected:
    H323GatekeeperListener & m_rasChannel;
};


class H323GatekeeperGRQ : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperGRQ, H323GatekeeperRequest);
  public:
    H323GatekeeperGRQ(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual void PrepareConfirm();
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_GatekeeperRequest & grq;
    H225_GatekeeperConfirm & gcf;
    H225_GatekeeperReject  & grj;

  protected:
    virtual Response OnHandlePDU();
};


class H323GatekeeperRRQ : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperRRQ, H323GatekeeperRequest);
  public:
    H323GatekeeperRRQ(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_RegistrationRequest & rrq;
    H225_RegistrationConfirm & rcf;
    H225_RegistrationReject  & rrj;

  protected:
    virtual Response OnHandlePDU();
};


class H323GatekeeperURQ : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperURQ, H323GatekeeperRequest);
  public:
    H323GatekeeperURQ(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_UnregistrationRequest & urq;
    H225_UnregistrationConfirm & ucf;
    H225_UnregistrationReject  & urj;

  protected:
    virtual Response OnHandlePDU();
};


class H323GatekeeperARQ : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperARQ, H323GatekeeperRequest);
  public:
    H323GatekeeperARQ(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_AdmissionRequest & arq;
    H225_AdmissionConfirm & acf;
    H225_AdmissionReject  & arj;

    PString alternateSecurityID;

  protected:
    virtual Response OnHandlePDU();
};


class H323GatekeeperDRQ : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperDRQ, H323GatekeeperRequest);
  public:
    H323GatekeeperDRQ(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_DisengageRequest & drq;
    H225_DisengageConfirm & dcf;
    H225_DisengageReject  & drj;

  protected:
    virtual Response OnHandlePDU();
};


class H323GatekeeperBRQ : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperBRQ, H323GatekeeperRequest);
  public:
    H323GatekeeperBRQ(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_BandwidthRequest & brq;
    H225_BandwidthConfirm & bcf;
    H225_BandwidthReject  & brj;

  protected:
    virtual Response OnHandlePDU();
};


class H323GatekeeperLRQ : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperLRQ, H323GatekeeperRequest);
  public:
    H323GatekeeperLRQ(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_LocationRequest & lrq;
    H225_LocationConfirm & lcf;
    H225_LocationReject  & lrj;

  protected:
    virtual Response OnHandlePDU();
};


class H323GatekeeperIRR : public H323GatekeeperRequest
{
    PCLASSINFO(H323GatekeeperIRR, H323GatekeeperRequest);
  public:
    H323GatekeeperIRR(
      H323GatekeeperListener & listener,
      const H323RasPDU & pdu
    );

#if PTRACING
    virtual const char * GetName() const;
#endif
    virtual PString GetGatekeeperIdentifier() const;
    virtual unsigned GetGatekeeperRejectTag() const;
    virtual PString GetEndpointIdentifier() const;
    virtual unsigned GetRegisteredEndPointRejectTag() const;
    virtual H235Authenticator::ValidationResult ValidatePDU() const;
    virtual unsigned GetSecurityRejectTag() const;
    virtual void SetRejectReason(
      unsigned reasonCode
    );

    H225_InfoRequestResponse & irr;
    H225_InfoRequestAck      & iack;
    H225_InfoRequestNak      & inak;

  protected:
    virtual Response OnHandlePDU();
};


/**This class describes an active call on a gatekeeper.
  */
class H323GatekeeperCall : public PSafeObject
{
    PCLASSINFO(H323GatekeeperCall, PSafeObject);
  public:
  /**@name Construction */
  //@{
    enum Direction {
      AnsweringCall,
      OriginatingCall,
      UnknownDirection
    };

    /**Create a new gatekeeper call tracking record.
     */
    H323GatekeeperCall(
      H323GatekeeperServer & server,               ///<  Owner gatekeeper server
      const OpalGloballyUniqueID & callIdentifier, ///<  Unique call identifier
      Direction direction                          ///<  Direction of call
    );

    /**Destroy the call, removing itself from the endpoint.
      */
    ~H323GatekeeperCall();
  //@}

  /**@name Overrides from PObject */
  //@{
    /**Compare two objects.
      */
    Comparison Compare(
      const PObject & obj  ///<  Other object
    ) const;

    /**Print the name of the gatekeeper.
      */
    void PrintOn(
      ostream & strm    ///<  Stream to print to.
    ) const;
  //@}

  /**@name Operations */
  //@{
    /**Handle an admission ARQ PDU.
       The default behaviour sets some internal variables from the ARQ data
       and then calls OnResolveAdmission, if necessary, and OnReplyAdmission
       every time.
      */
    virtual H323GatekeeperRequest::Response OnAdmission(
      H323GatekeeperARQ & request
    );

    /**Shut down a call.
       This sendsa DRQ to the endpoint(s) to close the call down.
      */
    virtual PBoolean Disengage(
      int reason = -1   ///<  Reason for disengage
    );

    /**Handle a disengage DRQ PDU.
       The default behaviour simply returns true.
      */
    virtual H323GatekeeperRequest::Response OnDisengage(
      H323GatekeeperDRQ & request
    );

    /**Handle a bandwidth BRQ PDU.
       The default behaviour adjusts the bandwidth used by the gatekeeper and
       adjusts the remote endpoint according to those limits.
      */
    virtual H323GatekeeperRequest::Response OnBandwidth(
      H323GatekeeperBRQ & request
    );

    /**Handle an info request response IRR PDU.
       The default behaviour resets the heartbeat time monitoring the call.
      */
    virtual H323GatekeeperRequest::Response OnInfoResponse(
      H323GatekeeperIRR & request,
      H225_InfoRequestResponse_perCallInfo_subtype & call
    );

    /**Call back when an info response detects an Alerting.
      */
    virtual void OnAlerting();

    /**Call back when an info response detects an Connected.
      */
    virtual void OnConnected();

    /**Function called to do heartbeat check of the call.
       Monitor the state of the call and make sure everything is OK.

       A return value of false indicates the call is to be closed for some
       reason.

       Default behaviour checks the time since the last received IRR and if
       it has been too long does an IRQ to see if the call (and endpoint!) is
       still there and running. If the IRQ fails, false is returned.
      */
    virtual PBoolean OnHeartbeat();

    /**Get the current credit for this call.
       This function is only called if the client indicates that it can use
       the information provided.

       The default behaviour calls the same function on the endpoint.
      */
    virtual PString GetCallCreditAmount() const;

    /**Get the call credit billing mode for this endpoint.
       This function is only called if the client indicates that it can use
       the information provided.

       The default behaviour calls the same function on the endpoint.
      */
    virtual PBoolean GetCallCreditMode() const;

    /**Get the duration limit for this call.
       This function is only called if the client indicates that it can use
       the information provided.

       The default behaviour returns zero which indicates there is no
       duration limit applicable.
      */
    virtual unsigned GetDurationLimit() const;

    /**Send the call credit service control PDU.
       This will send an SCI pdu to the endpoint with the control service
       session information for the current call credit, if enabled.
      */
    virtual PBoolean SendCallCreditServiceControl();

    /**Add call credit and duration information to PDU.
      */
    bool AddCallCreditServiceControl(
      H225_ArrayOf_ServiceControlSession & serviceControl
    ) const;

    /**Send the service control session for the PDU.
       This will send an SCI pdu to the endpoint with the control service
       session information provided.
      */
    virtual PBoolean SendServiceControlSession(
      const H323ServiceControlSession & session
    );

    /**Translate a given alias to an alias set and signal address.
       This is called by the OnAdmission() handler to fill in the ACF

       The default behaviour calls H323GatekeeperServer::TranslateAliasAddress.
      */
    virtual PBoolean TranslateAliasAddress(
      const H225_AliasAddress & alias,
      H225_ArrayOf_AliasAddress & aliases,
      H323TransportAddress & address,
      PBoolean & isGkRouted
    );

  //@}

  /**@name Access functions */
  //@{
    H323GatekeeperServer & GetGatekeeper() const { return m_gatekeeper; }
    H323RegisteredEndPoint & GetEndPoint() const { return *PAssertNULL(m_endpoint); }
    bool IsAnsweringCall() const { return m_direction == AnsweringCall; }
    unsigned GetCallReference() const { return m_callReference; }
    const OpalGloballyUniqueID & GetCallIdentifier() const { return m_callIdentifier; }
    const OpalGloballyUniqueID & GetConferenceIdentifier() const { return m_conferenceIdentifier; }
    const PString & GetSourceNumber() const { return m_srcNumber; }
    const PStringArray & GetSourceAliases() const { return m_srcAliases; }
    const H323TransportAddress & GetSourceHost() const { return m_srcHost; }
    PString GetSourceAddress() const;
    const PString & GetDestinationNumber() const { return m_dstNumber; }
    const PStringArray & GetDestinationAliases() const { return m_dstAliases; }
    const H323TransportAddress & GetDestinationHost() const { return m_dstHost; }
    PString GetDestinationAddress() const;
    unsigned GetBandwidthUsed() const { return m_bandwidthUsed; }
    bool SetBandwidthUsed(unsigned bandwidth);
    const PTime & GetLastInfoResponseTime() const { return m_lastInfoResponse; }
    const PTime & GetCallStartTime() const { return m_callStartTime; }
    const PTime & GetAlertingTime() const { return m_alertingTime; }
    const PTime & GetConnectedTime() const { return m_connectedTime; }
    const PTime & GetCallEndTime() const { return m_callEndTime; }
    H323Connection::CallEndReason GetCallEndReason() const { return m_callEndReason; }
  //@}

  protected:
    void SetUsageInfo(const H225_RasUsageInformation & usage);

    H323GatekeeperServer   & m_gatekeeper;
    H323RegisteredEndPoint * m_endpoint;
    H323GatekeeperListener * m_rasChannel;

    Direction            m_direction;
    unsigned             m_callReference;
    OpalGloballyUniqueID m_callIdentifier;
    OpalGloballyUniqueID m_conferenceIdentifier;
    PString              m_srcNumber;
    PStringArray         m_srcAliases;
    H323TransportAddress m_srcHost;
    PString              m_dstNumber;
    PStringArray         m_dstAliases;
    H323TransportAddress m_dstHost;
    unsigned             m_bandwidthUsed;
    unsigned             m_infoResponseRate;
    PTime                m_lastInfoResponse;

    bool                          m_drqReceived;
    PTime                         m_callStartTime;
    PTime                         m_alertingTime;
    PTime                         m_connectedTime;
    PTime                         m_callEndTime;
    H323Connection::CallEndReason m_callEndReason;
};


/**This class describes endpoints that are registered with a gatekeeper server.
   Note that a registered endpoint has no realationship in this software to a
   H323EndPoint class. This is purely a description of endpoints that are
   registered with the gatekeeper.
  */
class H323RegisteredEndPoint : public PSafeObject
{
    PCLASSINFO(H323RegisteredEndPoint, PSafeObject);
  public:
  /**@name Construction */
  //@{
    /**Create a new endpoint registration record.
     */
    H323RegisteredEndPoint(
      H323GatekeeperServer & server, ///<  Gatekeeper server data
      const PString & id             ///<  Identifier
    );
  //@}

  /**@name Overrides from PObject */
  //@{
    /**Compare two objects.
      */
    Comparison Compare(
      const PObject & obj  ///<  Other object
    ) const;

    /**Print the name of the gatekeeper.
      */
    void PrintOn(
      ostream & strm    ///<  Stream to print to.
    ) const;
  //@}

  /**@name Call Operations */
  //@{
    /**Add a call to the endpoints list of active calls.
       This is largely an internal routine, it is not expected the user would
       need to deal with this function.
      */
    virtual void AddCall(
      H323GatekeeperCall * call
    );

    /**Remove a call from the endpoints list of active calls.
       This is largely an internal routine, it is not expected the user would
       need to deal with this function.
      */
    virtual PBoolean RemoveCall(
      H323GatekeeperCall * call
    );

    /**Get the count of active calls on this endpoint.
      */
    PINDEX GetCallCount() const { return m_activeCalls.GetSize(); }

    /**Get the details of teh active call on this endpoint.
      */
    H323GatekeeperCall & GetCall(
      PINDEX idx
    ) { return m_activeCalls[idx]; }
  //@}

  /**@name Protocol Operations */
  //@{
    /**Call back on receiving a RAS registration for this endpoint.
       The default behaviour extract information from the RRQ and sets
       internal variables to that data.

       If returns true then a RCF is sent otherwise an RRJ is sent.
      */
    virtual H323GatekeeperRequest::Response OnRegistration(
      H323GatekeeperRRQ & request
    );

    /**Call back on receiving a RAS full registration for this endpoint.
       This is not called if the keepAlive flag is set indicating a
       lightweight RRQ has been received.

       The default behaviour extract information from the RRQ and sets
       internal variables to that data.

       If returns true then a RCF is sent otherwise an RRJ is sent.
      */
    virtual H323GatekeeperRequest::Response OnFullRegistration(
      H323GatekeeperRRQ & request
    );

    /**Call back to set security on RAS full registration for this endpoint.
       This is called from OnFullRegistration().

       The default behaviour extract information from the RRQ and sets
       internal variables to that data.

       If returns true then a RCF is sent otherwise an RRJ is sent.
      */
    virtual H323GatekeeperRequest::Response OnSecureRegistration(
      H323GatekeeperRRQ & request
    );

    /**Call back on receiving a RAS unregistration for this endpoint.
       The default behaviour clears all calls owned by this endpoint.
      */
    virtual H323GatekeeperRequest::Response OnUnregistration(
      H323GatekeeperURQ & request
    );

    /**Force unregistration of the endpoint.
       This sendsa URQ to the endpoint(s) to close the call down.
      */
    virtual PBoolean Unregister(
      int reason = -1   ///<  Reason for unregistration
    );

    /**Handle an info request response IRR PDU.
       The default behaviour finds each call current for endpoint and calls 
       the function of the same name in the H323GatekeeperCall instance.
      */
    virtual H323GatekeeperRequest::Response OnInfoResponse(
      H323GatekeeperIRR & request
    );

    /**Function called to do time to live check of the call.
       Monitor the state of the endpoint and make sure everything is OK.

       A return value of false indicates the endpoint has expired and is to be
       unregistered and removed.

       Default behaviour checks the time since the last received RRQ and if
       it has been too long does an IRQ to see if the endpoint is
       still there and running. If the IRQ fails, false is returned.
      */
    virtual PBoolean OnTimeToLive();

    /**Get the current call credit for this endpoint.
       This function is only called if the client indicates that it can use
       the information provided. If a server wishes to enable this feature by
       returning a non-empty string, it must be consistent in that usage. That
       is the H323GatekeeperCall::GetCallCreditAmount() for this endpoint
       must also return non-empty value.

       The return value is a UTF-8 string for amount, including currency.

       The default behaviour returns an empty string disabling the function.
      */
    virtual PString GetCallCreditAmount() const;

    /**Get the call credit billing mode for this endpoint.
       This function is only called if the client indicates that it can use
       the information provided.

       The default behaviour return true indicating that calls will debit the
       account.
      */
    virtual PBoolean GetCallCreditMode() const;

    /**Send the service control session for the PDU.
       This will send an SCI pdu to the endpoint with the control service
       session information provided.
      */
    virtual PBoolean SendServiceControlSession(
      const H323ServiceControlSession & session
    );

    /**Set the service control session for the PDU.
       This is an internal function.
      */
    virtual PBoolean AddServiceControlSession(
      const H323ServiceControlSession & session,
      H225_ArrayOf_ServiceControlSession & serviceControl
    );
  //@}

  /**@name Access functions */
  //@{
    /**Set password for user activating H.235 security.
      */
    virtual PBoolean SetPassword(
      const PString & password,
      const PString & username = PString::Empty()
    );

    /**Get the endpoint identifier assigned to the endpoint.
      */
    const PString & GetIdentifier() const { return m_identifier; }

    /**Get the Peer Element descriptor ID assigned to the endpoint.
      */
    const OpalGloballyUniqueID & GetDescriptorID() const { return m_descriptorID; }

    /**Get the gatekeeper server data object that owns this endpoint.
      */
    H323GatekeeperServer & GetGatekeeper() const { return m_gatekeeper; }

    /**Get the addresses that can be used to contact this endpoint via the
       RAS protocol.
      */
    const H323TransportAddressArray & GetRASAddresses() const { return m_rasAddresses; }

    /**Get the number of addresses that can be used to contact this
       endpoint via the RAS protocol.
      */
    PINDEX GetRASAddressCount() const { return m_rasAddresses.GetSize(); }

    /**Get an address that can be used to contact this endpoint via the RAS
       protocol.
      */
    H323TransportAddress GetRASAddress(
      PINDEX idx
    ) const { return m_rasAddresses[idx]; }

    /**Get the addresses that can be used to contact this
       endpoint via the H.225/Q.931 protocol, ie normal calls.
      */
    const H323TransportAddressArray & GetSignalAddresses() const { return m_signalAddresses; }

    /**Get the number of addresses that can be used to contact this
       endpoint via the H.225/Q.931 protocol, ie normal calls.
      */
    PINDEX GetSignalAddressCount() const { return m_signalAddresses.GetSize(); }

    /**Get an address that can be used to contact this endpoint via the
       H.225/Q.931 protocol, ie normal calls.
      */
    H323TransportAddress GetSignalAddress(
      PINDEX idx
    ) const { return m_signalAddresses[idx]; }

    /**Get the aliases this endpoint may be identified by.
      */
    const PStringArray & GetAliases() const { return m_aliases; }

    /**Determine if alias is an alias that this endpoint may be identified by.
      */
    bool ContainsAlias(
      const PString & alias
      ) { return m_aliases.GetStringsIndex(alias) != P_MAX_INDEX; }

    /**Get the number of aliases this endpoint may be identified by.
      */
    PINDEX GetAliasCount() const { return m_aliases.GetSize(); }

    /**Get an alias that this endpoint may be identified by.
      */
    PString GetAlias(
      PINDEX idx
    ) const { if (idx < m_aliases.GetSize()) return m_aliases[idx]; return PString::Empty(); }

    /** Remove an alias that this endpoint may be identified by.
      * If this was the last alias, then endpoint will be deleted soon
      * after by a cleanup thread. As this function is in the endpoint itself
      * it is not possible for this function to delete the endpoint immediately
      */
    void RemoveAlias(
      const PString & alias
    );

    /**Get the security context for this RAS connection.
      */
    virtual const H235Authenticators & GetAuthenticators() const { return m_authenticators; }

    /**Get the number of prefixes this endpoint can accept.
      */
    PINDEX GetPrefixCount() const { return m_voicePrefixes.GetSize(); }

    /**Get a prefix that this endpoint can accept.
      */
    PString GetPrefix(
      PINDEX idx
    ) const { return m_voicePrefixes[idx]; }

    /**Get application info (name/version etc) for endpoint.
      */
    PCaselessString GetApplicationInfo() const { return m_productInfo.AsString(); }

    /**Get application info (name/version etc) for endpoint.
      */
    const OpalProductInfo & GetProductInfo() const { return m_productInfo; }

    /**Get the protocol version the endpoint registered with.
      */
    unsigned GetProtocolVersion() const { return m_protocolVersion; }

    /**Return if gatekeeper thinks the endpoint is behind a firewall.
      */
    bool IsBehindNAT() const { return m_isBehindNAT; }

    /**Get the flag indicating the endpoint can display credit amounts.
      */
    bool CanDisplayAmountString() const { return m_canDisplayAmountString; }

    /**Get the flag indicating the endpoint can enforce a duration limit.
      */
    bool CanEnforceDurationLimit() const { return m_canEnforceDurationLimit; }

    /**Get the flag indicating the endpoint can handle RIPs (H225v1 endpoints cannot)
      */
    bool CanReceiveRIP() const;

    /**Get the H225 version reported in the RRQ
      */
    bool GetH225Version() const { return m_h225Version; }

    /**Get the creation time for endpoint.
      */
    const PTime & GetCreationTime() const { return m_creationTime; }
  //@}

  /**@name H.501 access functions */
  //@{
    /**
      * Function called when gatekeeper sends a descriptor for this endpoint.
      * This allows the gatekeeper to alter the descriptor information before
      * it is sent.
      *
      * If returns false then the desriptor is not sent
      */
      virtual PBoolean OnSendDescriptorForEndpoint(
        H225_ArrayOf_AliasAddress & aliases,          ///<  aliases for the enndpoint
        H225_EndpointType & terminalType,             ///<  terminal type
        H225_ArrayOf_AliasAddress & transportAddresses  ///<  transport addresses
      );
  //@}


  protected:
    H323GatekeeperServer    & m_gatekeeper;
    H323GatekeeperListener  * m_rasChannel;

    PString                   m_identifier;
    OpalGloballyUniqueID      m_descriptorID;
    H323TransportAddressArray m_rasAddresses;
    H323TransportAddressArray m_signalAddresses;
    PStringArray              m_aliases;
    PStringArray              m_voicePrefixes;
    OpalProductInfo           m_productInfo;
    unsigned                  m_protocolVersion;
    bool                      m_isBehindNAT;
    bool                      m_canDisplayAmountString;
    bool                      m_canEnforceDurationLimit;
    unsigned                  m_h225Version;
    unsigned                  m_timeToLive;
    H235Authenticators        m_authenticators;

    PTime m_creationTime;
    PTime m_lastRegistration;
    PTime m_lastInfoResponse;

    PSortedList<H323GatekeeperCall> m_activeCalls;
    POrdinalDictionary<PString>     m_serviceControlSessions;
};


/**This class embodies the low level H.225.0 RAS protocol on gatekeepers.
   One or more instances of this class may be used to access a single
   H323GatekeeperServer instance. Thus specific interfaces could be set up
   to receive UDP packets, all operating as the same gatekeeper.
  */
class H323GatekeeperListener : public H225_RAS
{
    PCLASSINFO(H323GatekeeperListener, H225_RAS);
  public:
  /**@name Construction */
  //@{
    /**Create a new gatekeeper listener.
     */
    H323GatekeeperListener(
      H323EndPoint & endpoint,               ///<  Local endpoint
      H323GatekeeperServer & server,         ///<  Database for gatekeeper
      const PString & gatekeeperIdentifier,  ///<  Name of this gatekeeper
      H323Transport * transport = NULL       ///<  Transport over which gatekeepers communicates.
    );

    /**Destroy gatekeeper listener.
     */
    ~H323GatekeeperListener();
  //@}

  /**@name Overrides from PObject */
  //@{
    /**Print the name of the gatekeeper.
      */
    void PrintOn(
      ostream & strm    ///<  Stream to print to.
    ) const;
  //@}

  /**@name Operations */
  //@{
    /**Send a UnregistrationRequest (URQ) to endpoint.
      */
    virtual PBoolean UnregistrationRequest(
      const H323RegisteredEndPoint & ep,
      unsigned reason
    );

    /**Send a DisengageRequest (DRQ) to endpoint.
      */
    virtual PBoolean DisengageRequest(
      const H323GatekeeperCall & call,
      unsigned reason
    );

    /**Send an InfoRequest (IRQ) to endpoint.
      */
    virtual PBoolean InfoRequest(
      H323RegisteredEndPoint & ep,
      H323GatekeeperCall * call = NULL
    );

    /**Send an ServiceControlIndication (SCI) to endpoint.
      */
    virtual PBoolean ServiceControlIndication(
      H323RegisteredEndPoint & ep,
      const H323ServiceControlSession & session,
      H323GatekeeperCall * call = NULL
    );
  //@}

  /**@name Operation callbacks */
  //@{
    /**Handle a discovery GRQ PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnDiscovery(
      H323GatekeeperGRQ & request
    );

    /**Handle a registration RRQ PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnRegistration(
      H323GatekeeperRRQ & request
    );

    /**Handle an unregistration URQ PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnUnregistration(
      H323GatekeeperURQ & request
    );

    /**Handle an admission ARQ PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnAdmission(
      H323GatekeeperARQ & request
    );

    /**Handle a disengage DRQ PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnDisengage(
      H323GatekeeperDRQ & request
    );

    /**Handle a bandwidth BRQ PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnBandwidth(
      H323GatekeeperBRQ & request
    );

    /**Handle a location LRQ PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnLocation(
      H323GatekeeperLRQ & request
    );

    /**Handle an info request response IRR PDU.
       The default behaviour does some checks and calls the gatekeeper server
       instances function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnInfoResponse(
      H323GatekeeperIRR & request
    );
  //@}

  /**@name Low level protocol callbacks */
  //@{
    virtual PBoolean OnReceiveGatekeeperRequest(const H323RasPDU &, const H225_GatekeeperRequest &);
    virtual PBoolean OnReceiveRegistrationRequest(const H323RasPDU &, const H225_RegistrationRequest &);
    virtual PBoolean OnReceiveUnregistrationRequest(const H323RasPDU &, const H225_UnregistrationRequest &);
    virtual PBoolean OnReceiveUnregistrationConfirm(const H225_UnregistrationConfirm &);
    virtual PBoolean OnReceiveUnregistrationReject(const H225_UnregistrationReject &);
    virtual PBoolean OnReceiveAdmissionRequest(const H323RasPDU &, const H225_AdmissionRequest &);
    virtual PBoolean OnReceiveBandwidthRequest(const H323RasPDU &, const H225_BandwidthRequest &);
    virtual PBoolean OnReceiveBandwidthConfirm(const H225_BandwidthConfirm &);
    virtual PBoolean OnReceiveBandwidthReject(const H225_BandwidthReject &);
    virtual PBoolean OnReceiveDisengageRequest(const H323RasPDU &, const H225_DisengageRequest &);
    virtual PBoolean OnReceiveDisengageConfirm(const H225_DisengageConfirm &);
    virtual PBoolean OnReceiveDisengageReject(const H225_DisengageReject &);
    virtual PBoolean OnReceiveLocationRequest(const H323RasPDU &, const H225_LocationRequest &);
    virtual PBoolean OnReceiveInfoRequestResponse(const H323RasPDU &, const H225_InfoRequestResponse &);
    virtual PBoolean OnReceiveResourcesAvailableConfirm(const H225_ResourcesAvailableConfirm &);
#if OPAL_H460
    virtual PBoolean OnSendFeatureSet(H460_MessageType pduType, H225_FeatureSet & features) const;
    virtual void OnReceiveFeatureSet(H460_MessageType pduType, const H225_FeatureSet & features) const;
#endif
  //@}

  /**@name Member access */
  //@{
    H323GatekeeperServer & GetGatekeeper() const { return m_gatekeeper; }
  //@}


  protected:
    H323GatekeeperServer & m_gatekeeper;
};


/**This class implements a basic gatekeeper server functionality.
   An instance of this class contains all of the state information and
   operations for a gatekeeper. Multiple gatekeeper listeners may be using
   this class to link individual UDP (or other protocol) packets from various
   sources (interfaces etc) into a single instance.

   There is typically only one instance of this class, though it is not
   limited to that. An application would also quite likely descend from this
   class and override call back functions to implement more complex policy.
  */
class H323GatekeeperServer : public H323TransactionServer
{
    PCLASSINFO(H323GatekeeperServer, H323TransactionServer);
  public:
  /**@name Construction */
  //@{
    /**Create a new gatekeeper.
     */
    H323GatekeeperServer(
      H323EndPoint & endpoint
    );

    /**Destroy gatekeeper.
     */
    ~H323GatekeeperServer();
  //@}

    WORD GetDefaultUdpPort() { return H225_RAS::DefaultRasUdpPort; }

  /**@name Protocol Handler Operations */
  //@{
    /**Create a new H323GatkeeperListener.
       The user woiuld not usually use this function as it is used internally
       by the server when new listeners are added by H323TransportAddress.

       However, a user may override this function to create objects that are
       user defined descendants of H323GatekeeperListener so the user can
       maintain extra information on a interface by interface basis.
      */
    virtual H323Transactor * CreateListener(
      H323Transport * transport  ///<  Transport for listener
    );

  //@}

  /**@name EndPoint Operations */
  //@{
    /**Handle a discovery GRQ PDU.
       The default behaviour deals with the authentication scheme nogotiation.
      */
    virtual H323GatekeeperRequest::Response OnDiscovery(
      H323GatekeeperGRQ & request
    );

    /**Call back on receiving a RAS registration for this endpoint.
       The default behaviour checks if the registered endpoint already exists
       and if not creates a new endpoint. It then calls the OnRegistration()
       on that new endpoint instance.

       If returns true then a RCF is sent otherwise an RRJ is sent.
      */
    virtual H323GatekeeperRequest::Response OnRegistration(
      H323GatekeeperRRQ & request
    );

    /**Handle an unregistration URQ PDU.
       The default behaviour removes the aliases defined in the URQ and if all
       aliases for the registered endpoint are removed then the endpoint itself
       is removed.
      */
    virtual H323GatekeeperRequest::Response OnUnregistration(
      H323GatekeeperURQ & request
    );

    /**Handle an info request response IRR PDU.
       The default behaviour calls the function of the same name in the
       endpoint instance.
      */
    virtual H323GatekeeperRequest::Response OnInfoResponse(
      H323GatekeeperIRR & request
    );

    /**Add a new registered endpoint to the server database.
       Once the endpoint has been added it is then owned by the server and
       will be deleted when it is removed.

       The user woiuld not usually use this function as it is used internally
       by the server when new registration requests (RRQ) are received.

       Note that a registered endpoint has no relationship in this software
       to a H323EndPoint class.
      */
    virtual void AddEndPoint(
      H323RegisteredEndPoint * ep
    );

    /**Remove a registered endpoint from the server database.
      */
    virtual PBoolean RemoveEndPoint(
      H323RegisteredEndPoint * ep
    );

    /**Create a new registered endpoint object.
       The user woiuld not usually use this function as it is used internally
       by the server when new GRQ or RRQ is received.

       However, a user may override this function to create objects that are
       user defined descendants of H323RegisteredEndPoint so the user can
       maintain extra information on a endpoint by endpoint basis.
      */
    virtual H323RegisteredEndPoint * CreateRegisteredEndPoint(
      H323GatekeeperRequest & request
    );

    /**Create a new unique identifier for the registered endpoint.
       The returned identifier must be unique over the lifetime of this
       gatekeeper server.

       The default behaviour simply returns the string representation of the
       member variable nextIdentifier. There could be a problem in this
       implementation after 4,294,967,296 have been registered.
      */
    virtual PString CreateEndPointIdentifier();

    /**Find a registered endpoint given its endpoint identifier.
      */
    virtual PSafePtr<H323RegisteredEndPoint> FindEndPointByIdentifier(
      const PString & identifier,
      PSafetyMode mode = PSafeReference
    );

    /**Find a registered endpoint given a list of signal addresses.
      */
    virtual PSafePtr<H323RegisteredEndPoint> FindEndPointBySignalAddresses(
      const H225_ArrayOf_TransportAddress & addresses,
      PSafetyMode mode = PSafeReference
    );

    /**Find a registered endpoint given its signal address.
      */
    virtual PSafePtr<H323RegisteredEndPoint> FindEndPointBySignalAddress(
      const H323TransportAddress & address,
      PSafetyMode mode = PSafeReference
    );

    /**Find a registered endpoint given its raw alias address.
      */
    virtual PSafePtr<H323RegisteredEndPoint> FindEndPointByAliasAddress(
      const H225_AliasAddress & alias,
      PSafetyMode mode = PSafeReadWrite
    );

    /**Find a registered endpoint given its simple alias string.
      */
    virtual PSafePtr<H323RegisteredEndPoint> FindEndPointByAliasString(
      const PString & alias,
      PSafetyMode mode = PSafeReference
    );

    /**Find the first registered endpoint given a partial alias string.
      */
    virtual PSafePtr<H323RegisteredEndPoint> FindEndPointByPartialAlias(
      const PString & alias,
      PSafetyMode mode = PSafeReference
    );

    /**Find the first registered endpoint given a number prefix string.
      */
    virtual PSafePtr<H323RegisteredEndPoint> FindEndPointByPrefixString(
      const PString & prefix,
      PSafetyMode mode = PSafeReference
    );

    /**Get registered endpoints for enumeration.
      */
    PSafeArray<H323RegisteredEndPoint> GetRegisteredEndPoints() const;
  //@}

    PSafePtr<H323RegisteredEndPoint> FindDestinationEndPoint(
      const OpalGloballyUniqueID & id, 
      H323GatekeeperCall::Direction direction
    );
    
  /**@name Call Operations */
  //@{
    /**Handle an admission ARQ PDU.
       The default behaviour verifies that the call is allowed by the policies
       the gatekeeper server requires, then attempts to look up the required
       signal address for the call. It also manages bandwidth allocations.
      */
    virtual H323GatekeeperRequest::Response OnAdmission(
      H323GatekeeperARQ & request
    );

    /**Handle a disengage DRQ PDU.
       The default behaviour finds the call by its id provided in the DRQ and
       removes it from the gatekeeper server database.
      */
    virtual H323GatekeeperRequest::Response OnDisengage(
      H323GatekeeperDRQ & request
    );

    /**Handle a bandwidth BRQ PDU.
       The default behaviour finds the call and does some checks then calls
       the H323GatekeeperCall function of the same name.
      */
    virtual H323GatekeeperRequest::Response OnBandwidth(
      H323GatekeeperBRQ & request
    );

    /**Create a new call object.
       The user woiuld not usually use this function as it is used internally
       by the server when new calls (ARQ) are made.

       However, a user may override this function to create objects that are
       user defined descendants of H323GatekeeperCall so the user can
       maintain extra information on a call by call basis.
      */
    virtual H323GatekeeperCall * CreateCall(
      const OpalGloballyUniqueID & callIdentifier,
      H323GatekeeperCall::Direction direction
    );

    /** Called whenever a new call is started
      */
    virtual void AddCall(H323GatekeeperCall *) 
    { }

    /** Called whenever call is ended. By default, removes the call from the call list
      */
    virtual void RemoveCall(
      H323GatekeeperCall * call
    );

    /**Find the call given the identifier.
      */
    virtual PSafePtr<H323GatekeeperCall> FindCall(
      const PString & description,
      PSafetyMode mode = PSafeReference
    );

    /**Find the call given the identifier.
      */
    virtual PSafePtr<H323GatekeeperCall> FindCall(
      const OpalGloballyUniqueID & callIdentifier,
      PBoolean answeringCall,
      PSafetyMode mode = PSafeReference
    );

    /**Find the call given the identifier.
      */
    virtual PSafePtr<H323GatekeeperCall> FindCall(
      const OpalGloballyUniqueID & callIdentifier,
      H323GatekeeperCall::Direction direction,
      PSafetyMode mode = PSafeReference
    );
  //@}

  /**@name Routing operations */
  //@{
    /**Handle a location LRQ PDU.
       The default behaviour just uses TranslateAliasAddressToSignalAddress to
       determine the endpoints location.

       It is expected that a user would override this function to implement
       application specified look up algorithms.
      */
    virtual H323GatekeeperRequest::Response OnLocation(
      H323GatekeeperLRQ & request
    );

    /**Translate a given alias to an alias set and signal address.
       This is called by the OnAdmission() handler to fill in the ACF
       or OnLocation() to fill the LCF informing the calling endpoint where
       to actually connect to.

       It is expected that a user would override this function to implement
       application specified look up algorithms.

       The default behaviour calls TranslateAliasAddressToSignalAddress() which
       is provided only for backwards compatibility.
      */
    virtual PBoolean TranslateAliasAddress(
      const H225_AliasAddress & alias,
      H225_ArrayOf_AliasAddress & aliases,
      H323TransportAddress & address,
      PBoolean & isGkRouted,
      H323GatekeeperCall * call
    );

    /**Translate a given alias to a signal address.
       This is called by the OnAdmission() handler to fill in the ACF
       or OnLocation() to fill the LCF informing the calling endpoint where
       to actually connect to.

       It is expected that a user would override this function to implement
       application specified look up algorithms.

       The default behaviour checks the isGatekeeperRouted and if true simply
       returns the gatekeepers associated endpoints (not registered endpoint,
       but real H323EndPoint) listening address.

       If isGatekeeperRouted is false then it looks up the registered
       endpoints by alias and uses the saved signal address in the database.

       If the alias is not registered then the address parameter is not
       changed and the function returns true if it is a valid address, false
       if it was empty.
      */
    virtual PBoolean TranslateAliasAddressToSignalAddress(
      const H225_AliasAddress & alias,
      H323TransportAddress & address
    );
  //@}

  /**@name Policy operations */
  //@{
    /**Check the signal address against the security policy.
       This validates that the specified endpoint is allowed to make a
       connection to or from the specified signal address.

       It is expected that a user would override this function to implement
       application specified security policy algorithms.

       The default behaviour simply returns true.
      */
    virtual PBoolean CheckSignalAddressPolicy(
      const H323RegisteredEndPoint & ep,
      const H225_AdmissionRequest & arq,
      const H323TransportAddress & address
    );

    /**Check the alias address against the security policy.
       This validates that the specified endpoint is allowed to make a
       connection to or from the specified alias address.

       It is expected that a user would override this function to implement
       application specified security policy algorithms.

       The default behaviour checks the canOnlyAnswerRegisteredEP or
       canOnlyCallRegisteredEP meber variables depending on if it is an
       incoming call and if that is true only allows the call to proceed
       if the alias is also registered with the gatekeeper.
      */
    virtual PBoolean CheckAliasAddressPolicy(
      const H323RegisteredEndPoint & ep,
      const H225_AdmissionRequest & arq,
      const H225_AliasAddress & alias
    );

    /**Check the alias address against the security policy.
       This validates that the specified endpoint is allowed to make a
       connection to or from the specified simple alias string.

       It is expected that a user would override this function to implement
       application specified security policy algorithms.

       The default behaviour checks the canOnlyAnswerRegisteredEP or
       canOnlyCallRegisteredEP meber variables depending on if it is an
       incoming call and if that is true only allows the call to proceed
       if the alias is also registered with the gatekeeper.
      */
    virtual PBoolean CheckAliasStringPolicy(
      const H323RegisteredEndPoint & ep,
      const H225_AdmissionRequest & arq,
      const PString & alias
    );

    /**Allocate or change the bandwidth being used.
       This function modifies the total bandwidth used by the all endpoints
       registered with this gatekeeper. It is called when ARQ or BRQ PDU's are
       received.
      */
    virtual unsigned AllocateBandwidth(
      unsigned newBandwidth,
      unsigned oldBandwidth = 0
    );
  //@}

  /**@name Security and authentication functions */
  //@{
    /**Get separate H.235 authentication for the connection.
       This allows an individual ARQ to override the authentical credentials
       used in H.235 based RAS for this particular connection.

       A return value of false indicates to use the default credentials of the
       endpoint, while true indicates that new credentials are to be used.

       The default behavour does nothing and returns false.
      */
    virtual PBoolean GetAdmissionRequestAuthentication(
      H323GatekeeperARQ & info,           ///<  ARQ being constructed
      H235Authenticators & authenticators ///<  New authenticators for ARQ
    );

    /**Get password for user if H.235 security active.
       Returns true if user is found and password returned. Note the password
       may be empty in which case the user was found but explicitly ddoes not
       require security, possibly overriding the requireH235 flag.
      */
    virtual PBoolean GetUsersPassword(
      const PString & alias,
      PString & password,
      H323RegisteredEndPoint & registeredEndpoint
    ) const;
    virtual PBoolean GetUsersPassword(
      const PString & alias,
      PString & password
    ) const;
    virtual void SetUsersPassword(
      const PString & alias,
      const PString & password
    );
    virtual void ClearPasswords() { m_passwords.RemoveAll(); }
  //@}

#if OPAL_H501
  /**@name H.323 Annex G Peer Element support */
  //@{
    /**Get the associated peer element for the gatekeeper.
      */
    H323PeerElement * GetPeerElement() const { return m_peerElement; }

    /**Set the associated peer element for the gatekeeper.
       The existing peer element is automatically deleted.
      */
    void SetPeerElement(
      H323PeerElement * newPeerElement
    );

    /**Create an associated peer element for the gatekeeper.
       The existing peer element is checked to be listening on the same
       interface as specified and if it is not it is changed to the specified
       address.
      */
    void CreatePeerElement(
      const H323TransportAddress & h501Interface
    );

    /**Create a new Peer Element and establish a service relationship.
       If append is false, the existing peer element is automatically deleted
       and recreated. If append is true then a new service relationship is
       added to the existing peer element.
      */
    bool OpenPeerElement(
      const H323TransportAddress & remotePeer,
      bool append = false,
      bool keepTrying = true
    );
  //@}
#endif

  /**@name Access functions */
  //@{
    /**Get the identifier name for this gatekeeper.
      */
    const PString & GetGatekeeperIdentifier() const { return m_gatekeeperIdentifier; }

    /**Set the identifier name for this gatekeeper.
       If adjustListeners is true then all gatekeeper listeners that are
       attached to this gatekeeper server have their identifier names changed
       as well.
      */
    void SetGatekeeperIdentifier(
      const PString & id,
      bool adjustListeners = true
    );

    /**Get the total bandwidth available in 100's of bits per second.
      */
    unsigned GetAvailableBandwidth() const { return m_totalBandwidth; }

    /**Set the total bandwidth available in 100's of bits per second.
      */
    void SetAvailableBandwidth(unsigned bps100) { m_totalBandwidth = bps100; }

    /**Get the total bandwidth used in 100's of bits per second.
      */
    unsigned GetUsedBandwidth() const { return m_usedBandwidth; }

    /**Get the default bandwidth for calls.
      */
    unsigned GetDefaultBandwidth() const { return m_defaultBandwidth; }
    void SetDefaultBandwidth(unsigned bw) { m_defaultBandwidth = bw; }

    /**Get the maximum bandwidth for calls.
      */
    unsigned GetMaximumBandwidth() const { return m_maximumBandwidth; }
    void SetMaximumBandwidth(unsigned bw) { m_maximumBandwidth = bw; }

    /**Get the default time to live for new registered endpoints.
      */
    unsigned GetTimeToLive() const { return m_defaultTimeToLive; }

    /**Set the default time to live for new registered endpoints.
      */
    void SetTimeToLive(unsigned seconds) { m_defaultTimeToLive = seconds; }

    /**Get the default time for monitoring calls via IRR.
      */
    unsigned GetInfoResponseRate() const { return m_defaultInfoResponseRate; }

    /**Set the default time for monitoring calls via IRR.
      */
    void SetInfoResponseRate(unsigned seconds) { m_defaultInfoResponseRate = seconds; }

    /// Allow new registration to gatekeeper on a specific signal address to override previous registration
    bool GetOverwriteOnSameSignalAddress() const { return m_overwriteOnSameSignalAddress; }
    void SetOverwriteOnSameSignalAddress(bool v) { m_overwriteOnSameSignalAddress = v; }

    /// Minimum value for aliases gatekeeper will allocate when endpoint does not provide one, 0 disables
    unsigned GetMinAliasToAllocate() const { return m_minAliasToAllocate; }
    void SetMinAliasToAllocate(unsigned v) { m_minAliasToAllocate = v; }

    /// Maximum value for aliases gatekeeper will allocate when endpoint does not provide one, 0 disables
    unsigned GetMaxAliasToAllocate() const { return m_maxAliasToAllocate; }
    void SetMaxAliasToAllocate(unsigned v) { m_maxAliasToAllocate = v; }

    /// Different endpoint can register with gatekeeper the same alias name as another endpoint
    bool GetCanHaveDuplicateAlias() const { return m_canHaveDuplicateAlias; }
    void SetCanHaveDuplicateAlias(bool v) { m_canHaveDuplicateAlias = v; }

    /// Gateways may register duplicate prefix E.164 numbers.
    bool GetCanHaveDuplicatePrefix() const { return m_canHaveDuplicatePrefix; }
    void SetCanHaveDuplicatePrefix(bool v) { m_canHaveDuplicatePrefix = v; }

    /// Gatekeeper will only allow EP to call another endpoint registered localy
    bool GetCanOnlyCallRegisteredEP() const { return m_canOnlyCallRegisteredEP; }
    void SetCanOnlyCallRegisteredEP(bool v) { m_canOnlyCallRegisteredEP = v; }

    /// Gatekeeper will only allow endpoint to answer another endpoint registered localy
    bool GetCanOnlyAnswerRegisteredEP() const { return m_canOnlyAnswerRegisteredEP; }
    void SetCanOnlyAnswerRegisteredEP(bool v) { m_canOnlyAnswerRegisteredEP = v; }

    /// Gatekeeper pre-grants all incoming calls to endpoint
    bool GetAnswerCallPreGrantedARQ() const { return m_answerCallPreGrantedARQ; }
    void SetAnswerCallPreGrantedARQ(bool v) { m_answerCallPreGrantedARQ = v; }

    /// Gatekeeper pre-grants all outgoing calls from endpoint
    bool GetMakeCallPreGrantedARQ() const { return m_makeCallPreGrantedARQ; }
    void SetMakeCallPreGrantedARQ(bool v) { m_makeCallPreGrantedARQ = v; }

    /// Gatekeeper allows endpoint to simply register its host name/IP address
    bool GetAliasCanBeHostName() const { return m_aliasCanBeHostName; }
    void SetAliasCanBeHostName(bool v) { m_aliasCanBeHostName = v; }

    /// Hang up call if heartbeat (IRR) fails.
    bool GetDisengageOnHearbeatFail() const { return m_disengageOnHearbeatFail; }
    void SetDisengageOnHearbeatFail(bool v) { m_disengageOnHearbeatFail = v; }

    /**Get flag for is gatekeeper routed.
      */
    bool IsGatekeeperRouted() const { return m_isGatekeeperRouted; }
    void SetGatekeeperRouted(bool is) { m_isGatekeeperRouted = is; }

    /**Get flag for if H.235 authentication is required.
      */
    bool IsRequiredH235() const { return m_requireH235; }
    void SetRequiredH235(bool req) { m_requireH235 = req; }

    /**Get the currently active registration count.
      */
    unsigned GetActiveRegistrations() const { return m_byIdentifier.GetSize(); }

    /**Get the peak registration count.
      */
    unsigned GetPeakRegistrations() const { return m_peakRegistrations; }

    /**Get the total registrations since start up.
      */
    unsigned GetTotalRegistrations() const { return m_totalRegistrations; }

    /**Get the total registrations rejected since start up.
      */
    unsigned GetRejectedRegistrations() const { return m_rejectedRegistrations; }

    /**Get the currently active call count.
      */
    unsigned GetActiveCalls() const { return m_activeCalls.GetSize(); }

    /**Get the peak calls count.
      */
    unsigned GetPeakCalls() const { return m_peakCalls; }

    /**Get the total calls since start up.
      */
    unsigned GetTotalCalls() const { return m_totalCalls; }

    /**Get the total calls rejected since start up.
      */
    unsigned GetRejectedCalls() const { return m_rejectedCalls; }
  //@}

    // Remove an alias from the server database.
    void RemoveAlias(
      H323RegisteredEndPoint & ep,
      const PString & alias
    );

    // called when an endpoint needs to send a descriptor to the H.501 peer element
    virtual PBoolean OnSendDescriptorForEndpoint(
      H323RegisteredEndPoint & /*ep*/,                    ///<  endpoint
      H225_ArrayOf_AliasAddress & /*aliases*/,            ///<  aliases for the enndpoint
      H225_EndpointType & /*terminalType*/,               ///<  terminal type
      H225_ArrayOf_AliasAddress & /*transportAddresses*/  ///<  transport addresses
    )
    { return true; } 

    virtual PBoolean AllowDuplicateAlias(const H225_ArrayOf_AliasAddress & /*aliases*/)
    { return m_canHaveDuplicateAlias; }

    virtual PString AllocateAlias(H225_RegistrationRequest & rrq);

#if OPAL_H460
    virtual PBoolean OnSendFeatureSet(H460_MessageType pduType, H225_FeatureSet & features) const;
    virtual void OnReceiveFeatureSet(H460_MessageType pduType, const H225_FeatureSet & features) const;
#endif

  protected:

    PDECLARE_NOTIFIER(PThread, H323GatekeeperServer, MonitorMain);

    // Configuration & policy variables
    PString  m_gatekeeperIdentifier;
    unsigned m_totalBandwidth;
    unsigned m_usedBandwidth;
    unsigned m_defaultBandwidth;
    unsigned m_maximumBandwidth;
    unsigned m_defaultTimeToLive;
    unsigned m_defaultInfoResponseRate;
    bool     m_overwriteOnSameSignalAddress;
    unsigned m_minAliasToAllocate; // Zero is no allocation RRJ
    unsigned m_maxAliasToAllocate;
    unsigned m_aliasToAllocate;
    bool     m_canHaveDuplicateAlias;
    bool     m_canHaveDuplicatePrefix;
    bool     m_canOnlyCallRegisteredEP;
    bool     m_canOnlyAnswerRegisteredEP;
    bool     m_answerCallPreGrantedARQ;
    bool     m_makeCallPreGrantedARQ;
    bool     m_isGatekeeperRouted;
    bool     m_aliasCanBeHostName;
    bool     m_requireH235;
    bool     m_disengageOnHearbeatFail;

    PStringToString m_passwords;

    // Dynamic variables
    time_t      m_identifierBase;
    unsigned    m_nextIdentifier;
    PThread   * m_monitorThread;
    PSyncPoint  m_monitorExit;

    PLIST(ListenerList, H323GatekeeperListener);
    ListenerList m_listeners;

#if OPAL_H501
    H323PeerElement * m_peerElement;
#endif

    typedef PSafeDictionary<H225_AliasAddress, H323RegisteredEndPoint> EndPointByAlias;
    EndPointByAlias m_discoveredEndpoints;

    typedef PSafeDictionary<PString, H323RegisteredEndPoint> EndPointByID;
    EndPointByID m_byIdentifier;

    class StringMap : public PString {
        PCLASSINFO(StringMap, PString);
      public:
        StringMap(const PString & from, const PString & id)
          : PString(from), identifier(id) { }
        PString identifier;
    };
    PSortedStringList m_byAddress;
    PSortedStringList m_byAlias;
    PSortedStringList m_byVoicePrefix;

    PSafeSortedList<H323GatekeeperCall> m_activeCalls;

    PINDEX         m_peakRegistrations;
    PINDEX         m_totalRegistrations;
    atomic<unsigned> m_rejectedRegistrations;
    PINDEX         m_peakCalls;
    PINDEX         m_totalCalls;
    atomic<unsigned> m_rejectedCalls;

  friend class H323GatekeeperRRQ;
  friend class H323GatekeeperARQ;

  P_REMOVE_VIRTUAL(H323RegisteredEndPoint *,CreateRegisteredEndPoint(H323GatekeeperRRQ &),0);
};


#endif // OPAL_H323

#endif // OPAL_H323_GKSERVER_H


/////////////////////////////////////////////////////////////////////////////

