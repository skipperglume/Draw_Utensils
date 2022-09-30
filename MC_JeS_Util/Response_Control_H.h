#ifndef  Response_Control_H
#define  Response_Control_H 

#include <iostream>
#include <vector>
#include <fstream>


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

class Response_vs_E_true {
public:
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
    std::vector<float> *pt = 0;
    std::vector<float> *jet_eta; //jet eta
    std::vector<float>* pt_true;
    std::vector<float>* jet_area;
    std::vector<float> *jet_E;
    std::vector<float> *jet_true_E;
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


    unsigned N_Jets;
    Response_vs_E_true();
    TChain* Set_Up_TChain(std::string path_to_files, std::string TTree_name);
    void Response_Control();
    char * FSTCA(std::string & name);
    char * From_String_To_Char_Array( std::string & name);
    bool is_file_exist(const char *fileName);
};
Response_vs_E_true::Response_vs_E_true(){
    N_Jets =0;
}
char * Response_vs_E_true::From_String_To_Char_Array( std::string & name){
    char * char_name[500];
    for (int i =0; i < name.size();i++){
        //cout<<name.at(i);
        char_name[i] = & name.at(i);
    }
    
    return (*char_name);
}

char * Response_vs_E_true::FSTCA(std::string & name){
    return From_String_To_Char_Array(  name);
}
bool Response_vs_E_true::is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    bool exists = infile.good();
    return exists;
}
#endif
