#include "./P_H.h"
#include "TTree.h"
#include "TH1F.h"
#include "TProfile.h"
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
#include "TLatex.h"
#include "TCanvas.h"

// #include "./Instances_H.h"

// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TTree.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TH1F.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TH2F.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TList.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TROOT.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TKey.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TChain.h"
bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    bool exists = infile.good();
    return exists;
}


TChain* Set_Up_TChain(string path_to_files,string TTree_name, TChain* ch_p){

    

    string str;
    ifstream infile ;
    // vector <string> paths_to_ttrees ;
    infile.open(FSTCA(path_to_files));
    while(!infile.eof()){
        getline(infile,str);
        // paths_to_ttrees.push_back(str);
        if(is_file_exist(FSTCA(str))){
            // cout<<"FILE EXISTS: "<<str<<"\n\n";
            ch_p->Add(FSTCA(str));
        }
        else { //cout<<"ERROR FILE DOES NOT EXIST: "<<str<<"\n\n"; 
        }
            
    }
    infile.close();
    return ch_p;
}
// mc20a: Enrtries: 215258386 | 215258386 ; N Jets: 58213383
// mc20d Enrtries: 
// mc20e Enrtries: 

// TH2D* TH2D_res_vs_E(TChain* ch ){



//     return result;
    
// }
std::vector<double> ComputeOffsets(std::vector<double> etaBins, std::vector<double> term)  {
        vector<double> offset;
        offset.push_back(term.at(0));  
        for(unsigned int i=1; i<etaBins.size();++i){
            double espace = etaBins.at(i)-etaBins.at(i-1);
            double ioffs = offset.at(i-1)+term.at(i)*espace;
            offset.push_back(ioffs);
        }
        return offset;
}
double Interpolation (std::vector<double> etaBins, std::vector<double> term, std::vector<double> offset, Float_t eta)  {
        double correction=0;
        //  std::cout<<"eta : "<<eta<<std::endl;
        for(unsigned int i=0; i<(etaBins.size()-1);++i){
            if (eta >= etaBins.at(i) && eta < etaBins.at(i+1)){
            correction = offset.at(i) + (eta-etaBins.at(i))*term.at(i+1); // computing value of the linear function at bin i for a given value of eta
            //  std::cout<<"inside interpolation if"<<std::endl;
            break;
            }
        }
        return correction;      
    }
    
float correction1D(float pt, float eta , float mu, float NPV, vector<double> &NPVTerm,vector<double> &MuTerm,vector<double> &ResidualAbsEtaBins )  {
        std::vector<double> NPVoffset;
        std::vector<double> Muoffset;           
        Double_t corr1D = 0.0;
        Double_t NPVtermAtEta, MutermAtEta;
        NPVoffset = ComputeOffsets(ResidualAbsEtaBins,NPVTerm);
        Muoffset = ComputeOffsets(ResidualAbsEtaBins,MuTerm);
        NPVtermAtEta = Interpolation(ResidualAbsEtaBins,NPVTerm,NPVoffset,abs(eta ));
        MutermAtEta = Interpolation(ResidualAbsEtaBins,MuTerm,Muoffset,abs(eta));
        corr1D = NPVtermAtEta*(NPV-1)+MutermAtEta*mu;
        return corr1D;

    }
    
float correctedPt1D(float pt, float eta, float area, float rho, float mu, float NPV, vector<double> &NPVTerm,vector<double> &MuTerm,vector<double> &ResidualAbsEtaBins   )  {
      float areaCorr; 
      areaCorr = area*rho*1.0;
            
      float calibration1D = correction1D(pt - areaCorr , eta, mu, NPV, NPVTerm, MuTerm, ResidualAbsEtaBins);  

      return pt - areaCorr - calibration1D;      
    }
float correctionFactor1D(const float pt, const  float eta, const  float area, const  float rho, const  float mu, const  float NPV, vector<double> &NPVTerm,vector<double> &MuTerm,vector<double> &ResidualAbsEtaBins)  {
      //std::cout<<"m_useRho = "<<m_useRho<<std::endl;
      // std::cout<<"1D\n";
      
      
      
      return correctedPt1D(pt,eta,area,rho,mu,NPV,NPVTerm,MuTerm,ResidualAbsEtaBins)/pt;
}
/*
float correctionFactorArea(const float pt, const  float eta, const  float area, const  float rho, const  float mu, const  float NPV)  {
      //std::cout<<"m_useRho = "<<m_useRho<<std::endl;
      // std::cout<<"1D\n";
      
      
      
      return (pt -area*rho )/pt;
}
*/
// void Instances::Response_vs_E_true(){
void Response_vs_E_true(){
    Float_t eta_min,eta_max;
    TBranch* b_pt;
    TBranch* b_eta;
    TBranch* b_E;
    TBranch* b_NPV;
    TBranch* b_mu;
    TBranch* b_weight;
    TBranch* b_weight_tot;
    TBranch* b_pt_true;
    TBranch* b_jet_area;
    TBranch* b_jet_true_E;
    TBranch* b_rho;   
    vector<float> *pt = 0;
    vector<float> *jet_eta; //jet eta
    vector<float>* pt_true;
    vector<float>* jet_area;
    vector<float> *jet_E;
    vector<float> *jet_true_E;
    Int_t           NPV;
    Float_t         mu;
    Double_t        weight_tot;
    
    Float_t         rho;
    Float_t pTmuNPVcorrection=0.0, calib4=0.0, term2=0.0;
    std::vector<double> NPVTerm =    {0.040, -0.002, 0.073, -0.065, -0.001, 0.103, 0.467, -0.212, 0.051, 0.345, 0.054, 0.015};//{  0.030, 0.002, 0.067, -0.026, 0.076, 0.073, 0.406, -0.220, 0.021, 0.344, 0.087, 0.032};
    std::vector<double> MuTerm =      {-0.012, -0.007, -0.054, -0.022, -0.074, -0.098, -0.345, 0.119, -0.056, -0.234, -0.019, 0.037};//{  -0.005, -0.008, -0.035, -0.016, -0.050, -0.073, -0.291, 0.096, -0.039, -0.205, -0.043, 0.028};
    std::vector<double> ResidualAbsEtaBins = { 0, 0.9, 1.2, 1.5, 1.8, 2.4, 2.8, 3.2, 3.5, 4.0, 4.3, 6.0 };
    TChain* ch ;
    std::string TreeName = "IsolatedJet_tree";
    // string path_to_files = "/afs/cern.ch/work/d/dtimoshy/RC_main/input/files_mc20a.txt";
    std::string path_to_files = "./partial_mc20a.txt";
    
    ch = new TChain(FSTCA(TreeName));
    ch = Set_Up_TChain(path_to_files, TreeName, ch);
    // cout<<ch->GetEntries()<<endl;
    // cout<<"+I+"<<endl;
    // TH2D * TH2_response_vs_E = TH2D_res_vs_E(ch); 
      
    // TH2D* result = TH2D_res_vs_E(ch);
    
    // vector<float>* pt== 0; ;//
  



    std::string name_TH2 = "response_TH2";
    TH2D* result = new TH2D (FSTCA(name_TH2),FSTCA(name_TH2), 100, 0, 7000, 180, -1.2,  2.4);
    ch->SetBranchAddress("rho", &rho, &b_rho);
    ch->SetBranchAddress("NPV", &NPV, &b_NPV);
    ch->SetBranchAddress("R_weight", &weight_tot, &b_weight_tot);
    ch->SetBranchAddress("actualInteractionsPerCrossing", &mu, &b_mu);

    ch->SetBranchAddress("jet_ConstitPt", &pt, &b_pt);
    ch->SetBranchAddress("jet_ConstitEta", &jet_eta, &b_eta);   
    // ch->SetBranchAddress("jet_E", &jet_E, &b_E);
    // ch->SetBranchAddress("jet_true_e", &jet_true_E, &b_jet_true_E);
    
    ch->SetBranchAddress("jet_true_pt", &pt_true, &b_pt_true);
    ch->SetBranchAddress("jet_ActiveArea4vec_pt", &jet_area, &b_jet_area);
    
    
    // long long   N_Entries = ch->GetEntries();
    // cout<<ch->GetEntries()<<"\n";
    // ch->Print();
    
    
    

    
    
    
    // cout<<NPV<<"\n";
    unsigned N_Entries = ch->GetEntries();
    unsigned N_Jets = 0 ;
    for(auto ientry = 0; ientry < N_Entries/100; ientry++){ //Loop on entries
        ch->GetEntry(ientry);
        // for(int i =0 ; i < (*pt).size();i++){
        //     cout<<(*pt)[i]<<" ";
        //     cout<<(*jet_eta)[i]<<" ";
        // }
        // cout<<"\n"<<(*pt).size()<<" ";
        // cout<<(*jet_eta).size()<<" ";
        // cout<<NPV<<"\n";
        // result->Fill(jet_true_E->at(0),jet_E->at(0)/jet_true_E->at(0)  , weight_tot );
    }
    TCanvas * canv = new TCanvas("cnvs","cnvs",1600,1600);
    result->Draw("COLZ");
    canv->SaveAs("test.png");
    // cout<< "\n Numbers of jets: "<<N_Jets<<"\n";
    delete ch;
    return;
}