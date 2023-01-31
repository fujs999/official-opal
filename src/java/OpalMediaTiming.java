/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.1.1
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public final class OpalMediaTiming {
  public final static OpalMediaTiming OpalMediaTimingNoChange = new OpalMediaTiming("OpalMediaTimingNoChange");
  public final static OpalMediaTiming OpalMediaTimingSynchronous = new OpalMediaTiming("OpalMediaTimingSynchronous");
  public final static OpalMediaTiming OpalMediaTimingAsynchronous = new OpalMediaTiming("OpalMediaTimingAsynchronous");
  public final static OpalMediaTiming OpalMediaTimingSimulated = new OpalMediaTiming("OpalMediaTimingSimulated");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static OpalMediaTiming swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + OpalMediaTiming.class + " with value " + swigValue);
  }

  private OpalMediaTiming(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private OpalMediaTiming(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private OpalMediaTiming(String swigName, OpalMediaTiming swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static OpalMediaTiming[] swigValues = { OpalMediaTimingNoChange, OpalMediaTimingSynchronous, OpalMediaTimingAsynchronous, OpalMediaTimingSimulated };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

