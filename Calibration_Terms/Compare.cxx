#include "Cal_Term_H.h"
vector<double>FromStringToDoubleVector(string str){
    str+=' ';
    vector<double> a;
    vector<string> b;
    int strt  = 0;
    for (int i = 0; i < str.size(); i++){

        if (str[i]==' ' || i == str.size()-1)
        {
            if (i== strt)
            {
                strt = i +1;
            }
            else{
                    string lcl_str ;
            for (int j = strt; j < i; j++){
                lcl_str += str[j];
            }   
            strt = i+1 ;
            b.push_back(lcl_str);
            }
            
        }
    }
    for (string s : b){
        // cout<< s<<"\n";
        a.push_back(stod(s));
    }
        


    return a;

}
vector<double>FSTDV(string str){
    return FromStringToDoubleVector(str);
}


void Compare(){
    Term_Name = "NPV";
    vector<double> Term1;
    vector<double> Term2;
    Term1 = FSTDV("        -0.001    -0.009          -0.041 -0.006 -0.059 -0.074 -0.284 0.095 -0.033           -0.194 -0.044 0.029");
    Term2 = MuTerm;
    gROOT->SetStyle("ATLAS");
    TGraph * Term_Graph1 = new TGraph(ResidualAbsEtaBins.size());
    TGraph * Term_Graph2 = new TGraph(ResidualAbsEtaBins.size());
    float t_curr, t_prev;
    t_curr = 0;
    t_prev = 0;
    
    cout<< Term1.size()<<endl;
    cout<< Term2.size()<<endl;
    
    vector<double> offset1 = computeoffsets(ResidualAbsEtaBins, Term1 ) ;
    vector<double> offset2 = computeoffsets(ResidualAbsEtaBins, Term2 ) ;
    
    
    for ( int i = 0 ; i < ResidualAbsEtaBins.size(); i ++){
    
        // cout<<t_curr<<"\n";
        Term_Graph1->AddPoint(ResidualAbsEtaBins[i], offset1[i]);
        Term_Graph2->AddPoint(ResidualAbsEtaBins[i], offset2[i]);
        // t_prev = t_curr ;
        
    }

    TCanvas * c = new TCanvas("canvas","canvas",800,800);
    char * name_to_graph ;
    if ( Term_Name == "NPV")
        Term_Graph2->SetTitle(From_String_To_Char_Array("NPV term factor;#eta;val"));
    else if ( Term_Name == "Mu")
        Term_Graph2->SetTitle(From_String_To_Char_Array("#mu term factor;#eta;val"));
    Print_Vector_Line(Term1);
    Print_Vector_Line(Term2);
    Term_Graph1->SetTitle("1D corr params: a vs ade;#eta;val");
    Term_Graph1->SetMarkerStyle(108);
    Term_Graph1->SetMarkerColor(kRed);
    Term_Graph1->SetMarkerSize(2);
    
    Term_Graph2->SetMarkerStyle(109);
    Term_Graph2->SetMarkerColor(kBlue);
    Term_Graph2->SetMarkerSize(1.5);
    
    
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("1D corr params: a vs ade;#eta;#frac{#partial p_{T}}{#partial #mu}");
    //mg->SetTitle("1D corr params: a vs ade;#eta;#frac{#partial p_{T}}{#partial NPV}");
    mg->Add(Term_Graph1,"APL");
    mg->Add(Term_Graph2,"APL");
    mg->Draw("a");

    TLegend *  legend = new TLegend(0.5,0.7,0.9,0.9);


       
    
    legend->AddEntry(Term_Graph1,"mc16 all","lp");
    legend->AddEntry(Term_Graph2,"mc16a","lp");
    legend->Draw();

    char * name_to_save = From_String_To_Char_Array("./"+Term_Name+"Term"+".png");
    cout<<name_to_save<<endl;
    c->SaveAs(name_to_save);
    
    
    
    return;
}