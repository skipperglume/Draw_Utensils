#include "Inclusive_H.h"



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

// This function gives the bin number in which the event by value of eta should be stored. 
// Can be used for general stuff

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
template <typename T> 
int Get_Bin_Of_Absolute_Value_T( vector<T> & etabin ,  T &eta ){
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

// Returns boundaries of filled elements in TProfile
Double_t Total_TProfile_Entries(TProfile & TProf){
    Double_t total = 0.0;
    for (int i =1 ; i < TProf.GetNbinsX()+1; i++) {
        total += TProf.GetBinEntries(i);
        
        
    }
    return total;
}

vector<int> Boundaries_Of_Fit(TProfile & TProf){
    vector<int> a;
    cout<< TProf.GetNbinsX()<<endl;
    cout<< TProf.GetNbinsY()<<endl;
    int x_min=0;
    int x_max=0;
    for (int i =1 ; i < TProf.GetNbinsX()+1; i++) {
        if ( TProf.GetBinContent( i )>0){
            if(x_min==0)
                x_min=i;
            x_max=i;
        }
        cout<< TProf.GetBinContent(i)<<"; ";
        
    }
    
    cout<<"\n";
    a.push_back(x_min);
    a.push_back(x_max);
    cout<<"First: "<<a[0]<<" Second: "<<a[1]<<"\n";
    return a;

}
template <typename T , typename Y> 
int Get_Bin_Of_Absolute_Value_T( vector<T> & etabin ,  Y &eta ){
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
template <typename T , typename Y,  typename U, typename I, typename O> 
string Create_Name_eta_pt_NPV_mu(string custom, T eta, Y pt, U NPV, I mu, O n, string end = "" ){
    string out = "";
    out = custom;
    out += "_eta_"+to_string((int)(eta));
    out += "_pt_"+to_string((int)pt);
    out += "_NPV_"+to_string((int)NPV);
    out += "_mu_"+to_string((int)mu);
    out += "_n_"+to_string((int)n);
    out += end;
    return out;
}

Double_t DeltaPtResidual(Double_t pt, Double_t z, Double_t f,Double_t s ){
    return z + f*pt+s*TMath::Log(pt);
}

Double_t Get_Correction(TList * CoeffLists, Double_t pt, int eta_bin, int NPV_bin, int mu_bin){
    string zero_order_name = "intersections";
    string first_order_name = "slopes";
    string second_order_name = "SecondOrderCoeff";
    //CoeffLists->Print();
    TList * intercepts = (TList *) CoeffLists->FindObject(From_String_To_Char_Array(zero_order_name));	
    
	TList * slopes = (TList *) CoeffLists->FindObject(From_String_To_Char_Array(first_order_name));	
    
	TList * secondOs = (TList *) CoeffLists->FindObject(From_String_To_Char_Array(second_order_name));	

    Double_t coeff_i = 0.0 ;
	Double_t coeff_s = 0.0 ;
	Double_t coeff_SO = 0.0 ;

    string name_of_th2d = "intersections_eta"+to_string(eta_bin);
	TH2D * TH2D_intercept = (TH2D*)intercepts->FindObject(From_String_To_Char_Array(name_of_th2d));
	name_of_th2d = "slopes_eta"+to_string(eta_bin);
    TH2D * TH2D_slope = (TH2D*)slopes->FindObject(From_String_To_Char_Array(name_of_th2d));
    name_of_th2d = "intersections_eta"+to_string(eta_bin);
    TH2D * TH2D_secondO = (TH2D*)secondOs->FindObject(From_String_To_Char_Array(name_of_th2d));

    coeff_i = TH2D_intercept->GetBinContent(NPV_bin,mu_bin);
    coeff_s = TH2D_slope->GetBinContent(NPV_bin,mu_bin);
    coeff_SO = TH2D_secondO->GetBinContent(NPV_bin,mu_bin);
    Double_t residual_correction = DeltaPtResidual(pt,coeff_i,coeff_s,coeff_SO );
    //delete TH2D_intercept, TH2D_slope, TH2D_secondO;
    
    return residual_correction;
}

vector<double> ComputeOffsets(vector<double> etaBins, vector<double> term){
  std::vector <double> offset;
  offset.push_back(term.at(0));  
  for(unsigned int i=1; i<etaBins.size();++i){
    double espace = etaBins.at(i)-etaBins.at(i-1);
    double ioffs = offset.at(i-1)+term.at(i)*espace;
    offset.push_back(ioffs);
  }
  return offset;
}

double Interpolation (vector<double> etaBins, vector<double> term, vector<double> offset, Float_t eta){
  double correction=0;
  //  std::cout<<"eta : "<<eta<<std::endl;
  for(unsigned int i=0; i<(etaBins.size()-1);++i){
    if (eta >= etaBins.at(i) && eta < etaBins.at(i+1)){
      correction = offset.at(i) + (eta-etaBins.at(i))*term.at(i+1); // computing value of the linear function at bin i for a given value of eta
      //  std::cout<<"inside interpolation if"<<std::endl;
      break;
    }
  }
  return correction;      
}


void Create_TProfiles(){
    
    cout<<"Welcome Aristocrat!"<<endl;
    Initialize_Binning();
    //Print_Vector_Line(Config_MuBins);
    
    //muNBin: 24    muLow:  0       muHigh: 72

    //NPVNBin: 25   NPVLow:  0      NPVHigh: 50

    
    if(PT_Dependence_On == "NPV"){
        // MuBins = NpvBins2;
        PtBins = PtBins2;
        EtaBins = EtaBins2;
        NpvBins = NpvBins2;
    }
    if(PT_Dependence_On == "Mu"){
        MuBins = MuBins2;
        PtBins = PtBins2;
        EtaBins = EtaBins2;
        // NpvBins = NpvBins2;
    }
    
    // Print_Vector_Line(Config_EtaBins);
    

    
    string str;
    ifstream infile ;
    vector <string> paths_to_ttrees ;
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
    vector<Float_t>* pt_true;
    vector<Float_t>* jet_area;
    Float_t         rho;
    //Double_t         rho;
    Int_t RunNum;

    TBranch* b_pt;
    TBranch* b_eta;
    TBranch* b_NPV;
    TBranch* b_mu;
    TBranch* b_weight;
    TBranch* b_weight_tot;
    TBranch* b_pt_true;
    TBranch* b_jet_area;
    TBranch* b_rho;
    TBranch* b_RunNum;

    Double_t luminosity=0;
    
    
    //vector<float> PtBins = { 0.0, 200.0};
    //vector<float> EtaBins = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.7,2.9,3.0,3.075,3.15,3.25,3.35,3.45,3.6,3.8,4.1,4.5,4.9};
    //vector<float> EtaBins = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0,1.2, 1.4,1.6,1.8,2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.3, 3.6, 3.9, 4.2, 4.5};
    //vector<Int_t> NpvBins = {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74};
    //vector<float> PtBins = { 10.0, 15.0, 20.0, 30.0, 60.0, 120.0, 200.0};


    
    
    

    
    
    // TProfile in which values are stored
    // They are organized, such that each event of bin in eta and in pt is saved in corresponding 
    // number of TProfile array. 
    // If event has eta bin I and pt bin J, than it is stored in: (I-1)*PtBins.size() + J
    int IS_NPV = 0; 
    int IS_Mu = 0; 
    if (PT_Dependence_On == "Mu")
        IS_Mu = 1;
    if (PT_Dependence_On == "NPV")
        IS_NPV = 1;
    vector<int> check;
    TProfile * TProfile_Pt_vs_mu_binned [ (EtaBins.size() -1) * (PtBins.size()) ];
    for ( int i=0; i< EtaBins.size()-1; i++ ){
        for ( int j=0; j< PtBins.size(); j++ ){
            
            int iter = i + ( EtaBins.size() - 1 )*j;
            
            string name_str = Create_Name_eta_pt_NPV_mu("TGraph_Pt_VS_Mu",i, j, IS_NPV, IS_Mu, iter );
            
            check.push_back(iter);
            
            name_str = Create_Name_eta_pt_NPV_mu("TProfile_Pt_VS_Mu_Eta_",i, j, IS_NPV, IS_Mu, iter,  ";#mu;p_{T}");
            if(PT_Dependence_On == "Mu")
                TProfile_Pt_vs_mu_binned[ iter ] = new TProfile(From_String_To_Char_Array(name_str),From_String_To_Char_Array(name_str), MuBins.size(), MuBins[0], MuBins[ MuBins.size()-1],  0.0,10000.0 );
            if(PT_Dependence_On == "NPV")
                TProfile_Pt_vs_mu_binned[ iter ] = new TProfile(From_String_To_Char_Array(name_str),From_String_To_Char_Array(name_str), NpvBins.size()-1, NpvBins[0], NpvBins[ NpvBins.size()-1],  0.0,10000.0 );
            TProfile_Pt_vs_mu_binned[ iter ]->Sumw2();
            cout<< From_String_To_Char_Array(name_str)<<endl;
            
        }
    }
    cout<< EtaBins.size()<<endl;
    cout<< PtBins.size()<<endl;
    
    
    

    string path_to_parameters = "/afs/cern.ch/work/d/dtimoshy/RC/CorrelatedCorrection/residualCalibParameters.root";	
	TFile *f = new TFile(From_String_To_Char_Array(path_to_parameters));
	TList *CoeffLists = (TList*)f->Get("param3D");
    Print_Vector_Line(EtaBins);
    Print_Vector_Line(PtBins);
    // Print_Vector_Line(NpvBins);
    // Print_Vector_Line(MuBins);

    
    
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
        //Tree->SetBranchAddress("rhoEM", &rho, &b_rho);
        Tree->SetBranchAddress("runNumber", &RunNum, &b_RunNum);
        Tree->SetBranchAddress("NPV", &NPV, &b_NPV);
        //recojet_pt->at(j)-pt->at(j)-jet_area->at(j)*rho*0.001
        for(int ientry=0;ientry<Tree->GetEntries()/100;ientry++){ 
            
            Tree->GetEntry(ientry);
            //rho*=0.001; // RHO  normalization CHANGED_HERE
            if (RunNum == 284500) { //mc16a
                luminosity = 3219.56 + 32988.1; 
                    
            } 
            else if (RunNum == 300000) { //mc16d
                luminosity = 44307.4;
                    
            } 
            else if (RunNum == 310000) { //mc16e
                luminosity = 58450.1;
                
            } 
            //cout<<luminosity<<"\n";
            //weight*=luminosity;
            //weight_tot*=luminosity;
            
            for (int jet_iter = 0; jet_iter < pt->size(); jet_iter++  ){
                //cout<< pt->at(jet_iter)<<"\n";
                
                int eta_bin = Get_Bin_Of_Absolute_Value_T( EtaBins, jet_eta->at(jet_iter) );
                int pt_bin = Get_Bin_Of_Absolute_Value_T( PtBins, pt_true->at(jet_iter) );
                // int NPV_bin = Get_Bin_Of_Absolute_Value_T( NpvBins, NPV);
                // int mu_bin = Get_Bin_Of_Absolute_Value_T( MuBins,mu );
                //cout<< eta_bin << " "<< pt_bin<<endl;
                //cout<< jet_eta->at(jet_iter)  << " " <<  pt_true->at(jet_iter)<<endl ;
                
                int iter = ( eta_bin -1 ) + ( EtaBins.size() - 1 )*( pt_bin -1 ) ;
                int iter_inclusive = ( eta_bin -1 ) + ( EtaBins.size() - 1 )*( PtBins.size() -1 ) ;
                cout<<"iter: "<<iter<<" ;inclusive: "<< iter_inclusive<<"\n";
                // cout<<"eta value: "<< jet_eta->at(jet_iter)<< " | eta bin: "<< eta_bin<<endl;
                // cout<<"pt value: "<< pt_true->at(jet_iter)<< " | pt bin: "<< pt_bin<<endl;
                //cout<<"NPV: "<<NPV<< " NPV bin: "<< NPV_bin<<endl;
                //cout<< " mu bin: "<< mu_bin<<endl;
                if(eta_bin > 0  ){
                    if(correction == "None"){
                        // cout<<"check I\n";
                        if (pt_bin > 0)
                            TProfile_Pt_vs_mu_binned [iter]->Fill( mu, pt->at(jet_iter) , weight_tot  );
                        // cout<<"check II\n";
                        if (pt_true->at(jet_iter) >= PtBins[0] && pt_true->at(jet_iter) <= PtBins[PtBins.size()-1])
                            TProfile_Pt_vs_mu_binned [iter_inclusive]->Fill( mu, pt->at(jet_iter) , weight_tot  );
                        // cout<<"check III\n";
                    }
                    if(correction == "Area"){
                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho ;
                        // cout<<"pt area: "<<pt_area << " pt: "<< pt->at(jet_iter) <<" diff: "<< jet_area->at(jet_iter)*rho<< " true - reco: " <<pt_true->at(jet_iter) <<"\n";

                        // cout<<"check I\n";
                        if (pt_bin > 0)
                            TProfile_Pt_vs_mu_binned [iter]->Fill( mu, pt_area , weight_tot  );
                        // cout<<"check II\n";
                        if (pt_true->at(jet_iter) >= PtBins[0] && pt_true->at(jet_iter) <= PtBins[PtBins.size()-1])
                            TProfile_Pt_vs_mu_binned [iter_inclusive]->Fill( mu, pt_area , weight_tot  );
                        // cout<<"check III\n";
                    }
                    else if (correction == "1D"){
                        vector<double> NPVoffset;
                        vector<double> Muoffset;

                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho ;
                        Double_t corr1D = 0.0;
                        Double_t NPVtermAtEta, MutermAtEta;
                        NPVoffset = ComputeOffsets(ResidualAbsEtaBins,NPVTerm);
                        Muoffset = ComputeOffsets(ResidualAbsEtaBins,MuTerm);
                        
                        NPVtermAtEta = Interpolation(ResidualAbsEtaBins,NPVTerm,NPVoffset,abs(jet_eta->at(jet_iter) ));
                        //cout<<"NPV term: "<<NPVtermAtEta<<"\n";
                        MutermAtEta = Interpolation(ResidualAbsEtaBins,MuTerm,Muoffset,abs(jet_eta->at(jet_iter) ));
                        //cout<<"mu term :"<<MutermAtEta<<"\n";
                        corr1D = NPVtermAtEta*(NPV-1)+MutermAtEta*mu;
                        
                        cout<<"pt area: "<<pt_area << " pt: "<< pt->at(jet_iter) <<" diff: "<< jet_area->at(jet_iter)*rho<< " true - reco: " <<pt_true->at(jet_iter) <<"\n";
                        cout<<"corr1D: "<<corr1D<<"\n";
                        if (pt_bin > 0)
                            TProfile_Pt_vs_mu_binned [iter]->Fill( mu, pt_area - corr1D , weight_tot  );
                        // cout<<"check II\n";
                        if (pt_true->at(jet_iter) >= PtBins[0] && pt_true->at(jet_iter) <= PtBins[PtBins.size()-1])
                            TProfile_Pt_vs_mu_binned [iter_inclusive]->Fill( mu, pt_area - corr1D , weight_tot  );
                    }
                }

                /*
                if (eta_bin > 0 && pt_bin > 0 && NPV_bin > 0){
                    
                    
                    else if(correction == "Area"){
                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho ;
                        //cout<<"pt area: "<<pt_area << " pt: "<< pt->at(jet_iter) <<" diff: "<< jet_area->at(jet_iter)*rho <<"\n";
                        TProfile_Pt_vs_mu_binned [iter]->Fill( mu, pt_area, weight_tot  );
                    }
                    
                    else if(correction == "3D"){
                        int config_eta_bin = Get_Bin_Of_Absolute_Value_T( Config_EtaBins, jet_eta->at(jet_iter) );
                        int config_pt_bin = Get_Bin_Of_Absolute_Value_T( Config_PtBins, pt_true->at(jet_iter) );
                        int config_NPV_bin = Get_Bin_Of_Absolute_Value_T( Config_NpvBins, NPV);
                        int config_mu_bin = Get_Bin_Of_Absolute_Value_T( Config_MuBins,mu );
                        //cout<<"eta: " << config_eta_bin<<endl;
                        //cout<<"pt: " << config_pt_bin<<endl;
                        //cout<<"NPV: " << config_NPV_bin<<endl;
                        //cout<<"mu: " << config_mu_bin<<endl;
                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho ;
                        //cout<<"pt area: "<<pt_area << " pt: "<< pt->at(jet_iter) <<" diff: "<< jet_area->at(jet_iter)*rho<<"\n";
                        
                        if(pt_area>0){                        
                            Double_t DeltaResidual = Get_Correction(CoeffLists, pt_area,  config_eta_bin-1,  config_NPV_bin,  config_mu_bin);
                            //cout<<"DeltaResidual: "<<DeltaResidual<<endl;
                            //cout<<"pt area: "<<pt_area<<endl;
                            if (DeltaResidual == DeltaResidual && pt_area - DeltaResidual > 0){
                                TProfile_Pt_vs_mu_binned [iter]->Fill( mu, pt_area + DeltaResidual , weight_tot  );
                            }
                        }
                    }
                    else if (correction == "1D"){

                        vector<double> NPVoffset;
                        vector<double> Muoffset;

                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho ;
                        Double_t corr1D = 0.0;
                        Double_t NPVtermAtEta, MutermAtEta;
                        NPVoffset = ComputeOffsets(ResidualAbsEtaBins,NPVTerm);
                        Muoffset = ComputeOffsets(ResidualAbsEtaBins,MuTerm);
                        
                        NPVtermAtEta = Interpolation(ResidualAbsEtaBins,NPVTerm,NPVoffset,abs(jet_eta->at(jet_iter) ));
                        //cout<<"NPV term: "<<NPVtermAtEta<<"\n";
                        MutermAtEta = Interpolation(ResidualAbsEtaBins,MuTerm,Muoffset,abs(jet_eta->at(jet_iter) ));
                        //cout<<"mu term :"<<MutermAtEta<<"\n";
                        corr1D = NPVtermAtEta*(NPV-1)+MutermAtEta*mu;
                        
                        //cout<<"corr1D: "<<corr1D<<"\n";
                        TProfile_Pt_vs_mu_binned [iter]->Fill( mu, pt_area + corr1D , weight_tot  );
                    }
                    
                }
                if (eta_bin > 0 && NPV_bin > 0){
                    if(correction == "None"){
                        TProfile_Pt_vs_mu_binned [iter_inclusive]->Fill( mu, pt->at(jet_iter) , weight_tot  );
                    }
                    else if(correction == "Area"){
                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho ;
                        TProfile_Pt_vs_mu_binned [iter_inclusive]->Fill( mu, pt_area, weight_tot  );
                    }
                    else if(correction == "3D"){
                        int config_eta_bin = Get_Bin_Of_Absolute_Value_T( Config_EtaBins, jet_eta->at(jet_iter) );
                        int config_pt_bin = Get_Bin_Of_Absolute_Value_T( Config_PtBins, pt_true->at(jet_iter) );
                        int config_NPV_bin = Get_Bin_Of_Absolute_Value_T( Config_NpvBins, NPV);
                        int config_mu_bin = Get_Bin_Of_Absolute_Value_T( Config_MuBins,mu );
                        //cout<<"eta: " << config_eta_bin<<endl;
                        //cout<<"pt: " << config_pt_bin<<endl;
                        //cout<<"NPV: " << config_NPV_bin<<endl;
                        //cout<<"mu: " << config_mu_bin<<endl;
                        //cout<<"rho: " << rho<<endl;
                        //cout<<"pt: " <<  pt->at(jet_iter)<<endl;
                        //cout<<"jet_area: " <<  jet_area->at(jet_iter)<<endl;
                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho ;
                        //cout<<"pt_area: " <<  pt_area<<endl;
                        if(pt_area>0){                        
                            Double_t DeltaResidual = Get_Correction(CoeffLists, pt_area,  config_eta_bin-1,  config_NPV_bin,  config_mu_bin);
                            //cout<<"DeltaResidual: "<<DeltaResidual<<endl;
                            //cout<<"pt area: "<<pt_area<<endl;
                            if (DeltaResidual == DeltaResidual && pt_area - DeltaResidual > 0){
                                TProfile_Pt_vs_mu_binned [iter_inclusive]->Fill( mu, pt_area + DeltaResidual , weight_tot  );
                            }
                        }
                    }
                    else if (correction == "1D"){

                        vector<double> NPVoffset;
                        vector<double> Muoffset;

                        Double_t pt_area = pt->at(jet_iter) - jet_area->at(jet_iter)*rho;
                        Double_t corr1D = 0.0;
                        Double_t NPVtermAtEta, MutermAtEta;
                        NPVoffset = ComputeOffsets(ResidualAbsEtaBins,NPVTerm);
                        Muoffset = ComputeOffsets(ResidualAbsEtaBins,MuTerm);
                        
                        NPVtermAtEta = Interpolation(ResidualAbsEtaBins,NPVTerm,NPVoffset,abs(jet_eta->at(jet_iter) ));
                        //cout<<"NPV term: "<<NPVtermAtEta<<"\n";
                        MutermAtEta = Interpolation(ResidualAbsEtaBins,MuTerm,Muoffset,abs(jet_eta->at(jet_iter) ));
                        //cout<<"mu term :"<<MutermAtEta<<"\n";
                        corr1D = NPVtermAtEta*(NPV-1)+MutermAtEta*mu;
                        //cout<<"corr1D: "<<corr1D<<"\n";
                        TProfile_Pt_vs_mu_binned [iter_inclusive]->Fill( mu, pt_area + corr1D , weight_tot  );
                    }
                }
                if ( eta_bin == 1 && pt_bin == 1){
                    //cout<<( eta_bin - 1 ) * PtBins.size() + pt_bin-1<<endl;
                    //cout<< eta_bin << " "<< pt_bin<<endl;
                    //cout<< jet_eta->at(jet_iter)  << " " <<  pt_true->at(jet_iter)<<endl ;
                }
            */
            }
            
        }
        cout<<Tree->GetEntries()<<"\n";
        FILE_TO_TTREE->Close();
    }
    cout<<"Finished Filling TProfiles\n";
    f->Close();
    
    string name_to_save = "./TProfile_pngs/saved_TProfiles_Dependence_On_"+PT_Dependence_On+"_CORR_"+correction+".root";
    TFile * saved_TProfiles = new TFile(From_String_To_Char_Array(name_to_save),"recreate");
    for ( int i=0; i< EtaBins.size()-1; i++ ){
        for ( int j=0; j< PtBins.size(); j++ ){
            
            int iter = i + ( EtaBins.size() - 1 )*j;
            string name_str = Create_Name_eta_pt_NPV_mu("TProfile_Pt_VS_Mu_Eta_", i, j, IS_NPV, IS_Mu, iter );
            TProfile_Pt_vs_mu_binned[iter]->Write(From_String_To_Char_Array(name_str),TObject::kSingleKey);
                
            
        }
    }
    saved_TProfiles->Close();
    
    /*
    */
    /*
    */

}



