
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
        //cout<<name.at(i);
        char_name[i] = & name.at(i);
    }
    
    return (*char_name);
}


int Get_Bin_Of_Absolute_Value( vector<float> & etabin , float &eta ){
    for (int i = 0 ; i< etabin.size(); i++ ){
        if (abs(eta) <= etabin[i]){
            if (i == 0)
                return -1;
            else 
                return i;
        }
    }
    return -1;
}

int Get_Bin_Of_Value( vector<float> & etabin , float &eta ){
    for (int i = 0 ; i< etabin.size(); i++ ){
        if ( eta <= etabin[i]){
            if (i == 0)
                return -1;
            else 
                return i;
        }
    }
    return -1;
}


void TProfile_draw_derivative_d_pt_d_mu_over_eta(){
    cout<<"Welcome Aristocrat!"<<endl;
    string str;
    ifstream infile ;
    vector <string> paths_to_ttrees ;
    infile.open("List_of_ttrees.txt");

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
    vector<Float_t>* pt_true;
    vector<Float_t>* jet_area;
    Float_t         rho;

    TBranch* b_pt;
    TBranch* b_eta;
    TBranch* b_NPV;
    TBranch* b_mu;
    TBranch* b_weight;
    TBranch* b_weight_tot;
    TBranch* b_pt_true;
    TBranch* b_jet_area;
    TBranch* b_rho;
    
    
    vector<float> MuBins = {};
    vector<float> PtBins = { 5.0, 20.0, 30.0, 60.0, 120.0};
    //vector<float> PtBins = { 0.0, 200.0};
    vector<float> EtaBins = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.7,2.9,3.0,3.075,3.15,3.25,3.35,3.45,3.6,3.8,4.1,4.5,4.9};
    //38
    for ( int i = 0 ; i <= 72 ; i+=3 ){
        MuBins.push_back(1.0*i);
        //cout<<MuBins[i/3]<<endl;
    }
    

    
    TGraph * Pt_vs_mu[ (EtaBins.size() -1) * (PtBins.size()) ];
    TProfile * TProfile_Pt_vs_mu_binned [ (EtaBins.size() -1) * (PtBins.size()) ];
    for ( int i=1; i< EtaBins.size(); i++ ){
        for ( int j=0; j< PtBins.size(); j++ ){
            string name_str = "TGraph_Pt_VS_Mu_"+to_string( ( i - 1 ) * PtBins.size() + j +1 )+";#mu;p_{T}";
            Pt_vs_mu[ ( i - 1 ) * PtBins.size() + j ] = new TGraph();
            Pt_vs_mu[( i - 1 ) * PtBins.size() + j]->SetName(From_String_To_Char_Array(name_str));
            Pt_vs_mu[( i - 1 ) * PtBins.size() + j]->GetYaxis()->SetRange(5.0,120.0);
            if (j != PtBins.size() -1 )
                name_str = "TProfile_Pt_VS_Mu_Eta_"+to_string(EtaBins[i-1])+"_"+to_string(EtaBins[i])+"_"+"PT_"+to_string(PtBins[j])+"_"+to_string(PtBins[j+1])+"_"+to_string( ( i - 1 ) * PtBins.size() + j +1 )+";#mu;p_{T}";
            else
                name_str = "TProfile_Pt_VS_Mu_Eta_"+to_string(EtaBins[i-1])+"_"+to_string(EtaBins[i])+"_"+"PT_"+to_string(PtBins[0])+"_"+to_string(PtBins[PtBins.size() -1])+"_"+to_string( ( i - 1 ) * PtBins.size() + j +1 )+";#mu;p_{T}";
            TProfile_Pt_vs_mu_binned [( i - 1 ) * PtBins.size() + j] = new TProfile(From_String_To_Char_Array(name_str),From_String_To_Char_Array(name_str), MuBins.size(), MuBins[0],MuBins[MuBins.size()-1],  PtBins[0],PtBins[PtBins.size()-1] );
            
            cout<< From_String_To_Char_Array(name_str)<<endl;
            
        }
    }
    

    Int_t NPV_Cut = 15;

    
    
    
    for (int i = 0 ; i <=  paths_to_ttrees.size()-1 ; i++){
        TFile* FILE_TO_TTREE = new TFile(From_String_To_Char_Array(paths_to_ttrees[i]),"read");
        cout<< "\n\n Processing file: "<<paths_to_ttrees[i]<<"\n";
        TTree* Tree = (TTree*) FILE_TO_TTREE->Get("IsolatedJet_tree");
        Tree->SetBranchAddress("jet_ConstitPt", &pt, &b_pt);
        Tree->SetBranchAddress("weight_tot", &weight_tot, &b_weight_tot);
        Tree->SetBranchAddress("weight", &weight, &b_weight);
        Tree->SetBranchAddress("actualInteractionsPerCrossing", &mu, &b_mu);
        Tree->SetBranchAddress("jet_eta", &jet_eta, &b_eta);
        Tree->SetBranchAddress("jet_true_pt", &pt_true, &b_pt_true);
        Tree->SetBranchAddress("jet_ActiveArea4vec_pt", &jet_area, &b_jet_area);
        Tree->SetBranchAddress("rho", &rho, &b_rho);
        Tree->SetBranchAddress("NPV", &NPV, &b_NPV);
        //recojet_pt->at(j)-pt->at(j)-jet_area->at(j)*rho*0.001
        for(int ientry=0;ientry<Tree->GetEntries();ientry++){ 
            Tree->GetEntry(ientry);
            for (int jet_iter = 0; jet_iter < pt->size(); jet_iter++  ){
                //cout<< pt->at(jet_iter)<<" ";
                if (NPV == NPV_Cut){
                int eta_bin = Get_Bin_Of_Absolute_Value( EtaBins, jet_eta->at(jet_iter) );
                int pt_bin = Get_Bin_Of_Absolute_Value( PtBins, pt_true->at(jet_iter) );
                //cout<< eta_bin << " "<< pt_bin<<endl;
                //cout<< jet_eta->at(jet_iter)  << " " <<  pt_true->at(jet_iter)<<endl ;
                
                if (eta_bin > 0 && pt_bin > 0 ){
                    TProfile_Pt_vs_mu_binned [( eta_bin - 1 ) * PtBins.size() + pt_bin-1]->Fill( mu, pt->at(jet_iter) , weight  );
                    //TProfile_Pt_vs_mu_binned [( eta_bin - 1 ) * PtBins.size() + pt_bin-1]->Fill( mu, pt->at(jet_iter) - jet_area->at(jet_iter)*rho, weight  );
                    //TProfile_Pt_vs_mu_binned [( eta_bin - 1 ) * PtBins.size() + pt_bin-1]->Fill( mu, pt_true->at(jet_iter) , weight  );
                }
                if (eta_bin > 0){
                    TProfile_Pt_vs_mu_binned [( eta_bin - 1 ) * PtBins.size() + PtBins.size()-1]->Fill( mu, pt->at(jet_iter) , weight  );
                    //TProfile_Pt_vs_mu_binned [( eta_bin - 1 ) * PtBins.size() + PtBins.size()-1]->Fill( mu, pt->at(jet_iter) - jet_area->at(jet_iter)*rho , weight  );
                    //TProfile_Pt_vs_mu_binned [( eta_bin - 1 ) * PtBins.size() + PtBins.size()-1]->Fill( mu, pt_true->at(jet_iter) , weight  );
                }
                if ( eta_bin == 1 && pt_bin == 1){
                    //cout<<( eta_bin - 1 ) * PtBins.size() + pt_bin-1<<endl;
                    //cout<< eta_bin << " "<< pt_bin<<endl;
                    //cout<< jet_eta->at(jet_iter)  << " " <<  pt_true->at(jet_iter)<<endl ;
                }
                    
                }


            }
          
        }
        cout<<Tree->GetEntries()<<"\n";
        FILE_TO_TTREE->Close();
    }



    
    TCanvas* Averaged_pt_canvas[ ( EtaBins.size()-1) *PtBins.size()];
    TF1 * averaged_linear_fit[ ( EtaBins.size()-1) *PtBins.size() ];
    for ( int i=1; i< EtaBins.size()-1; i++ ){
        for ( int j=0; j< PtBins.size(); j++ ){

            string name_str = "averaged_canvas" + to_string( (i-1)*PtBins.size() + j +1) ;
            Averaged_pt_canvas[(i-1)*PtBins.size() + j] = new TCanvas(From_String_To_Char_Array(name_str), From_String_To_Char_Array(name_str), 800, 800);
            Averaged_pt_canvas[(i-1)*PtBins.size() + j]->cd();
            
            TProfile_Pt_vs_mu_binned[(i-1)*PtBins.size() + j]->SetLineColor(kBlue);
            TProfile_Pt_vs_mu_binned[(i-1)*PtBins.size() + j]->Draw();
            
            
            
            string name_fit_name_str = "averaged_linear_fit_"+to_string( (i-1)*PtBins.size() + j +1);
                
            //cout<<From_String_To_Char_Array(name_fit_name_str)<<endl;
            
            averaged_linear_fit[(i-1)*PtBins.size() + j] = new TF1(From_String_To_Char_Array(name_fit_name_str) ,"[0]+x*[1]",MuBins[0],MuBins[MuBins.size()-1]);
            
            
            //TProfile_Pt_vs_mu_binned[(i-1)*PtBins.size() + j]->Fit(averaged_linear_fit[(i-1)], "F", "L",MuBins[0], 45.0); //
            TProfile_Pt_vs_mu_binned[(i-1)*PtBins.size() + j]->Fit(averaged_linear_fit[(i-1)*PtBins.size() + j]); //
            cout<<(i-1)*PtBins.size() + j <<endl;
            cout<< EtaBins[i] << ": "<<  averaged_linear_fit[(i-1)*PtBins.size() + j]->GetParameter(1) <<endl;
            averaged_linear_fit[(i-1)*PtBins.size() + j]->SetLineColor(kRed);
            averaged_linear_fit[(i-1)*PtBins.size() + j]->SetLineWidth(3);
            Averaged_pt_canvas[(i-1)*PtBins.size() + j]->cd();
            averaged_linear_fit[(i-1)*PtBins.size() + j]->Draw("SAME");
            
        
            name_str = "/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/tgraphs_pt_vs_mu/averaged_"+to_string((i-1)*PtBins.size() + j+1)+"_pt_vs_mu.png";
            Averaged_pt_canvas[(i-1)*PtBins.size() + j]->SaveAs(From_String_To_Char_Array(name_str));
            cout<<"\n";
        }
    }
    TCanvas* Slopes[ PtBins.size()];
    TGraph * Slopes_Graph[ PtBins.size()];
    for ( int j=0; j< PtBins.size(); j++ ){
        string name_str = "slopes_canvas" + to_string(  j +1) ;
        Slopes[j] = new TCanvas(From_String_To_Char_Array(name_str),From_String_To_Char_Array(name_str),800,800);
        Slopes[j]->cd();

        Slopes_Graph[j] = new TGraph();
        if (j != PtBins.size() -1 )
            name_str = "slopes_graph_over_eta_PT_"+to_string(PtBins[j])+"_"+to_string(PtBins[j+1])+"_" + to_string(  j +1)+";#eta;dp_{T}/d#mu";
        else 
            name_str = "slopes_graph_over_eta_PT_"+to_string(PtBins[0])+"_"+to_string( PtBins[PtBins.size() -1])+"_" + to_string(  j +1)+";#eta;dp_{T}/d#mu";
        
        Slopes_Graph[j]->SetName(From_String_To_Char_Array(name_str));
        Slopes_Graph[j]->SetTitle(From_String_To_Char_Array(name_str));
        
        cout<<name_str<<endl;
        for ( int i=1; i< EtaBins.size()-1; i++ ){
            Slopes_Graph[j]->AddPoint( EtaBins[i] , averaged_linear_fit[(i-1)*PtBins.size() + j]->GetParameter(1));
            cout<<(i-1)*PtBins.size() + j <<endl;

            cout<< EtaBins[i] << ": "<<  averaged_linear_fit[(i-1)*PtBins.size() + j]->GetParameter(1) <<endl;
            
        }
        Slopes_Graph[j]->Draw("A*");
        name_str = "/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/tgraphs_pt_vs_mu/slopes_"+to_string(j+1)+"_pt_vs_mu.png";
        Slopes[j]->SaveAs(From_String_To_Char_Array(name_str));
    }
    

}



