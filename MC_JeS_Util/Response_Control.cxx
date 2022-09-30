#include "Response_Control_H.h"
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

void Response_vs_E_true::Response_Control(){

    // std::string path_to_files = "./partial_mc20a.txt";
    std::string path_to_files = "./files_mc20a.txt";
    std::string TTree_name = "IsolatedJet_tree";
    std::cout<<"+I+"<<std::endl;
    ch = Set_Up_TChain(path_to_files, TTree_name);
    

    ch->SetBranchAddress("rho", &rho, &b_rho);
    ch->SetBranchAddress("NPV", &NPV, &b_NPV);
    ch->SetBranchAddress("R_weight", &weight_tot, &b_weight_tot);
    ch->SetBranchAddress("actualInteractionsPerCrossing", &mu, &b_mu);

    ch->SetBranchAddress("jet_ConstitPt", &pt, &b_pt);
    ch->SetBranchAddress("jet_ConstitEta", &jet_eta, &b_eta);   
    // ch->SetBranchAddress("jet_E", &jet_E, &b_E);
    // ch->SetBranchAddress("jet_true_e", &jet_true_E, &b_jet_true_E);
    
    ch->SetBranchAddress("jet_true_pt", &pt_true, &b_pt_true);
    ch->SetBranchAddress("jet_ActiveArea4vec_pt", &jet_area, &b_jet_area);
    unsigned N_Entries = ch->GetEntries();
    std::cout<< N_Entries<<std::endl;
    float Total_Weight = 0 ;
    for(auto ientry = 0; ientry < N_Entries; ientry++){ //Loop on entries
        ch->GetEntry(ientry);
        // for(int i =0 ; i < (*pt).size();i++){
        //     cout<<(*pt)[i]<<" ";
        //     cout<<(*jet_eta)[i]<<" ";
        // }
        // cout<<"\n"<<(*pt).size()<<" ";
        // cout<<(*jet_eta).size()<<" ";
        // cout<<NPV<<"\n";
        // result->Fill(jet_true_E->at(0),jet_E->at(0)/jet_true_E->at(0)  , weight_tot );
        N_Jets+=pt->size();
        Total_Weight+=weight_tot*pt->size();
    }
    std::cout<< "\n Numbers of jets: "<<N_Jets<<"\n";
    std::cout<< "\n Total weight of jets: "<<Total_Weight<<"\n";
    // 2848914
    // 215258386/
    // 58213383
    return ;
}