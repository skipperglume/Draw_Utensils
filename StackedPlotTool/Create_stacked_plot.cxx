
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

template <typename T>
void Print_Vector_Line(vector<T> &a){
    cout<<"\n";
    for(int i=0; i < a.size(); i++){
        cout<< a[i]<<"; ";
    }
    cout<<"\n";
    return;
}


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
        Histo_Stacked[i] = new TH1F(From_String_To_Char_Array(name),From_String_To_Char_Array(name),25,0.0,50.0);
        Histo_Stacked[i]->Sumw2();
    }
    
    int test_int = 100;
    
    cout<< Stack_Histi_Index(stack_tag, paths_to_ttrees[test_int])<<endl;
    cout<< paths_to_ttrees.size()<<endl;
    cout<< paths_to_ttrees[test_int]<<endl;
    vector <string> a = String_Split(paths_to_ttrees[test_int]);
    Print_Vector_Line(a);

    // 

    /*
    for (int i = 0 ; i <=  paths_to_ttrees.size()-1; i++){ 
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
    
    
    pT_weight->Write();
    pT_true_weight->Write();
    eta_weight->Write();
    eta_true_weight->Write();

    
    */
    TFile * Result = new TFile("result.root","recreate");
    for(int i=0;i<stack_tag.size();i++){
        string name = "JZ_"+to_string(i);
        Histo_Stacked[i]->Write();
    }
   
    Result->Close();


}

