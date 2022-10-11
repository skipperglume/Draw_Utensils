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
#include "TLegend.h"
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
    TBranch* b_njet;   
    std::vector<float> *pt = 0;
    std::vector<float> *jet_eta; //jet eta
    std::vector<float>* pt_true;
    std::vector<float>* jet_area;
    std::vector<float> *jet_E;
    std::vector<float> *jet_true_E;
    Int_t           NPV;
    Int_t           njet;
    Float_t         mu;
    // Double_t        weight_tot;
    Float_t        weight_tot;
    TH2F * R_vs_E_true;
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
    void Response_Control(std::string path_to_files, std::string TTree_name , int increment , std::string Step, float eta_min , float eta_max, std::string LegendName );



    void Create_Folder(std::string name);
    char * FSTCA(std::string & name);
    char * From_String_To_Char_Array( std::string & name);
    bool is_file_exist(const char *fileName);



    std::vector<double> ComputeOffsets(std::vector<double> etaBins, std::vector<double> term) ;
    double Interpolation (std::vector<double> etaBins, std::vector<double> term, std::vector<double> offset, Float_t eta) ;
    float correction1D(float pt, float eta , float mu, float NPV) ;
    float correctedPt1D(float pt, float eta, float area, float rho, float mu, float NPV );
    float correctionFactor(const float pt, const  float eta, const  float area, const  float rho, const  float mu, const  float NPV)  ;


    float Reco_Factor(float pt,float eta,float area , float rho , float mu, int NPV);
    float Area_Factor(float pt,float eta,float area , float rho , float mu, int NPV);
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

std::vector<double> Response_vs_E_true::ComputeOffsets(std::vector<double> etaBins, std::vector<double> term) {
    std::vector<double> offset;
    offset.push_back(term.at(0));  
    for(unsigned int i=1; i<etaBins.size();++i){
        double espace = etaBins.at(i)-etaBins.at(i-1);
        double ioffs = offset.at(i-1)+term.at(i)*espace;
        offset.push_back(ioffs);
    }
    return offset;
}

double Response_vs_E_true::Interpolation (std::vector<double> etaBins, std::vector<double> term, std::vector<double> offset, Float_t eta) {
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
float Response_vs_E_true::correction1D(float pt, float eta , float mu, float NPV)  {
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
    
float Response_vs_E_true::correctedPt1D(float pt, float eta, float area, float rho, float mu, float NPV ) {
    float areaCorr; 
    areaCorr = area*rho*1.0;        
    float calibration1D = correction1D(pt - areaCorr , eta, mu, NPV);  
    return pt - areaCorr - calibration1D;      
}

float Response_vs_E_true::correctionFactor(const float pt, const  float eta, const  float area, const  float rho, const  float mu, const  float NPV)  {
    //std::cout<<"m_useRho = "<<m_useRho<<std::endl;
    // std::cout<<"1D\n";
    return correctedPt1D(pt,eta,area,rho,mu,NPV)/pt;
}
#endif
