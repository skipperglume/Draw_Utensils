#ifndef Instances_H
#define Instances_H
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TTree.h"
#include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TH1F.h"
#include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TH2F.h"
#include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TList.h"
#include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TROOT.h"
#include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TKey.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TFile.h"
#include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TChain.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TF2.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TH3F.h"
// #include "/cvmfs/sft.cern.ch/lcg/releases/LCG_102/ROOT/6.26.04/x86_64-centos7-gcc11-opt/include/TEnv.h"
class Instances {
public:
    //Needed input variables
    TTree* Tree;
    TChain* ch ;
    TFile* file;
    TFile *f2dmaps;
    TList* map2d_pTuncalibHistList;
    TEnv* config;

    

    //Variables to be read from ntuple
    vector<float>* pt; //true pt
    vector<float>* recojet_pt; //const scale pt
    Int_t           NPV;
    Float_t         mu;
    vector<float>*  jet_area; //area
    //Double_t        rho;
    Float_t        rho;
    vector<float>* true_eta;
    //Float_t         weight;
    Double_t        weight;
    Double_t        w;
    std::vector<float>* recojet_eta; //const scale eta


    //Branches to be used
    TBranch* b_pt;
    TBranch* b_recojet_pt;
    TBranch* b_NPV;
    TBranch* b_mu;
    TBranch* b_rho;
    TBranch* b_jet_area;
    TBranch* b_true_eta;
    TBranch* b_weight;
    TBranch* b_recojet_eta;
    TBranch* b_bcid;

    Instances(); //constructor
    virtual ~Instances(); //destructor
    void Instances::is_file_exist();
    void Instances::Set_Up_TChain();
    void Instances::TH2D_res_vs_E();
    void Instances::Response_vs_E_true();
    
};

Instances::Instances(){

}
#endif