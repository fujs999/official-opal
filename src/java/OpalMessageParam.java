/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.1.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public class OpalMessageParam {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected OpalMessageParam(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpalMessageParam obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected static long swigRelease(OpalMessageParam obj) {
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
        OPALJNI.delete_OpalMessageParam(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setCommandError(String value) {
    OPALJNI.OpalMessageParam_commandError_set(swigCPtr, this, value);
  }

  public String getCommandError() {
    return OPALJNI.OpalMessageParam_commandError_get(swigCPtr, this);
  }

  public void setGeneral(OpalParamGeneral value) {
    OPALJNI.OpalMessageParam_general_set(swigCPtr, this, OpalParamGeneral.getCPtr(value), value);
  }

  public OpalParamGeneral getGeneral() {
    long cPtr = OPALJNI.OpalMessageParam_general_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamGeneral(cPtr, false);
  }

  public void setProtocol(OpalParamProtocol value) {
    OPALJNI.OpalMessageParam_protocol_set(swigCPtr, this, OpalParamProtocol.getCPtr(value), value);
  }

  public OpalParamProtocol getProtocol() {
    long cPtr = OPALJNI.OpalMessageParam_protocol_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamProtocol(cPtr, false);
  }

  public void setRegistrationInfo(OpalParamRegistration value) {
    OPALJNI.OpalMessageParam_registrationInfo_set(swigCPtr, this, OpalParamRegistration.getCPtr(value), value);
  }

  public OpalParamRegistration getRegistrationInfo() {
    long cPtr = OPALJNI.OpalMessageParam_registrationInfo_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamRegistration(cPtr, false);
  }

  public void setRegistrationStatus(OpalStatusRegistration value) {
    OPALJNI.OpalMessageParam_registrationStatus_set(swigCPtr, this, OpalStatusRegistration.getCPtr(value), value);
  }

  public OpalStatusRegistration getRegistrationStatus() {
    long cPtr = OPALJNI.OpalMessageParam_registrationStatus_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusRegistration(cPtr, false);
  }

  public void setCallSetUp(OpalParamSetUpCall value) {
    OPALJNI.OpalMessageParam_callSetUp_set(swigCPtr, this, OpalParamSetUpCall.getCPtr(value), value);
  }

  public OpalParamSetUpCall getCallSetUp() {
    long cPtr = OPALJNI.OpalMessageParam_callSetUp_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamSetUpCall(cPtr, false);
  }

  public void setCallToken(String value) {
    OPALJNI.OpalMessageParam_callToken_set(swigCPtr, this, value);
  }

  public String getCallToken() {
    return OPALJNI.OpalMessageParam_callToken_get(swigCPtr, this);
  }

  public void setIncomingCall(OpalStatusIncomingCall value) {
    OPALJNI.OpalMessageParam_incomingCall_set(swigCPtr, this, OpalStatusIncomingCall.getCPtr(value), value);
  }

  public OpalStatusIncomingCall getIncomingCall() {
    long cPtr = OPALJNI.OpalMessageParam_incomingCall_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusIncomingCall(cPtr, false);
  }

  public void setAnswerCall(OpalParamAnswerCall value) {
    OPALJNI.OpalMessageParam_answerCall_set(swigCPtr, this, OpalParamAnswerCall.getCPtr(value), value);
  }

  public OpalParamAnswerCall getAnswerCall() {
    long cPtr = OPALJNI.OpalMessageParam_answerCall_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamAnswerCall(cPtr, false);
  }

  public void setUserInput(OpalStatusUserInput value) {
    OPALJNI.OpalMessageParam_userInput_set(swigCPtr, this, OpalStatusUserInput.getCPtr(value), value);
  }

  public OpalStatusUserInput getUserInput() {
    long cPtr = OPALJNI.OpalMessageParam_userInput_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusUserInput(cPtr, false);
  }

  public void setMessageWaiting(OpalStatusMessageWaiting value) {
    OPALJNI.OpalMessageParam_messageWaiting_set(swigCPtr, this, OpalStatusMessageWaiting.getCPtr(value), value);
  }

  public OpalStatusMessageWaiting getMessageWaiting() {
    long cPtr = OPALJNI.OpalMessageParam_messageWaiting_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusMessageWaiting(cPtr, false);
  }

  public void setLineAppearance(OpalStatusLineAppearance value) {
    OPALJNI.OpalMessageParam_lineAppearance_set(swigCPtr, this, OpalStatusLineAppearance.getCPtr(value), value);
  }

  public OpalStatusLineAppearance getLineAppearance() {
    long cPtr = OPALJNI.OpalMessageParam_lineAppearance_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusLineAppearance(cPtr, false);
  }

  public void setCallCleared(OpalStatusCallCleared value) {
    OPALJNI.OpalMessageParam_callCleared_set(swigCPtr, this, OpalStatusCallCleared.getCPtr(value), value);
  }

  public OpalStatusCallCleared getCallCleared() {
    long cPtr = OPALJNI.OpalMessageParam_callCleared_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusCallCleared(cPtr, false);
  }

  public void setClearCall(OpalParamCallCleared value) {
    OPALJNI.OpalMessageParam_clearCall_set(swigCPtr, this, OpalParamCallCleared.getCPtr(value), value);
  }

  public OpalParamCallCleared getClearCall() {
    long cPtr = OPALJNI.OpalMessageParam_clearCall_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamCallCleared(cPtr, false);
  }

  public void setMediaStream(OpalStatusMediaStream value) {
    OPALJNI.OpalMessageParam_mediaStream_set(swigCPtr, this, OpalStatusMediaStream.getCPtr(value), value);
  }

  public OpalStatusMediaStream getMediaStream() {
    long cPtr = OPALJNI.OpalMessageParam_mediaStream_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusMediaStream(cPtr, false);
  }

  public void setSetUserData(OpalParamSetUserData value) {
    OPALJNI.OpalMessageParam_setUserData_set(swigCPtr, this, OpalParamSetUserData.getCPtr(value), value);
  }

  public OpalParamSetUserData getSetUserData() {
    long cPtr = OPALJNI.OpalMessageParam_setUserData_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamSetUserData(cPtr, false);
  }

  public void setRecording(OpalParamRecording value) {
    OPALJNI.OpalMessageParam_recording_set(swigCPtr, this, OpalParamRecording.getCPtr(value), value);
  }

  public OpalParamRecording getRecording() {
    long cPtr = OPALJNI.OpalMessageParam_recording_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalParamRecording(cPtr, false);
  }

  public void setTransferStatus(OpalStatusTransferCall value) {
    OPALJNI.OpalMessageParam_transferStatus_set(swigCPtr, this, OpalStatusTransferCall.getCPtr(value), value);
  }

  public OpalStatusTransferCall getTransferStatus() {
    long cPtr = OPALJNI.OpalMessageParam_transferStatus_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusTransferCall(cPtr, false);
  }

  public void setIvrStatus(OpalStatusIVR value) {
    OPALJNI.OpalMessageParam_ivrStatus_set(swigCPtr, this, OpalStatusIVR.getCPtr(value), value);
  }

  public OpalStatusIVR getIvrStatus() {
    long cPtr = OPALJNI.OpalMessageParam_ivrStatus_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalStatusIVR(cPtr, false);
  }

  public void setPresenceStatus(OpalPresenceStatus value) {
    OPALJNI.OpalMessageParam_presenceStatus_set(swigCPtr, this, OpalPresenceStatus.getCPtr(value), value);
  }

  public OpalPresenceStatus getPresenceStatus() {
    long cPtr = OPALJNI.OpalMessageParam_presenceStatus_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalPresenceStatus(cPtr, false);
  }

  public void setInstantMessage(OpalInstantMessage value) {
    OPALJNI.OpalMessageParam_instantMessage_set(swigCPtr, this, OpalInstantMessage.getCPtr(value), value);
  }

  public OpalInstantMessage getInstantMessage() {
    long cPtr = OPALJNI.OpalMessageParam_instantMessage_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalInstantMessage(cPtr, false);
  }

  public void setProtocolMessage(OpalProtocolMessage value) {
    OPALJNI.OpalMessageParam_protocolMessage_set(swigCPtr, this, OpalProtocolMessage.getCPtr(value), value);
  }

  public OpalProtocolMessage getProtocolMessage() {
    long cPtr = OPALJNI.OpalMessageParam_protocolMessage_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalProtocolMessage(cPtr, false);
  }

  public OpalMessageParam() {
    this(OPALJNI.new_OpalMessageParam(), true);
  }

}
