//
// h4503.h
//
// Code automatically generated by asnparse.
//

#include <opal_config.h>

#if ! H323_DISABLE_H4503

#ifndef __H4503_H
#define __H4503_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <ptclib/asner.h>

#include "h4501.h"
#include "h225.h"
#include "h225.h"
#include "h4501.h"
#include "h4501.h"


//
// H323CallDiversionOperations
//

class H4503_H323CallDiversionOperations : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_H323CallDiversionOperations, PASN_Enumeration);
#endif
  public:
    H4503_H323CallDiversionOperations(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_activateDiversionQ = 15,
      e_deactivateDiversionQ,
      e_interrogateDiversionQ,
      e_checkRestriction,
      e_callRerouting,
      e_divertingLegInformation1,
      e_divertingLegInformation2,
      e_divertingLegInformation3,
      e_divertingLegInformation4 = 100,
      e_cfnrDivertedLegFailed = 23
    };

    H4503_H323CallDiversionOperations & operator=(unsigned v);
    virtual PObject * Clone() const override;
};


//
// RESULT-activateDiversionQ
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_RESULT_activateDiversionQ : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_RESULT_activateDiversionQ, PASN_Choice);
#endif
  public:
    H4503_RESULT_activateDiversionQ(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// RESULT-deactivateDiversionQ
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_RESULT_deactivateDiversionQ : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_RESULT_deactivateDiversionQ, PASN_Choice);
#endif
  public:
    H4503_RESULT_deactivateDiversionQ(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// RESULT-checkRestriction
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_RESULT_checkRestriction : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_RESULT_checkRestriction, PASN_Choice);
#endif
  public:
    H4503_RESULT_checkRestriction(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// RESULT-callRerouting
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_RESULT_callRerouting : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_RESULT_callRerouting, PASN_Choice);
#endif
  public:
    H4503_RESULT_callRerouting(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-cfnrDivertedLegFailed
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_cfnrDivertedLegFailed : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_cfnrDivertedLegFailed, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_cfnrDivertedLegFailed(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// DiversionReason
//

class H4503_DiversionReason : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_DiversionReason, PASN_Enumeration);
#endif
  public:
    H4503_DiversionReason(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_unknown,
      e_cfu,
      e_cfb,
      e_cfnr
    };

    H4503_DiversionReason & operator=(unsigned v);
    virtual PObject * Clone() const override;
};


//
// IntResultList
//

class H4503_IntResult;

class H4503_IntResultList : public PASN_Array
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_IntResultList, PASN_Array);
#endif
  public:
    H4503_IntResultList(unsigned tag = UniversalSet, TagClass tagClass = UniversalTagClass);

    virtual PASN_Object * CreateObject() const override;
    H4503_IntResult & operator[](PINDEX i) const;
    virtual PObject * Clone() const override;
};


//
// Procedure
//

class H4503_Procedure : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_Procedure, PASN_Enumeration);
#endif
  public:
    H4503_Procedure(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_cfu,
      e_cfb,
      e_cfnr
    };

    H4503_Procedure & operator=(unsigned v);
    virtual PObject * Clone() const override;
};


//
// SubscriptionOption
//

class H4503_SubscriptionOption : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_SubscriptionOption, PASN_Enumeration);
#endif
  public:
    H4503_SubscriptionOption(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_noNotification,
      e_notificationWithoutDivertedToNr,
      e_notificationWithDivertedToNr
    };

    H4503_SubscriptionOption & operator=(unsigned v);
    virtual PObject * Clone() const override;
};


//
// CallDiversionErrors
//

class H4503_CallDiversionErrors : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_CallDiversionErrors, PASN_Enumeration);
#endif
  public:
    H4503_CallDiversionErrors(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_invalidDivertedNumber = 12,
      e_specialServiceNumber = 14,
      e_diversionToServedUserNumber,
      e_numberOfDiversionsExceeded = 24,
      e_temporarilyUnavailable = 1000,
      e_notAuthorized = 1007,
      e_unspecified
    };

    H4503_CallDiversionErrors & operator=(unsigned v);
    virtual PObject * Clone() const override;
};


//
// BasicService
//

class H4503_BasicService : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_BasicService, PASN_Enumeration);
#endif
  public:
    H4503_BasicService(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_allServices
    };

    H4503_BasicService & operator=(unsigned v);
    virtual PObject * Clone() const override;
};


//
// ExtensionSeq
//

class H4501_Extension;

class H4503_ExtensionSeq : public PASN_Array
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ExtensionSeq, PASN_Array);
#endif
  public:
    H4503_ExtensionSeq(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    virtual PASN_Object * CreateObject() const override;
    H4501_Extension & operator[](PINDEX i) const;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-activateDiversionQ_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_activateDiversionQ_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_activateDiversionQ_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_activateDiversionQ_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-deactivateDiversionQ_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_deactivateDiversionQ_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_deactivateDiversionQ_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_deactivateDiversionQ_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-interrogateDiversionQ_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_interrogateDiversionQ_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_interrogateDiversionQ_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_interrogateDiversionQ_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-checkRestriction_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_checkRestriction_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_checkRestriction_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_checkRestriction_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-callRerouting_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_callRerouting_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_callRerouting_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_callRerouting_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation1_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_divertingLegInformation1_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation1_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation1_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation2_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_divertingLegInformation2_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation2_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation2_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation3_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_divertingLegInformation3_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation3_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation3_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation4_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_ARGUMENT_divertingLegInformation4_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation4_extension, PASN_Choice);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation4_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// IntResult_extension
//

class H4503_ExtensionSeq;
class H225_NonStandardParameter;

class H4503_IntResult_extension : public PASN_Choice
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_IntResult_extension, PASN_Choice);
#endif
  public:
    H4503_IntResult_extension(unsigned tag = 0, TagClass tagClass = UniversalTagClass);

    enum Choices {
      e_extensionSeq,
      e_nonStandardData
    };

#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H4503_ExtensionSeq &() const;
#else
    operator H4503_ExtensionSeq &();
    operator const H4503_ExtensionSeq &() const;
#endif
#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
    operator H225_NonStandardParameter &() const;
#else
    operator H225_NonStandardParameter &();
    operator const H225_NonStandardParameter &() const;
#endif

    virtual PBoolean CreateObject() override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-activateDiversionQ
//

class H4503_ARGUMENT_activateDiversionQ : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_activateDiversionQ, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_activateDiversionQ(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H4503_Procedure m_procedure;
    H4503_BasicService m_basicService;
    H4501_EndpointAddress m_divertedToAddress;
    H4501_EndpointAddress m_servedUserNr;
    H4501_EndpointAddress m_activatingUserNr;
    H4503_ARGUMENT_activateDiversionQ_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-deactivateDiversionQ
//

class H4503_ARGUMENT_deactivateDiversionQ : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_deactivateDiversionQ, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_deactivateDiversionQ(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H4503_Procedure m_procedure;
    H4503_BasicService m_basicService;
    H4501_EndpointAddress m_servedUserNr;
    H4501_EndpointAddress m_deactivatingUserNr;
    H4503_ARGUMENT_deactivateDiversionQ_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-interrogateDiversionQ
//

class H4503_ARGUMENT_interrogateDiversionQ : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_interrogateDiversionQ, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_interrogateDiversionQ(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H4503_Procedure m_procedure;
    H4503_BasicService m_basicService;
    H4501_EndpointAddress m_servedUserNr;
    H4501_EndpointAddress m_interrogatingUserNr;
    H4503_ARGUMENT_interrogateDiversionQ_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-checkRestriction
//

class H4503_ARGUMENT_checkRestriction : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_checkRestriction, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_checkRestriction(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H4501_EndpointAddress m_servedUserNr;
    H4503_BasicService m_basicService;
    H4501_EndpointAddress m_divertedToNr;
    H4503_ARGUMENT_checkRestriction_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-callRerouting
//

class H4503_ARGUMENT_callRerouting : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_callRerouting, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_callRerouting(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_originalReroutingReason,
      e_callingPartySubaddress,
      e_callingInfo,
      e_originalCalledNr,
      e_redirectingInfo,
      e_originalCalledInfo,
      e_extension
    };

    H4503_DiversionReason m_reroutingReason;
    H4503_DiversionReason m_originalReroutingReason;
    H4501_EndpointAddress m_calledAddress;
    PASN_Integer m_diversionCounter;
    H4501_H225InformationElement m_h225InfoElement;
    H4501_EndpointAddress m_lastReroutingNr;
    H4503_SubscriptionOption m_subscriptionOption;
    H4501_PartySubaddress m_callingPartySubaddress;
    H4501_EndpointAddress m_callingNumber;
    PASN_BMPString m_callingInfo;
    H4501_EndpointAddress m_originalCalledNr;
    PASN_BMPString m_redirectingInfo;
    PASN_BMPString m_originalCalledInfo;
    H4503_ARGUMENT_callRerouting_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation1
//

class H4503_ARGUMENT_divertingLegInformation1 : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation1, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation1(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_nominatedInfo,
      e_redirectingNr,
      e_redirectingInfo,
      e_extension
    };

    H4503_DiversionReason m_diversionReason;
    H4503_SubscriptionOption m_subscriptionOption;
    H4501_EndpointAddress m_nominatedNr;
    PASN_BMPString m_nominatedInfo;
    H4501_EndpointAddress m_redirectingNr;
    PASN_BMPString m_redirectingInfo;
    H4503_ARGUMENT_divertingLegInformation1_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation2
//

class H4503_ARGUMENT_divertingLegInformation2 : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation2, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation2(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_originalDiversionReason,
      e_divertingNr,
      e_originalCalledNr,
      e_redirectingInfo,
      e_originalCalledInfo,
      e_extension
    };

    PASN_Integer m_diversionCounter;
    H4503_DiversionReason m_diversionReason;
    H4503_DiversionReason m_originalDiversionReason;
    H4501_EndpointAddress m_divertingNr;
    H4501_EndpointAddress m_originalCalledNr;
    PASN_BMPString m_redirectingInfo;
    PASN_BMPString m_originalCalledInfo;
    H4503_ARGUMENT_divertingLegInformation2_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation3
//

class H4503_ARGUMENT_divertingLegInformation3 : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation3, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation3(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_redirectionNr,
      e_redirectionInfo,
      e_extension
    };

    H4501_PresentationAllowedIndicator m_presentationAllowedIndicator;
    H4501_EndpointAddress m_redirectionNr;
    PASN_BMPString m_redirectionInfo;
    H4503_ARGUMENT_divertingLegInformation3_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// ARGUMENT-divertingLegInformation4
//

class H4503_ARGUMENT_divertingLegInformation4 : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_ARGUMENT_divertingLegInformation4, PASN_Sequence);
#endif
  public:
    H4503_ARGUMENT_divertingLegInformation4(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_callingInfo,
      e_nominatedInfo,
      e_extension
    };

    H4503_DiversionReason m_diversionReason;
    H4503_SubscriptionOption m_subscriptionOption;
    H4501_EndpointAddress m_callingNr;
    PASN_BMPString m_callingInfo;
    H4501_EndpointAddress m_nominatedNr;
    PASN_BMPString m_nominatedInfo;
    H4503_ARGUMENT_divertingLegInformation4_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


//
// IntResult
//

class H4503_IntResult : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4503_IntResult, PASN_Sequence);
#endif
  public:
    H4503_IntResult(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extension
    };

    H4501_EndpointAddress m_servedUserNr;
    H4503_BasicService m_basicService;
    H4503_Procedure m_procedure;
    H4501_EndpointAddress m_divertedToAddress;
    PASN_Boolean m_remoteEnabled;
    H4503_IntResult_extension m_extension;

    virtual PINDEX GetDataLength() const override;
    virtual PBoolean Decode(PASN_Stream & strm) override;
    virtual void Encode(PASN_Stream & strm) const override;
#ifndef PASN_NOPRINTON
    virtual void PrintOn(ostream & strm) const override;
#endif
    virtual Comparison Compare(const PObject & obj) const override;
    virtual PObject * Clone() const override;
};


#endif // __H4503_H

#endif // if ! H323_DISABLE_H4503


// End of h4503.h
