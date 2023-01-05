//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (https://www.swig.org).
// Version 4.1.1
//
// Do not make changes to this file unless you know what you are doing - modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class OpalStatusMessageWaiting : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalStatusMessageWaiting(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(OpalStatusMessageWaiting obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  internal static global::System.Runtime.InteropServices.HandleRef swigRelease(OpalStatusMessageWaiting obj) {
    if (obj != null) {
      if (!obj.swigCMemOwn)
        throw new global::System.ApplicationException("Cannot release ownership as memory is not owned");
      global::System.Runtime.InteropServices.HandleRef ptr = obj.swigCPtr;
      obj.swigCMemOwn = false;
      obj.Dispose();
      return ptr;
    } else {
      return new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
    }
  }

  ~OpalStatusMessageWaiting() {
    Dispose(false);
  }

  public void Dispose() {
    Dispose(true);
    global::System.GC.SuppressFinalize(this);
  }

  protected virtual void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalStatusMessageWaiting(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }

  public string party {
    set {
      OPALPINVOKE.OpalStatusMessageWaiting_party_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusMessageWaiting_party_get(swigCPtr);
      return ret;
    } 
  }

  public string type {
    set {
      OPALPINVOKE.OpalStatusMessageWaiting_type_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusMessageWaiting_type_get(swigCPtr);
      return ret;
    } 
  }

  public string extraInfo {
    set {
      OPALPINVOKE.OpalStatusMessageWaiting_extraInfo_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusMessageWaiting_extraInfo_get(swigCPtr);
      return ret;
    } 
  }

  public OpalStatusMessageWaiting() : this(OPALPINVOKE.new_OpalStatusMessageWaiting(), true) {
  }

}
