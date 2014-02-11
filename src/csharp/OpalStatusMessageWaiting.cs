/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OpalStatusMessageWaiting : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalStatusMessageWaiting(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OpalStatusMessageWaiting obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalStatusMessageWaiting() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalStatusMessageWaiting(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
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
