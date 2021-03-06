//--------------------------------------------------------------------------------------------------
// $Id: Jet.h,v 1.27 2010/05/30 14:00:24 bendavid Exp $
//
// Jet
//
// Base jet class to hold reconstructed jet information.
//
// Authors: S.Xie, C.Loizides, J.Bendavid
//--------------------------------------------------------------------------------------------------

#ifndef MITANA_DATATREE_JET_H
#define MITANA_DATATREE_JET_H
 
#include "MitCommon/DataFormats/interface/Vect4M.h"
#include "MitAna/DataTree/interface/Particle.h"

namespace mithep 
{
  class Jet : public Particle
  {
    public:
      enum ECorr { 
        L1 = 0, 
        L2,
        L3,
        L4,
        L5,
        L6,
        L7,
        Custom
      };
    
      Jet() : 
        fAlpha(0), fBeta(0), fMatchedMCFlavor(0),
        fJetProbabilityBJetTagsDisc(0), fJetBProbabilityBJetTagsDisc(0),
        fSimpleSecondaryVertexBJetTagsDisc(0), fSimpleSecondaryVertexHighEffBJetTagsDisc(0),
        fSimpleSecondaryVertexHighPurBJetTagsDisc(0), fCombinedSecondaryVertexBJetTagsDisc(0),
        fCombinedSecondaryVertexMVABJetTagsDisc(0), fTrackCountingHighEffBJetTagsDisc(0),
        fTrackCountingHighPurBJetTagsDisc(0), fSoftMuonBJetTagsDisc(0),
        fSoftMuonByIP3dBJetTagsDisc(0), fSoftMuonByPtBJetTagsDisc(0),
        fSoftElectronByIP3dBJetTagsDisc(0), fSoftElectronByPtBJetTagsDisc(0),
        fGhostTrackBJetTagsDisc(0),
        fL1OffsetCorrectionScale(0), fJetArea(0),
        fL2RelativeCorrectionScale(0), fL3AbsoluteCorrectionScale(0),
        fL4EMFCorrectionScale(0), fL5FlavorCorrectionScale(0), fL6LSBCorrectionScale(0),
        fL7PartonCorrectionScale(0),
        fCustomCorrectionScale(0) {}
      Jet(Double_t px, Double_t py, Double_t pz, Double_t e) : 
        fRawMom(FourVector(px,py,pz,e)),
        fAlpha(0), fBeta(0), fMatchedMCFlavor(0),
        fJetProbabilityBJetTagsDisc(0), fJetBProbabilityBJetTagsDisc(0),
        fSimpleSecondaryVertexBJetTagsDisc(0), fSimpleSecondaryVertexHighEffBJetTagsDisc(0),
        fSimpleSecondaryVertexHighPurBJetTagsDisc(0), fCombinedSecondaryVertexBJetTagsDisc(0),
        fCombinedSecondaryVertexMVABJetTagsDisc(0), fTrackCountingHighEffBJetTagsDisc(0),
        fTrackCountingHighPurBJetTagsDisc(0), fSoftMuonBJetTagsDisc(0),
        fSoftMuonByIP3dBJetTagsDisc(0), fSoftMuonByPtBJetTagsDisc(0),
        fSoftElectronByIP3dBJetTagsDisc(0), fSoftElectronByPtBJetTagsDisc(0),
        fGhostTrackBJetTagsDisc(0),
        fL1OffsetCorrectionScale(0), fJetArea(0),
        fL2RelativeCorrectionScale(0), fL3AbsoluteCorrectionScale(0),
        fL4EMFCorrectionScale(0), fL5FlavorCorrectionScale(0), fL6LSBCorrectionScale(0),
        fL7PartonCorrectionScale(0),
        fCustomCorrectionScale(0) {}

      Double_t      Alpha()                       const { return fAlpha;                        }
      Double_t      Beta()                        const { return fBeta;                         }
      Double_t      CombinedSecondaryVertexBJetTagsDisc()          const 
                      { return fCombinedSecondaryVertexBJetTagsDisc;    } 
      Double_t      CombinedSecondaryVertexMVABJetTagsDisc()       const 
                      { return fCombinedSecondaryVertexMVABJetTagsDisc; }
      Double_t      CombinedCorrectionScale()     const;
      Double_t      CustomCorrectionScale()       const { return fCustomCorrectionScale;        }
      void          DisableCorrection(ECorr c)          { fCorrections.ClearBit(c); ClearMom(); }
      void          DisableCorrections()                { fCorrections.Clear(); ClearMom();     }
      void          EnableCorrection(ECorr c)           { fCorrections.SetBit(c); ClearMom();   }
      Bool_t        CorrectionActive(ECorr c)     const { return fCorrections.TestBit(c);       }
      const BitMask8 &Corrections()               const { return fCorrections;                  }
      Double_t      JetProbabilityBJetTagsDisc()                   const 
                      { return fJetProbabilityBJetTagsDisc;     }
      Double_t      JetBProbabilityBJetTagsDisc()                  const 
                      { return fJetBProbabilityBJetTagsDisc;    }
      Int_t         MatchedMCFlavor()             const { return fMatchedMCFlavor;           }
      virtual Jet  *MakeCopy()                    const { return new Jet(*this);             }
      virtual 
      UInt_t        NConstituents()               const { return 0;                          }
      UInt_t        N()                           const { return NConstituents();            }
      Double_t      L1OffsetCorrectionScale()     const { return fL1OffsetCorrectionScale;   }
      Double_t      JetArea()                     const { return fJetArea;   }
      Double_t      L2RelativeCorrectionScale()   const { return fL2RelativeCorrectionScale; }
      Double_t      L3AbsoluteCorrectionScale()   const { return fL3AbsoluteCorrectionScale; }
      Double_t      L4EMFCorrectionScale()        const { return fL4EMFCorrectionScale;      }
      Double_t      L5FlavorCorrectionScale()     const { return fL5FlavorCorrectionScale;   }
      Double_t      L6LSBCorrectionScale()        const { return fL6LSBCorrectionScale;      }
      Double_t      L7PartonCorrectionScale()     const { return fL7PartonCorrectionScale;   }
      EObjType      ObjType()                     const { return kJet;                       }      
      Double_t      SimpleSecondaryVertexBJetTagsDisc()            const 
                      { return fSimpleSecondaryVertexBJetTagsDisc; }
      Double_t      SimpleSecondaryVertexHighEffBJetTagsDisc()            const 
                      { return fSimpleSecondaryVertexHighEffBJetTagsDisc; }
      Double_t      SimpleSecondaryVertexHighPurBJetTagsDisc()            const 
                      { return fSimpleSecondaryVertexHighPurBJetTagsDisc; }                      
      Double_t      SoftMuonBJetTagsDisc()                         const 
                      { return fSoftMuonBJetTagsDisc;              }
      Double_t      SoftMuonByIP3dBJetTagsDisc()                     const 
                      { return fSoftMuonByIP3dBJetTagsDisc;          }
      Double_t      SoftMuonByPtBJetTagsDisc()                     const 
                      { return fSoftMuonByPtBJetTagsDisc;          }
      Double_t      SoftElectronByIP3dBJetTagsDisc()                     const 
                      { return fSoftElectronByIP3dBJetTagsDisc;          }
      Double_t      SoftElectronByPtBJetTagsDisc()                     const 
                      { return fSoftElectronByPtBJetTagsDisc;          }
      Double_t      TrackCountingHighEffBJetTagsDisc()             const 
                      { return fTrackCountingHighEffBJetTagsDisc;  }
      Double_t      TrackCountingHighPurBJetTagsDisc()             const 
                      { return fTrackCountingHighPurBJetTagsDisc;  }
      Double_t      GhostTrackBJetTagsDisc()                       const 
                      { return fGhostTrackBJetTagsDisc; }                      
      FourVectorM   RawMom()                      const { return fRawMom.V();                }
      Double_t      SigmaEta()                    const { return fSigmaEta;                  }
      Double_t      SigmaPhi()                    const { return fSigmaPhi;                  }
      void          SetAlpha(Double_t val)              { fAlpha = val;                      }
      void          SetBeta(Double_t val)               { fBeta  = val;                      } 
      void          SetSigmaEta(Double_t val)           { fSigmaEta = val;                   }
      void          SetSigmaPhi(Double_t val)           { fSigmaPhi = val;                   }
      void          SetCorrections(const BitMask8 &cor) { fCorrections = cor;                }
      void          SetCombinedSecondaryVertexBJetTagsDisc(Double_t d) 
                      { fCombinedSecondaryVertexBJetTagsDisc = d;    }
      void          SetCombinedSecondaryVertexMVABJetTagsDisc(Double_t d) 
                      { fCombinedSecondaryVertexMVABJetTagsDisc = d; }
      void          SetJetProbabilityBJetTagsDisc(Double_t d)  
                      { fJetProbabilityBJetTagsDisc = d;     }
      void          SetJetBProbabilityBJetTagsDisc(Double_t d) 
                      { fJetBProbabilityBJetTagsDisc = d;    }
      void          SetRawMom(const FourVectorM &mom) { fRawMom = mom; ClearMom();           }
      void          SetMatchedMCFlavor(Int_t flavor)  { fMatchedMCFlavor = flavor;           }
      void          SetL1OffsetCorrectionScale(Double_t s )   
                      { fL1OffsetCorrectionScale = s; ClearMom(); }
      void          SetJetArea(Double_t a) { fJetArea = a; }
      void          SetL2RelativeCorrectionScale(Double_t s )   
                      { fL2RelativeCorrectionScale = s; ClearMom(); }
      void          SetL3AbsoluteCorrectionScale(Double_t s )   
                      { fL3AbsoluteCorrectionScale = s; ClearMom(); }
      void          SetL4EMFCorrectionScale(Double_t s )        
                      { fL4EMFCorrectionScale = s; ClearMom();      }
      void          SetL5FlavorCorrectionScale(Double_t s )     
                      { fL5FlavorCorrectionScale = s; ClearMom();   }
      void          SetL6LSBCorrectionScale(Double_t s )   
                      { fL6LSBCorrectionScale = s; ClearMom(); }
      void          SetL7PartonCorrectionScale(Double_t s )     
                      { fL7PartonCorrectionScale = s; ClearMom();   }
      void          SetCustomCorrectionScale(Double_t s)        
                      { fCustomCorrectionScale = s; ClearMom(); }
      void          SetSimpleSecondaryVertexBJetTagsDisc(Double_t d) 
                      { fSimpleSecondaryVertexBJetTagsDisc = d;     }
      void          SetSimpleSecondaryVertexHighEffBJetTagsDisc(Double_t d) 
                      { fSimpleSecondaryVertexHighEffBJetTagsDisc = d;     }
      void          SetSimpleSecondaryVertexHighPurBJetTagsDisc(Double_t d) 
                      { fSimpleSecondaryVertexHighPurBJetTagsDisc = d;     }                      
      void          SetSoftMuonBJetTagsDisc(Double_t d)     { fSoftMuonBJetTagsDisc = d;     }
      void          SetSoftMuonByIP3dBJetTagsDisc(Double_t d) { fSoftMuonByIP3dBJetTagsDisc = d; }
      void          SetSoftMuonByPtBJetTagsDisc(Double_t d) { fSoftMuonByPtBJetTagsDisc = d; }
      void          SetSoftElectronByIP3dBJetTagsDisc(Double_t d) { fSoftElectronByIP3dBJetTagsDisc = d; }
      void          SetSoftElectronByPtBJetTagsDisc(Double_t d) { fSoftElectronByPtBJetTagsDisc = d; }
      void          SetTrackCountingHighEffBJetTagsDisc(Double_t d) 
                      { fTrackCountingHighEffBJetTagsDisc = d;      }
      void          SetTrackCountingHighPurBJetTagsDisc(Double_t d) 
                      { fTrackCountingHighPurBJetTagsDisc = d;      }
      void          SetGhostTrackBJetTagsDisc(Double_t d) { fGhostTrackBJetTagsDisc = d; }                      

    protected:
      void          GetMom()                   const;

      Vect4M        fRawMom;                                 //uncorrected four momentum of jet
      Double32_t    fAlpha;         	                     //[0,0,14]jet vertex alpha variable
      Double32_t    fBeta;         	                     //[0,0,14]jet vertex beta variable
      Int_t         fMatchedMCFlavor;                        //[0,0,14]pdg of matched quark flavor
      Double32_t    fSigmaEta;                               //[0,0,14]sqrt(etaetaMoment)
      Double32_t    fSigmaPhi;                               //[0,0,14]sqrt(phiphiMoment)
      Double32_t    fJetProbabilityBJetTagsDisc;             //[0,0,14]discriminants b-tagging algos
      Double32_t    fJetBProbabilityBJetTagsDisc;            //[0,0,14]discriminants b-tagging algos
      Double32_t    fSimpleSecondaryVertexBJetTagsDisc;      //[0,0,14]discriminants b-tagging algos
      Double32_t    fSimpleSecondaryVertexHighEffBJetTagsDisc; //[0,0,14]discriminants b-tagging algos
      Double32_t    fSimpleSecondaryVertexHighPurBJetTagsDisc; //[0,0,14]discriminants b-tagging algos      
      Double32_t    fCombinedSecondaryVertexBJetTagsDisc;    //[0,0,14]discriminants b-tagging algos
      Double32_t    fCombinedSecondaryVertexMVABJetTagsDisc; //[0,0,14]discriminants b-tagging algos
      Double32_t    fTrackCountingHighEffBJetTagsDisc;       //[0,0,14]discriminants b-tagging algos
      Double32_t    fTrackCountingHighPurBJetTagsDisc;       //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftMuonBJetTagsDisc;                   //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftMuonByIP3dBJetTagsDisc;             //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftMuonByPtBJetTagsDisc;               //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftElectronByIP3dBJetTagsDisc;         //[0,0,14]discriminants b-tagging algos
      Double32_t    fSoftElectronByPtBJetTagsDisc;           //[0,0,14]discriminants b-tagging algos
      Double32_t    fGhostTrackBJetTagsDisc;                 //[0,0,14]discriminants b-tagging algos            
      Double32_t    fL1OffsetCorrectionScale;                //[0,0,14]L1 correction scale
      Double32_t    fJetArea;                                //[0,0,14]infrared safe jet area
      Double32_t    fL2RelativeCorrectionScale;              //[0,0,14]L2 correction scale
      Double32_t    fL3AbsoluteCorrectionScale;              //[0,0,14]L3 correction scale
      Double32_t    fL4EMFCorrectionScale;                   //[0,0,14]L4 correction scale
      Double32_t    fL5FlavorCorrectionScale;                //[0,0,14]L5 correction scale
      Double32_t    fL6LSBCorrectionScale;                   //[0,0,14]L7 correction scale
      Double32_t    fL7PartonCorrectionScale;                //[0,0,14]L7 correction scale
      Double32_t    fCustomCorrectionScale;                  //[0,0,14]custom correction scale
      BitMask8      fCorrections;                            //mask of corrections to be applied

    ClassDef(Jet, 6) // Jet class
  };
}

//--------------------------------------------------------------------------------------------------
inline Double_t mithep::Jet::CombinedCorrectionScale() const
{
  // compute combined correction scale from all enabled corrections
  Double_t scale = 1.0;

  if (CorrectionActive(L1))
    scale *= fL1OffsetCorrectionScale;

  if (CorrectionActive(L2))
    scale *= fL2RelativeCorrectionScale;
    
  if (CorrectionActive(L3))
    scale *= fL3AbsoluteCorrectionScale;
  
  if (CorrectionActive(L4))
    scale *= fL4EMFCorrectionScale;
    
  if (CorrectionActive(L5))
    scale *= fL5FlavorCorrectionScale;
    
  if (CorrectionActive(L7))
    scale *= fL7PartonCorrectionScale;
    
  if (CorrectionActive(Custom))
    scale *= fCustomCorrectionScale;

  return scale;
}

//--------------------------------------------------------------------------------------------------
inline void mithep::Jet::GetMom() const
{
  // Get raw momentum values from stored values and apply all enabled corrections.

  fCachedMom.SetCoordinates(fRawMom.Pt(),fRawMom.Eta(),fRawMom.Phi(),fRawMom.M()); 

  fCachedMom *= CombinedCorrectionScale();

}
#endif
