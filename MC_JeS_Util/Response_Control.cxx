#include "Response_Control_H.h"
//+I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+
void Response_vs_E_true::Create_Folder(std::string name){

    std::string command = "mkdir "+ name;
    system(FSTCA(command) );

    return;
}
std::string String_Float_Precision(float input, int precision);

template<class T>
void printMessage(T message){
    std::cout<< message<<"\n";
}
TChain* Response_vs_E_true::Set_Up_TChain(std::string path_to_files,std::string TTree_name){

    printMessage("Start Set_Up_TChain");
    TChain * ch_p= new TChain(FSTCA(TTree_name));
    std::string str;
    std::ifstream infile ;
    // vector <string> paths_to_ttrees ;
    infile.open(FSTCA(path_to_files));
    if (infile){
        printMessage(path_to_files);
    }
    else{
        printMessage("ERROR: No file with such name!");
        exit(1);
    }
    while(!infile.eof()){
        getline(infile,str);
        // paths_to_ttrees.push_back(str);
        
        if(is_file_exist(FSTCA(str)) && str != ""){
            std::cout<<"FILE EXISTS: "<<str<<"\n\n";
            ch_p->Add(FSTCA(str));
        }
        else {if (str != "" ) std::cout<<"ERROR FILE DOES NOT EXIST: "<<str<<"\n\n"; 
         
        }
            
    }
    infile.close();
    printMessage("End Set_Up_TChain");
    return ch_p;
}
//+I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+
float Response_vs_E_true::Reco_Factor(float pt,float eta,float area , float rho , float mu, int NPV){
    return 1.0;
}
//+I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+
float Response_vs_E_true::Area_Factor(float pt,float eta,float area , float rho , float mu, int NPV){
    return (pt- area*rho)/pt;
}
//+I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+
void Response_vs_E_true::Response_Control( std::string path_to_files, std::string TTree_name = "IsolatedJet_tree", int increment = 1,   std::string Step = "Area",float eta_min = -4.5, float eta_max = 4.5, std::string LegendName = "NoJetCal", int Num_Leading_Jets = 1){
    if (increment < 0 ) {std::cout<<"ERROR: Increment is less than 0"; return ;}
    if ( eta_max < eta_min ) {std::cout<<"ERROR: Check Eta ranges"; return ;}
    if (Num_Leading_Jets == 0  || Num_Leading_Jets < -1 ){std::cout<<"ERROR: Number of Leading jets is incorrect"; return ;}
    float (Response_vs_E_true::*Factor)(float pt,float eta,float area , float rho , float mu, int NPV);
    if (Step == "Reco"){
        Factor = &Response_vs_E_true::Reco_Factor;
    }
    else if (Step == "Area"){
        Factor = &Response_vs_E_true::Area_Factor;
    }
    else if (Step == "1D"){
        Factor = &Response_vs_E_true::correctionFactor;
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
    ch->SetBranchAddress("R_weight", &weight_tot, &b_weight_tot);
    // ch->SetBranchAddress("weight_tot", &weight_tot, &b_weight_tot);
    // ch->SetBranchAddress("weight", &weight_tot, &b_weight_tot);
    ch->SetBranchAddress("actualInteractionsPerCrossing", &mu, &b_mu);

    ch->SetBranchAddress("jet_ConstitPt", &pt, &b_pt);
    ch->SetBranchAddress("jet_ConstitEta", &jet_eta, &b_eta);   
    ch->SetBranchAddress("jet_E", &jet_E, &b_E);
    ch->SetBranchAddress("jet_true_e", &jet_true_E, &b_jet_true_E);
    
    ch->SetBranchAddress("jet_true_pt", &pt_true, &b_pt_true);
    ch->SetBranchAddress("jet_ActiveArea4vec_pt", &jet_area, &b_jet_area);
    const unsigned N_Entries = ch->GetEntries();
    std::cout<<"Total Events: "<< N_Entries<<std::endl;
    float Total_Weight = 0 ;
    
    
    const Int_t E_Bins_N = 28;
    Double_t  E_Bins[E_Bins_N+1] = {10, 15, 20, 25, 30, 35, 40, 50, 60, 80, 100, 120, 150, 200, 240, 300, 400, 500, 600, 800, 1000, 1200, 1500, 2000, 2500, 3000, 3500, 4000, 5500 };
    // const Int_t E_Bins_N = 2;
    // Double_t  E_Bins[E_Bins_N+1] = {10, 15, 20};

    R_vs_E_true = new TH2F("response v e true","response v e true",  E_Bins_N,E_Bins,180,-1.2,2.4);
    


    /**/
    int indexEntry;
    const float percent = 0.06;
    functions.push_back([&]() { displayProgress(indexEntry, N_Entries, percent); });
    // functions.push_back([&]() { function3("Hello", 'A', 2.71); });
    
    for(auto ientry = 0; ientry < N_Entries; ientry+=increment){ //Loop on entries
        indexEntry = ientry;
        ch->GetEntry(ientry);
        // for(int i =0 ; i < (*pt).size();i++){
        //     cout<<(*pt)[i]<<" ";
        //     cout<<(*jet_eta)[i]<<" ";
        // }
        // cout<<"\n"<<(*pt).size()<<" ";
        // cout<<(*jet_eta).size()<<" ";
        // cout<<NPV<<"\n";
        // result->Fill(jet_true_E->at(0),jet_E->at(0)/jet_true_E->at(0)  , weight_tot );
        if ( Num_Leading_Jets == -1 )
        {
            for(int jet_iter=0; jet_iter < jet_true_E->size(); jet_iter++){
                float f ;
                f = (*this.*Factor)(pt->at(jet_iter),jet_eta->at(jet_iter),jet_area->at(jet_iter),rho,mu, NPV);
                if ( jet_eta->at(jet_iter)  > eta_min && jet_eta->at(jet_iter)  < eta_max){
                    R_vs_E_true->Fill(jet_true_E->at(jet_iter) ,  f* jet_E->at(jet_iter) / jet_true_E->at(jet_iter) , weight_tot);
                    N_Jets_reco+=pt->size();
                    N_Jets_true+=jet_true_E->size();
                    Total_Weight+=weight_tot*pt->size();
                    N_Jets+=njet;
                }
                
            }
            
        }
        else if (Num_Leading_Jets > 0 && jet_true_E->size() >= Num_Leading_Jets)
        {
            for(int jet_iter=0; jet_iter < Num_Leading_Jets; jet_iter++){
            
                float f ;
                f = (*this.*Factor)(pt->at(jet_iter),jet_eta->at(jet_iter),jet_area->at(jet_iter),rho,mu, NPV);
                if ( jet_eta->at(jet_iter)  > eta_min && jet_eta->at(jet_iter)  < eta_max){
                    R_vs_E_true->Fill(jet_true_E->at(jet_iter) ,  f* jet_E->at(jet_iter) / jet_true_E->at(jet_iter) , weight_tot);
                    N_Jets_reco+=Num_Leading_Jets;
                    N_Jets_true+=Num_Leading_Jets;
                    Total_Weight+=weight_tot*Num_Leading_Jets;
                    N_Jets+=Num_Leading_Jets;
                }
                
            }
            
        }
        // Call each function in the vector        
        // for (const auto& func : functions) {
        //     func(); 
        // }
        std::for_each(functions.begin(), functions.end(), 
        [](std::function<void()> function){
            function();
        });
        

        

    }
    
    std::cout<<  100<<"%\n";
    TCanvas * tc = new TCanvas("canvas_to_save","canvas_to_save",2800,1600);
    // gROOT->SetStyle("Plain");
	// gStyle->SetOptFit(11111);
    // gStyle->SetOptStat(0);
    // gStyle->SetTitleFontSize(0.02);
    gROOT->SetStyle("ATLAS");
    gPad->SetLogx(1);
    std::string Histo_name = "Plot;E^{true}, #eta in ["+String_Float_Precision(eta_min,1)+":"+String_Float_Precision(eta_max,1)+  "];Response, "+Step+", ";
    if ( Num_Leading_Jets == -1){
        Histo_name += "all jets, ";
    }
    else {
        Histo_name += "lead "+std::to_string(Num_Leading_Jets)+", ";
    }
    Histo_name += LegendName;
    R_vs_E_true->SetTitle(FSTCA(Histo_name));
    
    
    
    R_vs_E_true->Draw("COLZ ");
    std::string SaveName = "Plots";
    Create_Folder(FSTCA(SaveName));
    SaveName+="/"+LegendName+"_"+Step+"_"+String_Float_Precision(eta_min,1)+"_"+String_Float_Precision(eta_max,1)+".png";
    tc->SaveAs(FSTCA(SaveName));
    std::cout<< "\nNumbers of reco jets: "<<N_Jets<<"\n";
    std::cout<< "Numbers of reco jets: "<<N_Jets_reco<<"\n";
    std::cout<< "Numbers of truth jets: "<<N_Jets_true<<"\n";
    std::cout<< "Total weight of jets: "<<Total_Weight<<"\n";
    
    return ;
}


// g++ -o Run Response_Control.cxx `root-config --cflags --glibs`
//  g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "partial_mc20a.txt" "IsolatedJet_tree" 3000
// g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" 3000
// g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" 3000
// ./Run "partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "3000" "Reco" "-4.5" "4.5" "JetCal"
// ./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "3000" "Reco" "-4.5" "4.5" "NoJetCal"

// g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "./Input_Files/MC23a_PFlow.txt" "IsolatedJet_tree" "50000" "Reco" "-4.5" "4.5" "NoJetCal" "-1"
// g++ -o Run Response_Control.cxx `root-config --cflags --glibs` && ./Run "./Input_Files/MC23a_PFlow_test.txt" "IsolatedJet_tree" "100" "Reco" "-4.5" "4.5" "NoJetCal" "-1" 2>&1 | tee > log.txt

//+I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+
int main ( int argc ,char* argv[] ){
    std::cout << "+I+\n";
    // path_to_files  increment Step eta_min eta_max LegendName
    std::string input = argv[3];
    // TTree_name
    std::string fileName = argv[1];
    std::cout<<fileName<<"\n";

    std::string treeName = argv[2];
    std::cout<<treeName<<"\n";
    
    int increment = std::stoi(argv[3]);
    std::cout<<increment<<"\n";

    std::string stepName = argv[4];
    std::cout<<"Step: "<<stepName<<"\n";
    
    float upper_limit = std::stof(argv[5]);
    float lower_limit = std::stof(argv[6]);
    std::cout<<"Eta in: ["<<lower_limit << "; "<<upper_limit<<"]\n";

    std::string legendName = argv[7];
    std::cout<<"Legend name: "<<legendName<<"\n";
    
    int Num_Leading_Jets = std::stoi(argv[8]);
    std::cout<<argc <<" \n";
    
    // Response_vs_E_true * h = new Response_vs_E_true( );

    std::unique_ptr<Response_vs_E_true> h = std::make_unique<Response_vs_E_true>();
    h->makeBinning(lower_limit, upper_limit);
    // h->Response_Control(fileName , treeName, increment, stepName, upper_limit, lower_limit, legendName , Num_Leading_Jets);
    
    /**/
    std::cout<<"C++ version: "<<__cplusplus<<std::endl;
    return 0;
}
//+I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+ +I+
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
