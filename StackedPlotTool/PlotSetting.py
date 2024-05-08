labels = {}

# Dictionary for { `variables` : `Full Name` }
labels['varNames'] = {
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

labels['xAxisNames'] = {
        'mu' : labels['varNames']['mu'],
        'NPV' : labels['varNames']['NPV'],
        'njet' : labels['varNames']['njet'],
        'leading_true_pt' : labels['varNames']['leading_true_pt'] + ' [GeV]',
        'jet_ConstitPt' : labels['varNames']['jet_ConstitPt'] + ' [GeV]',
        'last_true_pt' : labels['varNames']['last_true_pt'] + ' [GeV]',
        'last_reco_pt' : labels['varNames']['last_reco_pt'] + ' [GeV]',
        'leading_reco_pt' : labels['varNames']['leading_reco_pt'] + ' [GeV]',
        'jet_E' : labels['varNames']['jet_E'] + ' [GeV]',
        'last_true_E' : labels['varNames']['last_true_E'] + ' [GeV]',
        'last_reco_E' : labels['varNames']['last_reco_E'] + ' [GeV]',
        'jet_pt' : labels['varNames']['jet_pt'] + ' [GeV]',
}

labels['weightNames'] = {
        'R_weight' : 'Reweighted Weight',
        'tot_weight' : 'Total Weight',
        'one' : 'Unweighted',
        'weight' : 'Event Weight UnRe',
}



class plotSettings:
    '''
    This class is used to set the plotting settings for the histograms.
    '''
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
    