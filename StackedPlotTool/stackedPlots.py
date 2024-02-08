import os
import sys, re, glob
import ROOT 
import array
import uproot


sliceTag = ["801165","801166","801167","801168","801169","801170","801171","801172","801173","801174"]
variableNames1DHisto = [ 'mu',]
# variableNames1DHisto = ["leading_true_pt", "NPV", "mu", "constit_pt", "true_pt", "rho", "jet_area", "constit_eta", "true_eta", "num_jets", "leading_true_pt", "leading_reco_pt", "beamSpotWeight", "jet_E", "jet_E_true"]
weight_name = ["R_weight",]
# weight_name = ["tot_weight", "tot_weight" , "one" , "weight" , "one_nth"]
treeName = 'IsolatedJet_tree'
varBinning = {
"NPV" : [70, 0, 70],
"leading_true_pt" : [101, -10, 1000],
}


def getFiles(path='list.txt'):
    with open(path) as f:
        files = f.readlines()
    return files

# Foe each variable, weight combination, and slice, we need to fill a vector of input
def intialize1DHistos(histos, vList, wList, sList):
    for var in vList:
        for weight in wList:
            for slice in sList:
                nameTag = var + "_" + weight + "_" + slice 
                histos[nameTag] = ROOT.TH1F(nameTag, nameTag, *varBinning.get(var, [100, 0, 100]))
        histos[var] = ROOT.TH1F(var, var, *varBinning.get(var, [100, 0, 100]))
    return histos   
['runNumber',
 'eventNumber',
 'lumiBlock',
 'coreFlags',
 'bcid',
 'mcEventNumber',
 'mcChannelNumber',
 'mcEventWeight',

 'weight_pileup',
 'correctedAverageMu',
 'correctedAndScaledAverageMu',
 'correctedActualMu',
 'correctedAndScaledActualMu',
 'rand_run_nr',
 'rand_lumiblock_nr',
 'rhoEMPFLOW',
 'weight',
 'rho',
 'rho_Kt4EMTopoOriginEventShape',
 'rho_Kt4EMPFlowEventShape',
 'rho_Kt4EMPFlowPUSBEventShape',
 'rho_Kt4EMPFlowNeutEventShape',
 'rho_Kt4UFOCSSKEventShape',
 'rho_Kt4UFOCSSKNeutEventShape',
 'weight_xs',
 'weight_mcEventWeight',
 'weight_beamSpotWeight',
 'weight_pileup',
 
 'jet_rapidity',
 'jet_NumTrkPt1000PV',
 'jet_SumPtTrkPt1000PV',
 'jet_TrackWidthPt1000PV',
 'jet_NumTrkPt500PV',
 'jet_SumPtTrkPt500PV',
 'jet_TrackWidthPt500PV',
 'jet_JVFPV',
 'jet_JvtJvfcorr',
 'jet_JvtRpt',
 'jet_JvtPass_Loose',
 'jet_JvtEff_SF_Loose',
 'jet_JvtPass_Medium',
 'jet_JvtEff_SF_Medium',
 'jet_JvtPass_Tight',
 'jet_JvtEff_SF_Tight',
 'jet_JvtPass_FixedEffPt',
 'jet_JvtEff_SF_FixedEffPt',
 'jet_JvtPass_TightFwd',
 'jet_JvtEff_SF_TightFwd',
 'jet_fJvtPass_Loose',
 'jet_fJvtEff_SF_Loose',
 'jet_fJvtPass_Medium',
 'jet_fJvtEff_SF_Medium',
 'jet_fJvtPass_Tight',
 'jet_fJvtEff_SF_Tight',
 'jet_GhostArea',
 'jet_ActiveArea',
 'jet_VoronoiArea',
 'jet_ActiveArea4vec_pt',
 'jet_ActiveArea4vec_eta',
 'jet_ActiveArea4vec_phi',
 'jet_ActiveArea4vec_m',
 'jet_DetEta',
 
 'jet_respE',
 'jet_respPt',
 'jet_PartonTruthLabelID',
 'jet_Wtrk1000',
 'jet_Ntrk1000',
 'jet_EnergyPerSampling',
 'jet_ChargedFraction',
 
 'jet_n90Constituents',
 
 'sumw']
def getVariablesFromTree(fName,tName):
    upRootFile = uproot.open(str(fName.decode()))
    variableNames = upRootFile[tName].keys()
    variableTypeNames = upRootFile[tName].typenames()
    return (variableNames,variableTypeNames )

# Foe each variable, weight combination, and slice, we need to fill a vector of input
class fillInput:
    def __init__(self, file, dictVariables, extendedVariables ):
        self.file = file
        self.fillVector = []
        self.dictVariables = dictVariables
        self.extendedVariables = extendedVariables
        self.extDictVariables = {}
    def printDict(self):
        print(self.dictVariables)
        return
    def evaluateExtended(self):
        for name in self.extendedVariables:
            if name == 'mu':
                self.extDictVariables[name] = self.dictVariables['averageInteractionsPerCrossing']
        return
    def __call__(self, name):
        self.evaluateExtended()
        if name in self.dictVariables:
            return self.dictVariables[name]
        elif name in self.extDictVariables:
            return self.extDictVariables[name]
        else:
            print(f'ERROR: variable {name} not found in {self.file}')
            return None
        return None

def fill1DHistos(histos, vList, wList, sList, fillVector):
    print('start filling')
    for vName in vList:
        for wName in wList:
            for sName in sList:
                # print(var, weight, sliice)
                # print(var, weight, sliice)
                # print(var, weight, sliice)
                # print(var, weight, sliice)
                nameTag = vName + "_" + wName + "_" + sName
                value = fillVector(vName)
                weight = fillVector(wName)
                print(value, type(value), type(value)==type(array.array('i',[-1]) ))
                # print(input,weight)
                # print(input,weight)
                # print(input,weight)
                # print(input,weight)
                histos[nameTag].Fill(value[0], weight[0])
    print('finished filling')
    return 
def traverseTree(fName, tName, histos, kwargs): 
    if fName[-1] == '\n':
        fName = fName[:-1]
        print(fName)
    fName = fName.encode('utf-8')
    try:
        tfile = ROOT.TFile.Open(fName,'read')
        print(f'Opened: {fName}')
    except:
        os.system(f'ls -lh {fName}')
        print(f'ERROR opening root file {fName}')
        return
    try: 
        tree = tfile.Get(tName)
    except:
        print(f'ERROR getting tree {tName} from file {fName}')
        return
    # b_scale = Reweighted_ttree.Branch("sumw",scale,"sumw/D")
    # vec = ROOT.vector('double')()
    # tree.Print()

    R_weight                         = array.array('d',[-1])
    njet                             = array.array('i',[-1])
    NPV                              = array.array('i',[-1])
    actualInteractionsPerCrossing    = array.array('f',[-1])
    averageInteractionsPerCrossing   = array.array('f',[-1])


    jet_ConstitPt                    = ROOT.vector('float')()
    jet_m                            = ROOT.vector('float')()
    jet_true_m                       = ROOT.vector('float')()
    jet_ConstitPt                    = ROOT.vector('float')()
    jet_ConstitEta                   = ROOT.vector('float')()
    jet_ConstitPhi                   = ROOT.vector('float')()
    jet_ConstitMass                  = ROOT.vector('float')()
    jet_true_pt                      = ROOT.vector('float')()
    jet_true_eta                     = ROOT.vector('float')()
    jet_true_phi                     = ROOT.vector('float')()
    jet_true_e                       = ROOT.vector('float')()
    jet_E                            = ROOT.vector('float')()
    jet_pt                           = ROOT.vector('float')()
    jet_phi                          = ROOT.vector('float')()
    jet_eta                          = ROOT.vector('float')()


    dictVariables = {
        'jet_ConstitPt'      : jet_ConstitPt,
        'jet_m'      : jet_m,
        'jet_true_m'      : jet_true_m,
        'jet_ConstitPt'      : jet_ConstitPt,
        'jet_ConstitEta'      : jet_ConstitEta,
        'jet_ConstitPhi'      : jet_ConstitPhi,
        'jet_ConstitMass'      : jet_ConstitMass,
        'jet_true_pt'      : jet_true_pt,
        'jet_true_eta'      : jet_true_eta,
        'jet_true_phi'      : jet_true_phi,
        'jet_true_e'      : jet_true_e,
        'jet_E'      : jet_E,
        'jet_pt'      : jet_pt,
        'jet_phi'      : jet_phi,
        'jet_eta'              : jet_eta,
        'R_weight' : R_weight,
        'njet' : njet,
        'NPV' : NPV,
        'actualInteractionsPerCrossing' : actualInteractionsPerCrossing,
        'averageInteractionsPerCrossing' : averageInteractionsPerCrossing,
    }
    
    fi = fillInput(str(fName.decode()), dictVariables, variableNames1DHisto)
    


    # print('jet_ConstitPt', jet_ConstitPt, type(jet_ConstitPt))
    # print('R_weight',R_weight, type(R_weight))
    tree.SetBranchAddress("R_weight", R_weight)
    tree.SetBranchAddress("njet", njet)
    tree.SetBranchAddress("NPV", NPV)
    tree.SetBranchAddress("actualInteractionsPerCrossing", actualInteractionsPerCrossing)
    tree.SetBranchAddress("averageInteractionsPerCrossing", averageInteractionsPerCrossing)


    tree.SetBranchAddress("jet_m", jet_m)
    tree.SetBranchAddress("jet_true_m", jet_true_m)
    tree.SetBranchAddress("jet_ConstitPt", jet_ConstitPt)
    tree.SetBranchAddress("jet_ConstitEta", jet_ConstitEta)
    tree.SetBranchAddress("jet_ConstitPhi", jet_ConstitPhi)
    tree.SetBranchAddress("jet_ConstitMass", jet_ConstitMass)
    tree.SetBranchAddress("jet_true_pt", jet_true_pt)
    tree.SetBranchAddress("jet_true_eta", jet_true_eta)
    tree.SetBranchAddress("jet_true_phi", jet_true_phi)
    tree.SetBranchAddress("jet_true_e", jet_true_e)
    tree.SetBranchAddress("jet_E", jet_E)
    tree.SetBranchAddress("jet_pt", jet_pt)
    tree.SetBranchAddress("jet_phi", jet_phi)
    tree.SetBranchAddress("jet_eta", jet_eta)
    tree.SetBranchAddress("jet_ConstitPt", jet_ConstitPt)


    # Total Entries: 
    # print(getVariablesFromTree( fName,tName) )
    
    nEntries = tree.GetEntries()

    print('nEntries', nEntries)
    for ievt in range(min(10,nEntries)):
        tree.GetEntry(ievt)
        # fi.printDict()
        # print('R_weight',fi('R_weight'), tree.R_weight)
        # print('jet_ConstitPt',fi('jet_ConstitPt'))
        # print('NPV',fi('NPV'), tree.NPV)
        fill1DHistos(histos, variableNames1DHisto, weight_name, sliceTag, fi)    



    # exit(0)
    # print(tree)
    # tree.Print()

    return

def mainScript():
    files = getFiles('MC23a_UFOCSSK_7GeV_TEST.txt')
    histos = {}
    intialize1DHistos(histos, variableNames1DHisto, weight_name, sliceTag)
    for file in files:
        traverseTree(file, treeName, histos, [variableNames1DHisto, weight_name,  sliceTag])
    print(histos)

    print('kek')

if __name__ == '__main__':
    mainScript()
    # exit(0)

    a = array.array('d',[-1])
    print(type(a[0]))
    exit(0)
    fileName = '/eos/user/d/dtimoshy/MC23_CSSKUFO_7GeV/MC23a/MC23a_801173/__reweighted__user.dtimoshy.35989412._000001.tree.root'
    # fileName = '__reweighted__user.dtimoshy.35989361._000001.tree.root'
    print(fileName)
    try:
        # fileName = fileName.encode('utf-8')
        # tfile = TFile.Open(fileName,'read')
        # print(f'Opened: {fileName}')
        print(uproot.open(str(fileName)).keys())

    except:
        os.system(f'ls -lh {fileName}')
        print(f'ERROR opening root file {fileName}', [fileName])

