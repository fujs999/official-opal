/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.1.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public class OpalStatusRegistration {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected OpalStatusRegistration(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpalStatusRegistration obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected static long swigRelease(OpalStatusRegistration obj) {
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
        OPALJNI.delete_OpalStatusRegistration(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setProtocol(String value) {
    OPALJNI.OpalStatusRegistration_protocol_set(swigCPtr, this, value);
  }

  public String getProtocol() {
    return OPALJNI.OpalStatusRegistration_protocol_get(swigCPtr, this);
  }

  public void setServerName(String value) {
    OPALJNI.OpalStatusRegistration_serverName_set(swigCPtr, this, value);
  }

  public String getServerName() {
    return OPALJNI.OpalStatusRegistration_serverName_get(swigCPtr, this);
  }

  public void setError(String value) {
    OPALJNI.OpalStatusRegistration_error_set(swigCPtr, this, value);
  }

  public String getError() {
    return OPALJNI.OpalStatusRegistration_error_get(swigCPtr, this);
  }

  public void setStatus(OpalRegistrationStates value) {
    OPALJNI.OpalStatusRegistration_status_set(swigCPtr, this, value.swigValue());
  }

  public OpalRegistrationStates getStatus() {
    return OpalRegistrationStates.swigToEnum(OPALJNI.OpalStatusRegistration_status_get(swigCPtr, this));
  }

  public void setProduct(OpalProductDescription value) {
    OPALJNI.OpalStatusRegistration_product_set(swigCPtr, this, OpalProductDescription.getCPtr(value), value);
  }

  public OpalProductDescription getProduct() {
    long cPtr = OPALJNI.OpalStatusRegistration_product_get(swigCPtr, this);
    return (cPtr == 0) ? null : new OpalProductDescription(cPtr, false);
  }

  public OpalStatusRegistration() {
    this(OPALJNI.new_OpalStatusRegistration(), true);
  }

}
