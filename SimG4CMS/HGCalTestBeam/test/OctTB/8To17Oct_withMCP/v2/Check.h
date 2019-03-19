//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jun 24 18:20:31 2017 by ROOT version 6.08/07
// from TTree HGCTB/SimHitEnergy
// found on file: TBGenSim.root
//////////////////////////////////////////////////////////

#ifndef Check_h
#define Check_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class Check {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *simHitLayEn1EE;
   vector<float>   *simHitLayEn2EE;
   vector<float>   *simHitLayEn1FH;
   vector<float>   *simHitLayEn2FH;
   vector<float>   *simHitLayEn1BH;
   vector<float>   *simHitLayEn2BH;
   Double_t        xBeam;
   Double_t        yBeam;
   Double_t        zBeam;
   Double_t        pBeam;
   vector<unsigned int> *simHitCellIdEE;
   vector<float>   *simHitCellEnEE;
   vector<unsigned int> *simHitCellIdFH;
   vector<float>   *simHitCellEnFH;
   vector<unsigned int> *simHitCellIdBH;
   vector<float>   *simHitCellEnBH;
   vector<unsigned int> *simHitCellIdBeam;
   vector<float>   *simHitCellEnBeam;
   vector<float>   *hgcPassiveEEEnergy;
   vector<string>  *hgcPassiveEEName;
   vector<int>     *hgcPassiveEEID;
   vector<float>   *hgcPassiveFHEnergy;
   vector<string>  *hgcPassiveFHName;
   vector<int>     *hgcPassiveFHID;
   vector<float>   *hgcPassiveBHEnergy;
   vector<string>  *hgcPassiveBHName;
   vector<int>     *hgcPassiveBHID;

   vector<float>   *hgcPassiveCMSEEnergy;
   vector<string>  *hgcPassiveCMSEName;
   vector<int>     *hgcPassiveCMSEID;

   // List of branches
   TBranch        *b_simHitLayEn1EE;   //!
   TBranch        *b_simHitLayEn2EE;   //!
   TBranch        *b_simHitLayEn1FH;   //!
   TBranch        *b_simHitLayEn2FH;   //!
   TBranch        *b_simHitLayEn1BH;   //!
   TBranch        *b_simHitLayEn2BH;   //!
   TBranch        *b_xBeam;   //!
   TBranch        *b_yBeam;   //!
   TBranch        *b_zBeam;   //!
   TBranch        *b_pBeam;   //!
   TBranch        *b_simHitCellIdEE;   //!
   TBranch        *b_simHitCellEnEE;   //!
   TBranch        *b_simHitCellIdFH;   //!
   TBranch        *b_simHitCellEnFH;   //!
   TBranch        *b_simHitCellIdBH;   //!
   TBranch        *b_simHitCellEnBH;   //!
   TBranch        *b_simHitCellIdBeam;   //!
   TBranch        *b_simHitCellEnBeam;   //!
   TBranch        *b_hgcPassiveEEEnergy;   //!
   TBranch        *b_hgcPassiveEEName;   //!
   TBranch        *b_hgcPassiveEEID;   //!
   TBranch        *b_hgcPassiveFHEnergy;   //!
   TBranch        *b_hgcPassiveFHName;   //!
   TBranch        *b_hgcPassiveFHID;   //!
   TBranch        *b_hgcPassiveBHEnergy;   //!
   TBranch        *b_hgcPassiveBHName;   //!
   TBranch        *b_hgcPassiveBHID;   //!

   TBranch        *b_hgcPassiveCMSEEnergy;   //!
   TBranch        *b_hgcPassiveCMSEName;   //!
   TBranch        *b_hgcPassiveCMSEID;   //!

   Check(TTree *tree=0);
   virtual ~Check();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Check_cxx
Check::Check(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TBGenSim.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("TBGenSim.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("TBGenSim.root:/HGCalTBAnalyzer");
      dir->GetObject("HGCTB",tree);

   }
   Init(tree);
}

Check::~Check()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Check::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Check::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Check::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   simHitLayEn1EE = 0;
   simHitLayEn2EE = 0;
   simHitLayEn1FH = 0;
   simHitLayEn2FH = 0;
   simHitLayEn1BH = 0;
   simHitLayEn2BH = 0;
   simHitCellIdEE = 0;
   simHitCellEnEE = 0;
   simHitCellIdFH = 0;
   simHitCellEnFH = 0;
   simHitCellIdBH = 0;
   simHitCellEnBH = 0;
   simHitCellIdBeam = 0;
   simHitCellEnBeam = 0;
   hgcPassiveEEEnergy = 0;
   hgcPassiveEEName = 0;
   hgcPassiveEEID = 0;
   hgcPassiveFHEnergy = 0;
   hgcPassiveFHName = 0;
   hgcPassiveFHID = 0;
   hgcPassiveBHEnergy = 0;
   hgcPassiveBHName = 0;
   hgcPassiveBHID = 0;

   hgcPassiveCMSEEnergy = 0;
   hgcPassiveCMSEName = 0;
   hgcPassiveCMSEID = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("simHitLayEn1EE", &simHitLayEn1EE, &b_simHitLayEn1EE);
   fChain->SetBranchAddress("simHitLayEn2EE", &simHitLayEn2EE, &b_simHitLayEn2EE);
   fChain->SetBranchAddress("simHitLayEn1FH", &simHitLayEn1FH, &b_simHitLayEn1FH);
   fChain->SetBranchAddress("simHitLayEn2FH", &simHitLayEn2FH, &b_simHitLayEn2FH);
   fChain->SetBranchAddress("simHitLayEn1BH", &simHitLayEn1BH, &b_simHitLayEn1BH);
   fChain->SetBranchAddress("simHitLayEn2BH", &simHitLayEn2BH, &b_simHitLayEn2BH);
   fChain->SetBranchAddress("xBeam", &xBeam, &b_xBeam);
   fChain->SetBranchAddress("yBeam", &yBeam, &b_yBeam);
   fChain->SetBranchAddress("zBeam", &zBeam, &b_zBeam);
   fChain->SetBranchAddress("pBeam", &pBeam, &b_pBeam);
   fChain->SetBranchAddress("simHitCellIdEE", &simHitCellIdEE, &b_simHitCellIdEE);
   fChain->SetBranchAddress("simHitCellEnEE", &simHitCellEnEE, &b_simHitCellEnEE);
   fChain->SetBranchAddress("simHitCellIdFH", &simHitCellIdFH, &b_simHitCellIdFH);
   fChain->SetBranchAddress("simHitCellEnFH", &simHitCellEnFH, &b_simHitCellEnFH);
   fChain->SetBranchAddress("simHitCellIdBH", &simHitCellIdBH, &b_simHitCellIdBH);
   fChain->SetBranchAddress("simHitCellEnBH", &simHitCellEnBH, &b_simHitCellEnBH);
   fChain->SetBranchAddress("simHitCellIdBeam", &simHitCellIdBeam, &b_simHitCellIdBeam);
   fChain->SetBranchAddress("simHitCellEnBeam", &simHitCellEnBeam, &b_simHitCellEnBeam);
   fChain->SetBranchAddress("hgcPassiveEEEnergy", &hgcPassiveEEEnergy, &b_hgcPassiveEEEnergy);
   fChain->SetBranchAddress("hgcPassiveEEName", &hgcPassiveEEName, &b_hgcPassiveEEName);
   fChain->SetBranchAddress("hgcPassiveEEID", &hgcPassiveEEID, &b_hgcPassiveEEID);
   fChain->SetBranchAddress("hgcPassiveFHEnergy", &hgcPassiveFHEnergy, &b_hgcPassiveFHEnergy);
   fChain->SetBranchAddress("hgcPassiveFHName", &hgcPassiveFHName, &b_hgcPassiveFHName);
   fChain->SetBranchAddress("hgcPassiveFHID", &hgcPassiveFHID, &b_hgcPassiveFHID);
   fChain->SetBranchAddress("hgcPassiveBHEnergy", &hgcPassiveBHEnergy, &b_hgcPassiveBHEnergy);
   fChain->SetBranchAddress("hgcPassiveBHName", &hgcPassiveBHName, &b_hgcPassiveBHName);
   fChain->SetBranchAddress("hgcPassiveBHID", &hgcPassiveBHID, &b_hgcPassiveBHID);

   fChain->SetBranchAddress("hgcPassiveCMSEEnergy", &hgcPassiveCMSEEnergy, &b_hgcPassiveCMSEEnergy);
   fChain->SetBranchAddress("hgcPassiveCMSEName", &hgcPassiveCMSEName, &b_hgcPassiveCMSEName);
   fChain->SetBranchAddress("hgcPassiveCMSEID", &hgcPassiveCMSEID, &b_hgcPassiveCMSEID);

   Notify();
}

Bool_t Check::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Check::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Check::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Check_cxx
