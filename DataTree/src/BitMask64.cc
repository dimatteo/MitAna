// $Id: Track.cc,v 1.4 2008/07/03 08:22:18 loizides Exp $

#include "MitAna/DataTree/interface/BitMask64.h"

ClassImp(mithep::BitMask64)

using namespace mithep;

//--------------------------------------------------------------------------------------------------
UInt_t mithep::BitMask64::NBitsSet(UInt_t first, UInt_t last) const
{
  // Count number of bits which are set.

  UInt_t numBits = 0;
  for (UInt_t i=first; i<=last; i++)
    numBits += TestBit(i);
    
  return numBits;
}
