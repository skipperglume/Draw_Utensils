#ifndef HELPER_H 
#define HELPER_H

#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
#include <array>
#include <iterator>  
#include <utility>
#include <fstream>

// using namespace std;
char * FSTCA(std::string & name);
void Create_Folder(std::string name){

    std::string command = "mkdir "+ name;
    system(FSTCA(command) );

    return;
}
void Write_Date(std::string name){
    std::string command = "echo "+name+" >> txt.txt";
    system(FSTCA(command) );
    command = "date >> txt.txt";
    system(FSTCA(command) );

    return;
}

char * From_String_To_Char_Array( std::string & name){
    char * char_name[500];
    for (int i =0; i < name.size();i++){
        //cout<<name.at(i);
        char_name[i] = & name.at(i);
    }
    
    return (*char_name);
}

char * FSTCA(std::string & name){
    return From_String_To_Char_Array(  name);
}


template <typename T>
void Print_Vector_Line(vector<T> &a){
    cout<<"\n";
    for(int i=0; i < a.size(); i++){
        cout<< a[i]<<"; ";
    }
    cout<<"\n";
    return;
}
bool FindSubString(const std::string  str, const  std::string  substr){
    for(int i = 0; i < str.size(); i++){
        if(str.size()-i < substr.size())
            return false;
        if (substr[0] == str[i]){
            bool o = true;
            for(int j = 1; j < substr.size(); j++){
                if(substr[j]!=str[i+j]){
                    o = false;
                    break;
                }
            }   
            if(o){
                //cout<<i<<"\n";
                return true;    
            }
        }
        
    }
    return false;
}
#endif
