/*
 * vidcodec.h
 *
 * Uncompressed video handler
 *
 * Open Phone Abstraction Library
 *
 * Copyright (c) 2003 Equivalence Pty. Ltd.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Open Phone Abstraction Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): 
 */

#ifndef OPAL_CODEC_VIDCODEC_H
#define OPAL_CODEC_VIDCODEC_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <opal_config.h>

#include <opal/transcoders.h>

#if OPAL_VIDEO

#if OPAL_H323
#include <h323/h323caps.h>
#endif

#include <codec/opalplugin.h>
#include <codec/known.h>


extern const OpalVideoFormat & GetOpalRGB24();
extern const OpalVideoFormat & GetOpalRGB32();
extern const OpalVideoFormat & GetOpalBGR24();
extern const OpalVideoFormat & GetOpalBGR32();
extern const OpalVideoFormat & GetOpalYUV420P();

#define OpalRGB24   GetOpalRGB24()
#define OpalRGB32   GetOpalRGB32()
#define OpalBGR24   GetOpalBGR24()
#define OpalBGR32   GetOpalBGR32()
#define OpalYUV420P GetOpalYUV420P()

#define OPAL_REGISTER_RAW_VIDEO() \
              GetOpalRGB24(); \
              GetOpalRGB32(); \
              GetOpalBGR24(); \
              GetOpalBGR32(); \
              GetOpalYUV420P()


///////////////////////////////////////////////////////////////////////////////

/**Handle logic for Intra frame control.
    This class deals with issues of too many and too few Intra frames being
    sent in response to requests from various sources.
  */
class OpalIntraFrameControl : public PObject
{
    PCLASSINFO(OpalIntraFrameControl, PObject);
  public:
    static PTimeInterval const DefaultMinThrottle;
    static PTimeInterval const DefaultMaxThrottle;
    static PTimeInterval const DefaultPeriodic;

    OpalIntraFrameControl(
      const PTimeInterval & minThrottle = DefaultMinThrottle, ///< Minimum time between intra frames
      const PTimeInterval & maxThrottle = DefaultMaxThrottle, ///< If many requests, throttle period increases to this
      const PTimeInterval & periodic = DefaultPeriodic        ///< Make sure Intra frames are at least this often
    );

    /**Handling incoming request for Intra frame.
      */
    void IntraFrameRequest();

    /**Indicate that now is the time for an Intra frame to be generated.
      */
    bool RequireIntraFrame();

    /**Detected Intra frame, so can cease requests.
      */
    void IntraFrameDetected();

    /**Set throttle times for controlling Intra Frame.
       This is 
      */
    void SetTimes(
      const PTimeInterval & minThrottle, ///< Minimum time between intra frames
      const PTimeInterval & maxThrottle, ///< If many requests, throttle period increases to this
      const PTimeInterval & periodic,    ///< Make sure Intra frames are at least this often
      const PTimeInterval & retry        ///< Retry request, typically the media round trip time, plus a bit.
    );

  protected:
    PTimeInterval m_minThrottleTime;
    PTimeInterval m_maxThrottleTime;
    PTimeInterval m_periodicTime;
    PTimeInterval m_retryTime;
    PTimeInterval m_currentThrottleTime;

    enum State
    {
      e_Idle,
      e_Periodic,
      e_Throttled,
      e_Requesting,
      e_Requested
    } m_state;

    unsigned m_stuckCount;

   PDECLARE_MUTEX(m_mutex);
    PTime  m_lastRequest;
    PTimer m_requestTimer;
    PDECLARE_NOTIFIER(PTimer, OpalIntraFrameControl, OnTimedRequest);
};

///////////////////////////////////////////////////////////////////////////////

/**This class defines a transcoder implementation class that will
   encode/decode video.

   An application may create a descendent off this class and override
   functions as required for descibing a specific transcoder.
 */
class OpalVideoTranscoder : public OpalTranscoder
{
    PCLASSINFO(OpalVideoTranscoder, OpalTranscoder);
  public:
    typedef PluginCodec_Video_FrameHeader FrameHeader;

  /**@name Construction */
  //@{
    /** Create a new video transcoder implementation.
      */
    OpalVideoTranscoder(
      const OpalMediaFormat & inputMediaFormat,  ///<  Input media format
      const OpalMediaFormat & outputMediaFormat  ///<  Output media format
    );
  //@}

  /**@name Operations */
  //@{
#if OPAL_STATISTICS
    virtual void GetStatistics(OpalMediaStatistics & statistics) const override;
#endif

    /**Update the input and output media formats. This can be used to adjust
       the parameters of a codec at run time. Note you cannot change the basic
       media format, eg change GSM0610 to G.711, only options for that
       format, eg 6k3 mode to 5k3 mode in G.723.1. If the formats are
       different then a OpalMediaFormat::Merge() is performed.

       If a format is empty (invalid) it is ignored and does not update the
       internal variable. In this way only the input or output side can be
       updated.

       The default behaviour updates the inputMediaFormat and outputMediaFormat
       member variables.
      */
    virtual bool UpdateMediaFormats(
      const OpalMediaFormat & inputMediaFormat,  ///<  Input media format
      const OpalMediaFormat & outputMediaFormat  ///<  Output media format
    ) override;

    /**Get the optimal size for data frames to be converted.
       This function returns the size of frames that will be most efficient
       in conversion. A RTP_DataFrame will attempt to provide or use data in
       multiples of this size. Note that it may not do so, so the transcoder
       must be able to handle any sized packets.
      */
    virtual PINDEX GetOptimalDataFrameSize(
      PBoolean input      ///<  Flag for input or output data size
    ) const override;

    /**Execute the command specified to the transcoder. The commands are
       highly context sensitive, for example OpalVideoUpdatePicture would only
       apply to a video transcoder.

       The default behaviour checks for a OpalVideoUpdatePicture and sets the
       updatePicture member variable if that is the command.

       @returns true if command is handled.
      */
    virtual PBoolean ExecuteCommand(
      const OpalMediaCommand & command    ///<  Command to execute.
    ) override;

    /**Convert the data from one format to another.
       This function takes the input data as a RTP_DataFrame and converts it
       to its output format, placing it into the RTP_DataFrame provided.

       This is a dummy function as nearly all video conversion will does not
       have a one to one input to output frames ratio, so the ConvertFrames()
       function is used instead.

       Returns false if the conversion fails.
      */
    virtual PBoolean Convert(
      const RTP_DataFrame & input,  ///<  Input data
      RTP_DataFrame & output        ///<  Output data
    ) override;


    virtual bool HasErrorConcealment() const  { return m_errorConcealment; }

    virtual bool ShouldDropFrame(RTP_Timestamp ts);
    virtual void UpdateFrameDrop(const RTP_DataFrameList & encoded);

    bool WasLastFrameIFrame() const { return m_lastFrameWasIFrame; }
    virtual void SendIFrameRequest(unsigned sequenceNumber, unsigned timestamp);
    virtual bool HandleIFrameRequest();

    void SetEncodingIntraFrameControlTimes(
      const PTimeInterval & minThrottle, ///< Minimum time between intra frames
      const PTimeInterval & maxThrottle, ///< If many requests, throttle period increases to this
      const PTimeInterval & periodic,    ///< Make sure Intra frames are at least this often
      const PTimeInterval & retry        ///< Retry request, typically the media round trip time, plus a bit.
    ) { m_encodingIntraFrameControl.SetTimes(minThrottle, maxThrottle, periodic, retry); }

    void SetDecodingIntraFrameControlTimes(
      const PTimeInterval & minThrottle, ///< Minimum time between intra frames
      const PTimeInterval & maxThrottle, ///< If many requests, throttle period increases to this
      const PTimeInterval & periodic,    ///< Make sure Intra frames are at least this often
      const PTimeInterval & retry        ///< Retry request, typically the media round trip time, plus a bit.
    ) { m_decodingIntraFrameControl.SetTimes(minThrottle, maxThrottle, periodic, retry); }
  //@}

  protected:
    PINDEX m_inDataSize;
    PINDEX m_outDataSize;
    bool   m_errorConcealment;
    bool   m_freezeTillIFrame;
    bool   m_frozenTillIFrame;
    bool   m_lastFrameWasIFrame;

    unsigned      m_frameDropRate;
    int           m_frameDropBits;
    RTP_Timestamp m_lastTimestamp;
    unsigned      m_framesDropped;

    OpalIntraFrameControl m_encodingIntraFrameControl;
    OpalIntraFrameControl m_decodingIntraFrameControl;
};


///////////////////////////////////////////////////////////////////////////////

OPAL_DEFINE_MEDIA_COMMAND(OpalVideoFreezePicture, "Freeze Picture", OpalMediaType::Video());

/**This indicates that a force video picture update is required, that
   is an Intra or Key frame MUST be sent. This may be called when the
   system logic requires a scene chage, e.g. when recording a video an
   Intra frame is required before it can start, the sender must send one.
  */
class OpalVideoUpdatePicture : public OpalMediaCommand
{
    PCLASSINFO_WITH_CLONE(OpalVideoUpdatePicture, OpalMediaCommand);
  public:
    OpalVideoUpdatePicture(
      unsigned sessionID = 0,          ///< Session for media stream, 0 is use first \p mediaType stream
      unsigned ssrc = 0                ///< Sync Source for media stream (if RTP)
    );
    virtual PString GetName() const override;
};

/**This indicates that the remote has had a picture loss and that a
   video picture update is desired, that is an Intra or Key frame should be
   sent, however, the sender can opt due to say bandwidth constraints not to
   do so and suffer with the corrupted video.
  */
class OpalVideoPictureLoss : public OpalVideoUpdatePicture
{
    PCLASSINFO_WITH_CLONE(OpalVideoPictureLoss, OpalVideoUpdatePicture);
  public:
    OpalVideoPictureLoss(
      unsigned sequenceNumber = 0,
      unsigned timestamp = 0,
      unsigned sessionID = 0,          ///< Session for media stream, 0 is use first \p mediaType stream
      unsigned ssrc = 0                ///< Sync Source for media stream (if RTP)
    );

    virtual PString GetName() const override;

    unsigned GetSequenceNumber() const { return m_sequenceNumber; }
    unsigned GetTimestamp() const { return m_timestamp; }

  protected:
    unsigned m_sequenceNumber;
    unsigned m_timestamp;
};


/**This is an indication to the video encoder to change the way it is to
   encode the video stream.

   The trade off integer is a value that trade spatial quality (blocky-ness)
   for temporal quality (frame rate). A value of zero will maximise spatial
   quality, sacrificing frame rate and a value of 31 will maximize frame rate
   and sacrifice 
  */
class OpalTemporalSpatialTradeOff : public OpalMediaCommand
{
    PCLASSINFO_WITH_CLONE(OpalTemporalSpatialTradeOff, OpalMediaCommand);
  public:
    OpalTemporalSpatialTradeOff(
      unsigned tradeoff,
      unsigned sessionID = 0,          ///< Session for media stream, 0 is use first \p mediaType stream
      unsigned ssrc = 0                ///< Sync Source for media stream (if RTP)
    );

    virtual PString GetName() const override;

    enum {
      MaximiseSpatial = 0,
      MaximiseTemporal = 31
    };

    unsigned GetTradeOff() const { return m_tradeOff; }

  protected:
    unsigned m_tradeOff;
};


#endif // OPAL_VIDEO

#endif // OPAL_CODEC_VIDCODEC_H

/////////////////////////////////////////////////////////////////////////////
