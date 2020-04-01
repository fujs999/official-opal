/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public class OpalParamRecording {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected OpalParamRecording(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpalParamRecording obj) {
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
        OPALJNI.delete_OpalParamRecording(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setCallToken(String value) {
    OPALJNI.OpalParamRecording_callToken_set(swigCPtr, this, value);
  }

  public String getCallToken() {
    return OPALJNI.OpalParamRecording_callToken_get(swigCPtr, this);
  }

  public void setFile(String value) {
    OPALJNI.OpalParamRecording_file_set(swigCPtr, this, value);
  }

  public String getFile() {
    return OPALJNI.OpalParamRecording_file_get(swigCPtr, this);
  }

  public void setChannels(long value) {
    OPALJNI.OpalParamRecording_channels_set(swigCPtr, this, value);
  }

  public long getChannels() {
    return OPALJNI.OpalParamRecording_channels_get(swigCPtr, this);
  }

  public void setAudioFormat(String value) {
    OPALJNI.OpalParamRecording_audioFormat_set(swigCPtr, this, value);
  }

  public String getAudioFormat() {
    return OPALJNI.OpalParamRecording_audioFormat_get(swigCPtr, this);
  }

  public void setVideoFormat(String value) {
    OPALJNI.OpalParamRecording_videoFormat_set(swigCPtr, this, value);
  }

  public String getVideoFormat() {
    return OPALJNI.OpalParamRecording_videoFormat_get(swigCPtr, this);
  }

  public void setVideoWidth(long value) {
    OPALJNI.OpalParamRecording_videoWidth_set(swigCPtr, this, value);
  }

  public long getVideoWidth() {
    return OPALJNI.OpalParamRecording_videoWidth_get(swigCPtr, this);
  }

  public void setVideoHeight(long value) {
    OPALJNI.OpalParamRecording_videoHeight_set(swigCPtr, this, value);
  }

  public long getVideoHeight() {
    return OPALJNI.OpalParamRecording_videoHeight_get(swigCPtr, this);
  }

  public void setVideoRate(long value) {
    OPALJNI.OpalParamRecording_videoRate_set(swigCPtr, this, value);
  }

  public long getVideoRate() {
    return OPALJNI.OpalParamRecording_videoRate_get(swigCPtr, this);
  }

  public void setVideoMixing(OpalVideoRecordMixMode value) {
    OPALJNI.OpalParamRecording_videoMixing_set(swigCPtr, this, value.swigValue());
  }

  public OpalVideoRecordMixMode getVideoMixing() {
    return OpalVideoRecordMixMode.swigToEnum(OPALJNI.OpalParamRecording_videoMixing_get(swigCPtr, this));
  }

  public void setAudioBufferSize(long value) {
    OPALJNI.OpalParamRecording_audioBufferSize_set(swigCPtr, this, value);
  }

  public long getAudioBufferSize() {
    return OPALJNI.OpalParamRecording_audioBufferSize_get(swigCPtr, this);
  }

  public OpalParamRecording() {
    this(OPALJNI.new_OpalParamRecording(), true);
  }

}
