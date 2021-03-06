//--------------------------------------------------------------------------------------------------
// $Id: Ref.h,v 1.7 2010/09/19 23:46:08 bendavid Exp $
//
// Ref
//
// Templated implementation of our own TRef.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATACONT_REF_H
#define MITANA_DATACONT_REF_H

#include <TObject.h>
#include <TRefTable.h>
#include <TProcessID.h>
#include <TError.h>
#include "MitAna/DataCont/interface/RefResolver.h"
#include "MitAna/DataCont/interface/ProcIDRef.h"
 
namespace mithep 
{
  template<class ArrayElement>
  class Ref
  {
    public:
      Ref() : fPID(0), fUID(0)    {}
      Ref(const ArrayElement *ae) { SetObject(ae); }
      virtual ~Ref()              {}

      Bool_t                       IsNull()        const { return fUID==0 ? kTRUE : kFALSE; }
      Bool_t                       IsValid()       const { return !IsNull();                }
      const ArrayElement          *Obj()           const;
      ArrayElement                *Obj();
      Bool_t                       RefsObject(const ArrayElement *ae) const;
      void                         SetObject(const ArrayElement *ae);
      
      void                         operator= (const ArrayElement *ae) { SetObject(ae);         }
      Bool_t                       operator==(const ArrayElement *ae) { return RefsObject(ae); }

    protected:
      TObject                     *GetObject()     const;

      ProcIDRef                    fPID;     //||process id corresponding to referenced object
      UInt_t                       fUID;     //unique id of the referenced object

    ClassDef(Ref, 1) // Templated implementation of our own TRef
  };
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
TObject *mithep::Ref<ArrayElement>::GetObject() const
{
  // Return pointer to object. Code adapted from TRef::GetObject().

  if (IsNull())
    return 0;
  
  TProcessID *pid = fPID.Pid(); 
  if (!pid) {
    Fatal("GetObject","Process id pointer is null!");
    return 0;
  }

  if (!TProcessID::IsValid(pid)) {
    Fatal("GetObject","Process id is invalid!");
    return 0;
  }

  TObject *obj = RefResolver::GetObjectWithID(fUID,pid);
  if (!obj) {
    Fatal("Ref::GetObject","Null pointer for valid ref!");
  }
  
  return obj;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
const ArrayElement *mithep::Ref<ArrayElement>::Obj() const
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  return reinterpret_cast<const ArrayElement*>(GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
ArrayElement *mithep::Ref<ArrayElement>::Obj()
{
  // Return entry at given index. Code adapted from TRef::GetObject().

  return reinterpret_cast<ArrayElement*>(GetObject());
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
Bool_t mithep::Ref<ArrayElement>::RefsObject(const ArrayElement *ae) const
{
  // Check whether Ref points to given object.

  if (IsNull())
    return kFALSE;

  const TObject *oe = reinterpret_cast<const TObject*>(ae);
  
  if (!oe->TestBit(kIsReferenced))
    return kFALSE;

  UInt_t oUid = oe->GetUniqueID();
  TProcessID *oPid = TProcessID::GetProcessWithUID(oUid, const_cast<TObject*>(oe));
  if (!oPid)
    return kFALSE;

  if ( (fUID&0xffffff)!=(oUid&0xffffff) || fPID.Pid()->GetUniqueID()!=oPid->GetUniqueID())
    return kFALSE;
  return kTRUE;
}

//--------------------------------------------------------------------------------------------------
template<class ArrayElement>
void mithep::Ref<ArrayElement>::SetObject(const ArrayElement *ae)
{
  // Set reference to object.

  if (!ae)
    return;

  const TObject *oe = reinterpret_cast<const TObject*>(ae);


  // check if the object can belong here and assign or get its uid
  if (oe->TestBit(kHasUUID)) {
    Fatal("Add", "Object cannot be added as it has not UUID!");
    return;
  }

  if (oe->TestBit(kIsReferenced)) {
    fUID = oe->GetUniqueID();
    fPID.SetPid(TProcessID::GetProcessWithUID(fUID, const_cast<TObject*>(oe)));
  } else {
    fPID.SetPid(TProcessID::GetSessionProcessID());
    fUID = TProcessID::AssignID(const_cast<TObject*>(oe));
  }
}
#endif
