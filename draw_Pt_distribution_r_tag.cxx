
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
#include <array>
#include <iterator>  

#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TList.h"
#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TChain.h"
#include "TF2.h"
#include "TH3F.h"
#include "TEnv.h"

using namespace std;



bool BOOL_exists_file (const string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}
char * From_String_To_Char_Array( string & name){
    char * char_name[500];
    for (int i =0; i < name.size();i++){
        cout<<name.at(i);
        char_name[i] = & name.at(i);
    }
    
    return (*char_name);
}

void draw_Pt_distribution_r_tag(){
    cout<<"Welcome Aristocrat!"<<endl;
    string str;
    ifstream infile ;
    vector <string> paths_to_ttrees ;
    //infile.open("List_of_ttrees.txt");
    infile.open("TTrees_MC16d.txt");

    while(!infile.eof()){
        getline(infile,str);
        paths_to_ttrees.push_back(str);
        if(BOOL_exists_file(str))
            cout<<"FILE EXISTS: "<<str<<"\n\n";
        else
            cout<<"ERROR FILE DOES NOT EXIST: "<<str<<"\n\n";
    }
    infile.close();

    vector<Float_t>* pt; //true pt    
    Int_t           NPV;
    Float_t         mu;
    Double_t        weight_tot;
    Float_t        weight;
    std::vector<float>* jet_eta; //jet eta
    std::vector<float>* jet_eta_true;
    vector<Float_t>* pt_true;
    vector<Float_t>* jet_area;
    Float_t         rho;

    /*
    pTtrue_weight = new TH1F("pTtrue_weight","pTtrue weight considered",200,0.,200.);
  pTtrue = new TH1F("pTtrue","pTtrue weight not considered",200,0.,200.);
  mu_dist = new TH1F("mu","mu",munbins,mulow,muhigh);
  NPV_dist = new TH1F("NPV","NPV",NPVnbins,NPVlow,NPVhigh);
  NPV_mu = new TH2F("NPVvsMu","",munbins,mulow,muhigh,NPVnbins,NPVlow,NPVhigh);
    */
    TBranch* b_pt;
    TBranch* b_eta;
    TBranch* b_eta_true;
    TBranch* b_NPV;
    TBranch* b_mu;
    TBranch* b_weight;
    TBranch* b_weight_tot;
    TBranch* b_pt_true;
    TBranch* b_jet_area;
    TBranch* b_rho;

    
    //ch->SetBranchAddress(config->GetValue("CaloPt",""), &recojet_pt, &b_recojet_pt);
    //ch->SetBranchAddress("NPV", &NPV, &b_NPV);
    //ch->SetBranchAddress(config->GetValue("mu",""), &mu, &b_mu);
    //ch->SetBranchAddress(config->GetValue("PtDensity",""), &rho, &b_rho);
    //ch->SetBranchAddress(config->GetValue("JetArea",""), &jet_area, &b_jet_area);
    //ch->SetBranchAddress(config->GetValue("TrueEta",""), &true_eta, &b_true_eta);
    //ch->SetBranchAddress(config->GetValue("WeightBranch","weight"), &weight, &b_weight);
    //ch->SetBranchAddress(config->GetValue("CaloEta","jet_ConstitEta"), &recojet_eta, &b_recojet_eta);
    //ch->SetBranchAddress(config->GetValue("BCID","bcid"), &bcid, &b_bcid);
    
    
    TH1F * pT_weight = new TH1F("Pt_distribution","pT weight considered",200,0.,200.);
    TH1F * pT_true_weight = new TH1F("Pt_true_distribution","pt true weight considered",200,0.,200.);
    TH1F * eta_weight = new TH1F("eta_distribution","eta weight considered",100,-5.,5.);
    TH1F * eta_true_weight = new TH1F("eta_true_distribution","eta true weight considered",100,-5.,5.);


    pT_weight->Sumw2();
    pT_true_weight->Sumw2();
    eta_weight->Sumw2();
    eta_true_weight->Sumw2();

    for (int i = 0 ; i <=  paths_to_ttrees.size()-1 /* paths_to_ttrees.size() */; i++){
        TFile* FILE_TO_TTREE = new TFile(From_String_To_Char_Array(paths_to_ttrees[i]),"read");
        cout<< "\n\n Processing file: "<<paths_to_ttrees[i]<<"\n";
        TTree* Tree = (TTree*) FILE_TO_TTREE->Get("IsolatedJet_tree");
        Tree->SetBranchAddress("jet_ConstitPt", &pt, &b_pt);
        Tree->SetBranchAddress("weight_tot", &weight_tot, &b_weight_tot);
        Tree->SetBranchAddress("weight", &weight, &b_weight);
        Tree->SetBranchAddress("actualInteractionsPerCrossing", &mu, &b_mu);
        Tree->SetBranchAddress("jet_eta", &jet_eta, &b_eta);
        Tree->SetBranchAddress("jet_true_eta", &jet_eta_true, &b_eta_true);
        Tree->SetBranchAddress("jet_true_pt", &pt_true, &b_pt_true);
        Tree->SetBranchAddress("jet_ActiveArea4vec_pt", &jet_area, &b_jet_area);
        Tree->SetBranchAddress("rho", &rho, &b_rho);
        Tree->SetBranchAddress("NPV", &NPV, &b_NPV);
        for(int ientry=0;ientry<Tree->GetEntries()/10;ientry++){ 
            Tree->GetEntry(ientry);
            for (int jet_iter = 0; jet_iter < pt->size(); jet_iter++  ){
                //cout<< pt->at(jet_iter)<<" ";
                
                pT_weight->Fill(        pt->at(jet_iter), weight ) ;
                pT_true_weight->Fill(   pt_true->at(jet_iter), weight ) ;
                eta_weight->Fill(       jet_eta->at(jet_iter), weight ) ;
                eta_true_weight->Fill(  jet_eta_true->at(jet_iter), weight ) ;
            }
            //cout<<"\n";
            //cout<<"weight_tot: "<<weight_tot<<"\n";
                //pTtrue_weight->Fill(pt[jet_iter],weight);
        }
        cout<<Tree->GetEntries()<<"\n";
        FILE_TO_TTREE->Close();
    }
    TFile * Result = new TFile("result.root","recreate");
    
    pT_weight->Write();
    pT_true_weight->Write();
    eta_weight->Write();
    eta_true_weight->Write();

    Result->Close();




}

