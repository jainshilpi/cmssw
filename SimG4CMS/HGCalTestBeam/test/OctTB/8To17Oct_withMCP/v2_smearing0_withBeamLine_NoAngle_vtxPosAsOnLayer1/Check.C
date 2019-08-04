#define Check_cxx
#include "Check.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Check::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Check.C
//      root> Check t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      double sum = 0;
      for(int ii=0; ii<hgcPassiveEEEnergy->size(); ii++){

	double en = hgcPassiveEEEnergy->at(ii);
	//cout<<"en is "<<en<<endl;
	sum += en;

      }
      
      double sum_out = 0;
      for(int ii=0; ii<hgcPassiveCMSEEnergy->size(); ii++){

	double en = hgcPassiveCMSEEnergy->at(ii);
	//cout<<"en is "<<en<<endl;
	sum_out += en;

      }

      double sum_tot = sum + sum_out;
      cout<<"jentry : size : sum : sum_out : sum_tot "<<jentry<<" "<<hgcPassiveEEEnergy->size()<<" "<<sum<<" "<<sum_out<<" "<<sum_tot<<endl;
   }
}
