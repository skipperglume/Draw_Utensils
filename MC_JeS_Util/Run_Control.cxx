#include "TInterpreter.h"
void Run_Control(){
    // gInterpreter->ProcessLine(".L Response_Control_H.h");
    gInterpreter->ProcessLine(".L Response_Control.cxx");
    gInterpreter->ProcessLine("Response_vs_E_true R_vs_Etrue");
    gInterpreter->ProcessLine("R_vs_Etrue.Response_Control()");
    
    
    return;
}