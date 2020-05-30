/*
 Autor: Mariana Soeiro
 About: Exercicio 4 - Lista 3 (ROOT)
 
- Using the tree.root make the distribution of the total mometum [x]
- Do a histogram [x]
- Draw and save in a file [x]

 
 */

#include "TMath.h"
#include "TVector2.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TEfficiency.h"
#include "TH2F.h"


void exercicio4()
{
        // style setting
       
    printf("\n ----------- Read a Tree -----------\n");
    
    TFile *f = new TFile("tree.root");
    
    //TTree *tree = (TTree*)f->Get("tree1");
    TTree *t1 = (TTree*)f->Get("tree1");
    Float_t px, py, pz,ebeam;

    t1->SetBranchAddress("px",&px);
    t1->SetBranchAddress("py",&py);
    t1->SetBranchAddress("pz",&pz);
    t1->SetBranchAddress("ebeam",&ebeam);

    //create one histogram
    TH1F *hpxpypz  = new TH1F("hpxpypz","Distribution",100,10,10);

    //read all entries and fill the histograms
    Int_t nentries = t1->GetEntries();
    for (Int_t i=0;i<nentries;i++) {
        t1->GetEntry(i);
        if (ebeam > 150.2 || ebeam < 149.8){
        hpxpypz->Fill(TMath::Sqrt(px*py +py*py + pz*pz));
        //hpxpypz->Fill(px);
        //hpxpy->Fill(px,py);
        }
    }
        
    printf("\n ----------- Export hpxpypz -----------\n");

        TCanvas *c = new TCanvas("c1","multigraph",700,500);
        c->SetGrid();
        hpxpypz->Draw();
        c->Print("output_exercicio4.pdf");
     

}

