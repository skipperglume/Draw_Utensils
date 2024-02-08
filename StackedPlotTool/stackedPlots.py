import os
import sys, re, glob
import ROOT 
import array
from ROOT import TFile

sliceTag = ["801165","801166","801167","801168","801169","801170","801171","801172","801173","801174"]
variableNames1DHisto = ["leading_true_pt", "NPV"]
# variableNames1DHisto = ["leading_true_pt", "NPV", "mu", "constit_pt", "true_pt", "rho", "jet_area", "constit_eta", "true_eta", "num_jets", "leading_true_pt", "leading_reco_pt", "beamSpotWeight", "jet_E", "jet_E_true"]
weight_name = ["tot_weight",]
# weight_name = ["tot_weight", "tot_weight" , "one" , "weight" , "one_nth"]
treeName = 'IsolatedJet_tree'
varBinning = {
"NPV" : [70, 0, 70],
"leading_true_pt" : [101, -10, 1000],
}

# Foe each variable, weight combination, and slice, we need to fill a vector of input
class fillInput:
    def __init__(self, file, tree, weight):
        self.file = file
        self.tree = tree
        self.weight = weight
        self.fillVector = []


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

def traverseTree(fileName, tName, histos, kwargs):
    if fileName[-1] == '\n':
        fileName = fileName[:-1]
        print(fileName)
    fileName = fileName.encode('utf-8')
    try:
        tfile = ROOT.TFile.Open(fileName,'read')
        print(f'Opened: {fileName}')
    except:
        os.system(f'ls -lh {fileName}')
        print(f'ERROR opening root file {fileName}')
        return
    try: 
        tree = tfile.Get(tName)
    except:
        print(f'ERROR getting tree {tName} from file {fileName}')
        return
    
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
    fileName = '/eos/user/d/dtimoshy/MC23_CSSKUFO_7GeV/MC23a/MC23a_801173/__reweighted__user.dtimoshy.35989412._000001.tree.root'
    # fileName = '__reweighted__user.dtimoshy.35989361._000001.tree.root'
    print(fileName)
    try:
        fileName = fileName.encode('utf-8')
        tfile = TFile.Open(fileName,'read')
        print(f'Opened: {fileName}')
    except:
        os.system(f'ls -lh {fileName}')
        print(f'ERROR opening root file {fileName}', [fileName])
