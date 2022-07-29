#include "./Draw_Tool.cxx"
void Produce_Plots(){
    
    
    

    // tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_Reco_LVL/MuTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");
    // tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_Area_LVL/MuTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");
    // tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_1D_LVL/MuTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");
    // tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_3D_LVL/MuTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");

    tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_Reco_LVL/NPVTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");
    tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_Area_LVL/NPVTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");
    tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_1D_LVL/NPVTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");
    tfile_name.push_back("/afs/cern.ch/work/d/dtimoshy/RC_main/residualcalibration/residual_3D_LVL/NPVTermOption1_13122020_139fb_ptfrom10_v2AntiKt4EMPFlowJets.root");
    for (int pt_bin =0; pt_bin <  TruePtBinning.size()-1; pt_bin++){
        PT_BIN = pt_bin;
        Draw_Tool();
    }
    
    return;
}