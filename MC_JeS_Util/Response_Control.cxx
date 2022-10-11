#include "Response_Control_H.h"
void Response_vs_E_true::Create_Folder(std::string name){

    std::string command = "mkdir "+ name;
    system(FSTCA(command) );

    return;
}
std::string String_Float_Precision(float input, int precision);
TChain* Response_vs_E_true::Set_Up_TChain(std::string path_to_files,std::string TTree_name){

    
    TChain * ch_p= new TChain(FSTCA(TTree_name));
    std::string str;
    std::ifstream infile ;
    // vector <string> paths_to_ttrees ;
    infile.open(FSTCA(path_to_files));
    while(!infile.eof()){
        getline(infile,str);
        // paths_to_ttrees.push_back(str);
        if(is_file_exist(FSTCA(str))){
            std::cout<<"FILE EXISTS: "<<str<<"\n\n";
            ch_p->Add(FSTCA(str));
        }
        else { std::cout<<"ERROR FILE DOES NOT EXIST: "<<str<<"\n\n"; 
        }
            
    }
    infile.close();
    return ch_p;
}
float Response_vs_E_true::Reco_Factor(float pt,float eta,float area , float rho , float mu, int NPV){
    return 1.0;
}
float Response_vs_E_true::Area_Factor(float pt,float eta,float area , float rho , float mu, int NPV){
    return (pt- area*rho)/pt;
}
// float 1D_Factor(float pt,float eta,float area , float rho , float mu, int NPV){
//     return 1;
// }
void Response_vs_E_true::Response_Control( std::string path_to_files, std::string TTree_name = "IsolatedJet_tree", int increment = 1,   std::string Step = "Area",float eta_min = -4.5, float eta_max = 4.5, std::string LegendName = "NoJetCal"){
    if (increment < 0 ) {std::cout<<"Increment is less than 0"; return ;}

    float (Response_vs_E_true::*Factor)(float pt,float eta,float area , float rho , float mu, int NPV);
    if (Step == "Reco"){
        Factor = &Response_vs_E_true::Reco_Factor;
    }
    else if (Step == "Area"){
        Factor = &Response_vs_E_true::Area_Factor;
    }

    // std::string path_to_files = "./partial_mc20a.txt";
    // std::string path_to_files = "./files_mc20a.txt";
    // std::string path_to_files = "./files_mc16a.txt";
    // std::string TTree_name = "IsolatedJet_tree";
    std::cout<<"+I+"<<std::endl;
    ch = Set_Up_TChain(path_to_files, TTree_name);
    
    ch->SetBranchAddress("njet", &njet, &b_njet);
    ch->SetBranchAddress("rho", &rho, &b_rho);
    ch->SetBranchAddress("NPV", &NPV, &b_NPV);
    // ch->SetBranchAddress("R_weight", &weight_tot, &b_weight_tot);
    // ch->SetBranchAddress("weight_tot", &weight_tot, &b_weight_tot);
    ch->SetBranchAddress("weight", &weight_tot, &b_weight_tot);
    ch->SetBranchAddress("actualInteractionsPerCrossing", &mu, &b_mu);

    ch->SetBranchAddress("jet_ConstitPt", &pt, &b_pt);
    ch->SetBranchAddress("jet_ConstitEta", &jet_eta, &b_eta);   
    ch->SetBranchAddress("jet_E", &jet_E, &b_E);
    ch->SetBranchAddress("jet_true_e", &jet_true_E, &b_jet_true_E);
    
    ch->SetBranchAddress("jet_true_pt", &pt_true, &b_pt_true);
    ch->SetBranchAddress("jet_ActiveArea4vec_pt", &jet_area, &b_jet_area);
    unsigned N_Entries = ch->GetEntries();
    std::cout<< N_Entries<<std::endl;
    float Total_Weight = 0 ;
    int N_Jets_reco = 0 ;
    int N_Jets_true = 0 ;
    
    const Int_t E_Bins_N = 28;
    Double_t  E_Bins[E_Bins_N+1] = {10, 15, 20, 25, 30, 35, 40, 50, 60, 80, 100, 120, 150, 200, 240, 300, 400, 500, 600, 800, 1000, 1200, 1500, 2000, 2500, 3000, 3500, 4000, 5500 };
    // const Int_t E_Bins_N = 2;
    // Double_t  E_Bins[E_Bins_N+1] = {10, 15, 20};

    R_vs_E_true = new TH2F("response v e true","response v e true",  E_Bins_N,E_Bins,180,-1.2,2.4);
    


    /**/
    for(auto ientry = 0; ientry < N_Entries; ientry+=increment){ //Loop on entries
        ch->GetEntry(ientry);
        // for(int i =0 ; i < (*pt).size();i++){
        //     cout<<(*pt)[i]<<" ";
        //     cout<<(*jet_eta)[i]<<" ";
        // }
        // cout<<"\n"<<(*pt).size()<<" ";
        // cout<<(*jet_eta).size()<<" ";
        // cout<<NPV<<"\n";
        // result->Fill(jet_true_E->at(0),jet_E->at(0)/jet_true_E->at(0)  , weight_tot );
        for(int jet_iter=0; jet_iter < jet_true_E->size(); jet_iter++){
            R_vs_E_true->Fill(jet_true_E->at(jet_iter) , jet_E->at(jet_iter) / jet_true_E->at(jet_iter) , weight_tot);
            // float f = correctionFactor(pt->at(jet_iter),jet_eta->at(jet_iter),jet_area->at(jet_iter),rho,mu, NPV);
            float f ;
            f = (*this.*Factor)(pt->at(jet_iter),jet_eta->at(jet_iter),jet_area->at(jet_iter),rho,mu, NPV);
            if ( jet_eta->at(jet_iter)  > eta_min && jet_eta->at(jet_iter)  < eta_max)
                R_vs_E_true->Fill(jet_true_E->at(jet_iter) ,  f* jet_E->at(jet_iter) / jet_true_E->at(jet_iter) , weight_tot);
            // std::cout<< f<<"\n";

        }


        N_Jets_reco+=pt->size();
        N_Jets_true+=jet_true_E->size();
        Total_Weight+=weight_tot*pt->size();
        N_Jets+=njet;

        if(ientry %100000==0) std::cout<< ((float) ientry / (float)N_Entries)* 100.0<<"%\n";

    }
    
    std::cout<<  100<<"%\n";
    TCanvas * tc = new TCanvas("canvas_to_save","canvas_to_save",2800,1600);
    // gROOT->SetStyle("Plain");
	// gStyle->SetOptFit(11111);
    // gStyle->SetOptStat(0);
    // gStyle->SetTitleFontSize(0.02);
    gROOT->SetStyle("ATLAS");
    gPad->SetLogx(1);
    std::string Histo_name = "Plot;E^{true}, #eta in ["+String_Float_Precision(eta_min,1)+":"+String_Float_Precision(eta_max,1)+  "];Response, "+Step+", "+LegendName;
    R_vs_E_true->SetTitle(FSTCA(Histo_name));
    
    
    
    R_vs_E_true->Draw("COLZ ");
    std::string SaveName = "Plots";
    Create_Folder(FSTCA(SaveName));
    SaveName+="/"+LegendName+"_"+Step+"_"+String_Float_Precision(eta_min,1)+"_"+String_Float_Precision(eta_max,1)+".png";
    tc->SaveAs(FSTCA(SaveName));
    std::cout<< "\n Numbers of reco jets: "<<N_Jets<<"\n";
    std::cout<< "\n Numbers of reco jets: "<<N_Jets_reco<<"\n";
    std::cout<< "\n Numbers of truth jets: "<<N_Jets_true<<"\n";
    std::cout<< "\n Total weight of jets: "<<Total_Weight<<"\n";
    
    return ;
}

// ./Run "partial_mc20a.txt" "IsolatedJet_tree" 3000

//  partial_mc20a.txt  "IsolatedJet_tree" 1 "Area" -4.5  4.5
//  g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "partial_mc20a.txt" "IsolatedJet_tree" 3000
// g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" 3000
// g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" 3000
// ./Run "partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "3000" "Reco" "-4.5" "4.5" "JetCal"
// ./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "3000" "Reco" "-4.5" "4.5" "NoJetCal"
int main ( int argc ,char* argv[] ){
    std::cout << "+I+\n";
    // path_to_files TTree_name increment Step eta_min eta_max LegendName
    // std::string input = argv[3];
    std::string input_1 = argv[1];
    std::string input_2 = argv[2];
    int increment = std::stoi(argv[3]);
    std::string input_3 = argv[4];
    float upper_limit = std::stof(argv[5]);
    float lower_limit = std::stof(argv[6]);
    std::string input_4 = argv[7];

    std::cout<<argc <<" \n";

    Response_vs_E_true * h = new Response_vs_E_true( );
    h->Response_Control(input_1 , input_2 ,increment, input_3, upper_limit, lower_limit, input_4);
    
    delete h;
    /**/
    std::cout<<__cplusplus<<std::endl;
    return 0;
}


std::string String_Float_Precision(float input, int precision){
    std::string result = std::to_string (input);
    int before_point = 0 ;
    for (int i = 0 ; i < result.size(); i ++){
        if (result[i] == '.') break;
        else before_point+=1;
    }
    if(precision == 0)
        return result.substr(0,before_point);
    if (before_point+1+precision <=  result.size())
        return result.substr(0,before_point+1+precision);
    else 
        return result;
}