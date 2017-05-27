/*
 * vsdl.cxx
 *
 * Classes to support video output via SDL
 *
 * Portable Windows Library
 *
 * Copyright (c) 1993-2000 Equivalence Pty. Ltd.
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
 * The Original Code is Portable Windows Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 */

#ifdef __GNUC__
#pragma implementation "vsdl.h"
#endif

#include <ptlib.h>

#if P_SDL

#define P_FORCE_STATIC_PLUGIN 1

#include <ptclib/vsdl.h>
#include <ptlib/vconvert.h>

#ifdef P_MACOSX
  #include <ptlib/pprocess.h>
#endif

#define new PNEW
#define PTraceModule() "SDL"


extern "C" {
  #include <SDL.h>
};

#ifdef _MSC_VER
  #pragma comment(lib, P_SDL_LIBRARY)
#endif


PCREATE_VIDOUTPUT_PLUGIN_EX(SDL,

  virtual const char * GetFriendlyName() const
  {
    return "Simple DirectMedia Layer Video Output";
  }

  virtual bool ValidateDeviceName(const PString & deviceName, P_INT_PTR /*userData*/) const
  {
    return deviceName.NumCompare(GetServiceName()) == PObject::EqualTo;
  }
);


///////////////////////////////////////////////////////////////////////

class PSDL_System
{
  public:
    static PSDL_System & GetInstance()
    {
      static PSDL_System instance;
      return instance;
    }


    enum UserEvents {
      e_Open,
      e_Close,
      e_SetFrameSize,
      e_SetFrameData,
      e_ForceQuit
    };

  
    void ForceQuit()
    {
      PTRACE(3, "Forcing quit of event thread");
      
      SDL_Event sdlEvent;
      sdlEvent.type = SDL_USEREVENT;
      sdlEvent.user.code = e_ForceQuit;
      sdlEvent.user.data1 = NULL;
      ::SDL_PushEvent(&sdlEvent);
    }
  
#ifdef P_MACOSX
  void ReturnToApplicationMain()
  {
    PProcess::Current().InternalMain();
    ForceQuit();
  }
  
  void ApplicationMain()
  {
    if (m_thread != NULL)
      return;
    
    m_thread = PThread::Current();

    new PThreadObj<PSDL_System>(*this, &PSDL_System::ReturnToApplicationMain, true, PProcess::Current().GetName());
    MainLoop();
  }
#endif

    void Run()
    {
      if (m_thread == NULL) {
        PTRACE(3, "Starting event thread.");
        m_thread = new PThreadObj<PSDL_System>(*this, &PSDL_System::MainLoop, true, "SDL");
        m_started.Wait();
      }
    }


  private:
    PThread     * m_thread;
    PSyncPoint    m_started;
  
    typedef std::set<PVideoOutputDevice_SDL *> DeviceList;
    DeviceList m_devices;

    PSDL_System()
      : m_thread(NULL)
    {
    }

    ~PSDL_System()
    {
      ForceQuit();
    }

    virtual void MainLoop()
    {
#if PTRACING
      PTRACE(4, "Start of event thread");

      SDL_version hdrVer, binVer;
      SDL_VERSION(&hdrVer);
      SDL_GetVersion(&binVer);
      PTRACE(3, "Compiled version: "
             << (unsigned)hdrVer.major << '.' << (unsigned)hdrVer.minor << '.' << (unsigned)hdrVer.patch
             << "  Run-Time version: "
             << (unsigned)binVer.major << '.' << (unsigned)binVer.minor << '.' << (unsigned)binVer.patch);
#endif

      // initialise the SDL library
      int err = ::SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
      if (err != 0) {
        PTRACE(1, "Couldn't initialize SDL: error=" << err << ' ' << ::SDL_GetError());
        return;
      }

      //SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
      
#ifdef _WIN32
      SDL_SetModuleHandle(GetModuleHandle(NULL));
#endif

      m_started.Signal();

      PTRACE(4, "Starting main event loop");
      SDL_Event sdlEvent;
      do {
        if (!SDL_WaitEvent(&sdlEvent)) {
          PTRACE(1, "Error in WaitEvent: " << ::SDL_GetError());
          break;
        }
      } while (HandleEvent(sdlEvent));

      PTRACE(3, "Quitting SDL");
      for (DeviceList::iterator it = m_devices.begin(); it != m_devices.end(); ++it)
        (*it)->InternalClose();
      
      m_devices.clear();
      
      ::SDL_Quit();
      m_thread = NULL;

      PTRACE(4, "End of event thread");
    }


    bool HandleEvent(SDL_Event & sdlEvent)
    {
      switch (sdlEvent.type) {
        case SDL_USEREVENT :
        {
          PVideoOutputDevice_SDL * device = reinterpret_cast<PVideoOutputDevice_SDL *>(sdlEvent.user.data1);
          switch (sdlEvent.user.code) {
            case e_Open :
              if (device->InternalOpen())
                m_devices.insert(device);
              break;

            case e_Close :
              device->InternalClose();
              if (m_devices.erase(device) == 0)
                PTRACE(2, "Close of unknown device: " << device);
              break;

            case e_SetFrameSize :
              if (m_devices.find(device) != m_devices.end())
                device->InternalSetFrameSize();
              break;

            case e_SetFrameData :
              if (m_devices.find(device) != m_devices.end())
                device->InternalSetFrameData();
              break;

            case e_ForceQuit :
              return false;

            default :
              PTRACE(5, "Unhandled user event " << sdlEvent.user.code);
          }
          break;
        }

        case SDL_WINDOWEVENT :
          switch (sdlEvent.window.event) {
            case SDL_WINDOWEVENT_RESIZED :
              PTRACE(4, "Resize window to " << sdlEvent.window.data1 << " x " << sdlEvent.window.data2 << " on " << sdlEvent.window.windowID);
              break;
              
            default :
              PTRACE(5, "Unhandled windows event " << (unsigned)sdlEvent.window.event);
          }
          break;
          
        default :
          PTRACE(5, "Unhandled event " << (unsigned)sdlEvent.type);
      }
      
      return true;
    }
};


///////////////////////////////////////////////////////////////////////

#ifdef P_MACOSX
void PVideoOutputDevice_SDL::ApplicationMain()
{
  PSDL_System::GetInstance().ApplicationMain();
}
#endif


PVideoOutputDevice_SDL::PVideoOutputDevice_SDL()
  : m_window(NULL)
  , m_renderer(NULL)
  , m_texture(NULL)
{
  m_colourFormat = PVideoFrameInfo::YUV420P();
  PTRACE(5, "Constructed device: " << this);
}


PVideoOutputDevice_SDL::~PVideoOutputDevice_SDL()
{ 
  Close();
  PTRACE(5, "Destroyed device: " << this);
}


PStringArray PVideoOutputDevice_SDL::GetOutputDeviceNames()
{
  return PPlugin_PVideoOutputDevice_SDL::ServiceName();
}


PStringArray PVideoOutputDevice_SDL::GetDeviceNames() const
{
  return GetOutputDeviceNames();
}


PBoolean PVideoOutputDevice_SDL::Open(const PString & name, PBoolean /*startImmediate*/)
{
  Close();

  m_deviceName = name;

  PTRACE(5, "Opening device " << this << ' ' << m_deviceName);
  PSDL_System::GetInstance().Run();
  PostEvent(PSDL_System::e_Open, true);
  return IsOpen();
}


bool PVideoOutputDevice_SDL::InternalOpen()
{
  PWaitAndSignal sync(m_operationComplete, false);
  
  int x = SDL_WINDOWPOS_UNDEFINED;
  int y = SDL_WINDOWPOS_UNDEFINED;
  PINDEX x_pos = m_deviceName.Find("X=");
  PINDEX y_pos = m_deviceName.Find("Y=");
  if (x_pos != P_MAX_INDEX && y_pos != P_MAX_INDEX) {
    x = atoi(&m_deviceName[x_pos+2]);
    y = atoi(&m_deviceName[y_pos+2]);
  }
  
  PString title = "Video Output";
  PINDEX pos = m_deviceName.Find("TITLE=\"");
  if (pos != P_MAX_INDEX) {
    pos += 6;
    PINDEX quote = m_deviceName.FindLast('"');
    title = PString(PString::Literal, m_deviceName(pos, quote > pos ? quote : P_MAX_INDEX));
  }
  
  m_window = SDL_CreateWindow(title, x, y, GetFrameWidth(), GetFrameHeight(), SDL_WINDOW_RESIZABLE);
  if (m_window == NULL) {
    PTRACE(1, "Couldn't create SDL window: " << ::SDL_GetError());
    return false;
  }
  
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (m_renderer == NULL) {
    PTRACE(1, "Couldn't create SDL renderer: " << ::SDL_GetError());
    return false;
  }
  
  m_texture = SDL_CreateTexture(m_renderer,
                                SDL_PIXELFORMAT_IYUV,
                                SDL_TEXTUREACCESS_STREAMING,
                                GetFrameWidth(), GetFrameHeight());
  if (m_texture == NULL) {
    PTRACE(1, "Couldn't create SDL texture: " << ::SDL_GetError());
    return false;
  }
  
  PTRACE(3, "Opened window for device: " << this << ' ' << m_deviceName);
  return true;
}


PBoolean PVideoOutputDevice_SDL::IsOpen()
{
  return m_texture != NULL;
}


PBoolean PVideoOutputDevice_SDL::Close()
{
  if (!IsOpen())
    return false;
  
  PTRACE(5, "Closing device: " << this << ' ' << m_deviceName);
  PostEvent(PSDL_System::e_Close, true);
  return true;
}


void PVideoOutputDevice_SDL::InternalClose()
{
  SDL_DestroyTexture(m_texture);   m_texture  = NULL;
  SDL_DestroyRenderer(m_renderer); m_renderer = NULL;
  SDL_DestroyWindow(m_window);     m_window   = NULL;
  PTRACE(3, "Closed window on device " << this << ' ' << m_deviceName);
  m_operationComplete.Signal();
}


PBoolean PVideoOutputDevice_SDL::SetColourFormat(const PString & colourFormat)
{
  if (colourFormat *= PVideoFrameInfo::YUV420P())
    return PVideoOutputDevice::SetColourFormat(colourFormat);

  return false;
}


PBoolean PVideoOutputDevice_SDL::SetFrameSize(unsigned width, unsigned height)
{
  if (width == m_frameWidth && height == m_frameHeight)
    return true;

  if (!PVideoOutputDevice::SetFrameSize(width, height))
    return false;

  if (IsOpen())
    PostEvent(PSDL_System::e_SetFrameSize, true);

  return true;
}


void PVideoOutputDevice_SDL::InternalSetFrameSize()
{
  PWaitAndSignal sync(m_operationComplete, false);
  
  if (m_renderer == NULL)
    return;
  
  if (m_texture != NULL)
    SDL_DestroyTexture(m_texture);

  m_texture = SDL_CreateTexture(m_renderer,
                                SDL_PIXELFORMAT_IYUV,
                                SDL_TEXTUREACCESS_STREAMING,
                                GetFrameWidth(), GetFrameHeight());
  PTRACE_IF(1, m_texture == NULL, "Couldn't create SDL texture: " << ::SDL_GetError());
}


PINDEX PVideoOutputDevice_SDL::GetMaxFrameBytes()
{
  return GetMaxFrameBytesConverted(CalculateFrameBytes(m_frameWidth, m_frameHeight, m_colourFormat));
}


PBoolean PVideoOutputDevice_SDL::SetFrameData(unsigned x, unsigned y,
                                          unsigned width, unsigned height,
                                          const BYTE * data,
                                          PBoolean endFrame) 
{
  if (!IsOpen())
    return false;

  if (x != 0 || y != 0 || width != m_frameWidth || height != m_frameHeight || data == NULL || !endFrame)
    return false;

  void * ptr;
  int pitch;
  SDL_LockTexture(m_texture, NULL, &ptr, &pitch);
  if (pitch == width)
    memcpy(ptr, data, width*height*3/2);
  SDL_UnlockTexture(m_texture);
  
  PostEvent(PSDL_System::e_SetFrameData, false);
  return true;
}


void PVideoOutputDevice_SDL::InternalSetFrameData()
{
  if (m_texture == NULL)
    return;
  
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
  SDL_RenderPresent(m_renderer);
}


void PVideoOutputDevice_SDL::PostEvent(unsigned code, bool wait)
{
  SDL_Event sdlEvent;
  sdlEvent.type = SDL_USEREVENT;
  sdlEvent.user.code = code;
  sdlEvent.user.data1 = this;
  sdlEvent.user.data2 = NULL;
  if (::SDL_PushEvent(&sdlEvent) < 0) {
    PTRACE(1, "Couldn't post user event " << (unsigned)sdlEvent.user.code << ": " << ::SDL_GetError());
    return;
  }

  PTRACE(5, "Posted user event " << (unsigned)sdlEvent.user.code);
  if (wait)
    PAssert(m_operationComplete.Wait(10000),
            PSTRSTRM("Couldn't process user event " << (unsigned)sdlEvent.user.code));
}
#endif // P_SDL
