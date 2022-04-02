
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


int Eta_Bin( vector<float> & etabin , float &eta ){
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
vector<vector<float>> Averaged_pT_aver_mu_Bins_over_Eta_Bins(vector<vector<vector<pair<float,float>>>> & pt ){
    vector<vector<float>> result;

    for (int i = 0 ; i <pt.size(); i++ ){
        vector<float> a;
        a.resize(pt[i].size());
        result.push_back(a);
        for (int j = 0 ; j <pt.at(i).size(); j++ ){
            float  sum = 0 ;
            float weight = 0 ;
            for(int k =0 ; k < pt.at(i).at(j).size(); k++){
                
                sum += (pt.at(i).at(j).at(k).first*pt.at(i).at(j).at(k).second);
                weight += pt.at(i).at(j).at(k).second;
            }
            if (sum == 0 || weight == 0)
                result.at(i).at(j) = 0;
            else 
                result.at(i).at(j) = sum/weight;
        }
    }

    
    return result;
}
void draw_derirative_d_pt_d_mu_over_eta(){
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

    

    //vector<float>*  jet_area; //area
    //Double_t        rho;
    //Float_t        rho;
    //vector<float>* true_eta;
    //Float_t         weight;
    //vector<float>* recojet_pt; //const scale pt
    // /Double_t        weight;
    //Double_t        w;    
    //std::vector<float>* recojet_eta; //const scale eta
    /*
    pTtrue_weight = new TH1F("pTtrue_weight","pTtrue weight considered",200,0.,200.);
    pTtrue = new TH1F("pTtrue","pTtrue weight not considered",200,0.,200.);
    mu_dist = new TH1F("mu","mu",munbins,mulow,muhigh);
    NPV_dist = new TH1F("NPV","NPV",NPVnbins,NPVlow,NPVhigh);
    NPV_mu = new TH2F("NPVvsMu","",munbins,mulow,muhigh,NPVnbins,NPVlow,NPVhigh);
    */
    
    //TBranch* b_recojet_pt;
    
    //TBranch* b_rho;
    //TBranch* b_jet_area;
    //TBranch* b_true_eta;
    //TBranch* b_recojet_eta;
    //TBranch* b_bcid;

    
    //ch->SetBranchAddress(config->GetValue("CaloPt",""), &recojet_pt, &b_recojet_pt);
    //ch->SetBranchAddress("NPV", &NPV, &b_NPV);
    
    //ch->SetBranchAddress(config->GetValue("PtDensity",""), &rho, &b_rho);
    //ch->SetBranchAddress(config->GetValue("JetArea",""), &jet_area, &b_jet_area);
    //ch->SetBranchAddress(config->GetValue("TrueEta",""), &true_eta, &b_true_eta);
    //ch->SetBranchAddress(config->GetValue("WeightBranch","weight"), &weight, &b_weight);
    //ch->SetBranchAddress(config->GetValue("CaloEta","jet_ConstitEta"), &recojet_eta, &b_recojet_eta);
    //ch->SetBranchAddress(config->GetValue("BCID","bcid"), &bcid, &b_bcid);
    
    vector<Float_t>* pt; //true pt    
    Int_t           NPV;
    Float_t         mu;
    Double_t        weight_tot;
    Float_t        weight;
    std::vector<float>* jet_eta; //jet eta
    

    TBranch* b_pt;
    TBranch* b_eta;
    TBranch* b_NPV;
    TBranch* b_mu;
    TBranch* b_weight;
    TBranch* b_weight_tot;


    vector<float> MuBins = {};
    vector<float> PtBins = { 10.0, 15.0, 20.0, 30.0, 60.0, 120.0};
    vector<float> EtaBins = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.7,2.9,3.0,3.075,3.15,3.25,3.35,3.45,3.6,3.8,4.1,4.5,4.9};
    //38
    for ( int i = 0 ; i <= 72 ; i+=3 ){
        MuBins.push_back(1.0*i);
        //cout<<MuBins[i/3]<<endl;
    }
    

    TFile * Result = new TFile("tgraphs_pt_vs_mu.root","recreate");
    TGraph * Pt_vs_mu[ EtaBins.size() -1 ];
    for ( int i=1; i< EtaBins.size(); i++ ){
        string name_str = "TGraph_Pt_VS_Mu_"+to_string(i);
        Pt_vs_mu[i-1] = new TGraph();
        Pt_vs_mu[i-1]->SetName(From_String_To_Char_Array(name_str));
        Pt_vs_mu[i-1]->GetYaxis()->SetRange(5.0,120.0);
        cout<< From_String_To_Char_Array(name_str)<<endl;
        cout<<i<<"/"<<EtaBins.size()<<endl;
    }
    



    vector<vector<vector<pair<float,Float_t>>>> pt_for_mu_bin_for_eta_bin ;
    for ( int i=1; i< EtaBins.size(); i++ ){
        vector<vector <pair<float,float>>> a;
        for ( int j=1; j< MuBins.size(); j++ ){
            vector <pair<float,float>> b;
            a.push_back(b);
        }
        pt_for_mu_bin_for_eta_bin.push_back(a);
        
    }
    cout<<pt_for_mu_bin_for_eta_bin.size()<<"/"<<EtaBins.size()-1<<endl;
    for ( int i=1; i< EtaBins.size(); i++ ){
        cout<<pt_for_mu_bin_for_eta_bin[i-1].size()<<"/"<<MuBins.size()-1<<endl;
    }
    
    
    float eettaa = 0.15;
    cout<<  Eta_Bin(EtaBins , eettaa)<<endl;
    

    //TH1F * pTtrue_weight = new TH1F("Pt_distribution","pT weight considered",200,0.,200.);
    vector<float> a;
    for (int i = 0 ; i <=  paths_to_ttrees.size()-1 /* paths_to_ttrees.size() */; i++){
        TFile* FILE_TO_TTREE = new TFile(From_String_To_Char_Array(paths_to_ttrees[i]),"read");
        cout<< "\n\n Processing file: "<<paths_to_ttrees[i]<<"\n";
        TTree* Tree = (TTree*) FILE_TO_TTREE->Get("IsolatedJet_tree");
        Tree->SetBranchAddress("jet_pt", &pt, &b_pt);
        Tree->SetBranchAddress("weight_tot", &weight_tot, &b_weight_tot);
        Tree->SetBranchAddress("weight", &weight, &b_weight);
        Tree->SetBranchAddress("actualInteractionsPerCrossing", &mu, &b_mu);
        Tree->SetBranchAddress("jet_eta", &jet_eta, &b_eta);
         
        for(int ientry=0;ientry<Tree->GetEntries();ientry++){ 
            Tree->GetEntry(ientry);
            for (int jet_iter = 0; jet_iter < pt->size(); jet_iter++  ){
                //cout<< pt->at(jet_iter)<<" ";
                //pTtrue_weight->Fill( pt->at(jet_iter), weight_tot ) ;
                if ( Eta_Bin( EtaBins , jet_eta->at(jet_iter)  ) >= 1 ){
                    Pt_vs_mu[Eta_Bin( EtaBins , jet_eta->at(jet_iter) )-1 ]->AddPoint( pt->at(jet_iter) , mu );
                    //cout << jet_eta->at(jet_iter) << "__"<< jet_eta->size() << endl; 
                }

                
                    
                    
                    
                if (Eta_Bin( EtaBins , jet_eta->at(jet_iter)  ) >= 1 && Eta_Bin( MuBins , mu  ) >= 1){
                    pt_for_mu_bin_for_eta_bin[Eta_Bin( EtaBins , jet_eta->at(jet_iter)  ) - 1 ][Eta_Bin( MuBins , mu  ) -1].push_back(make_pair(pt->at(jet_iter), weight_tot)) ;
                    //pt_and_weight.push_back( std::make_pair()) ;
                    //pt_and_weight.push_back( std::make_pair(pt->at(jet_iter),weight_tot));
                    //cout << jet_eta->at(jet_iter) << "__"<< jet_eta->size() << endl; 
                }


            }
            /*
            cout<<"check start: "<<"\n";
            for (int jet_iter = 0; jet_iter < pt->size(); jet_iter++  ){
                cout << jet_eta->at(jet_iter) << "__"<< jet_eta->size() << endl; 
            }
            cout<<"check end: "<<"\n";
            */

            
            //cout<<"\n";
            //cout<<"weight_tot: "<<weight_tot<<"\n";
                //pTtrue_weight->Fill(pt[jet_iter],weight);
        }
        cout<<Tree->GetEntries()<<"\n";
        FILE_TO_TTREE->Close();
    }
    for ( int i=1; i< EtaBins.size(); i++ ){
    cout<<pt_for_mu_bin_for_eta_bin.size()<<"/"<<EtaBins.size()-1<<endl;
    cout<<pt_for_mu_bin_for_eta_bin[i-1].size()<<"/"<<MuBins.size()-1<<endl;
    for ( int j=1; j< MuBins.size(); j++ )
    cout<<":  "<<pt_for_mu_bin_for_eta_bin[i-1][j-1].size()<<"/"<<MuBins.size()<<endl;
    }
    vector<vector<float>> averaged_pT_aver_mu_Bins_over_Eta_Bins = Averaged_pT_aver_mu_Bins_over_Eta_Bins(pt_for_mu_bin_for_eta_bin);
    


    TGraph * Averaged_G[EtaBins.size()-1]; 
    TCanvas* Averaged_pt_canvas[EtaBins.size()-1];
    TF1 * averaged_linear_fit[EtaBins.size()-1];
    for ( int i=1; i< EtaBins.size(); i++ ){
        string name_str = "averaged_canvas" + to_string(i) ;
        Averaged_pt_canvas[i-1] = new TCanvas(From_String_To_Char_Array(name_str), From_String_To_Char_Array(name_str), 800, 800);
        Averaged_pt_canvas[i-1]->cd();
        name_str = "averaged_TGraph" + to_string(i) ;
        Averaged_G[i-1] = new TGraph();
        Averaged_G[i-1]->SetName(From_String_To_Char_Array(name_str));
        for(int j =1 ; j< MuBins.size();j++){
            if(averaged_pT_aver_mu_Bins_over_Eta_Bins[i-1][j-1]>0)
                Averaged_G[i-1]->AddPoint( MuBins[j],averaged_pT_aver_mu_Bins_over_Eta_Bins[i-1][j-1]);       
        }
        if(Averaged_G[i-1]->GetN()>0){
            Averaged_G[i-1]->GetXaxis()->SetLimits(MuBins[0], MuBins[MuBins.size()-1]);
            Averaged_G[i-1]->SetLineColor(kBlue);
            Averaged_G[i-1]->Draw("A*");
        }
        cout<<"\n";
        
        if(Averaged_G[i-1]->GetN()>0)
        {
            
            string name_fit_name_str = "averaged_linear_fit_"+to_string( (i-1));
            
            
            cout<<From_String_To_Char_Array(name_fit_name_str)<<endl;
            
            
            averaged_linear_fit[(i-1)] = new TF1(From_String_To_Char_Array(name_fit_name_str) ,"[0]+x*[1]",MuBins[0],MuBins[MuBins.size()-1]);
            
            
            
            
            Averaged_G[i-1]->Fit(averaged_linear_fit[(i-1)], "F", "L",MuBins[0], 40.0); //
            averaged_linear_fit[(i-1)]->SetLineColor(kRed);
            averaged_linear_fit[(i-1)]->SetLineWidth(3);
            Averaged_pt_canvas[i-1]->cd();
            averaged_linear_fit[(i-1)]->Draw("SAME");
                   
                
                
                
            
        }
        

        name_str = "/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/tgraphs_pt_vs_mu/averaged_"+to_string(i)+"_pt_vs_mu.png";
        Averaged_pt_canvas[i-1]->SaveAs(From_String_To_Char_Array(name_str));
        cout<<"\n";
        
        
        
    }
    
    string name_final="";
    TGraph * d_pt_d_mu_vs_eta[1];
    d_pt_d_mu_vs_eta[0] = new TGraph(); 
    //d_pt_d_mu_vs_eta->SetName(From_String_To_Char_Array(name_final));

    name_final="graph";
    


    TCanvas* d_pt_d_mu_vs_eta_canvas = new TCanvas("final_canvas","final_canvas",800,800);
    d_pt_d_mu_vs_eta_canvas->cd();
    
    // Warning : for last value of eta theree was empty tgraph
    for ( int i=1; i< EtaBins.size()-1; i++ ){
        d_pt_d_mu_vs_eta[0]->AddPoint(EtaBins[i-1],averaged_linear_fit[i-1]->GetParameter(1) );
        cout<<i<<": "<<averaged_linear_fit[i-1]->GetParameter(1)<<endl;
    }



    
    d_pt_d_mu_vs_eta[0]->Draw("A*");
    name_final = "/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/tgraphs_pt_vs_mu/final.png";
    d_pt_d_mu_vs_eta_canvas->SaveAs(From_String_To_Char_Array(name_final));
    /*
    */

    /*
    TCanvas* c[EtaBins.size()-1];
    TF1 * linear_fit[(EtaBins.size()-1)*(PtBins.size())];
    for ( int i=1; i< EtaBins.size(); i++ ){
        string name_str = "canvas" + to_string(i) ;
        c[i-1] = new TCanvas(From_String_To_Char_Array(name_str), From_String_To_Char_Array(name_str), 800, 800);
        c[i-1]->cd();
        if(Pt_vs_mu[i-1]->GetN()>0){
            Pt_vs_mu[i-1]->GetXaxis()->SetLimits(5.0,120.0);
            Pt_vs_mu[i-1]->Draw("A*");
        }
        cout<<"\n";
        //for ( int eta_bin_iter = 1; eta_bin_iter < EtaBins.size();  eta_bin_iter++ ) 
        if(Pt_vs_mu[i-1]->GetN()>0)
        {
            for ( int pt_bin_iter = 0; pt_bin_iter < PtBins.size();  pt_bin_iter++ ) {
                string name_fit_name_str = "linear_fit_function_"+to_string( (i-1)*PtBins.size() + pt_bin_iter);
                
                
                cout<<From_String_To_Char_Array(name_fit_name_str)<<endl;
                
                if(pt_bin_iter == PtBins.size()-1){
                    linear_fit[(i-1)*PtBins.size() + pt_bin_iter] = new TF1(From_String_To_Char_Array(name_fit_name_str) , "[0]+x*[1]" , PtBins[0] , PtBins[PtBins.size()-1] );
                }
                else{
                    linear_fit[(i-1)*PtBins.size() + pt_bin_iter] = new TF1(From_String_To_Char_Array(name_fit_name_str) ,"[0]+x*[1]",PtBins[pt_bin_iter],PtBins[pt_bin_iter+1]);
                }
                cout<<(i-1)*PtBins.size() + pt_bin_iter<<endl;
                if(pt_bin_iter == PtBins.size()-1){
                    cout<<PtBins[PtBins.size()-1]<<endl;
                    Pt_vs_mu[i-1]->Fit(linear_fit[(i-1)*PtBins.size() + pt_bin_iter], "W", "L",PtBins[0], PtBins[PtBins.size()-1]); //
                    linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineColor(kBlack);
                    linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineWidth(3);
                    c[i-1]->cd();
                    linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->Draw("SAME");
                    cout<<" "<<linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->Eval(10);
                    cout<<" "<<linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->Eval(20);
                    cout<<" "<<linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->Eval(30);
                    cout<<" "<<linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->Eval(40);
                    cout<<" "<<linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->Eval(50);
                    cout<<" "<<linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->Eval(60);
                    cout<<endl;
                }
                else{
                    Pt_vs_mu[i-1]->Fit(linear_fit[(i-1)*PtBins.size() + pt_bin_iter], "W", "L",PtBins[pt_bin_iter],PtBins[pt_bin_iter+1] ); //  
                    if (pt_bin_iter == 0) linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineColor(kRed);
                    if (pt_bin_iter == 1) linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineColor(kBlue);
                    if (pt_bin_iter == 2) linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineColor(kGreen);
                    if (pt_bin_iter == 3) linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineColor(kYellow);
                    if (pt_bin_iter == 4) linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineColor(kMagenta);
                    if (pt_bin_iter == 5) linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineColor(kCyan);
                    linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->SetLineWidth(3);
                    c[i-1]->cd();
                    linear_fit[(i-1)*PtBins.size() + pt_bin_iter]->DrawClone("Same");
                }
                
            }
        }
        

        name_str = "/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/tgraphs_pt_vs_mu/_"+to_string(i)+"_pt_vs_mu.png";
        c[i-1]->SaveAs(From_String_To_Char_Array(name_str));
        cout<<"\n";
        
        
        
    }
    Result->Write();
    Result->Close();
    cout<<EtaBins.size()-1<<endl;
    */



}



