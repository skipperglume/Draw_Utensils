
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

#include "Stack_H.h"

using namespace std;







bool BOOL_exists_file (const string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

vector <string> String_Split(const string str, const char delimiter = '/'){
    vector <string> substrings = {};
    string temp_str =  "";
    for (int i = 0; i < str.size(); i++){
        if(str[i] == delimiter){
            substrings.push_back(temp_str);
            temp_str = "";
        }
        else temp_str+=str[i];
    }
    return substrings;

}

int Stack_Histi_Index(const vector<string> & vstr, const string path, char delimeter = '/',int n=-1, int t=-1){

    vector <string> sub_string = String_Split(path);
    string temp_str={};
    if(n==-1){
        temp_str = sub_string[sub_string.size()-1];
    }
    else 
        temp_str = sub_string[n];
    
    for(int i = 0 ; i < vstr.size(); i++ ){
        if (FindSubString(temp_str, vstr[i])){
            cout<< vstr[i]<<endl;
            return i;
        }
            
    }
    // 

    cout<<"INDEX NOT FOUND"<<endl;
    return -1;

}

void Create_stacked_plot(){
    cout<<"Welcome Aristocrat!"<<endl;
    Write_Date("Started_"+variable_name+"_"+weight_name);
    string str;
    ifstream infile ;
    vector <string> paths_to_ttrees ;
    //infile.open("List_of_ttrees.txt");
    infile.open("/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/List_of_ttrees.txt");

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
    
    
    const vector<string> stack_tag = {  "364700","364701","364702","364703","364704","364705","364706","364707","364708","364709","364710","364711","364712"}; 
    TH1F * Histo_Stacked [stack_tag.size()];
    for(int i=0;i<stack_tag.size();i++){
        string name = "JZ_"+to_string(i);
        Histo_Stacked[i] = new TH1F(From_String_To_Char_Array(name),From_String_To_Char_Array(name),num_bins , low_value, high_value);
        Histo_Stacked[i]->Sumw2();
    }
    
    int test_int = 100;
    
    cout<< Stack_Histi_Index(stack_tag, paths_to_ttrees[test_int])<<endl;
    cout<< paths_to_ttrees.size()<<endl;
    cout<< paths_to_ttrees[test_int]<<endl;
    vector <string> a = String_Split(paths_to_ttrees[test_int]);
    Print_Vector_Line(a);

    

    int index =0;
    for (int i = 0 ; i <=  paths_to_ttrees.size()-1; i++){ 
        TFile* FILE_TO_TTREE = new TFile(From_String_To_Char_Array(paths_to_ttrees[i]),"read");
        cout<< "\n\n Processing file: "<<paths_to_ttrees[i]<<"\n";
        index = Stack_Histi_Index(stack_tag, paths_to_ttrees[i]);
        cout<<i<<"/"<<paths_to_ttrees.size()<<" : " << index<<endl;
        TTree* Tree = (TTree*) FILE_TO_TTREE->Get("IsolatedJet_tree");
        cout<<Tree->GetEntries()<<"\n";
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
        for(int ientry=0;ientry<Tree->GetEntries();ientry++){ 
            
            Tree->GetEntry(ientry);
            Int_t x_int=0;
            Double_t x_double=0;
            Double_t wght =0;
            // cout<<"jets num"<< pt->size()<<"NPV: "<<NPV<<endl;
            for (int jet_iter = 0; jet_iter < pt->size(); jet_iter++  ){
                //cout<< pt->at(jet_iter)<<" ";
                // tot_weight , one , weight , one_nth
                bool is_int = false;
                if (weight_name == "tot_weight")
                    wght = weight_tot;
                else if (weight_name == "one")
                    wght = 1.0;
                else if (weight_name == "weight")
                    wght = weight;
                else if (weight_name == "one_nth")
                    {wght = 1.0/((float)pt->size());/*cout<<wght<<" "<<pt->size()<<"\n";*/}
                else {cout<<"ERRROR WRONG WEIGHT\n";return -1;}

                //  vector<Float_t>* pt; //true pt    
                // Int_t           NPV;
                // Float_t         mu;
                // Double_t        weight_tot;
                // Float_t        weight;
                // std::vector<float>* jet_eta; //jet eta
                // std::vector<float>* jet_eta_true;
                // vector<Float_t>* pt_true;
                // vector<Float_t>* jet_area;
                // Float_t         rho;
                // cout<<pt->at(0)<<endl;
                // cout<<pt[0]<<endl;
                // NPV , mu , constit_pt , true_pt, rho , jet_area , constit_eta , true_eta
                if (variable_name == "NPV"){
                    is_int = true;
                    x_int = NPV;
                }
                else if (variable_name == "num_jets"){
                    is_int = true;
                    x_int = pt->size();
                }                
                else if (variable_name == "mu"){
                    x_double = mu;}
                else if (variable_name == "constit_pt"){
                    x_double = (Double_t)(pt->at(jet_iter));}
                else if (variable_name == "true_pt"){
                    x_double = (Double_t)(pt_true->at(jet_iter));}
                else if (variable_name == "constit_eta"){
                    x_double = (Double_t)(jet_eta->at(jet_iter));}
                else if (variable_name == "true_eta"){
                    x_double = (Double_t)jet_eta_true->at(jet_iter);}
                else if (variable_name == "jet_area"){
                    x_double = (Double_t)jet_area->at(jet_iter);}
                else if (variable_name == "rho"){
                    x_double = (Double_t)rho;}
                else {cout<<"ERRROR WRONG AR NAME\n";return -1;}
                
                if (is_int)
                    Histo_Stacked[index]->Fill(x_int,       wght );
                else
                    Histo_Stacked[index]->Fill(x_double,    wght );
            }
            //cout<<"\n";
            //cout<<"weight_tot: "<<weight_tot<<"\n";
                //pTtrue_weight->Fill(pt[jet_iter],weight);
            /**/
        }
        
        FILE_TO_TTREE->Close();
    }
    
    /**/

    string folder_name = "./Created_Stacked_Plots/";
    Create_Folder(folder_name);
    string name = folder_name+variable_name+"_"+weight_name+"_"+legend_name+"_"+"result.root";
    TFile * Result = new TFile(From_String_To_Char_Array(name),"recreate");
    for(int i=0;i<stack_tag.size();i++){
        string name = legend_name+"_"+to_string(i);
        Histo_Stacked[i]->Write();
    }
    
    Result->Close();
    Write_Date("Finished_"+variable_name+"_"+weight_name);


}