import os
import sys, re, glob
import ROOT 
import array
import uproot
import argparse
import pickle
from PlotSetting import plotSettings, labels

folderName = 'stackedPlots'
sliceTag = [
    # '801165',
    '801166',
    '801167',
    '801168',
    '801169',
    '801170',
    '801171',
    '801172',
    '801173',
    '801174',
]



variableNames1DHisto = set()
variableNames1DHisto.add('mu')
variableNames1DHisto.add('NPV')
variableNames1DHisto.add('njet')
variableNames1DHisto.add('leading_true_pt')
variableNames1DHisto.add('jet_ConstitPt')
variableNames1DHisto.add('last_true_pt')
variableNames1DHisto.add('last_reco_pt')
variableNames1DHisto.add('leading_reco_pt')
variableNames1DHisto.add('jet_E')
variableNames1DHisto.add('jet_pt')
variableNames1DHisto.add('jet_true_pt')
variableNames1DHisto.add('jet_true_e')
variableNames1DHisto.add('last_true_E')
variableNames1DHisto.add('last_reco_E')
variableNames1DHisto.add('leading_true_E')
variableNames1DHisto.add('leading_reco_E')

variableNames1DHisto.add('reco_eta')
variableNames1DHisto.add('reco_eta_pos_0')
variableNames1DHisto.add('reco_eta_pos_1')
variableNames1DHisto.add('reco_eta_pos_2')
variableNames1DHisto.add('reco_eta_pos_3')

variableNames1DHisto.add('true_eta')
variableNames1DHisto.add('true_eta_pos_0')
variableNames1DHisto.add('true_eta_pos_1')
variableNames1DHisto.add('true_eta_pos_2')
variableNames1DHisto.add('true_eta_pos_3')

variableNames1DHisto.add('eta_diff_0')
variableNames1DHisto.add('eta_diff_1')
variableNames1DHisto.add('eta_diff_2')
variableNames1DHisto.add('eta_diff_3')


# TODO: Add the following variables:
# Delta R between leading reco and true jet
# Delta Phi between leading reco and true jet

# reco_eta_pos_1
# reco_eta_pos_2
# reco_eta_pos_3

# variableNames1DHisto = ["leading_true_pt", "NPV", "mu", "constit_pt", "true_pt", "rho", "jet_area", "constit_eta", "true_eta", "num_jets", "leading_true_pt", "leading_reco_pt", "beamSpotWeight", "jet_E", "jet_E_true"]
weight_name = ['R_weight', ]
# All stared weight values are : "R_weight", "tot_weight" , "weight" 
# "R_weight" is the one that is produced at reweighting step

varBinning = {
'mu' : [70, 0, 70],
'NPV' : [50, 0, 50],
'leading_true_pt' : [101, -10, 1000],
'leading_reco_pt' : [101, -10, 1000],
'last_true_E' : [101, -10, 1000],
'last_reco_E' : [101, -10, 1000],
'jet_pt' : [101, -10, 1000],
'jet_true_e' : [101, -10, 1000],
'jet_true_pt' : [101, -10, 1000],
'last_true_pt' : [101, -10, 1000],
'jet_ConstitPt' : [101, -10, 1000],
'jet_E' : [101, -10, 1000],
'njet' : [20, -0.5, 19.5],

'reco_eta' : [90, -4.5, 4.5],
'reco_eta_pos_0' : [90, -4.5, 4.5],
'reco_eta_pos_1' : [90, -4.5, 4.5],
'reco_eta_pos_2' : [90, -4.5, 4.5],
'reco_eta_pos_3' : [90, -4.5, 4.5],

'true_eta' : [90, -4.5, 4.5],
'true_eta_pos_0' : [90, -4.5, 4.5],
'true_eta_pos_1' : [90, -4.5, 4.5],
'true_eta_pos_2' : [90, -4.5, 4.5],
'true_eta_pos_3' : [90, -4.5, 4.5],

'eta_diff_0' : [60, -0.3, 0.3],
'eta_diff_1' : [60, -0.3, 0.3],
'eta_diff_2' : [60, -0.3, 0.3],
'eta_diff_3' : [60, -0.3, 0.3],
}

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kOrange, ROOT.kCyan, ROOT.kMagenta, ROOT.kGray, ROOT.kViolet, ROOT.kAzure, ROOT.kTeal, ROOT.kSpring, ROOT.kPink, ROOT.kRed+3, ROOT.kBlue-7]

def format_sci_notation(value):
    return f'{value:.1e}'

def getJZValue(fName):
    # re.search('JZ(\d+)', fName  )
    countFoundDSID = []
    for sTag in sliceTag:
        if sTag in fName:
            countFoundDSID.append(sTag)
    if len(countFoundDSID) > 1 or len(countFoundDSID) == 0:
        print(f'ERROR: found more than one or no DSID in {fName}')
        print(f'Found JZ tags are: {countFoundDSID}')
        print('Rename the files or rewrite the code to handle this case.')
        exit(1)
    if len(countFoundDSID) == 1:
        return (sliceTag.index(countFoundDSID[0]), countFoundDSID[0])
    return None

def getFilesByPath(path=None):
    '''
    This method returns the list of ntuple files from a path.
    '''
    if path:
        files = glob.glob(path)
    else:
        print('ERROR: No path provided')
        exit(1)
    return files

def getFilesFromFile(path='list.txt'):
    '''
    This method returns the list of ntuple files from a file.
    '''
    with open(path) as f:
        files = f.readlines()
    return files

# Foe each variable, weight combination, and slice, we need to fill a vector of input
def intialize1DHistos(histos, vList, wList, sList):
    '''
    Creat needed histograms for each variable, weight, and slice.
    '''
    for v in vList:
        for w in wList:
            for s in sList:
                nameTag = v + "_" + w + "_" + s
                histos[nameTag] = ROOT.TH1F(nameTag, nameTag, *varBinning.get(v, [100, 0, 100]))
                histos[nameTag].Sumw2()
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


def getVariablesFromTree(fName, tName):
    '''
    This method returns the list of variables and their types from a tree.
    As well as the list of variables that are not present in the tree.
    '''
    if fName[-1] == '\n':
        fName = fName[:-1]
    upRootFile = uproot.open(str(fName))
    variableNames = upRootFile[tName].keys()
    variableTypeNames = upRootFile[tName].typenames()
    abscentFromTreeVariables = set()
    for var in variableNames1DHisto:
        if not var in variableNames:
            abscentFromTreeVariables.add(var)
    return (variableNames,variableTypeNames, abscentFromTreeVariables )

# Foe each variable, weight combination, and slice, we need to fill a vector of input
class Quantities:
    def __init__(self, file, dictVariables, extendedVariables, args ):
        self.file = file
        self.fillVector = []
        self.dictVariables = dictVariables
        self.extendedVariables = extendedVariables
        self.extDictVariables = {}
        self.args = args
        
    def printDict(self):
        print(self.dictVariables)
        return
    
    def evaluateExtended(self):
        '''
        This method evaluates the extended variables. 
        '''
        # print(self.dictVariables)
        # print('\n')
        self.extDictVariables['mu'] = array.array( 'd', [self.dictVariables['averageInteractionsPerCrossing']][0])
        self.extDictVariables['leading_true_pt'] = array.array( 'd', [self.dictVariables['jet_true_pt'][0]])
        self.extDictVariables['leading_reco_pt'] = array.array( 'd', [self.dictVariables['jet_pt'][0]])
        
        self.extDictVariables['reco_eta'] = array.array( 'd', list( self.dictVariables['jet_ConstitEta'])  )

        # Jet Reco Eta by index:
        self.extDictVariables['reco_eta_pos_0'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][0]]) if len(self.dictVariables['jet_ConstitEta']) > 0 else array.array( 'd', [])
        self.extDictVariables['reco_eta_pos_1'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][1]]) if len(self.dictVariables['jet_ConstitEta']) > 1 else array.array( 'd', [])
        self.extDictVariables['reco_eta_pos_2'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][2]]) if len(self.dictVariables['jet_ConstitEta']) > 2 else array.array( 'd', [])
        self.extDictVariables['reco_eta_pos_3'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][3]]) if len(self.dictVariables['jet_ConstitEta']) > 3 else array.array( 'd', [])

        self.extDictVariables['true_eta'] = array.array( 'd', list( self.dictVariables['jet_true_eta'])  )
        # Jet True Eta by index:
        self.extDictVariables['true_eta_pos_0'] = array.array( 'd', [ self.dictVariables['jet_true_eta'][0]]) if len(self.dictVariables['jet_true_eta']) > 0 else array.array( 'd', [])
        self.extDictVariables['true_eta_pos_1'] = array.array( 'd', [ self.dictVariables['jet_true_eta'][1]]) if len(self.dictVariables['jet_true_eta']) > 1 else array.array( 'd', [])
        self.extDictVariables['true_eta_pos_2'] = array.array( 'd', [ self.dictVariables['jet_true_eta'][2]]) if len(self.dictVariables['jet_true_eta']) > 2 else array.array( 'd', [])
        self.extDictVariables['true_eta_pos_3'] = array.array( 'd', [ self.dictVariables['jet_true_eta'][3]]) if len(self.dictVariables['jet_true_eta']) > 3 else array.array( 'd', [])
        
        # Jet Eta Diff:
        self.extDictVariables['eta_diff_0'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][0] - self.dictVariables['jet_true_eta'][0]] ) if len(self.dictVariables['jet_ConstitEta']) > 0 and len(self.dictVariables['jet_true_eta']) > 0 else array.array( 'd', [])
        
        self.extDictVariables['eta_diff_1'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][1] - self.dictVariables['jet_true_eta'][1]] ) if len(self.dictVariables['jet_ConstitEta']) > 1 and len(self.dictVariables['jet_true_eta']) > 1 else array.array( 'd', [])

        self.extDictVariables['eta_diff_2'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][2] - self.dictVariables['jet_true_eta'][2]] ) if len(self.dictVariables['jet_ConstitEta']) > 2 and len(self.dictVariables['jet_true_eta']) > 2 else array.array( 'd', [])

        self.extDictVariables['eta_diff_3'] = array.array( 'd', [ self.dictVariables['jet_ConstitEta'][3] - self.dictVariables['jet_true_eta'][3]] ) if len(self.dictVariables['jet_ConstitEta']) > 3 and len(self.dictVariables['jet_true_eta']) > 3 else array.array( 'd', [])

        self.extDictVariables['last_true_pt'] = array.array( 'd', [self.dictVariables['jet_true_pt'][-1]])
        self.extDictVariables['last_reco_pt'] = array.array( 'd', [self.dictVariables['jet_pt'][-1]])

        self.extDictVariables['leading_true_E'] = array.array( 'd', [self.dictVariables['jet_true_e'][0]])
        self.extDictVariables['leading_reco_E'] = array.array( 'd', [self.dictVariables['jet_E'][0]])

        self.extDictVariables['last_true_E'] = array.array( 'd', [self.dictVariables['jet_true_e'][-1]])
        self.extDictVariables['last_reco_E'] = array.array( 'd', [self.dictVariables['jet_E'][-1]])
        self.extDictVariables['one'] = array.array( 'd', [1])
            
        return
    
    def setFileName(self, file):
        self.file = file
        self.jzNumber, self.dsid = getJZValue(file)
        return
    
    def __call__(self, name):
        if name in self.dictVariables:
            return self.dictVariables[name]
        elif name in self.extDictVariables:
            return self.extDictVariables[name]
        else:
            print(f'ERROR: variable [{name}] not found in: {self.file}')
            exit(1)
        return None

def fill1DHistos(histos, vList, wList, sList, fillVector : Quantities):
    '''
    This method fills the histograms for each variable, weight, and slice.
    '''
    for vName in vList:
        for wName in wList:
            for sName in sList:
                if not sName == fillVector.dsid:
                    continue
                nameTag = vName + "_" + wName + "_" + sName
                value = fillVector(vName)
                weight = fillVector(wName)
                wegetJZValueight = fillVector(wName)
                # print(vName + "_" + wName, value, weight)
                for i in range(len(value)):
                    histos[nameTag].Fill(value[i], weight[0])
                    
    return  

def traverseTree(fName, tName, histos, kwargs, args): 
    print('\nFound JZ value:', getJZValue(fName)[1])
    print('JZ Index:', getJZValue(fName)[0])
    if fName[-1] == '\n':
        fName = fName[:-1]
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
    extendedVariables = [x for x in variableNames1DHisto if x not in dictVariables]
    fi = Quantities(str(fName.decode()), dictVariables, extendedVariables, args)
    fi.setFileName(str(fName.decode()))

    #-----------------------------------------
    tree.SetBranchAddress("weight", R_weight)
    tree.SetBranchAddress("njet", njet)
    tree.SetBranchAddress("NPV", NPV)
    tree.SetBranchAddress("actualInteractionsPerCrossing", actualInteractionsPerCrossing)
    tree.SetBranchAddress("averageInteractionsPerCrossing", averageInteractionsPerCrossing)

    #-----------------------------------------
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

    # Total Entries: 
    nEntries = tree.GetEntries()

    print(f'Tree has {nEntries} events')

    tillEvent = nEntries
    if args.test:
        tillEvent = min( int(nEntries/1000),nEntries)

    for ievt in range(tillEvent):
        tree.GetEntry(ievt)
        # print('Dictionary of tree object:')
        # print(tree.__dict__)
        # print(tree.R_weight)
        fi.evaluateExtended()
        fill1DHistos(histos, variableNames1DHisto, weight_name, sliceTag, fi)    

    return

def finalizeHistos(histos, vList, wList, sList, outName='output.root'):
    '''
    This method writes the histograms to a root file and to pickle file.
    '''
    
    # Creating root File to save
    print(f'Saving to: {outName}')
    outFile = ROOT.TFile(f'{outName}', 'recreate')
    for v in vList:
        for w in wList:
            subDir = outFile.mkdir(v+'_'+w)
            subDir.cd()
            for s in sList:
                nameTag = v + "_" + w + "_" + s
                # writing to a sub directory named after variable
                histos[nameTag].Write()
            mother = subDir.GetMotherDir()
            mother.cd()



    pcklData = {}
    pcklData['histos'] = histos
    pcklData['vList'] = vList
    pcklData['wList'] = wList
    pcklData['sList'] = sList

    pcklName = outName.replace('.root','') + '.pkl'

    pickle.dump(pcklData, open(pcklName, 'wb'))

def mainScript(inName, outName, args):
    '''
    This is a main body script to create, run over entris && fill, and save histograms.
    '''
    files = getFilesFromFile(f'{inName}')
    totalFiles = len(files)
    histos = {}
    intialize1DHistos(histos, variableNames1DHisto, weight_name, sliceTag)
    for file in files:
        # Printing number of file in a list:
        print(f'Processing file {files.index(file)+1}/{totalFiles}:', file)
        print('Variables and their type:', getVariablesFromTree(file, args.treename)[1] )
        print('Variables to calculate:',   getVariablesFromTree(file, args.treename)[2] )
        traverseTree(file, args.treename, histos, [variableNames1DHisto, weight_name,  sliceTag], args=args)
    finalizeHistos(histos, variableNames1DHisto, weight_name, sliceTag, )
    return outName

def getDateSubstring():
    import time
    import datetime
    # today = time.strftime("%m/%d/%Y")
    # today_format = datetime.datetime.strptime(today, "%m/%d/%Y")
    # exp_date = str(today_format + datetime.timedelta(days=365)).split(" ")
    
    return datetime.datetime.today().strftime('%m-%d-%Y')

def labelPresenceForPlotting(variableNames, labelDict):
    '''
    This method checks the presence of the variable label for plotting.
    '''
    missingLabels = []

    for var in variableNames:
        if not var in labelDict:
            missingLabels.append(var)

    return missingLabels

def plotHistStack(histList, vName, wName, varBinning, args):
    '''
    This method plots the stacked histograms for each variable, weight, and slice.
    '''
    varNameDict = labels['varNames']
    
    weightNameDict = labels['weightNames']
    
    xAxisNameDict = labels['xAxisNames']
    
    variableName = varNameDict.get(vName, f'PLACE_HOLDER for {vName}')
    weightName = weightNameDict.get(wName, f'PLACE_HOLDER for {wName}')
    xAxisTitle = xAxisNameDict.get(vName, f'PLACE_HOLDER for {vName}')
    pltSttngs = plotSettings({
        'vName' : variableName,
        'wName' : weightName,
        'vBin' : varBinning,
        'jzName' : 'All JZ',
        'xaxis' : xAxisTitle,
        'yaxis' : weightName,
        'title' : f'{variableName} with {weightName}'
    })

    canvas = ROOT.TCanvas(f'{vName}_{wName}', f'{vName}_{wName}', 1000, 800)
    # Setting log scale
    if args.logAxisY:
        canvas.SetLogy()
    thstacked = ROOT.THStack(f'{vName}_{wName}', f'{vName}_{wName}')
    legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
    # Setting up ranges for diplaying plots:
    name = list(histList.keys())[0]
    minValueToDisplay = histList[name].GetMinimum()
    maxValueToDisplay = histList[name].GetMaximum()
    minValueList = []
    maxValueList = []
    for hist in histList:
        minValueList.append(histList[hist].GetMinimum())
        maxValueList.append(histList[hist].GetMaximum())
        if histList[hist].GetMinimum() < minValueToDisplay:
            minValueToDisplay = histList[hist].GetMinimum()
        if histList[hist].GetMaximum() > maxValueToDisplay:
            maxValueToDisplay = histList[hist].GetMaximum()
    # Remove zeros from the list:
    minValueList = [x for x in minValueList if x > 0]
    maxValueList = [x for x in maxValueList if x > 0]

    print('Min value in a list:', minValueList, 'Number of elements:', len(minValueList))
    
    print('Max value in a list:', maxValueList, 'Number of elements:', len(maxValueList))

    if len(maxValueList) == 0:
        maxValueList.append(args.maxY)
    
    if len(minValueList) == 0:
        minValueList.append(args.minY)

    # Make a check that the lists are not empty:
    if len(maxValueList) == 0:
        print('ERROR: maxValueList is empty')
        print('Check these variables:')
        print(histList, vName, wName, sep='\n')
        exit(1)
    
    if len(minValueList) == 0:
        print('ERROR: minValueList is empty')
        print('Check these variables:')
        print(histList, vName, wName, sep='\n')
        exit(1)
    minValueList.append(min(maxValueList)*0.1)

    # Find the minimum and maximum values to display:
    minValueToDisplay = min(minValueList)
    maxValueToDisplay = sum(maxValueList)
    if args.debug: 
        print('===========================================')
        print(f'minValueToDisplay for: {vName} with {wName}', minValueToDisplay)
        print(f'maxValueToDisplay for: {vName} with {wName}', maxValueToDisplay)
    minValueToDisplay = min(minValueToDisplay, 0.001)
    # Here we plotting the histogram in reverse order 
    for sTag in sliceTag[::-1]:
        histName = vName + "_" + wName + "_" + sTag
        histList[histName].SetDirectory(0)
        histList[histName].SetLineColor(colors[ (getJZValue(histName.split('_')[-1])[0]) % len(colors) ])
        histList[histName].SetLineWidth(3)
        histList[histName].SetFillColor(colors[ (getJZValue(histName.split('_')[-1])[0]) % len(colors) ])
        histList[histName].SetFillStyle(1)
        histList[histName].SetMarkerStyle(0)
        histList[histName].GetYaxis().SetRangeUser(minValueToDisplay, maxValueToDisplay)
        thstacked.Add(histList[histName])
        legend.AddEntry(histList[histName], 'JZ'+str(getJZValue(histName)[0])+' '+str(format_sci_notation(histList[histName].Integral(0,-1))), 'l')

    thstacked.SetMinimum(minValueToDisplay)
    thstacked.SetMaximum(maxValueToDisplay)
    print('Title:', pltSttngs.getTitle())
    thstacked.SetTitle(pltSttngs.getTitle())
    thstacked.Draw()
    legend.Draw()
    canvas.Update()
    os.system(f'mkdir -p ./{folderName}/{getDateSubstring()}')
    os.system(f'mkdir -p ./{folderName}/{getDateSubstring()}/{wName}')
    canvas.SaveAs(f'{folderName}/{getDateSubstring()}/{wName}/{vName}_{wName}.png')
    return None

def checkHistos(plotsFile, sName, vNames, wNames,  vBins, args):
    return

def plotStackedPlots(plotsFile, sName, vNames, wNames,  vBins, args):

    print('Path to root file: {plotsFile}')

    folderNames = set()
    for x in uproot.open(plotsFile).keys():
        folderNames.add(x.split('/')[0].split(';')[0])

    # if folderNames 
    print(f'Folder Name: [{folderNames}]')
    outFile = ROOT.TFile('output.root', 'read')
    mother = outFile.GetMotherDir()
    print(f'TFile info: {outFile}')
    for v in vNames:
        for w in wNames:
            if not v+'_'+w in folderNames:
                continue
            subDir = outFile.Get(v+'_'+w)
            subDir.cd()
            histos = {}
            for s in sName:
                nameTag = v + "_" + w + "_" + s
                histos[nameTag] = subDir.Get(nameTag)
                histos[nameTag].SetDirectory(0)
            # print('===========================================')
            # print(histos)
            try:
                plotHistStack(histos, v, w, vBins.get(v, [100, 0, 100]), args)
            except Exception as e:
                print('failed for ', v, w)
                print(e)
            mother = subDir.GetMotherDir()
            mother.cd()
    outFile.Close()
    return

def checkInputFileExistence(files:list)->bool:
    '''
    Simple method to check presence of input files.
    '''
    if len(files) == 0 :
        print('ERROR: file list is empty!')
        exit(1)
        
    missingFiles = []
    
    for fileName in files:
        fileName = fileName.strip()
        if not os.path.exists(fileName):
            print(f'Warning: file is missing: [{fileName}]')
            missingFiles.append(fileName)
    
    if len(missingFiles) == 0: 
        print('All files are present!')
        return True
    
    if len(missingFiles) == len(files): 
        print('ERROR: All files are missing!')
        exit(1)
    
    if len(missingFiles) > 0: 
        print('Warning: following files are missing:')
        for fileName in missingFiles:
            print(fileName)
        return False
    
    return False

def testRootFile(filePath:str, args)->int:
    '''
    Method to test openening and closing of root files.
    Uses the fact that `0` is `False` in python.
    In C++ it is reversed.
    '''
    filePath = filePath.strip()
    if not isinstance(filePath, str):
        print(f'ERROR: Provided File path is not [str], it is {type(filePath)}')
        exit(1)
        
    if not os.path.exists(filePath):
        print(f'ERROR: File is missing: {filePath}')
        exit(1)
    
    numberOfEntries = -1
        
    try:
        tfile = ROOT.TFile.Open(filePath,'read')
        # print(f'Opened: {filePath}')
        # print(uproot.open(str(filePath)).keys())
        
        tree = tfile.Get(args.treename)
        numberOfEntries = tree.GetEntries()
        tfile.Close()
    except: 
        print(f'File could not be opened: {filePath}')
        
    if numberOfEntries == -1:
        return 0
    else:
        return numberOfEntries 

if __name__ == '__main__':

    parser=argparse.ArgumentParser()
    parser.add_argument('-i', '--inloc', default='/home/timoshyd/RAC_4tops_analysis/ntuples/v06_BDT_SPANET_Input/nom', type=str, help='Input file location.')
    parser.add_argument('-o', '--outloc', default='/home/timoshyd/spanet4Top/ntuples/four_top_SPANET_input/plotbook/four_top_SPANET_input', type=str, help='Output location. File type of .h5 will be added automatically.')
    parser.add_argument('-r', '--reconstruction', default='j1()|j2()', type=str, help='Topology of underlying event.')
    parser.add_argument('-t', '--topo', default='jj', type=str, help='Topology of underlying event.')
    parser.add_argument('-m', '--maxjets', default=15, type=int, help='Max number of jets.')
    parser.add_argument('-tr', '--treename', default='IsolatedJet_tree', type=str, help='Name of nominal tree.')
    parser.add_argument('-b', '--btag', type=str, default='DL1r', help='Which btag alg to use.')
    parser.add_argument('-test','--test', action='store_true', help='Test the code on smaller amount of entries.')
    parser.add_argument('--debug', action='store_true', help='Print out info. Use when need to develop new functionality.')
    parser.add_argument('--tag',default='_MC23d', help='Suffix to differentiate files.')
    parser.add_argument('--ignoreCuts', action='store_true', help='Ignore the cuts. Used to produced dataset for prediction.')
    parser.add_argument('-plot', '--plotOnly', action='store_true', help='To plot already produced histograms.')
    parser.add_argument('-minY', '--minY', default=0.01, type=float, help='The space holder in case the weights are negative for histogram layers.')
    parser.add_argument('-maxY', '--maxY', default=-100.0, type=float, help='The space holder in case the weights are negative for histogram layers.')
    parser.add_argument('-lay', '--logAxisY', action='store_true', help='Option to use logarithm axis on Y-axis.')
    args = parser.parse_args()

    outName = 'output.root'
    inName = 'MC23a_PFlow.txt'
    # inName = 'notReweighted.txt'
    # inName = 'test.txt'

    # print(glob.glob('/eos/user/d/dtimoshy/MC23_CSSKUFO_7GeV/MC23d/MC23d_*/*.root'))
    # print(glob.glob('/eos/user/d/dtimoshy/MC23_CSSKUFO_7GeV/MC23d/MC23d_*/*.root')[0])
    # print(glob.glob('/eos/user/d/dtimoshy/MC23_CSSKUFO_7GeV/MC23d/MC23d_*/*.root')[1])

    inputFilesBySlice = {}

    for slce in sliceTag:
        print(slce)

    # Get files to process:
    files = getFilesFromFile(f'{inName}')
    
    print(f'Found files: {len(files)}')
    
    if not checkInputFileExistence(files):
        exit(1)
        
    numberOfEntriesDict = {}

    for fileIter in range(len(files)):
        filePath = files[fileIter]
        filePath = filePath.strip()
        fileResult = testRootFile(filePath, args)
        if not fileResult:
            print(f'ERROR: a problem with file: {filePath}')
            exit(1)
            
        numberOfEntriesDict[fileIter] = {'EntriesCount':fileResult, 'JZValue':getJZValue(filePath),}
            
    print(numberOfEntriesDict)
            
    # exit(0)
    print(type(args))
    if not args.plotOnly:
        outName = mainScript( inName, outName, args )

    # Check the presence of the variable names and x-labels for plotting:
    missingVarNames = labelPresenceForPlotting(variableNames1DHisto, labels['varNames'])    
    if len(missingVarNames) > 0:
        print('Warning: Missing variable names for plotting:')
        print(missingVarNames)
    
    missingxAxisNames = labelPresenceForPlotting(variableNames1DHisto, labels['xAxisNames'])    
    if len(missingxAxisNames) > 0:
        print('Warning: Missing Axis variable names for plotting:')
        print(missingxAxisNames)

    print('Plotting:')
    plotStackedPlots(outName, sliceTag, variableNames1DHisto, weight_name, varBinning, args)
    exit(0)

    exit(0)
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
        
