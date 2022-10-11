(g++ -o Run Response_Control.cxx `root-config --cflags --glibs` &&
./Run "partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "JetCal" &&
./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "NoJetCal")