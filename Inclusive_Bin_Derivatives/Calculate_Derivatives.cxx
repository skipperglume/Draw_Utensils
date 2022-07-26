#include "Inclusive_H.h"

Double_t Get_Mean_Slope(const vector<Double_t> &sl ){

    Double_t AV=0.0;
    
    for(int t =0; t< sl.size();t++){
        
        AV+=sl[t];
    }
    AV/=sl.size();
    return AV;
}

Double_t Get_Average_Slope(const vector<Double_t> &sl, const vector<Double_t> &we ){

    Double_t AV=0.0;
    Double_t WE=0.0;
    for(int t =0; t< sl.size();t++){
        WE+=we[t];
        AV+=we[t]*sl[t];
    }
    AV/=WE;
    return AV;
}

Double_t Get_RMS(const vector<Double_t> &sl, const vector<Double_t> &we , Double_t AV){

    Double_t RMS=0.0;
    Double_t WE=0.0;
    for(int t =0; t< sl.size();t++){
        WE+=we[t];
        
    }
    for(int t =0; t< sl.size();t++){
        Double_t w = we[t]/WE;
        RMS+=w*w*(sl[t]-AV)*(sl[t]-AV);
        
    }
    

    return sqrt(RMS);
}
Double_t Get_Averaged_Error(const vector<Double_t> &er, const vector<Double_t> &we ){

    Double_t ER=0.0;
    Double_t WE=0.0;
    for(int t =0; t< er.size();t++){
        WE+=we[t];        
    }
    for(int t =0; t< er.size();t++){
        Double_t w = we[t]/WE;
        ER+=w*w*er[t]*er[t];
    }
    

    return sqrt(ER);
}
Double_t Get_MAX_Error(const vector<Double_t> &er){

    Double_t ER=0.0;
    
    
    for(int t =0; t< er.size();t++){
        if(abs(er[t])>ER) ER = abs(er[t]);
    }
    

    return ER;
}
void Calculate_Derivatives(){
    
    
        //      /afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/saved_TProfiles.root  NO corr
    //      /afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TProfiles_area_coor.root  AREA correction
    //      /afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TProfiles_Dependence_On_Mu_CORR_None.root
    //      /afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TProfiles_Dependence_On_Mu_CORR_Area.root
    //      /afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TProfiles_Dependence_On_Mu_CORR_3D.root

    // string tfile_name = "./TProfile_pngs/saved_TProfiles_Dependence_On_Mu_CORR_None.root";
    // string tfile_name = "./TProfile_pngs/saved_TProfiles_Dependence_On_Mu_CORR_Area.root";
    // string tfile_name = "./TProfile_pngs/saved_TProfiles_Dependence_On_Mu_CORR_1D.root";
    
    
    //string tfile_name = "/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TProfiles_Dependence_On_Mu_CORR_3D.root";

    
    string tfile_name = "./TProfile_pngs/saved_TProfiles_Dependence_On_NPV_CORR_None.root";
    // string tfile_name = "./TProfile_pngs/saved_TProfiles_Dependence_On_NPV_CORR_Area.root";
    // string tfile_name = "./TProfile_pngs/saved_TProfiles_Dependence_On_NPV_CORR_1D.root";


    // string tfile_name = "/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TProfiles_Dependence_On_NPV_CORR_3D.root";
    
    gROOT->SetStyle("Plain");
	gStyle->SetOptFit(11111);
    gStyle->SetOptStat(0);
    Initialize_Binning();
    if (FindSubString(tfile_name, "Mu"))
        PT_Dependence_On = "Mu";
    if (FindSubString(tfile_name, "NPV"))
        PT_Dependence_On = "NPV";
    if (FindSubString(tfile_name, "None"))        
        correction = "None";
    if (FindSubString(tfile_name, "3D"))        
        correction = "3D";
    if (FindSubString(tfile_name, "1D"))        
        correction = "1D";
    if (FindSubString(tfile_name, "Area"))        
        correction = "Area";
    if(PT_Dependence_On == "" || correction == "")
        return;
    cout<<PT_Dependence_On<<" : : "<< correction<<"\n";

    int IS_NPV = 0; 
    int IS_Mu = 0; 
    if (PT_Dependence_On == "Mu")
        IS_Mu = 1;
    if (PT_Dependence_On == "NPV")
        IS_NPV = 1;
    if(PT_Dependence_On == "NPV"){
        PtBins = PtBins2;
        EtaBins = EtaBins2;
        NpvBins = NpvBins2;
    }
    if(PT_Dependence_On == "Mu"){
        MuBins = MuBins2;
        PtBins = PtBins2;
        EtaBins = EtaBins2;
    }
    TProfile * TProfile_Pt_vs_mu_binned [ (EtaBins.size() -1) * (PtBins.size())  ];
    
    

    TFile * loaded_TProfiles = new TFile(From_String_To_Char_Array(tfile_name),"read");
    
    
        
    

    
    
    for ( int i=0; i< EtaBins.size()-1; i++ ){
        for ( int j=0; j< PtBins.size(); j++ ){            
            int iter = i + ( EtaBins.size() - 1 )*j;
            string name_str = Create_Name_eta_pt_NPV_mu("TProfile_Pt_VS_Mu_Eta_",i, j, IS_NPV, IS_Mu, iter );
        
            TProfile_Pt_vs_mu_binned[iter] = (TProfile*)loaded_TProfiles->Get(From_String_To_Char_Array(name_str));
            cout<< name_str <<"\n";
            cout<<iter<<": "<<TProfile_Pt_vs_mu_binned[iter]->GetEntries()<<"\n";
        }
    }
    
    
    
    TCanvas* Averaged_pt_canvas[ (EtaBins.size() -1) * (PtBins.size()) ];
    TF1 * averaged_linear_fit[ (EtaBins.size() -1) * (PtBins.size()) ];
    
    for ( int i=0; i< EtaBins.size()-1; i++ ){
        for ( int j=0; j< PtBins.size(); j++ ){
            int iter = i + ( EtaBins.size() - 1 )*j;
            vector<int> bounaries = Boundaries_Of_Fit((*TProfile_Pt_vs_mu_binned[iter]));
            string name_str = Create_Name_eta_pt_NPV_mu("averaged_canvas",i, j, IS_NPV, IS_Mu, iter );
            Averaged_pt_canvas[iter] = new TCanvas(From_String_To_Char_Array(name_str), From_String_To_Char_Array(name_str), 800, 800);
            Averaged_pt_canvas[iter]->cd();
            if (PT_Dependence_On == "Mu")
                Averaged_pt_canvas[iter]->DrawFrame(MuBins[0],0.0,MuBins[MuBins.size()-1],80.0);
            else if (PT_Dependence_On == "NPV")
                Averaged_pt_canvas[iter]->DrawFrame(NpvBins[0],0.0,NpvBins[NpvBins.size()-1],80.0);
            
            TProfile_Pt_vs_mu_binned[iter]->SetLineColor(kBlue);
            TProfile_Pt_vs_mu_binned[iter]->GetYaxis()->SetRangeUser(0.0,80.0);
            TProfile_Pt_vs_mu_binned[iter]->Draw("E1");
            string name_fit_name_str =    Create_Name_eta_pt_NPV_mu("averaged_linear_fit_",i, j, IS_NPV, IS_Mu, iter );
                //cout<<From_String_To_Char_Array(name_fit_name_str)<<endl;
            
            if (PT_Dependence_On == "Mu")
                averaged_linear_fit[iter ] = new TF1(From_String_To_Char_Array(name_fit_name_str) ,"[0]+x*[1]",MuBins[0],MuBins[MuBins.size()-1]);
            else if (PT_Dependence_On == "NPV")
                averaged_linear_fit[iter ] = new TF1(From_String_To_Char_Array(name_fit_name_str) ,"[0]+x*[1]",NpvBins[0],NpvBins[NpvBins.size()-1]);
            
            averaged_linear_fit[iter ]->SetParameter(0,0.0);
            averaged_linear_fit[iter ]->SetParameter(1,0.0);
            
                //TProfile_Pt_vs_mu_binned[(i-1)*PtBins.size() + j]->Fit(averaged_linear_fit[(i-1)], "F", "L",MuBins[0], 45.0); //
            
            cout<<"CheckP V\n";
            

            if (PT_Dependence_On == "Mu")
                TProfile_Pt_vs_mu_binned[iter]->Fit(averaged_linear_fit[iter], "M","A",MuBins[bounaries[0]+1],MuBins[bounaries[1]-1]); 
            else if (PT_Dependence_On == "NPV")
                TProfile_Pt_vs_mu_binned[iter]->Fit(averaged_linear_fit[iter], "M","A",NpvBins[bounaries[0]+1],NpvBins[bounaries[1]-1]); 

            averaged_linear_fit[iter]->SetLineColor(kRed);
            averaged_linear_fit[iter]->SetLineWidth(3);
            Averaged_pt_canvas[iter]->cd();
            cout<<"CheckP VI\n";
            averaged_linear_fit[iter]->Draw("SAME");
            string folder_name = "./Linear_Fit_pngs/PT_Bin_"+to_string(j);
            Create_Folder(folder_name);
            string sub_name = folder_name+"/averaged_"+correction+"_"+PT_Dependence_On+"_";
            name_str = Create_Name_eta_pt_NPV_mu(sub_name,i, j, IS_NPV, IS_Mu, iter ,"_pt_vs_mu.png" );
            
            Averaged_pt_canvas[iter]->SaveAs(From_String_To_Char_Array(name_str));

            cout<<"\n";
            /*                
                
                cout<<Total_TProfile_Entries((*TProfile_Pt_vs_mu_binned[iter]))<<"\n";
                cout<<iter <<endl;
                
                //cout<< EtaBins[i] << ": "<<  averaged_linear_fit[(i-1)*PtBins.size() + j]->GetParameter(1) <<endl;
                
                
                
                
                
                
            */            
        }

    }
    

    
    TH1D * THistos[PtBins.size()];

    for ( int j=0; j< PtBins.size(); j++ ){
        string name = Create_Name_eta_pt_NPV_mu("th1d_"+correction+"_"+PT_Dependence_On+"_",0, j, IS_NPV, IS_Mu, j );
        THistos[j] = new TH1D(From_String_To_Char_Array(name),From_String_To_Char_Array(name),EtaBins.size()-1, &EtaBins[0]);
    }
    
    for ( int i=0; i< EtaBins.size()-1; i++ ){

        for ( int j=0; j< PtBins.size(); j++ ){
            int iter = i + ( EtaBins.size() - 1 )*j ;
            cout<<"ETABIN: "<<i<<" PTBIN: "<<j<<"\n";
            
            
            
            
            
            THistos[j]->SetBinContent( i+1 , averaged_linear_fit[iter]->GetParameter(1));
            THistos[j]->SetBinError( i+1 , averaged_linear_fit[iter]->GetParError(1) );
            
            cout<< THistos[j]->GetBinWidth(i+1)<<"\n";
        }

    }

    string folder_name = "./Slopes_root";
    Create_Folder(folder_name);
    
    string save_name = folder_name+"/saved_TH1_slopes_Dependence_" +PT_Dependence_On+"_CORR_"+correction  +".root";
    
    TFile * save_Histos = new TFile(From_String_To_Char_Array(save_name),"recreate");
    
    TCanvas* TH1d_pt_canvas[ PtBins.size()];
    
    for ( int j=0; j< PtBins.size(); j++ ){
        string name = Create_Name_eta_pt_NPV_mu("canvas",0, j, IS_NPV, IS_Mu, j );
        TH1d_pt_canvas[j] = new TCanvas(From_String_To_Char_Array(name), From_String_To_Char_Array(name), 800, 800);
        TH1d_pt_canvas[j ]->cd();
        THistos[j]->Draw();
        THistos[j]->Print();
        name = Create_Name_eta_pt_NPV_mu(folder_name + "/canvas_"+correction+"_"+PT_Dependence_On+"_",0, j, 0, 0, j ,"_dpt_vs_eta.png" );
        TH1d_pt_canvas[j]->SaveAs(From_String_To_Char_Array(name));
        name=to_string(j);
        THistos[j]->Write();
    }
    save_Histos->Close();
    /*
    for ( int i=0; i< EtaBins.size(); i++ ){
        cout<< EtaBins[i]<<";";
        //cout<< &EtaBins[0];
    }
    cout<<"\n";
    
    loaded_TProfiles->Close();
    
    */
    return;
}