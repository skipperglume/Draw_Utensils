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
// vector<double> NPVTerm = {0.135, 0.002, 0.068, -0.029, 0.072, 0.070, 0.407, -0.220, 0.024, 0.349, 0.085, 0.056};
vector<double> NPVTerm =    {  0.030, 0.002, 0.067, -0.026, 0.076, 0.073, 0.406, -0.220, 0.021, 0.344, 0.087, 0.032};
// vector<double> MuTerm = {0.046, -0.009, -0.037, -0.015, -0.048, -0.073, -0.288, 0.096, -0.040, -0.206, -0.040, 0.032};
vector<double> MuTerm =     {  -0.005, -0.008, -0.035, -0.016, -0.050, -0.073, -0.291, 0.096, -0.039, -0.205, -0.043, 0.028};
vector<double> ResidualAbsEtaBins = { 0, 0.9, 1.2, 1.5, 1.8, 2.4, 2.8, 3.2, 3.5, 4.0, 4.3, 6.0 };

// string Term_Name = "NPV";
string Term_Name = "Mu";


template <typename T>
void Print_Vector_Line(vector<T> &a){
    cout<<"\n";
    for(int i=0; i < a.size(); i++){
        cout<< a[i]<<"; ";
    }
    cout<<"\n";
    return;
}
char * From_String_To_Char_Array( string  name){
    char * char_name[500];
    for (int i =0; i < name.size();i++){
        //cout<<name.at(i);
        char_name[i] = & name.at(i);
    }
    
    return (*char_name);
}


vector<double> computeoffsets(vector<double> etaBins, vector<double> term){
  vector <double> offset;
  offset.push_back(term.at(0));  
  for(unsigned int i=1; i<etaBins.size();++i){
    double espace = etaBins.at(i)-etaBins.at(i-1);
    double ioffs = offset.at(i-1)+term.at(i)*espace;
    offset.push_back(ioffs);
  }
  return offset;
}



#endif