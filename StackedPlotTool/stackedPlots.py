import os
import sys, re, glob
import ROOT 
import array
import uproot

folderName = 'stackedPlots'
sliceTag = ["801165","801166","801167","801168","801169","801170","801171","801172","801173","801174"]
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

# variableNames1DHisto = ["leading_true_pt", "NPV", "mu", "constit_pt", "true_pt", "rho", "jet_area", "constit_eta", "true_eta", "num_jets", "leading_true_pt", "leading_reco_pt", "beamSpotWeight", "jet_E", "jet_E_true"]
weight_name = ['R_weight', 'one']
# weight_name = ["tot_weight", "tot_weight" , "one" , "weight" , "one_nth"]
treeName = 'IsolatedJet_tree'
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
def getFiles(path='list.txt'):
    with open(path) as f:
        files = f.readlines()
    return files

# Foe each variable, weight combination, and slice, we need to fill a vector of input
def intialize1DHistos(histos, vList, wList, sList):
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
class plotSettings:
    def __init__(self, settingDict):
        self.vName = settingDict['vName']
        self.wName = settingDict['wName']
        self.vBin = settingDict['vBin']
        self.jzName = settingDict['jzName']
        self.xaxis = settingDict['xaxis']
        self.yaxis = settingDict['yaxis']
        self.title = settingDict['title']
    def getTitle(self):
        return f'{self.title};{self.xaxis};{self.yaxis}'
    # def 
def getVariablesFromTree(fName, tName):
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
        self.extDictVariables['mu'] = array.array( 'd', [self.dictVariables['averageInteractionsPerCrossing']][0])
        self.extDictVariables['leading_true_pt'] = array.array( 'd', [self.dictVariables['jet_true_pt'][0]])
        self.extDictVariables['leading_reco_pt'] = array.array( 'd', [self.dictVariables['jet_pt'][0]])

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
            print(f'ERROR: variable {name} not found in {self.file}')
            return None
        return None

def fill1DHistos(histos, vList, wList, sList, fillVector):
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
def traverseTree(fName, tName, histos, kwargs): 
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
    fi = fillInput(str(fName.decode()), dictVariables, extendedVariables)
    fi.setFileName(str(fName.decode()))


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
    nEntries = tree.GetEntries()

    print(f'Tree has {nEntries} events')
    tillEvent = min(100,nEntries)

    for ievt in range(nEntries):
        tree.GetEntry(ievt)
        fi.evaluateExtended()
        # fi.printDict()
        # print('R_weight',fi('R_weight'), tree.R_weight)
        # print('jet_ConstitPt',fi('jet_ConstitPt'))
        # print('NPV',fi('NPV'), tree.NPV)
        fill1DHistos(histos, variableNames1DHisto, weight_name, sliceTag, fi)    

    return
def finalizeHistos(histos, vList, wList, sList, outName='output.root'):
    for histoName in histos:
        entries = histos[histoName].GetEntries()
        # print(histoName,f'entries: {entries}')
        # print(f'Effective {histos[histoName].GetEffectiveEntries() }')
        # print(f'Integral {histos[histoName].GetIntegral() }')
        # print(f'SumOfWeights {histos[histoName].GetSumOfWeights() }')
        # print(f'Sumw2 {histos[histoName].GetSumw2() }')
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
def mainScript(inName, outName):
    files = getFiles(f'{inName}')
    totalFiles = len(files)
    histos = {}
    intialize1DHistos(histos, variableNames1DHisto, weight_name, sliceTag)
    for file in files:
        # Printing number of file in a list:
        print(f'Processing file {files.index(file)+1}/{totalFiles}:', file)
        print('Variables and their type:', getVariablesFromTree(file, treeName)[1])
        print('Variables to calculate:', getVariablesFromTree(file, treeName)[2])
        traverseTree(file, treeName, histos, [variableNames1DHisto, weight_name,  sliceTag])
    finalizeHistos(histos, variableNames1DHisto, weight_name, sliceTag, )
    return outName
def getDateSubstring():
    import time
    import datetime
    # today = time.strftime("%m/%d/%Y")
    # today_format = datetime.datetime.strptime(today, "%m/%d/%Y")
    # exp_date = str(today_format + datetime.timedelta(days=365)).split(" ")
    
    return datetime.datetime.today().strftime('%m-%d-%Y')

def plotStack(histList, vName, wName, vBin):
    varNameDict= {
        'mu' : '#mu, Average Interactions per Crossing',
        'NPV' : 'Number of Primary Vertices',
        'njet' : 'Number of Jets',
        'leading_true_pt' : 'Leading True Jet p_{T}',
        'jet_ConstitPt' : 'Jet Constituents p_{T}',
        'last_true_pt' : 'Last True Jet p_{T}',
        'last_reco_pt' : 'Last Reconstructed Jet p_{T}',
        'leading_reco_pt' : 'Leading Reconstructed Jet p_{T}',
        'jet_E' : 'Jet Energy',
        'last_true_E' : 'Last True Jet Energy',
        'last_reco_E' : 'Last Reconstructed Jet Energy',
        'jet_pt' : 'Jet p_{T}',
        'jet_true_pt' : 'Jet True p_{T}',
        'jet_true_e' : 'Jet True Energy',

    }
    weightNameDict = {
        'R_weight' : 'Reweighted Weight',
        'tot_weight' : 'Total Weight',
        'one' : 'Unweighted',
        'weight' : 'Event Weight UnRe',
    }
    xAxisNameDict = {
        'mu' : varNameDict['mu'],
        'NPV' : varNameDict['NPV'],
        'njet' : varNameDict['njet'],
        'leading_true_pt' : varNameDict['leading_true_pt'] + ' [GeV]',
        'jet_ConstitPt' : varNameDict['jet_ConstitPt'] + ' [GeV]',
        'last_true_pt' : varNameDict['last_true_pt'] + ' [GeV]',
        'last_reco_pt' : varNameDict['last_reco_pt'] + ' [GeV]',
        'leading_reco_pt' : varNameDict['leading_reco_pt'] + ' [GeV]',
        'jet_E' : varNameDict['jet_E'] + ' [GeV]',
        'last_true_E' : varNameDict['last_true_E'] + ' [GeV]',
        'last_reco_E' : varNameDict['last_reco_E'] + ' [GeV]',
        'jet_pt' : varNameDict['jet_pt'] + ' [GeV]',

    }
    pltSttngs = plotSettings({
        'vName' : varNameDict.get(vName, f'place holder for {vName}'),
        'wName' : weightNameDict.get(wName, f'place holder for {wName}'),
        'vBin' : vBin,
        'jzName' : 'All JZ',
        'xaxis' : xAxisNameDict.get(vName, f'place holder for {vName}'),
        'yaxis' : weightNameDict.get(wName, f'place holder for {wName}'),
        'title' : f'{vName} with {wName}'
    })
    canvas = ROOT.TCanvas(f'{vName}_{wName}', f'{vName}_{wName}', 1000, 800)
    # Setting log scale
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
    minValueList.append(min(maxValueList)*0.1)
    # Make a check that the list is not empty:
    if  len(maxValueList) == 0:
        print('ERROR: maxValueList is empty')
        print('Check these variables:')
        print(histList, vName, wName, sep='\n')
        exit(1)
    # Find the minimum and maximum values to display:
    minValueToDisplay = min(minValueList)
    maxValueToDisplay = sum(maxValueList)
    print(f'minValueToDisplay for: {vName} with {wName}', minValueToDisplay)
    print(f'maxValueToDisplay for: {vName} with {wName}', maxValueToDisplay)
    minValueToDisplay = min(minValueToDisplay, 0.01)
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
    print('Title:',pltSttngs.getTitle())
    thstacked.SetTitle(pltSttngs.getTitle())
    thstacked.Draw()
    legend.Draw()
    canvas.Update()
    os.system(f'mkdir -p ./{folderName}/{getDateSubstring()}')
    os.system(f'mkdir -p ./{folderName}/{getDateSubstring()}/{wName}')
    canvas.SaveAs(f'{folderName}/{getDateSubstring()}/{wName}/{vName}_{wName}.png')
    return None
def plotStackedPlots(plotsFile, sName, vNames, wNames,  vBins):
    folderNames = set()
    for x in uproot.open(plotsFile).keys():
        folderNames.add(x.split('/')[0].split(';')[0])
    print('folder Names:')
    print(f'{folderNames}')
    outFile = ROOT.TFile('output.root', 'read')
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
            plotStack(histos, v, w, vBins.get(v, [100, 0, 100]))
            print('===========================================')
            mother = subDir.GetMotherDir()
            mother.cd()
    outFile.Close()
    return

if __name__ == '__main__':
    outName = 'output.root'
    inName = 'MC23a_UFOCSSK_7GeV.txt'
    outName = mainScript( inName, outName )
    plotStackedPlots(outName, sliceTag, variableNames1DHisto, weight_name, varBinning)
    exit(0)

    exit(0)
    a = array.array('d',[-1])
    print(type(a[0]))
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