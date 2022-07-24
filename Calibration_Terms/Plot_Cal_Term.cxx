#include "Cal_Term_H.h"

void Plot_Cal_Term(){
    Print_Vector_Line( ResidualAbsEtaBins );
    TGraph * Term_Graph = new TGraph(ResidualAbsEtaBins.size());

    float t_curr, t_prev;
    t_curr = 0;
    t_prev = 0;
    vector<double>  Term_Vec; 
    if ( Term_Name == "NPV")
        Term_Vec = NPVTerm;
    else if ( Term_Name == "Mu")
        Term_Vec = MuTerm;
    else {cout<<"UNKNOWN TERM\n";return;    }

    for ( int i =0 ; i < ResidualAbsEtaBins.size(); i ++){
        t_curr = Term_Vec[i]+t_prev;
        Term_Graph->AddPoint(ResidualAbsEtaBins[i], t_curr );
        t_prev = t_curr ;
        cout<<t_curr<<"\n";
    }

    TCanvas * c = new TCanvas("canvas","canvas",800,800);
    Term_Graph->SetTitle("AW");
    Term_Graph->Draw("*A");
    c->SaveAs("./plot.png");



    return;
}