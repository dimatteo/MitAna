#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TEnv.h>
#include <TString.h>
#include <TSystem.h>
#include <TRegexp.h>
#include <TROOT.h>
#include <TFile.h>
#include <TClass.h>
#include <TClassTable.h>
#include <TInterpreter.h>
#include <TRandom3.h>
#include <TError.h>
#endif

void sayHello     ();
void setIncludes  ();
void loadLibraries(const char *libpattern="libMitAna*.so");
void loadmylib    (const char *name);
void loadmylib    (const char *pkgname, const char *subpkgname);
void loadextlib   (const char *name);
void loadextlib   (const char *pkgname, const char *subpkgname);

//__________________________________________________________________________________________________

void setRootEnv()
{
  // automatically restore gDirectory
  TDirectory::TContext context(0);

  // set a better default random generator
  delete gRandom;
  gRandom = new TRandom3;
  gRandom->SetSeed(0);

  // customizing the MIT analysis framework things
  setIncludes();
  loadLibraries();
  loadmylib("libMitCommonMathTools.so");
}

void sayHello()
{
  // have a friendly welcome message
  if (gClassTable->GetID("mithep::Particle") >= 0)
    ::Info("setRootEnv", "Welcome to Bambu! Loaded default libraries.\n");
  else
    ::Info("setRootEnv", "Ooops, at least one essential library did not load....\n");
}

void setIncludes()
{
  if (gSystem->Getenv("CMSSW_VERSION")) {
    TString str = gSystem->GetMakeSharedLib();
    if (str.Contains("-m32")==0 && str.Contains("-m64")==0) {
      str.ReplaceAll("g++", "g++ -m32");
      gSystem->SetMakeSharedLib(str);
    }
  }
  printf(" Make Shared Library option: %s\n",gSystem->GetMakeSharedLib());

  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  gSystem->AddIncludePath("-I$CMSSW_RELEASE_BASE/src/");
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/MitAna/TreeMod/interface");
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/MitAna/macros");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_RELEASE_BASE"))+"/src/");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+
			       "/src/MitAna/TreeMod/interface");
  gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/MitAna/macros");
  gROOT->SetMacroPath(TString(gROOT->GetMacroPath())
                      +TString(gSystem->Getenv("CMSSW_BASE"))+"/src/MitAna/macros");
}

void loadLibraries(const char *libpattern)
{
  TString libstr(Form("%s/lib/%s",gSystem->Getenv("CMSSW_BASE"),gSystem->Getenv("SCRAM_ARCH")));

  void *dir = gSystem->OpenDirectory(libstr.Data());
  TRegexp re(libpattern, kTRUE);
  TRegexp reignore("libMitAnalysis*.so", kTRUE);

  while (const char *direntry=gSystem->GetDirEntry(dir) ) {
    TString sdirentry(direntry);
    if (sdirentry.Index(re) == kNPOS)
      continue;
    if (sdirentry.Index(reignore) != kNPOS)
      continue;
    Int_t len = strlen(direntry)-3;
    if (len<=0)
      continue;
    char *tmpstr = new char[len+1];
    for (Int_t i=0;i<len;i++)
      tmpstr[i]=direntry[i];
    tmpstr[len]='\0';

    // Check whether already loaded
    if (gInterpreter->IsLoaded(tmpstr)) {
      if (gDebug)
        Warning("setRootEnv","Trying to load \"%s\", but it is already loaded", tmpstr);
    }
    else {

      // Here is where we load the library
      if (gSystem->Load(tmpstr)<0)
        gROOT->Error("setRootEnv", "could not load \"%s\" for use in ACLiC", tmpstr);
      else {
	if (gDebug)
	  Info("setRootEnv","Loaded \"%s\" for use in ACLiC", tmpstr);
      }

    }
    delete[] tmpstr;
  }

  gSystem->FreeDirectory(dir);
}

void loadmylib(const char *name)
{
  TString libstr(Form("%s/lib/%s/%s",
		      gSystem->Getenv("CMSSW_BASE"),gSystem->Getenv("SCRAM_ARCH"),name));

  Int_t slevel = gErrorIgnoreLevel;
  gErrorIgnoreLevel = kFatal;

  // Load here
  Int_t suc = gSystem->Load(libstr);

  gErrorIgnoreLevel = slevel;
  
  if (suc<0) {
    gROOT->Error("loadmylib", "could not load \"%s\" for use in ACLiC", libstr.Data());
  } else {
    if (gDebug)
      Info("loadmylib","Loaded \"%s\" for use in ACLiC", name);
  }
}

void loadmylib(const char *pkgname, const char *subpkgname)
{
  loadmylib(Form("lib%s%s.so", pkgname, subpkgname));
}

void loadextlib(const char *name)
{
  TString libstr(Form("%s/external/%s/lib/%s",
		      gSystem->Getenv("CMSSW_BASE"),gSystem->Getenv("SCRAM_ARCH"),name));

  Int_t slevel = gErrorIgnoreLevel;
  gErrorIgnoreLevel = kFatal;

  // Load here
  Int_t suc = gSystem->Load(libstr);

  gErrorIgnoreLevel = slevel;
  
  // Deal with errors and messages
  if (suc<0) {
    gROOT->Error("loadextlib", "could not load \"%s\" for use in ACLiC", libstr.Data());
  } else {
    if (gDebug)
      Info("loadmylib","Loaded \"%s\" for use in ACLiC", name);
  }
}

void loadextlib(const char *pkgname, const char *subpkgname)
{
  loadextlib(Form("lib%s%s.so", pkgname, subpkgname));
}
