//
// h45010.h
//
// Code automatically generated by asnparse.
//

#include <opal_config.h>

#if ! H323_DISABLE_H45010

#ifndef __H45010_H
#define __H45010_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <ptclib/asner.h>

#include "h4504.h"
#include "h4506.h"


//
// H323CallOfferOperations
//

class H45010_H323CallOfferOperations : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H45010_H323CallOfferOperations, PASN_Enumeration);
#endif
  public:
    H45010_H323CallOfferOperations(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_callOfferRequest = 34,
      e_remoteUserAlerting = 115,
      e_cfbOverride = 49
    };

    H45010_H323CallOfferOperations & operator=(unsigned v);
    PObject * Clone() const;
};


//
// ArrayOf_MixedExtension
//

class H4504_MixedExtension;

class H45010_ArrayOf_MixedExtension : public PASN_Array
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H45010_ArrayOf_MixedExtension, PASN_Array);
#endif
  public:
    H45010_ArrayOf_MixedExtension(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    PASN_Object * CreateObject() const;
    H4504_MixedExtension & operator[](PINDEX i) const;
    PObject * Clone() const;
};


//
// CoReqOptArg
//

class H45010_CoReqOptArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H45010_CoReqOptArg, PASN_Sequence);
#endif
  public:
    H45010_CoReqOptArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H45010_ArrayOf_MixedExtension m_extension;

    PINDEX GetDataLength() const;
    bool Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// RUAlertOptArg
//

class H45010_RUAlertOptArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H45010_RUAlertOptArg, PASN_Sequence);
#endif
  public:
    H45010_RUAlertOptArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H45010_ArrayOf_MixedExtension m_extension;

    PINDEX GetDataLength() const;
    bool Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// CfbOvrOptArg
//

class H45010_CfbOvrOptArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H45010_CfbOvrOptArg, PASN_Sequence);
#endif
  public:
    H45010_CfbOvrOptArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H45010_ArrayOf_MixedExtension m_extension;

    PINDEX GetDataLength() const;
    bool Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


#endif // __H45010_H

#endif // if ! H323_DISABLE_H45010


// End of h45010.h
