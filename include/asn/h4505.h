//
// h4505.h
//
// Code automatically generated by asnparse.
//

#include <opal_config.h>

#if ! H323_DISABLE_H4505

#ifndef __H4505_H
#define __H4505_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#include <ptclib/asner.h>

#include "h4501.h"
#include "h4501.h"
#include "h4501.h"
#include "h4504.h"
#include "h225.h"


//
// CallParkPickupOperations
//

class H4505_CallParkPickupOperations : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CallParkPickupOperations, PASN_Enumeration);
#endif
  public:
    H4505_CallParkPickupOperations(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_cpRequest = 106,
      e_cpSetup,
      e_groupIndicationOn = 8,
      e_groupIndicationOff,
      e_pickrequ = 110,
      e_pickup,
      e_pickExe,
      e_cpNotify,
      e_cpickupNotify
    };

    H4505_CallParkPickupOperations & operator=(unsigned v);
    PObject * Clone() const;
};


//
// ParkedToPosition
//

class H4505_ParkedToPosition : public PASN_Integer
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_ParkedToPosition, PASN_Integer);
#endif
  public:
    H4505_ParkedToPosition(unsigned tag = UniversalInteger, TagClass tagClass = UniversalTagClass);

    H4505_ParkedToPosition & operator=(int v);
    H4505_ParkedToPosition & operator=(unsigned v);
    PObject * Clone() const;
};


//
// ParkCondition
//

class H4505_ParkCondition : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_ParkCondition, PASN_Enumeration);
#endif
  public:
    H4505_ParkCondition(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_unspecified,
      e_parkedToUserIdle,
      e_parkedToUserBusy,
      e_parkedToGroup
    };

    H4505_ParkCondition & operator=(unsigned v);
    PObject * Clone() const;
};


//
// CallType
//

class H4505_CallType : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CallType, PASN_Enumeration);
#endif
  public:
    H4505_CallType(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_parkedCall,
      e_alertingCall
    };

    H4505_CallType & operator=(unsigned v);
    PObject * Clone() const;
};


//
// CallPickupErrors
//

class H4505_CallPickupErrors : public PASN_Enumeration
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CallPickupErrors, PASN_Enumeration);
#endif
  public:
    H4505_CallPickupErrors(unsigned tag = UniversalEnumeration, TagClass tagClass = UniversalTagClass);

    enum Enumerations {
      e_callPickupIdInvalid = 2000,
      e_callAlreadyPickedUp,
      e_undefined
    };

    H4505_CallPickupErrors & operator=(unsigned v);
    PObject * Clone() const;
};


//
// ArrayOf_MixedExtension
//

class H4504_MixedExtension;

class H4505_ArrayOf_MixedExtension : public PASN_Array
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_ArrayOf_MixedExtension, PASN_Array);
#endif
  public:
    H4505_ArrayOf_MixedExtension(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    PASN_Object * CreateObject() const;
    H4504_MixedExtension & operator[](PINDEX i) const;
    PObject * Clone() const;
};


//
// CpRequestArg
//

class H4505_CpRequestArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CpRequestArg, PASN_Sequence);
#endif
  public:
    H4505_CpRequestArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_parkedToPosition,
      e_extensionArg
    };

    H4501_EndpointAddress m_parkingNumber;
    H4501_EndpointAddress m_parkedNumber;
    H4501_EndpointAddress m_parkedToNumber;
    H4505_ParkedToPosition m_parkedToPosition;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// CpRequestRes
//

class H4505_CpRequestRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CpRequestRes, PASN_Sequence);
#endif
  public:
    H4505_CpRequestRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_parkedToPosition,
      e_extensionRes
    };

    H4501_EndpointAddress m_parkedToNumber;
    H4505_ParkedToPosition m_parkedToPosition;
    H4505_ParkCondition m_parkCondition;
    H4505_ArrayOf_MixedExtension m_extensionRes;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// CpSetupArg
//

class H4505_CpSetupArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CpSetupArg, PASN_Sequence);
#endif
  public:
    H4505_CpSetupArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_parkedToPosition,
      e_extensionArg
    };

    H4501_EndpointAddress m_parkingNumber;
    H4501_EndpointAddress m_parkedNumber;
    H4501_EndpointAddress m_parkedToNumber;
    H4505_ParkedToPosition m_parkedToPosition;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// CpSetupRes
//

class H4505_CpSetupRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CpSetupRes, PASN_Sequence);
#endif
  public:
    H4505_CpSetupRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_parkedToPosition,
      e_extensionRes
    };

    H4501_EndpointAddress m_parkedToNumber;
    H4505_ParkedToPosition m_parkedToPosition;
    H4505_ParkCondition m_parkCondition;
    H4505_ArrayOf_MixedExtension m_extensionRes;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// GroupIndicationOnArg
//

class H4505_GroupIndicationOnArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_GroupIndicationOnArg, PASN_Sequence);
#endif
  public:
    H4505_GroupIndicationOnArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_parkPosition,
      e_extensionArg
    };

    H225_CallIdentifier m_callPickupId;
    H4501_EndpointAddress m_groupMemberUserNr;
    H4505_CallType m_retrieveCallType;
    H4501_EndpointAddress m_partyToRetrieve;
    H4501_EndpointAddress m_retrieveAddress;
    H4505_ParkedToPosition m_parkPosition;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// GroupIndicationOnRes
//

class H4505_GroupIndicationOnRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_GroupIndicationOnRes, PASN_Sequence);
#endif
  public:
    H4505_GroupIndicationOnRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionRes
    };

    H4505_ArrayOf_MixedExtension m_extensionRes;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// GroupIndicationOffArg
//

class H4505_GroupIndicationOffArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_GroupIndicationOffArg, PASN_Sequence);
#endif
  public:
    H4505_GroupIndicationOffArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionArg
    };

    H225_CallIdentifier m_callPickupId;
    H4501_EndpointAddress m_groupMemberUserNr;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// GroupIndicationOffRes
//

class H4505_GroupIndicationOffRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_GroupIndicationOffRes, PASN_Sequence);
#endif
  public:
    H4505_GroupIndicationOffRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionRes
    };

    H4505_ArrayOf_MixedExtension m_extensionRes;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// PickrequArg
//

class H4505_PickrequArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_PickrequArg, PASN_Sequence);
#endif
  public:
    H4505_PickrequArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_callPickupId,
      e_partyToRetrieve,
      e_parkPosition,
      e_extensionArg
    };

    H4501_EndpointAddress m_picking_upNumber;
    H225_CallIdentifier m_callPickupId;
    H4501_EndpointAddress m_partyToRetrieve;
    H4501_EndpointAddress m_retrieveAddress;
    H4505_ParkedToPosition m_parkPosition;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// PickrequRes
//

class H4505_PickrequRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_PickrequRes, PASN_Sequence);
#endif
  public:
    H4505_PickrequRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionRes
    };

    H225_CallIdentifier m_callPickupId;
    H4505_ArrayOf_MixedExtension m_extensionRes;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// PickupArg
//

class H4505_PickupArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_PickupArg, PASN_Sequence);
#endif
  public:
    H4505_PickupArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionArg
    };

    H225_CallIdentifier m_callPickupId;
    H4501_EndpointAddress m_picking_upNumber;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// PickupRes
//

class H4505_PickupRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_PickupRes, PASN_Sequence);
#endif
  public:
    H4505_PickupRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionRes
    };

    H4505_ArrayOf_MixedExtension m_extensionRes;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// PickExeArg
//

class H4505_PickExeArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_PickExeArg, PASN_Sequence);
#endif
  public:
    H4505_PickExeArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionArg
    };

    H225_CallIdentifier m_callPickupId;
    H4501_EndpointAddress m_picking_upNumber;
    H4501_EndpointAddress m_partyToRetrieve;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// PickExeRes
//

class H4505_PickExeRes : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_PickExeRes, PASN_Sequence);
#endif
  public:
    H4505_PickExeRes(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_extensionRes
    };

    H4505_ArrayOf_MixedExtension m_extensionRes;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// CpNotifyArg
//

class H4505_CpNotifyArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CpNotifyArg, PASN_Sequence);
#endif
  public:
    H4505_CpNotifyArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_parkingNumber,
      e_extensionArg
    };

    H4501_EndpointAddress m_parkingNumber;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


//
// CpickupNotifyArg
//

class H4505_CpickupNotifyArg : public PASN_Sequence
{
#ifndef PASN_LEANANDMEAN
    PCLASSINFO(H4505_CpickupNotifyArg, PASN_Sequence);
#endif
  public:
    H4505_CpickupNotifyArg(unsigned tag = UniversalSequence, TagClass tagClass = UniversalTagClass);

    enum OptionalFields {
      e_picking_upNumber,
      e_extensionArg
    };

    H4501_EndpointAddress m_picking_upNumber;
    H4505_ArrayOf_MixedExtension m_extensionArg;

    PINDEX GetDataLength() const;
    PBoolean Decode(PASN_Stream & strm);
    void Encode(PASN_Stream & strm) const;
#ifndef PASN_NOPRINTON
    void PrintOn(ostream & strm) const;
#endif
    Comparison Compare(const PObject & obj) const;
    PObject * Clone() const;
};


#endif // __H4505_H

#endif // if ! H323_DISABLE_H4505


// End of h4505.h