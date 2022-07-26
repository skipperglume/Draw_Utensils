#include "Cal_Term_H.h"

void Plot_Cal_Term(){
    
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
    vector<double> offset = computeoffsets(ResidualAbsEtaBins, Term_Vec ) ;
    Print_Vector_Line( ResidualAbsEtaBins );
    Print_Vector_Line( Term_Vec );
    Print_Vector_Line( offset ) ;
    
    for ( int i = 0 ; i < ResidualAbsEtaBins.size(); i ++){
        // t_curr = Term_Vec[i]+t_prev;
        // cout<<t_curr<<"\n";
        Term_Graph->AddPoint(ResidualAbsEtaBins[i], offset[i]);
        // t_prev = t_curr ;
        
    }

    TCanvas * c = new TCanvas("canvas","canvas",800,800);
    char * name_to_graph ;
    if ( Term_Name == "NPV")
        Term_Graph->SetTitle(From_String_To_Char_Array("NPV term factor;#eta;val"));
    else if ( Term_Name == "Mu")
        Term_Graph->SetTitle(From_String_To_Char_Array("#mu term factor;#eta;val"));
    
    
    Term_Graph->SetMarkerStyle(108);
    Term_Graph->SetMarkerColor(kRed);
    Term_Graph->SetMarkerSize(1.5);
    Term_Graph->Draw("APL");

    char * name_to_save = From_String_To_Char_Array("./"+Term_Name+"Term"+".png");
    cout<<name_to_save<<endl;
    c->SaveAs(name_to_save);
    
    

    return;
}