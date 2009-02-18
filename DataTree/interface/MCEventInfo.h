//--------------------------------------------------------------------------------------------------
// $Id: MCEventInfo.h,v 1.6 2008/12/09 17:47:00 loizides Exp $
//
// MCEventInfo
//
// Authors: C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_MCEVENTINFO_H
#define MITANA_DATATREE_MCEVENTINFO_H
 
#include "MitAna/DataTree/interface/DataBase.h"

namespace mithep 
{
  class MCEventInfo : public DataBase
  {
    public:
      MCEventInfo(Double_t w=0) : fWeight(w)  {}

      EObjType            ObjType()             const { return kMCEventInfo; }      
      Double_t            Weight()              const { return fWeight;      }
      void                SetWeight(Double_t w)       { fWeight=w;           }

    protected:
      Double32_t          fWeight;              //event weight
      
    ClassDef(MCEventInfo, 1) // Monte-Carlo event info class
  };
}
#endif
