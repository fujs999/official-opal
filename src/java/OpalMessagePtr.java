/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.1.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public class OpalMessagePtr {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected OpalMessagePtr(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpalMessagePtr obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected static long swigRelease(OpalMessagePtr obj) {
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
        OPALJNI.delete_OpalMessagePtr(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public OpalMessagePtr(OpalMessageType type) {
    this(OPALJNI.new_OpalMessagePtr__SWIG_0(type.swigValue()), true);
  }

  public OpalMessagePtr() {
    this(OPALJNI.new_OpalMessagePtr__SWIG_1(), true);
  }

  public OpalMessageType GetType() {
    return OpalMessageType.swigToEnum(OPALJNI.OpalMessagePtr_GetType(swigCPtr, this));
  }

  public OpalMessagePtr SetType(OpalMessageType type) {
    return new OpalMessagePtr(OPALJNI.OpalMessagePtr_SetType(swigCPtr, this, type.swigValue()), false);
  }

  public String GetCallToken() {
    return OPALJNI.OpalMessagePtr_GetCallToken(swigCPtr, this);
  }

  public void SetCallToken(String token) {
    OPALJNI.OpalMessagePtr_SetCallToken(swigCPtr, this, token);
  }

  public String GetCommandError() {
    return OPALJNI.OpalMessagePtr_GetCommandError(swigCPtr, this);
  }

  public OpalParamGeneral GetGeneralParams() {
    long cPtr = OPALJNI.OpalMessagePtr_GetGeneralParams(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamGeneral(cPtr, false);
  }

  public OpalParamProtocol GetProtocolParams() {
    long cPtr = OPALJNI.OpalMessagePtr_GetProtocolParams(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamProtocol(cPtr, false);
  }

  public OpalParamRegistration GetRegistrationParams() {
    long cPtr = OPALJNI.OpalMessagePtr_GetRegistrationParams(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamRegistration(cPtr, false);
  }

  public OpalStatusRegistration GetRegistrationStatus() {
    long cPtr = OPALJNI.OpalMessagePtr_GetRegistrationStatus(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusRegistration(cPtr, false);
  }

  public OpalParamSetUpCall GetCallSetUp() {
    long cPtr = OPALJNI.OpalMessagePtr_GetCallSetUp(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamSetUpCall(cPtr, false);
  }

  public OpalStatusIncomingCall GetIncomingCall() {
    long cPtr = OPALJNI.OpalMessagePtr_GetIncomingCall(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusIncomingCall(cPtr, false);
  }

  public OpalParamAnswerCall GetAnswerCall() {
    long cPtr = OPALJNI.OpalMessagePtr_GetAnswerCall(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamAnswerCall(cPtr, false);
  }

  public OpalStatusUserInput GetUserInput() {
    long cPtr = OPALJNI.OpalMessagePtr_GetUserInput(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusUserInput(cPtr, false);
  }

  public OpalStatusMessageWaiting GetMessageWaiting() {
    long cPtr = OPALJNI.OpalMessagePtr_GetMessageWaiting(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusMessageWaiting(cPtr, false);
  }

  public OpalStatusLineAppearance GetLineAppearance() {
    long cPtr = OPALJNI.OpalMessagePtr_GetLineAppearance(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusLineAppearance(cPtr, false);
  }

  public OpalStatusCallCleared GetCallCleared() {
    long cPtr = OPALJNI.OpalMessagePtr_GetCallCleared(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusCallCleared(cPtr, false);
  }

  public OpalParamCallCleared GetClearCall() {
    long cPtr = OPALJNI.OpalMessagePtr_GetClearCall(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamCallCleared(cPtr, false);
  }

  public OpalStatusMediaStream GetMediaStream() {
    long cPtr = OPALJNI.OpalMessagePtr_GetMediaStream(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusMediaStream(cPtr, false);
  }

  public OpalParamSetUserData GetSetUserData() {
    long cPtr = OPALJNI.OpalMessagePtr_GetSetUserData(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamSetUserData(cPtr, false);
  }

  public OpalParamRecording GetRecording() {
    long cPtr = OPALJNI.OpalMessagePtr_GetRecording(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamRecording(cPtr, false);
  }

  public OpalStatusTransferCall GetTransferStatus() {
    long cPtr = OPALJNI.OpalMessagePtr_GetTransferStatus(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusTransferCall(cPtr, false);
  }

  public OpalPresenceStatus GetPresenceStatus() {
    long cPtr = OPALJNI.OpalMessagePtr_GetPresenceStatus(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalPresenceStatus(cPtr, false);
  }

  public OpalInstantMessage GetInstantMessage() {
    long cPtr = OPALJNI.OpalMessagePtr_GetInstantMessage(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalInstantMessage(cPtr, false);
  }

}
