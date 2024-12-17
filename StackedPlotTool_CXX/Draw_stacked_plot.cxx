
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


vector<float>* Min_Max_Limits(TH1F* histos[], const int size){//
    vector<float>* a = new vector<float>();
    for (int  i =0; i < size ; i++){
        // a->push_back( histos[i].GetMaximum() );
        a->push_back((*(histos+i))->GetMaximum());
        
    }
    float min = a->at(0);
    float max = 0;
    for (int  i =0; i < size ; i++){
        if ( a->at(i) < min ) min = a->at(i);
        max += a->at(i);
    }
    while (!a->empty())
        a->pop_back();
        
    a->push_back(min);
    a->push_back(max);
    return a;
}

string Find_Variable_Name( const string f_str){
    string var_name = "";
    vector<string> name_V = { "NPV" , "mu" , "constit_pt" , "true_pt", "rho" , "jet_area" , "constit_eta" , "true_eta", "num_jets" };
    for ( string strng : name_V  ){
        var_name = (FindSubString(f_str, strng)) ? strng : "";
        if (var_name.size()!=0) return var_name;
    }

    return var_name;
}

string Find_Weight_Name( const string f_str){
    string var_name = "";
    vector<string> name_V = { "tot_weight" , "one" , "weight" , "one_nth" };
    for ( string strng : name_V  ){
        var_name = (FindSubString(f_str, strng)) ? strng : "";
        if (var_name.size()!=0) return var_name;
    }

    return var_name;
}

string Get_Main_Name(string path){
    string name="";
    int start = -1 ;
    for (int pos = 0 ; pos < path.size(); pos++ ){
        start = (path[pos] == '/') ?  pos : start;
    }
    for (int pos = start+1 ; pos < path.size(); pos++ ){
        name += path[pos];
    }
    return name;
}

// weight is:  tot_weight , one , weight , one_nth
void Draw_stacked_plot(){
    cout<<"Welcome Aristocrat!"<<endl;

    
    string str;
    ifstream infile ;
    // vector <string> paths_to_ttrees ;
    //infile.open("List_of_ttrees.txt");
    
    const vector<string> stack_tag = {  "364700","364701","364702","364703","364704","364705","364706","364707","364708","364709","364710","364711","364712"}; 
    TH1F * Histo_Stacked [stack_tag.size()];
    string file_name = "./Created_Stacked_Plots/constit_pt_tot_weight_JZ_result.root";
    cout<<Get_Main_Name(file_name)<<"\n";
    TFile * Result = new TFile(FSTCA(file_name),"read");
    variable_name = Find_Variable_Name(  Get_Main_Name(file_name)  );
    weight_name = Find_Weight_Name(  Get_Main_Name(file_name)  );
    cout<<"Variable is: " << variable_name<<endl;
    cout<<"Weight is: " << weight_name<<endl;
    
    /*
    vector<string> testing_vals = {"constit_eta_tot_weight_JZ_result.root", "mu_tot_weight_JZ_result.root",   "rho_tot_weight_JZ_result.root",
    "constit_pt_one_JZ_result.root",          "NPV_tot_weight_JZ_result.root",  "true_eta_tot_weight_JZ_result.root",
    "constit_pt_tot_weight_JZ_result.root",   "num_jets_one_JZ_result.root",    "true_pt_tot_weight_JZ_result.root"};
    for ( string TEST : testing_vals){
        cout<< TEST<<"\n";
        cout<< Find_Variable_Name(  Get_Main_Name(TEST)  )<<"\n";
        cout<< Find_Weight_Name(  Get_Main_Name(TEST)  )<<"\n";

    }
    */
    



    
    for(int i=0;i<stack_tag.size();i++){
        string name = "JZ_"+to_string(i);
        Histo_Stacked[i] = (TH1F*)Result->Get(From_String_To_Char_Array(name));
    }
    Histo_Stacked[0]->ls();
    // cout<<Histo_Stacked[0]->GetNbinsX()<<endl;
    for(int i=0;i<stack_tag.size();i++){
        cout<< Histo_Stacked[i]->GetMaximum()<<endl;
    }
    cout<<"\n"<<endl;
    vector<float> * a = Min_Max_Limits( Histo_Stacked, stack_tag.size() );//
    Print_Vector_Line(*a);
    
    
    TCanvas *cst = new TCanvas("cst","stacked hists",10,10,1100,900);
    cst->SetLogy();
    THStack *hs = new THStack("hs","Stacked 1D histograms");
    cout<<a->at(0)<<"\n"<<endl;
    cout<<a->at(1)<<"\n"<<endl;
    
    // for(int i=0;i<stack_tag.size();i++){
    for(int i=stack_tag.size()-1;i>-1;i--){
        //Histo_Stacked[i]->SetFillColorAlpha(4,0.35);
        Histo_Stacked[i]->SetFillColor( colors[i % colors.size()] );
        Histo_Stacked[i]->GetXaxis()->SetRangeUser(0.00001, 10000);
        // Histo_Stacked[i]->SetMarkerStyle(21);
        //Histo_Stacked[i]->SetMarkerColor(kRed);
        Histo_Stacked[i]->SetLineColor( colors[i % colors.size()] );
        string title_name = variable_name   +" with "+weight_name+" weight " +";"+variable_name+";"+weight_name;
        Histo_Stacked[i]->SetTitle(  FSTCA(title_name));
        hs->Add(Histo_Stacked[i]);        
    }
    // Histo_Stacked[2]->SetFillColor(2);
    // Histo_Stacked[0]->Draw("bar");
    hs->SetMinimum(a->at(0));
    hs->SetMaximum(a->at(1));
    string title_name = variable_name   +" with "+weight_name+" weight " +";"+variable_name+";"+weight_name;
    hs->SetTitle(FSTCA(title_name));
    hs->Draw("bar");

    TLegend* legend = new TLegend(0.8, 0.4, .9, .9);
    for(int i=stack_tag.size()-1;i>-1;i--){
        string local_name = "";
        if ( stack_tag[i][stack_tag[i].size()-2] != '0')
            local_name = legend_name +" "+ stack_tag[i][stack_tag[i].size()-2]+stack_tag[i][stack_tag[i].size()-1];
        else if ( stack_tag[i][stack_tag[i].size()-2] == '0')
            local_name = legend_name +" "+stack_tag[i][stack_tag[i].size()-1];
        legend->AddEntry(Histo_Stacked[i], From_String_To_Char_Array(local_name), "f");
    }
    legend->Draw();

    // hs->GetYaxis()->SetRangeUser(0.0001, 10.0);
    // hs->GetYaxis()->SetLimits(0.0001, 10.0);
    // cout<<stack_tag.size()<<endl;
    string folder_name = "./Stacked_Plots/";
    Create_Folder(folder_name);
    string canvas_name = folder_name  +variable_name  + "_"+weight_name+"_" +".png";
    cst->SaveAs(FSTCA(canvas_name));
    
    Result->Close();
    

}



