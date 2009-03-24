//--------------------------------------------------------------------------------------------------
// $Id:$
//
// TriggerTable
//
// A convenient THashTable for storage of TriggerNames (not streamable).
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_TRIGGERTABLE_H
#define MITANA_DATATREE_TRIGGERTABLE_H

#include <string>
#include <TObject.h> 
#include <TString.h>
#include <THashTable.h>
#include "MitAna/DataTree/interface/TriggerName.h"

namespace mithep 
{
  class TriggerTable : public THashTable
  {
    public:
      TriggerTable(Int_t capacity = TCollection::kInitHashTableCapacity, Int_t rehash = 0) :
        THashTable(capacity,rehash) {}

      const TriggerName *Get(const char *name)   const;
      UShort_t           GetId(const char *name) const;
      using TCollection::Print;
      void               Print(Option_t *opt="") const;

    ClassDef(TriggerTable, 0) // A convenient trigger table
  };
}

//--------------------------------------------------------------------------------------------------
inline const mithep::TriggerName *mithep::TriggerTable::Get(const char *name) const
{ 
  // Return TriggerName pointer for given name.

  return dynamic_cast<const TriggerName *>(FindObject(name)); 
}

//--------------------------------------------------------------------------------------------------
inline UShort_t mithep::TriggerTable::GetId(const char *name) const
{
  // Return trigger id of trigger with given name.

  const mithep::TriggerName *tn = Get(name); 
  if (tn) 
    return tn->Id();
  
  Error("GetId", "TriggerName for %s not found. Returning 65535.", name);
  return 65535;
}
#endif
