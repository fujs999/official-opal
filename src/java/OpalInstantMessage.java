/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public class OpalInstantMessage {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected OpalInstantMessage(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpalInstantMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  @SuppressWarnings("deprecation")
  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        OPALJNI.delete_OpalInstantMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setFrom(String value) {
    OPALJNI.OpalInstantMessage_from_set(swigCPtr, this, value);
  }

  public String getFrom() {
    return OPALJNI.OpalInstantMessage_from_get(swigCPtr, this);
  }

  public void setTo(String value) {
    OPALJNI.OpalInstantMessage_to_set(swigCPtr, this, value);
  }

  public String getTo() {
    return OPALJNI.OpalInstantMessage_to_get(swigCPtr, this);
  }

  public void setHost(String value) {
    OPALJNI.OpalInstantMessage_host_set(swigCPtr, this, value);
  }

  public String getHost() {
    return OPALJNI.OpalInstantMessage_host_get(swigCPtr, this);
  }

  public void setConversationId(String value) {
    OPALJNI.OpalInstantMessage_conversationId_set(swigCPtr, this, value);
  }

  public String getConversationId() {
    return OPALJNI.OpalInstantMessage_conversationId_get(swigCPtr, this);
  }

  public void setTextBody(String value) {
    OPALJNI.OpalInstantMessage_textBody_set(swigCPtr, this, value);
  }

  public String getTextBody() {
    return OPALJNI.OpalInstantMessage_textBody_get(swigCPtr, this);
  }

  public void setBodyCount(long value) {
    OPALJNI.OpalInstantMessage_bodyCount_set(swigCPtr, this, value);
  }

  public long getBodyCount() {
    return OPALJNI.OpalInstantMessage_bodyCount_get(swigCPtr, this);
  }

  public void setMimeType(SWIGTYPE_p_p_char value) {
    OPALJNI.OpalInstantMessage_mimeType_set(swigCPtr, this, SWIGTYPE_p_p_char.getCPtr(value));
  }

  public SWIGTYPE_p_p_char getMimeType() {
    long cPtr = OPALJNI.OpalInstantMessage_mimeType_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_p_char(cPtr, false);
  }

  public void setBodies(SWIGTYPE_p_p_char value) {
    OPALJNI.OpalInstantMessage_bodies_set(swigCPtr, this, SWIGTYPE_p_p_char.getCPtr(value));
  }

  public SWIGTYPE_p_p_char getBodies() {
    long cPtr = OPALJNI.OpalInstantMessage_bodies_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_p_char(cPtr, false);
  }

  public void setMessageId(long value) {
    OPALJNI.OpalInstantMessage_messageId_set(swigCPtr, this, value);
  }

  public long getMessageId() {
    return OPALJNI.OpalInstantMessage_messageId_get(swigCPtr, this);
  }

  public void setHtmlBody(String value) {
    OPALJNI.OpalInstantMessage_htmlBody_set(swigCPtr, this, value);
  }

  public String getHtmlBody() {
    return OPALJNI.OpalInstantMessage_htmlBody_get(swigCPtr, this);
  }

  public void setBodyData(OpalMIME value) {
    OPALJNI.OpalInstantMessage_bodyData_set(swigCPtr, this, OpalMIME.getCPtr(value), value);
  }

  public OpalMIME getBodyData() {
    long cPtr = OPALJNI.OpalInstantMessage_bodyData_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalMIME(cPtr, false);
  }

  public OpalInstantMessage() {
    this(OPALJNI.new_OpalInstantMessage(), true);
  }

}
