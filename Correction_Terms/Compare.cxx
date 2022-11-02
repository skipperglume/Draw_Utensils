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


TLegend * Custom_Legend_Coordinates(std::vector<float> coordinates){
    if (coordinates.size() !=4 ){
        std::cout<< "Wrong size of coordinates vector\n";
        return NULL;
    }

    TLegend * lg = new TLegend(coordinates[0],coordinates[1],coordinates[2],coordinates[3]);
    return lg;
}

void Compare(){
    Term_Name = "Mu";


    if (Term_Name != "NPV" && Term_Name != "Mu"){
        cout<< "Error of term name\n";
        return;
    }
    vector<double> Term1;
    vector<double> Term2;
    // NPV
    //   0.027 0.002 0.086 -0.035 0.073 0.079 0.398 -0.212 0.008 0.340 0.086 0.026
    // Mu
    //  -0.001 -0.009 -0.041 -0.006 -0.059 -0.074 -0.284 0.095 -0.033 -0.194 -0.044 0.029

    
    
    if (Term_Name == "Mu" ){
        // UFO MC20a
        // Term1 = FSTDV(" -0.017 -0.011 -0.039 -0.012 -0.055 -0.087 -0.316 0.122 -0.057 -0.229 -0.012 0.225");
        // Term2 = FSTDV(" -0.006 -0.011 -0.037 -0.016 -0.056 -0.086 -0.318 0.122 -0.064 -0.224 -0.011 0.224");
        Term1 = FSTDV(" -0.014 -0.009 -0.033 -0.009 -0.061 -0.081 -0.315 0.134 -0.068 -0.218 -0.022 0.234");
        Term2 = FSTDV(" -0.002 -0.009 -0.036 -0.007 -0.063 -0.082 -0.316 0.136 -0.071 -0.216 -0.018 0.232");
        
        
    }
        
    if (Term_Name == "NPV" ){
        // UFO MC20a
        // Term1 = FSTDV(" 0.016 0.012 0.090 -0.060 -0.018 0.086 0.598 -0.227 0.046 0.371 0.063 -0.220");
        // Term2 = FSTDV(" 0.027 0.010 0.093 -0.059 -0.016 0.085 0.603 -0.228 0.061 0.368 0.058 -0.222");
        Term1 = FSTDV(" 0.020 0.010 0.117 -0.059 -0.017 0.072 0.572 -0.236 0.055 0.357 0.076 -0.250");
        Term2 = FSTDV("0.029 0.008 0.121 -0.060 -0.010 0.070 0.583 -0.239 0.061 0.358 0.070 -0.249");
    }
        
    
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
    if (Term_Name == "Mu" )
        mg->SetTitle("1D corr params: a vs ade;#eta;#frac{#partial p_{T}}{#partial #mu}");
    if (Term_Name == "NPV" )
        mg->SetTitle("1D corr params: a vs ade;#eta;#frac{#partial p_{T}}{#partial NPV}");
    mg->Add(Term_Graph1,"APL");
    mg->Add(Term_Graph2,"APL");
    mg->Draw("a");

    std::vector<float> MuLegCoord  =    {0.5,0.7,0.9,0.9};
    std::vector<float> NPVLegCoord =    {0.5,0.2,0.9,0.4};

    TLegend *  legend ;
    if (Term_Name == "Mu" )
        legend = Custom_Legend_Coordinates(MuLegCoord);
    if (Term_Name == "NPV" )
        legend = Custom_Legend_Coordinates(NPVLegCoord);



       
    
    legend->AddEntry(Term_Graph1,"MC20a UFO NoArea","lp");
    legend->AddEntry(Term_Graph2,"MC20a UFO Area","lp");
    legend->Draw();

    char * name_to_save = From_String_To_Char_Array("./"+Term_Name+"Term"+".png");
    cout<<name_to_save<<endl;
    c->SaveAs(name_to_save);
    cout<<"All mc16 params: \n";
    Print_Vector_Line(Term1);
    cout<<"mc16a params: \n";
    Print_Vector_Line(Term2);
    
    
    return;
}   
