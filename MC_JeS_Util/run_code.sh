# (g++ -o Run Response_Control.cxx `root-config --cflags --glibs` &&
# ./Run "MC20a_JZ01.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ01" &&
# ./Run "partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "JetCal" &&
# ./Run "partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "1D" "-4.5" "4.5" "JetCal" &&
# ./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "NoJetCal" &&
# ./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "NoJetCal" &&
# ./Run "partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "1D" "-4.5" "4.5" "NoJetCal")

# (g++ -o Run Response_Control.cxx `root-config --cflags --glibs` &&
# ./Run "MC20a_JZ12.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ12" )

g++ -o Run Response_Control.cxx `root-config --cflags --glibs`
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "100" "Reco" "-4.5" "4.5" "JetCal" "-1" 

# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "0.0" "0.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "1.0" "1.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "2.0" "2.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "2.4" "2.5" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "3.0" "3.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "3.4" "3.5" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "4.0" "4.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Reco" "4.4" "4.5" "JetCal" "-1" 


# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "0.0" "0.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "1.0" "1.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "2.0" "2.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "2.4" "2.5" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "3.0" "3.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "3.4" "3.5" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "4.0" "4.1" "JetCal" "-1" 
# ./Run "Input_Files/MC20a_PFlow.txt" "IsolatedJet_tree" "10" "Area" "4.4" "4.5" "JetCal" "-1" 
g++ -o Run Response_Control.cxx `root-config --cflags --glibs`
g++ -o Run Response_Control.cxx `root-config --cflags --glibs`
g++ -o Run Response_Control.cxx `root-config --cflags --glibs`

./Run "Input_Files/MC20a_PFlow_JZ08.txt" "IsolatedJet_tree" "10" "Area" "3.0" "3.5" "JetCalLead" "1"

# ./Run "Input_Files/MC20a_JZ08.txt" "IsolatedJet_tree" "1" "Area" "0.5" "1.5" "MC20a_PFlow_JZ08" "-1"
# ./Run "Input_Files/MC20a_JZ08.txt" "IsolatedJet_tree" "1" "Area" "0.5" "1.5" "MC20a_PFlow_JZ08" "1"


# (   ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "JetCal" "-1" &
#     ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "JetCal" "-1"&
#     ./Run "Input_Files/partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "NoJetCal" "-1"&
#     ./Run "Input_Files/partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "NoJetCal" "-1"&)&

# (   ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "JetCal_Lead"    "1" &
#     ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "JetCal_Lead"    "1"&
#     ./Run "Input_Files/partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "NoJetCal_Lead"  "1"&
#     ./Run "Input_Files/partion_WOUT_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "NoJetCal_Lead"  "1"&)&
# ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "JetCal" "-1" 
# ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "2.5" "4.5" "JetCal" "-1" 
# ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "-0.1" "0.1" "JetCal" "-1" 
# ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "1.0" "1.1" "JetCal" "-1" 
# ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "2.0" "2.1" "JetCal" "-1" 
# ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "3.0" "3.1" "JetCal" "-1" 
# ./Run "Input_Files/partion_With_Jet_Calibrator.txt" "IsolatedJet_tree" "1" "Reco" "4.0" "4.1" "JetCal" "-1" 

# ./Run "MC20a_PFlow_JZ12.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ12" "-1"
# ./Run "MC20a_PFlow_JZ11.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ11" "-1"
# ./Run "MC20a_PFlow_JZ10.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ10"
# ./Run "MC20a_PFlow_JZ09.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ09"
# ./Run "MC20a_PFlow_JZ08.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ08"
# ./Run "MC20a_PFlow_JZ07.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ07"
# ./Run "MC20a_PFlow_JZ06.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ06"
# ./Run "MC20a_PFlow_JZ05.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ05"
# ./Run "MC20a_PFlow_JZ04.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ04"
# ./Run "MC20a_PFlow_JZ03.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ03"
# ./Run "MC20a_PFlow_JZ02.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ02"
# ./Run "MC20a_PFlow_JZ01.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ01"
# ./Run "MC20a_PFlow_JZ00.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_PFlow_JZ00"

# ./Run "MC20a_JZ12.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ12"
# ./Run "MC20a_JZ11.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ11"
# ./Run "MC20a_JZ10.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ10"
# ./Run "MC20a_JZ09.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ09"
# ./Run "MC20a_JZ08.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ08"
# ./Run "MC20a_JZ07.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ07"
# ./Run "MC20a_JZ06.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ06"
# ./Run "MC20a_JZ05.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ05"
# ./Run "MC20a_JZ04.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ04"
# ./Run "MC20a_JZ03.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ03"
# ./Run "MC20a_JZ02.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ02"
# ./Run "MC20a_JZ01.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ01"
# ./Run "MC20a_JZ00.txt" "IsolatedJet_tree" "1" "Area" "-4.5" "4.5" "MC20a_UFO_JZ00"

# ./Run "MC20a_JZ12.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ12"
# ./Run "MC20a_JZ11.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ11"
# ./Run "MC20a_JZ10.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ10"
# ./Run "MC20a_JZ09.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ09"
# ./Run "MC20a_JZ08.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ08"
# ./Run "MC20a_JZ07.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ07"
# ./Run "MC20a_JZ06.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ06"
# ./Run "MC20a_JZ05.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ05"
# ./Run "MC20a_JZ04.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ04"
# ./Run "MC20a_JZ03.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ03"
# ./Run "MC20a_JZ02.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ02"
# ./Run "MC20a_JZ01.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ01"
# ./Run "MC20a_JZ00.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_JZ00"

# ./Run "MC20a_JZ12.txt" "IsolatedJet_tree" "1" "Reco" "0.0" "0.1" "MC20a_UFO_JZ12" "-1"
# ./Run "MC20a_PFlow_JZ12.txt" "IsolatedJet_tree" "1" "Reco" "0.0" "0.1" "MC20a_PFlow_JZ12" "-1"


# ./Run "MC20a_JZ12.txt" "IsolatedJet_tree" "1" "Area" "0.0" "0.1" "MC20a_UFO_JZ12" "-1"
# ./Run "MC20a_PFlow_JZ12.txt" "IsolatedJet_tree" "1" "Area" "0.0" "0.1" "MC20a_PFlow_JZ12" "-1"

# ./Run "test.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "test_WOUT_JZ12"

# ./Run "Input_Files/PFlow_MC20d_JZ09_7k_Clean_T_Matching_T_JetCal_F.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_PFlow_new_JZ09" "-1"
# ./Run "Input_Files/PFlow_MC20d_JZ10_7k_Clean_T_Matching_T_JetCal_F.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_PFlow_new_JZ10" "-1"
# ./Run "Input_Files/PFlow_MC20d_JZ11_7k_Clean_T_Matching_T_JetCal_F.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_PFlow_new_JZ11" "-1"
# ./Run "Input_Files/PFlow_MC20d_JZ12_7k_Clean_T_Matching_T_JetCal_F.txt" "IsolatedJet_tree" "1" "Reco" "-4.5" "4.5" "MC20a_PFlow_new_JZ12" "-1"