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

#include "../Plot_Helpers_H.h"

using namespace std;



// #####################################################################################
Int_t num_bins = 200;
Double_t low_value = -5.;
Double_t high_value = 5.0;
string variable_name = "true_eta";
// vairables are: NPV , mu , constit_pt , true_pt, rho , jet_area , constit_eta , true_eta , num_jets
string weight_name = "tot_weight";
// weight is:  tot_weight , one , weight , one_nth
// #####################################################################################
        

string histo_title_name = "ASDASD mc16a, JZ cuts;NPV;events";

string legend_name = "JZ";

vector<int> colors = {29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};
// cd Draw_Utensils/StackedPlotTool/ && root Create_stacked_plot.cxx
#endif