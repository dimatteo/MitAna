//--------------------------------------------------------------------------------------------------
// $Id: Muon.h,v 1.4 2008/06/11 13:48:37 loizides Exp $
//
// Vertex
//
// Vertex class implemented as holding a 3d vector as a point in space.
//
// Authors: J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef DATATREE_VERTEX_H
#define DATATREE_VERTEX_H
 
#include "MitAna/DataTree/interface/DataObject.h"

namespace mithep 
{
  class Vertex : public DataObject
  {
    public:
      Vertex() {}
      Vertex(Double_t x, Double_t y, Double_t z) : fPoint(x,y,z) {}
      ~Vertex() {}
      
      Double_t		Rho()   const { return fPoint.Rho(); }
      void		SetXYZ(Double_t x, Double_t y, Double_t z) { fPoint.SetXYZ(x,y,z); }
      Double_t		X()     const { return fPoint.X();   }
      Double_t		Y()     const { return fPoint.Y();   }
      Double_t		Z()     const { return fPoint.Z();   }
            
    protected:
      ThreeVector	fPoint; //point in space
	
    ClassDef(Vertex, 1) // Vertex class
  };
}
#endif