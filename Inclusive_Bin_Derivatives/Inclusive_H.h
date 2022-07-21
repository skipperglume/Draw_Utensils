#ifndef CODE_H 
#define CODE_H

#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
#include <array>
#include <iterator>  
#include <utility>

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

using namespace std;


vector<float> PtBins2= { 10.0, 20.0, 30.0, 60.0, 120.0, 200.0};
vector<float> EtaBins2 = {0.0, 0.4,0.8,1.2,1.6,2.0,2.4,2.8,3.2,3.6,4.5};

vector<float> NpvBins2 = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32};
// vector<float> NpvBins2 = {2,4,30,32};

vector<float> MuBins2= {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42};
//vector<float> MuBins2= {0, 3, 39, 42};

vector<float> MuBins ;
vector<float> PtBins ;
vector<float> EtaBins;
vector<float> NpvBins;

vector<float> Config_EtaBins = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.7,2.9,3.0,3.075,3.15,3.25,3.35,3.45,3.6,3.8,4.1,4.5,4.9};
vector<float> Config_PtBins = { 10.0, 15.0, 20.0, 30.0, 60.0, 120.0, 200.0 };
vector<Int_t> Config_NpvBins = {};
vector<float> Config_MuBins = {};

// string correction = "None";
string correction = "Area";
//string correction = "1D";
//string correction = "3D";

// string PT_Dependence_On = "Mu";
string PT_Dependence_On = "NPV";

//vector<double> NPVTerm =    {0.025, -0.004, 0.057, -0.036, 0.145, 0.056, 0.479, -0.261, 0.051, 0.326, 0.032, 50951.609};
//vector<double> MuTerm =     {-0.001, -0.009, -0.020, -0.019, -0.063, -0.068, -0.324, 0.116, -0.055, -0.193, -0.011, -17788.504};

// vector<double> NPVTerm =    {-0.013, 0.007, -0.003, 0.023, -0.087, 0.030, -0.009, -0.016, -0.020, 0.011, 0.316, 2.653};
    vector<double> NPVTerm = {-0.015 , 0.008 , -0.004 , 0.017 ,  -0.081 , 0.025 , -0.004 , -0.014 , -0.019 , 0.007 , 0.202 , 332222.652}   ;

// vector<double> MuTerm =     {-0.009, 0.002, -0.004, -0.002, 0.026, -0.013, -0.000, 0.031, 0.005, -0.019, -0.126, -0.757};
    vector<double> MuTerm =   {  -0.009 ,  0.001 , -0.004 ,  0.001 , 0.023 , -0.011 , -0.001 , 0.031 , 0.004 , -0.016 , -0.060 , -96384.805};


vector<double> ResidualAbsEtaBins = { 0, 0.9, 1.2, 1.5, 1.8, 2.4, 2.8, 3.2, 3.5, 4.0, 4.3, 6.0 };

bool FindSubString(const string  str, const  string  substr){
    for(int i = 0; i < str.size(); i++){
        if(str.size()-i < substr.size())
            return false;
        if (substr[0] == str[i]){
            bool o = true;
            for(int j = 1; j < substr.size(); j++){
                if(substr[j]!=str[i+j]){
                    o = false;
                    break;
                }
            }   
            if(o){
                //cout<<i<<"\n";
                return true;    
            }
        }
        
    }
    return false;
}

// Initializes the config values of NPV and mu bins for 1d and 3d residual calibrations
void Initialize_Binning(){
    Config_NpvBins = {};
    Config_MuBins = {};
    for(int i=0; i <= 24;i++){
        Config_MuBins.push_back(3.0*i);
    }
    for(int i=0; i <= 24;i++){
        Config_MuBins.push_back(3.0*i);
    }
    for(int i=0; i <= 25;i++){
        Config_NpvBins.push_back(2*i);
    }
    return;
}

// Helping funciton to print values of vector
template <typename T>
void Print_Vector_Line(vector<T> &a){
    cout<<"\n";
    for(int i=0; i < a.size(); i++){
        cout<< a[i]<<"; ";
    }
    cout<<"\n";
    return;
}

#endif
// cd Draw_Utensils/project_derivative/ && root new_try.cxx