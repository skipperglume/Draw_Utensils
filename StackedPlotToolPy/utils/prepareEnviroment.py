import os
import sys
import glob
import ROOT
from utils.utils import displayHeader, getJZValue

def getDateSubstring():
    import time
    import datetime
    return datetime.datetime.today().strftime('%m-%d-%Y')

def setTime(args):
    '''
    Set the datetime to args
    '''
    if hasattr(args, 'datetime'):
        if args.datetime is None:
            args.datetime = args.datetime
        else:
            print(f'Warning: already set datetime to {args.datetime}')
            return
    else:
        args.datetime = getDateSubstring()
        
def createOutputFolder(args):
    '''
    Create the output folder if it does not exist
    '''
    if hasattr(args, 'output_file'):
        outputFolder = os.path.dirname(args.output_file)
        os.makedirs(outputFolder, exist_ok=True)
    else:
        print('Warning: No output file specified. Skipping output folder creation.')
        return
        
def getFilesFromFile(path:str):
    '''
    This method returns the list of ntuple files from a file.
    '''
    
    if not os.path.exists(path):
        raise ValueError(f'ERROR: file {path} does not exist!')
    
    if not os.path.isfile(path):
        raise ValueError(f'ERROR: {path} is not a file!')
    
    with open(path) as f:
        files = f.readlines()
    return files

def checkInputFileExistence(files:list)->bool:
    '''
    Simple method to check presence of input files.
    '''
    if len(files) == 0 :
        print('ERROR: file list is empty!')
        raise ValueError('ERROR: file list is empty!')
        
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
    Uses the fact that `0` is `False` in python - In C++ it is reversed.
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
        
def checkInputNtuples(args):
    '''
    Check that input files are present and can be read
    '''
    
    
    # Get files to process:
    files = getFilesFromFile(f'{args.input_list}')
    
    print(f'Found files: {len(files)}')
    
    displayHeader('Checking the existence of input files:')
    
    if not checkInputFileExistence(files):
        raise ValueError('ERROR: No input files found!')
        
    numberOfEntriesDict = {}

    for fileIter in range(len(files)):
        filePath = files[fileIter]
        filePath = filePath.strip()
        fileResult = testRootFile(filePath, args)
        if not fileResult:
            raise ValueError(f'ERROR: a problem with file: {filePath}')
            
        numberOfEntriesDict[fileIter] = {'EntriesCount':fileResult, 'JZValue':getJZValue(filePath, args.sliceList),}
            
    for keyIter in numberOfEntriesDict:
        print(f'{keyIter} : {numberOfEntriesDict[keyIter]}')



if __name__ == '__main__':
    
    
    
    exit(0)