
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
        // cout<<name.at(i);
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

void Draw_stacked_plot(){
    cout<<"Welcome Aristocrat!"<<endl;
    string str;
    ifstream infile ;
    vector <string> paths_to_ttrees ;
    //infile.open("List_of_ttrees.txt");
    
    const vector<string> stack_tag = {  "364700","364701","364702","364703","364704","364705","364706","364707","364708","364709","364710","364711","364712"}; 
    TH1F * Histo_Stacked [stack_tag.size()];

    TFile * Result = new TFile("result.root","read");

    for(int i=0;i<stack_tag.size();i++){
        string name = "JZ_"+to_string(i);
        Histo_Stacked[i] = (TH1F*)Result->Get(From_String_To_Char_Array(name));
    }
    Histo_Stacked[0]->ls();
    cout<<Histo_Stacked[0]->GetNbinsX()<<endl;
    
    
    TCanvas *cst = new TCanvas("cst","stacked hists",10,10,700,700);
    cst->SetLogy();
    THStack *hs = new THStack("hs","Stacked 1D histograms");
    
    
    // for(int i=0;i<stack_tag.size();i++){
    for(int i=stack_tag.size()-1;i>-1;i--){
        //Histo_Stacked[i]->SetFillColorAlpha(4,0.35);
        Histo_Stacked[i]->SetFillColor( colors[i % colors.size()] );
        Histo_Stacked[i]->GetXaxis()->SetRangeUser(0.00001, 10000);
        // Histo_Stacked[i]->SetMarkerStyle(21);
        //Histo_Stacked[i]->SetMarkerColor(kRed);
        Histo_Stacked[i]->SetLineColor( colors[i % colors.size()] );
        hs->Add(Histo_Stacked[i]);        
    }
    // Histo_Stacked[2]->SetFillColor(2);
    // Histo_Stacked[0]->Draw("bar");
    hs->SetMinimum(0.00000000000000001);
    hs->SetMaximum(100000000);
    hs->SetTitle(From_String_To_Char_Array(histo_title_name));
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
    cout<<stack_tag.size();
    cst->SaveAs("stack.png");
   
    Result->Close();
    

}


