#include<vector>
#include<string>
#include<iostream>
using namespace std;
void plot(const char * histo, const std::shared_ptr<TFile> &myFile){
    // myFile->Get(histo)->ls();
    std::unique_ptr<TCanvas> canvas(new TCanvas("canvas","canvas", 800,800)  );
    if (!myFile->Get(histo)){
        std::cout<<"ERROR\n";
        exit(1);
    }
    myFile->Get(histo)->Draw();
    string saveName = histo ;
    saveName  = "./plots/"+saveName+ ".png";
    canvas->SaveAs (saveName.c_str());
    std::cout << "Saved at: "<<saveName<<"\n";
    return;
}
void test(){
    system("mkdir plots");
    std::shared_ptr<TFile> myFile = std::shared_ptr<TFile>{TFile::Open("testFile.root", "READ")};
    myFile->ls();
    myFile->Print();
    vector<string> toPlot;

    for (int i =0 ; i < 22; i++){
        toPlot.push_back("diff_eta_" + to_string(i)+"_pt_0_zy0_mean_myfit_par1_myfit_par0");
        cout<< toPlot[toPlot.size()-1]<<"\n";
        plot(toPlot[toPlot.size()-1].c_str(),myFile);
    }


    
    return;
}
