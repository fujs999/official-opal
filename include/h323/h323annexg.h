/*
 * h323annexg.h
 *
 * Implementation of H.323 Annex G using H.501
 *
 * Open H323 Library
 *
 * Copyright (c) 2003 Equivalence Pty. Ltd.
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
 * Contributor(s): ______________________________________.
 */

#ifndef OPAL_H323_H323ANNEXG_H
#define OPAL_H323_H323ANNEXG_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <opal_config.h>

#if OPAL_H501

#include <h323/h323trans.h>
#include <h323/h501pdu.h>


class PASN_Sequence;
class PASN_Choice;

class H323EndPoint;


///////////////////////////////////////////////////////////////////////////////

/**This class embodies the H.323 Annex G using the H.501 protocol 
  */
class H323_AnnexG : public H323Transactor
{
  PCLASSINFO(H323_AnnexG, H323Transactor);
  public:
  /**@name Construction */
  //@{
    enum {
      DefaultUdpPort = 2099,
      DefaultTcpPort = 2099
    };

    /**Create a new protocol handler.
     */
    H323_AnnexG(
      H323EndPoint & endpoint,  ///<  Endpoint gatekeeper is associated with.
      H323Transport * transport ///<  Transport over which gatekeepers communicates.
    );
    H323_AnnexG(
      H323EndPoint & endpoint,           ///<  Endpoint gatekeeper is associated with.
      const H323TransportAddress & addr ///<  Transport over which gatekeepers communicates.
    );

    /**Destroy protocol handler.
     */
    ~H323_AnnexG();
  //@}

  /**@name Overrides from PObject */
  //@{
    /**Print the name of the gatekeeper.
      */
    void PrintOn(
      ostream & strm    ///<  Stream to print to.
    ) const;
  //@}

  /**@name Overrides from H323Transactor */
  //@{
    /**Create the transaction PDU for reading.
      */
    virtual H323TransactionPDU * CreateTransactionPDU() const;

    /**Handle and dispatch a transaction PDU
      */
    virtual bool HandleTransaction(
      const PASN_Object & rawPDU
    );

    /**Allow for modifications to PDU on send.
      */
    virtual void OnSendingPDU(
      PASN_Object & rawPDU
    );
  //@}

  /**@name Protocol callbacks */
  //@{
    virtual bool OnReceiveServiceRequest              (const H501PDU & pdu, const H501_ServiceRequest & pduBody);
    virtual bool OnReceiveServiceConfirmation         (const H501PDU & pdu, const H501_ServiceConfirmation & pduBody);
    virtual bool OnReceiveServiceRejection            (const H501PDU & pdu, const H501_ServiceRejection & pduBody);
    virtual bool OnReceiveServiceRelease              (const H501PDU & pdu, const H501_ServiceRelease & pduBody);
    virtual bool OnReceiveDescriptorRequest           (const H501PDU & pdu, const H501_DescriptorRequest & pduBody);
    virtual bool OnReceiveDescriptorConfirmation      (const H501PDU & pdu, const H501_DescriptorConfirmation & pduBody);
    virtual bool OnReceiveDescriptorRejection         (const H501PDU & pdu, const H501_DescriptorRejection & pduBody);
    virtual bool OnReceiveDescriptorIDRequest         (const H501PDU & pdu, const H501_DescriptorIDRequest & pduBody);
    virtual bool OnReceiveDescriptorIDConfirmation    (const H501PDU & pdu, const H501_DescriptorIDConfirmation & pduBody);
    virtual bool OnReceiveDescriptorIDRejection       (const H501PDU & pdu, const H501_DescriptorIDRejection & pduBody);
    virtual bool OnReceiveDescriptorUpdate            (const H501PDU & pdu, const H501_DescriptorUpdate & pduBody);
    virtual bool OnReceiveDescriptorUpdateACK         (const H501PDU & pdu, const H501_DescriptorUpdateAck & pduBody);
    virtual bool OnReceiveAccessRequest               (const H501PDU & pdu, const H501_AccessRequest & pduBody);
    virtual bool OnReceiveAccessConfirmation          (const H501PDU & pdu, const H501_AccessConfirmation & pduBody);
    virtual bool OnReceiveAccessRejection             (const H501PDU & pdu, const H501_AccessRejection & pduBody);
    virtual bool OnReceiveRequestInProgress           (const H501PDU & pdu, const H501_RequestInProgress & pduBody);
    virtual bool OnReceiveNonStandardRequest          (const H501PDU & pdu, const H501_NonStandardRequest & pduBody);
    virtual bool OnReceiveNonStandardConfirmation     (const H501PDU & pdu, const H501_NonStandardConfirmation & pduBody);
    virtual bool OnReceiveNonStandardRejection        (const H501PDU & pdu, const H501_NonStandardRejection & pduBody);
    virtual bool OnReceiveUnknownMessageResponse      (const H501PDU & pdu, const H501_UnknownMessageResponse & pduBody);
    virtual bool OnReceiveUsageRequest                (const H501PDU & pdu, const H501_UsageRequest & pduBody);
    virtual bool OnReceiveUsageConfirmation           (const H501PDU & pdu, const H501_UsageConfirmation & pduBody);
    virtual bool OnReceiveUsageIndicationConfirmation (const H501PDU & pdu, const H501_UsageIndicationConfirmation & pduBody);
    virtual bool OnReceiveUsageIndicationRejection    (const H501PDU & pdu, const H501_UsageIndicationRejection & pduBody);
    virtual bool OnReceiveUsageRejection              (const H501PDU & pdu, const H501_UsageRejection & pduBody);
    virtual bool OnReceiveValidationRequest           (const H501PDU & pdu, const H501_ValidationRequest & pduBody);
    virtual bool OnReceiveValidationConfirmation      (const H501PDU & pdu, const H501_ValidationConfirmation & pduBody);
    virtual bool OnReceiveValidationRejection         (const H501PDU & pdu, const H501_ValidationRejection & pduBody);
    virtual bool OnReceiveAuthenticationRequest       (const H501PDU & pdu, const H501_AuthenticationRequest & pduBody);
    virtual bool OnReceiveAuthenticationConfirmation  (const H501PDU & pdu, const H501_AuthenticationConfirmation & pduBody);
    virtual bool OnReceiveAuthenticationRejection     (const H501PDU & pdu, const H501_AuthenticationRejection & pduBody);
    virtual bool OnReceiveUnknown(const H501PDU &);

  protected:
    void Construct();
};


#endif // OPAL_H501

#endif // OPAL_H323_H323ANNEXG_H


/////////////////////////////////////////////////////////////////////////////
