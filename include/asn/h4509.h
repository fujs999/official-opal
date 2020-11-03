//
// h4509.h
//
// Code automatically generated by asnparse.
//

#include <opal_config.h>

#if ! H323_DISABLE_H4509

#ifndef __H4509_H
#define __H4509_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <ptclib/asner.h>

#include "h4501.h"
#include "h225.h"
#include "h4501.h"
#include "h4504.h"
#include "h4501.h"
#include "h4507.h"


//
// H323CallCompletionOperations
//

class H4509_H323CallCompletionOperations : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_H323CallCompletionOperations, PASN_Enumeration);
#endif
  public:
    H4509_H323CallCompletionOperations(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_ccbsRequest = 40,
      e_ccnrRequest = 27,
      e_ccCancel,
      e_ccExecPossible,
      e_ccRingout = 31,
      e_ccSuspend,
      e_ccResume
    };

    H4509_H323CallCompletionOperations & operator=(unsigned v);
    PObject * Clone() const;
};


//
// CcArg
//

class H4509_CcShortArg;
class H4509_CcLongArg;

class H4509_CcArg : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_CcArg, PASN_Choice);
#endif
  public:
    H4509_CcArg(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_shortArg,
      e_longArg
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4509_CcShortArg &() const;
#else
    operator H4509_CcShortArg &();
    operator const H4509_CcShortArg &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4509_CcLongArg &() const;
#else
    operator H4509_CcLongArg &();
    operator const H4509_CcLongArg &() const;
#endif

    bool CreateObject();
    PObject * Clone() const;
};


//
// CallCompletionErrors
//

class H4509_CallCompletionErrors : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_CallCompletionErrors, PASN_Enumeration);
#endif
  public:
    H4509_CallCompletionErrors(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_shortTermRejection = 1010,
      e_longTermRejection,
      e_remoteUserBusyAgain,
      e_failureToMatch
    };

    H4509_CallCompletionErrors & operator=(unsigned v);
    PObject * Clone() const;
};


//
// ArrayOf_MixedExtension
//

class H4504_MixedExtension;

class H4509_ArrayOf_MixedExtension : public PASN_Array
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_ArrayOf_MixedExtension, PASN_Array);
#endif
  public:
    H4509_ArrayOf_MixedExtension(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    PASN_Object * CreateObject() const;
    H4504_MixedExtension & operator[](PINDEX i) const;
    PObject * Clone() const;
};


//
// CcRequestArg
//

class H4509_CcRequestArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_CcRequestArg, PASN_Sequence);
#endif
  public:
    H4509_CcRequestArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_ccIdentifier,
      e_retain_sig_connection,
      e_extension
    };

    H4501_EndpointAddress m_numberA;
    H4501_EndpointAddress m_numberB;
    H225_CallIdentifier m_ccIdentifier;
    H4507_BasicService m_service;
    PASN_Boolean m_can_retain_service;
    PASN_Boolean m_retain_sig_connection;
    H4509_ArrayOf_MixedExtension m_extension;

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
// CcRequestRes
//

class H4509_CcRequestRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_CcRequestRes, PASN_Sequence);
#endif
  public:
    H4509_CcRequestRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    PASN_Boolean m_retain_service;
    H4509_ArrayOf_MixedExtension m_extension;

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
// CcShortArg
//

class H4509_CcShortArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_CcShortArg, PASN_Sequence);
#endif
  public:
    H4509_CcShortArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_ccIdentifier,
      e_extension
    };

    H225_CallIdentifier m_ccIdentifier;
    H4509_ArrayOf_MixedExtension m_extension;

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
// CcLongArg
//

class H4509_CcLongArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4509_CcLongArg, PASN_Sequence);
#endif
  public:
    H4509_CcLongArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_numberA,
      e_numberB,
      e_ccIdentifier,
      e_service,
      e_extension
    };

    H4501_EndpointAddress m_numberA;
    H4501_EndpointAddress m_numberB;
    H225_CallIdentifier m_ccIdentifier;
    H4507_BasicService m_service;
    H4509_ArrayOf_MixedExtension m_extension;

    PINDEX GetDataLength() const;
    bool Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


#endif // __H4509_H

#endif // if ! H323_DISABLE_H4509


// End of h4509.h
