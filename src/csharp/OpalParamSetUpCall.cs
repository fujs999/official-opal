//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.12
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class OpalParamSetUpCall : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalParamSetUpCall(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(OpalParamSetUpCall obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalParamSetUpCall() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalParamSetUpCall(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public string partyA {
    set {
      OPALPINVOKE.OpalParamSetUpCall_partyA_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamSetUpCall_partyA_get(swigCPtr);
      return ret;
    } 
  }

  public string partyB {
    set {
      OPALPINVOKE.OpalParamSetUpCall_partyB_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamSetUpCall_partyB_get(swigCPtr);
      return ret;
    } 
  }

  public string callToken {
    set {
      OPALPINVOKE.OpalParamSetUpCall_callToken_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamSetUpCall_callToken_get(swigCPtr);
      return ret;
    } 
  }

  public string alertingType {
    set {
      OPALPINVOKE.OpalParamSetUpCall_alertingType_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamSetUpCall_alertingType_get(swigCPtr);
      return ret;
    } 
  }

  public string protocolCallId {
    set {
      OPALPINVOKE.OpalParamSetUpCall_protocolCallId_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamSetUpCall_protocolCallId_get(swigCPtr);
      return ret;
    } 
  }

  public OpalParamProtocol overrides {
    set {
      OPALPINVOKE.OpalParamSetUpCall_overrides_set(swigCPtr, OpalParamProtocol.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = OPALPINVOKE.OpalParamSetUpCall_overrides_get(swigCPtr);
      OpalParamProtocol ret = (cPtr == global::System.IntPtr.Zero) ? null : new OpalParamProtocol(cPtr, false);
      return ret;
    } 
  }

  public uint extraCount {
    set {
      OPALPINVOKE.OpalParamSetUpCall_extraCount_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamSetUpCall_extraCount_get(swigCPtr);
      return ret;
    } 
  }

  public OpalMIME extras {
    set {
      OPALPINVOKE.OpalParamSetUpCall_extras_set(swigCPtr, OpalMIME.getCPtr(value));
    } 
    get {
      global::System.IntPtr cPtr = OPALPINVOKE.OpalParamSetUpCall_extras_get(swigCPtr);
      OpalMIME ret = (cPtr == global::System.IntPtr.Zero) ? null : new OpalMIME(cPtr, false);
      return ret;
    } 
  }

  public OpalParamSetUpCall() : this(OPALPINVOKE.new_OpalParamSetUpCall(), true) {
  }

}
