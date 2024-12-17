#include "Create_stacked_plot.cxx"
void Calculate_Total_Events(){
    cout<<"Welcome Aristocrat!"<<endl;
    Write_Date("Started_"+variable_name+"_"+weight_name);
    string str;
    ifstream infile ;
    vector <string> paths_to_ttrees ;
    
    infile.open("./UFO_MC20a.txt");
    
    while(!infile.eof()){
        getline(infile,str);
        if(BOOL_exists_file(str)){
            cout<<"FILE EXISTS: "<<str<<"\n\n";
            paths_to_ttrees.push_back(str);
        }            
        else
            cout<<"ERROR FILE DOES NOT EXIST: "<<str<<"\n\n";
    }
    infile.close();
    const vector<string> stack_tag = {  "364700","364701","364702","364703","364704","364705","364706","364707","364708","364709","364710","364711","364712"}; 
    vector<int> EntriesCount = vector<int>(stack_tag.size());
    int index = 0;
    for (int i = 0 ; i <=  paths_to_ttrees.size()-1; i++){ 
        TFile* FILE_TO_TTREE = new TFile(From_String_To_Char_Array(paths_to_ttrees[i]),"read");
        cout<< "\n\n Processing file: "<<paths_to_ttrees[i]<<"\n";
        index = Stack_Histi_Index(stack_tag, paths_to_ttrees[i]);
        cout<<i<<"/"<<paths_to_ttrees.size()<<" : " << index<<endl;
        TTree* Tree = (TTree*) FILE_TO_TTREE->Get("IsolatedJet_tree");
        cout<<Tree->GetEntries()<<"\n";
        EntriesCount[index]+=Tree->GetEntries();
    }
    for (int i =0 ; i < EntriesCount.size() ; i++ ){
        PrOut(i);
    }
    int sum = std::accumulate(EntriesCount.begin(), EntriesCount.end(), 0);
    PrOut(sum);
    // vector<int> EntriesCount(stack_tag.size());
    // PrOut(EntriesCount.size());
    // int test_int = 100;
    // PrOut(paths_to_ttrees[test_int]);
    // cout<< Stack_Histi_Index(stack_tag, paths_to_ttrees[test_int],'/',7)<<endl;
    /*
    
    
    
    
    
    
    cout<< paths_to_ttrees.size()<<endl;
    cout<< paths_to_ttrees[test_int]<<endl;
    vector <string> a = String_Split(paths_to_ttrees[test_int]);
    Print_Vector_Line(a);

    

    
       */
}