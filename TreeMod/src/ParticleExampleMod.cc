// $Id: ParticleExampleMod.cc,v 1.4 2008/07/03 08:22:19 loizides Exp $

#include "MitAna/TreeMod/interface/ParticleExampleMod.h"
#include <TH1D.h>
#include "MitAna/DataTree/interface/Names.h"

using namespace mithep;

ClassImp(mithep::ParticleExampleMod)

//--------------------------------------------------------------------------------------------------
ParticleExampleMod::ParticleExampleMod(const char *name, const char *title) : 
  BaseMod(name,title),
  fPartName(Names::gkGenPartBrn),
  fParticles(0),
  fPtHist(0),
  fEtaHist(0)
{
  // Constructor.
}

//--------------------------------------------------------------------------------------------------
void ParticleExampleMod::Begin()
{
  // Run startup code on the client machine. For this module, we dont
  // do anything here.
}

//--------------------------------------------------------------------------------------------------
void ParticleExampleMod::BeginRun()
{
  // Run startup code on the client machine. For this module, we dont
  // do anything here.
}

//--------------------------------------------------------------------------------------------------
void ParticleExampleMod::EndRun()
{
  // Run startup code on the client machine. For this module, we dont
  // do anything here.
}

//--------------------------------------------------------------------------------------------------
void ParticleExampleMod::Process()
{
  // Process entries of the tree. For this module, we just load
  // the branch and fill the histograms.

  LoadBranch(GetPartName());

  Int_t ents=fParticles->GetEntries();
  for(Int_t i=0;i<ents;++i) {
     GenParticle* p = fParticles->At(i);
     fPtHist->Fill(p->Pt());
     fEtaHist->Fill(p->Eta());
  }

}

//--------------------------------------------------------------------------------------------------
void ParticleExampleMod::SlaveBegin()
{
  // Run startup code on the computer (slave) doing the actual
  // analysis. Here, we typically initialize histograms and 
  // other analysis objects and request branches. For this module,
  // we request a branch of the MitTree.

  ReqBranch(GetPartName(), fParticles);

  fPtHist  = new TH1D("hPtHist",";p_{t};#",100,0.,25.);
  AddOutput(fPtHist);
  fEtaHist = new TH1D("hEtaHist",";#eta;#",160,-8.,8.);
  AddOutput(fEtaHist);
}

//--------------------------------------------------------------------------------------------------
void ParticleExampleMod::SlaveTerminate()
{
  // Run finishing code on the computer (slave) that did the
  // analysis. For this module, we dont do anything here.
}

//--------------------------------------------------------------------------------------------------
void ParticleExampleMod::Terminate()
{
  // Run finishing code on the client computer. 
  // For this module, we dont do anything here.
}
