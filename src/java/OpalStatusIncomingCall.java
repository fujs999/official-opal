/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.1.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public class OpalStatusIncomingCall {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected OpalStatusIncomingCall(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpalStatusIncomingCall obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected static long swigRelease(OpalStatusIncomingCall obj) {
    long ptr = 0;
    if (obj != null) {
      if (!obj.swigCMemOwn)
        throw new RuntimeException("Cannot release ownership as memory is not owned");
      ptr = obj.swigCPtr;
      obj.swigCMemOwn = false;
      obj.delete();
    }
    return ptr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        OPALJNI.delete_OpalStatusIncomingCall(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setCallToken(String value) {
    OPALJNI.OpalStatusIncomingCall_callToken_set(swigCPtr, this, value);
  }

  public String getCallToken() {
    return OPALJNI.OpalStatusIncomingCall_callToken_get(swigCPtr, this);
  }

  public void setLocalAddress(String value) {
    OPALJNI.OpalStatusIncomingCall_localAddress_set(swigCPtr, this, value);
  }

  public String getLocalAddress() {
    return OPALJNI.OpalStatusIncomingCall_localAddress_get(swigCPtr, this);
  }

  public void setRemoteAddress(String value) {
    OPALJNI.OpalStatusIncomingCall_remoteAddress_set(swigCPtr, this, value);
  }

  public String getRemoteAddress() {
    return OPALJNI.OpalStatusIncomingCall_remoteAddress_get(swigCPtr, this);
  }

  public void setRemotePartyNumber(String value) {
    OPALJNI.OpalStatusIncomingCall_remotePartyNumber_set(swigCPtr, this, value);
  }

  public String getRemotePartyNumber() {
    return OPALJNI.OpalStatusIncomingCall_remotePartyNumber_get(swigCPtr, this);
  }

  public void setRemoteDisplayName(String value) {
    OPALJNI.OpalStatusIncomingCall_remoteDisplayName_set(swigCPtr, this, value);
  }

  public String getRemoteDisplayName() {
    return OPALJNI.OpalStatusIncomingCall_remoteDisplayName_get(swigCPtr, this);
  }

  public void setCalledAddress(String value) {
    OPALJNI.OpalStatusIncomingCall_calledAddress_set(swigCPtr, this, value);
  }

  public String getCalledAddress() {
    return OPALJNI.OpalStatusIncomingCall_calledAddress_get(swigCPtr, this);
  }

  public void setCalledPartyNumber(String value) {
    OPALJNI.OpalStatusIncomingCall_calledPartyNumber_set(swigCPtr, this, value);
  }

  public String getCalledPartyNumber() {
    return OPALJNI.OpalStatusIncomingCall_calledPartyNumber_get(swigCPtr, this);
  }

  public void setProduct(OpalProductDescription value) {
    OPALJNI.OpalStatusIncomingCall_product_set(swigCPtr, this, OpalProductDescription.getCPtr(value), value);
  }

  public OpalProductDescription getProduct() {
    long cPtr = OPALJNI.OpalStatusIncomingCall_product_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalProductDescription(cPtr, false);
  }

  public void setAlertingType(String value) {
    OPALJNI.OpalStatusIncomingCall_alertingType_set(swigCPtr, this, value);
  }

  public String getAlertingType() {
    return OPALJNI.OpalStatusIncomingCall_alertingType_get(swigCPtr, this);
  }

  public void setProtocolCallId(String value) {
    OPALJNI.OpalStatusIncomingCall_protocolCallId_set(swigCPtr, this, value);
  }

  public String getProtocolCallId() {
    return OPALJNI.OpalStatusIncomingCall_protocolCallId_get(swigCPtr, this);
  }

  public void setReferredByAddress(String value) {
    OPALJNI.OpalStatusIncomingCall_referredByAddress_set(swigCPtr, this, value);
  }

  public String getReferredByAddress() {
    return OPALJNI.OpalStatusIncomingCall_referredByAddress_get(swigCPtr, this);
  }

  public void setRedirectingNumber(String value) {
    OPALJNI.OpalStatusIncomingCall_redirectingNumber_set(swigCPtr, this, value);
  }

  public String getRedirectingNumber() {
    return OPALJNI.OpalStatusIncomingCall_redirectingNumber_get(swigCPtr, this);
  }

  public void setExtraCount(long value) {
    OPALJNI.OpalStatusIncomingCall_extraCount_set(swigCPtr, this, value);
  }

  public long getExtraCount() {
    return OPALJNI.OpalStatusIncomingCall_extraCount_get(swigCPtr, this);
  }

  public void setExtras(OpalMIME value) {
    OPALJNI.OpalStatusIncomingCall_extras_set(swigCPtr, this, OpalMIME.getCPtr(value), value);
  }

  public OpalMIME getExtras() {
    long cPtr = OPALJNI.OpalStatusIncomingCall_extras_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalMIME(cPtr, false);
  }

  public void setRemoteIdentity(String value) {
    OPALJNI.OpalStatusIncomingCall_remoteIdentity_set(swigCPtr, this, value);
  }

  public String getRemoteIdentity() {
    return OPALJNI.OpalStatusIncomingCall_remoteIdentity_get(swigCPtr, this);
  }

  public void setSupportedFeatures(String value) {
    OPALJNI.OpalStatusIncomingCall_supportedFeatures_set(swigCPtr, this, value);
  }

  public String getSupportedFeatures() {
    return OPALJNI.OpalStatusIncomingCall_supportedFeatures_get(swigCPtr, this);
  }

  public OpalStatusIncomingCall() {
    this(OPALJNI.new_OpalStatusIncomingCall(), true);
  }

}
