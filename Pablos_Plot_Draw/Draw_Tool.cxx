#include "../Plot_Helpers_H.h"
#include "./HEADER_H.h"
string Find_Dependence_On(string f_str){
    string dep = "";
    dep =  FindSubString( f_str,  "Mu")? "Mu" : "";
    if (dep.size()>0)  return dep;
    dep =  FindSubString( f_str,  "NPV")? "NPV" : "";
    
    return dep;
}
string Find_Correction_On(string f_str){
    string corr = "";
    corr =  FindSubString( f_str,  "Reco")? "None" : "";
    if (corr.size()>0)  return corr;
    corr =  FindSubString( f_str,  "Area")? "Area" : "";
    if (corr.size()>0)  return corr;
    corr =  FindSubString( f_str,  "1D")? "1D" : "";
    if (corr.size()>0)  return corr;
    corr =  FindSubString( f_str,  "3D")? "3D" : "";
    if (corr.size()>0)  return corr;

    return corr;
}
void Draw_Tool(){

    gROOT->SetStyle("Plain");
	gStyle->SetOptFit(11111);
    gStyle->SetOptStat(0);
    gStyle->SetTitleFontSize(0.02);

    string PT_Dependence_On="";
    string correction="";
    

    

    TFile * Pablo_file [4];
    TH1F * Pablo_hist[4];
    TCanvas *canvas = new TCanvas("dpt","dpt",1000,1000);
    TLegend *  legend = new TLegend(0.75,0.75,0.9,0.9);
    legend->AddEntry("","Correction","");
    canvas->cd();
    for (int file_iter  = 0; file_iter< tfile_name.size(); file_iter ++){
        PT_Dependence_On = Find_Dependence_On(tfile_name[file_iter]);
        cout<<PT_Dependence_On<<"\n";
        correction = Find_Correction_On(tfile_name[file_iter]);
        cout<<correction<<"\n";
        string title_name = "";
        title_name = "#frac{d p_{T}}{d"+PT_Dependence_On+"} for p_{T}^{true} bin ["+TruePtBinning[PT_BIN]+":"+TruePtBinning[PT_BIN+1]+"];#eta;val" ;
        string Pablo_hist_name = "etaDep_pT_"+to_string(PT_BIN);
        Pablo_file[file_iter] = new TFile(FSTCA(tfile_name[file_iter]),"read");
        Pablo_hist[file_iter] =  (TH1F*)Pablo_file[file_iter]->Get(FSTCA(Pablo_hist_name));
        Pablo_hist[file_iter]->SetTitle(FSTCA(title_name));
        Pablo_hist[file_iter]->GetYaxis()->SetRangeUser(-0.35,0.3);
        
        if (file_iter == 0) Pablo_hist[file_iter]->SetLineColor(kRed);
        if (file_iter == 1) Pablo_hist[file_iter]->SetLineColor(kBlue);
        if (file_iter == 2) Pablo_hist[file_iter]->SetLineColor(kGreen);
        if (file_iter == 3) Pablo_hist[file_iter]->SetLineColor(kMagenta);
        Pablo_hist[file_iter]->SetLineWidth(4);
        legend->AddEntry(Pablo_hist[file_iter],FSTCA(correction),"lep");
        Pablo_hist[file_iter]->Draw("SAME");
        // th1 = (TH1D *)th1_file[i]->Get(From_String_To_Char_Array(name_histo));
    }
    legend->Draw("SAME");
    string folder = "./Plots_"+PT_Dependence_On+"/";
    Create_Folder(folder);
    string canvas_name = folder + PT_Dependence_On+"_"+to_string((int)TruePtBinning[PT_BIN])+"_"+to_string((int)TruePtBinning[PT_BIN+1])+".png";
    canvas->SaveAs(FSTCA(canvas_name));
    // Pablo_file[0]->ls();














    // Print_Vector_Line(tfile_name);
    
    
    return;
}