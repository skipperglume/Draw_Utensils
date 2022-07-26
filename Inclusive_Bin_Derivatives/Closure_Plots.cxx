#include "Inclusive_H.h"

void Closure_Plots(){
    gROOT->SetStyle("Plain");
	gStyle->SetOptFit(11111);
    gStyle->SetOptStat(0);
    gStyle->SetTitleFontSize(0.02);
    Initialize_Binning();
    PT_Dependence_On="";
    correction="";
    vector<string> tfile_name = {};

    // tfile_name.push_back("./Slopes_root/saved_TH1_slopes_Dependence_Mu_CORR_None.root");
    // tfile_name.push_back("./Slopes_root/saved_TH1_slopes_Dependence_Mu_CORR_Area.root");
    // tfile_name.push_back("./Slopes_root/saved_TH1_slopes_Dependence_Mu_CORR_1D.root");
    
    
    

    
    
    
    
    //tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TH1_slopes_Dependence_Mu_CORR_3D.root");

    
    
    tfile_name.push_back("./Slopes_root/saved_TH1_slopes_Dependence_NPV_CORR_None.root");
    tfile_name.push_back("./Slopes_root/saved_TH1_slopes_Dependence_NPV_CORR_Area.root");
    tfile_name.push_back("./Slopes_root/saved_TH1_slopes_Dependence_NPV_CORR_1D.root");


    // tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC/Draw_Utensils/project_derivative/saved_TH1_slopes_Dependence_NPV_CORR_3D.root");

    
    int PT_BIN = 1;
    
    if (PT_BIN >= PtBins2.size()){
        cout<<"Erorr: wrong PT BIN\n";
        return;
    }
    int pt_low,pt_high;
    if(PT_BIN ==  PtBins2.size()-1){
        pt_low = (int)PtBins2[0];
        pt_high = (int)PtBins2[PtBins2.size()-1];
    }
    else{
        pt_low = (int)PtBins2[PT_BIN];
        pt_high = (int)PtBins2[PT_BIN+1];
    }
    cout<< pt_low<<"   "<< pt_high<<"\n";
    TCanvas *canvas = new TCanvas("dpt","dpt",1000,1000);
    canvas->SetGridy();
    TFile * th1_file[tfile_name.size()];
    TH1D * th1;
    TLegend *  legend = new TLegend(0.75,0.75,0.9,0.9);
    legend->AddEntry("","Correction","");
    for(int i = 0; i <  tfile_name.size(); i ++){
        string name = tfile_name[i];

        if (FindSubString(name, "Mu"))
            PT_Dependence_On = "Mu";
        if (FindSubString(name, "NPV"))
            PT_Dependence_On = "NPV";
        if (FindSubString(name, "None"))        
            correction = "None";
        if (FindSubString(name, "3D"))        
            correction = "3D";
        if (FindSubString(name, "1D"))        
            correction = "1D";
        if (FindSubString(name, "Area"))        
            correction = "Area";
        if(PT_Dependence_On == "" || correction == "")
            return;
        int IS_NPV = 0; 
        int IS_Mu = 0; 
        if (PT_Dependence_On == "Mu")
            IS_Mu = 1;
        if (PT_Dependence_On == "NPV")
            IS_NPV = 1;
        cout<<PT_Dependence_On<<" : : "<< correction<<"\n";

        
        th1_file[i] = new TFile(From_String_To_Char_Array(name),"read");
        string name_histo =  Create_Name_eta_pt_NPV_mu("th1d_"+correction+"_"+PT_Dependence_On+"_", 0, PT_BIN, IS_NPV, IS_Mu, PT_BIN);
        th1 = (TH1D *)th1_file[i]->Get(From_String_To_Char_Array(name_histo));
        canvas->cd();
        th1->Print();
        th1->SetLineWidth(3);
        th1->GetYaxis()->SetRangeUser(-0.35,0.3);
        if (PT_Dependence_On == "Mu"){
            name = "#frac{dp_{T}}";
            name+="{d#mu}";
            name+=" over pt bin ["+ to_string(pt_low) + ":" + to_string(pt_high) + "];";
            name+="#eta;";
            name+="#frac{dp_{T}}{d#mu};";
        }
        if (PT_Dependence_On == "NPV"){
            name = "#frac{dp_{T}}";
            name+="{dNPV}";
            name+=" over pt bin ["+ to_string(pt_low) + ":" + to_string(pt_high) + "];";
            name+="#eta;";
            name+="#frac{dp_{T}}{dNPV};";
        }
        th1->SetTitle(From_String_To_Char_Array(name));
        //th1->SetTitleFont(63);
        //th1->SetTitleSize(0.01,"xyz");
        if(correction == "None"){
            th1->SetLineColor(kRed);
            th1->SetLineWidth(5);
            legend->AddEntry(th1,"None","lep");
        }
        if(correction == "Area"){
            th1->SetLineColor(kBlue);
            legend->AddEntry(th1,"Area","lep");
        }
        if(correction == "3D"){
            th1->SetLineColor(kGreen);
            legend->AddEntry(th1,"3D","lep");
        }
        if(correction == "1D"){
            th1->SetLineColor(kMagenta);
            legend->AddEntry(th1,"1D","lep");
        }
        th1->Draw("SAME");
        //cout<<"Check: "<<th1->GetBinContent(1)<<"\n";
        
    }
    string folder_name = "";
    string name = PT_Dependence_On+"_pT_"+to_string(pt_low)+"_"+to_string(pt_high)+"_.png";
    if (PT_Dependence_On == "Mu"){
        folder_name = "./Dependence_Mu/";
        Create_Folder(folder_name);
        name = folder_name + name;
    }
    if (PT_Dependence_On == "NPV"){
        folder_name = "./Dependence_NPV/";
        Create_Folder(folder_name);
        name = folder_name + name;
    }
    canvas->cd();
    legend->Draw();
    cout<<"+I+\n";
    canvas->SaveAs(From_String_To_Char_Array(name));
    cout<<"+I+\n";
    for(int i = 0; i <  tfile_name.size(); i ++){
        th1_file[i]->Close();
    }
    cout<<"+I+\n";
    return;
}