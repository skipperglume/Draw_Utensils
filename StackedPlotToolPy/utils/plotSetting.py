labels = {}

# Dictionary for { `variables` : `Full Name` }

['', '0', '', '1', 'leading_reco_E', '2', 'leading_true_E', '', '', '3', '', '']

# Dictionary for labels to use for variables
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
        
        'true_eta' : 'True #eta',
        'true_eta_pos_0' : 'True #eta_{0}',
        'true_eta_pos_1' : 'True #eta_{1}',
        'true_eta_pos_2' : 'True #eta_{2}',
        'true_eta_pos_3' : 'True #eta_{3}',
        
        'reco_eta' : 'Reco #eta',
        'reco_eta_pos_0' : 'Reco #eta_{0}',
        'reco_eta_pos_1' : 'Reco #eta_{1}',
        'reco_eta_pos_2' : 'Reco #eta_{2}',
        'reco_eta_pos_3' : 'Reco #eta_{3}',

        'eta_diff_0' : 'Reco - True #eta_{0}',
        'eta_diff_1' : 'Reco - True #eta_{1}',
        'eta_diff_2' : 'Reco - True #eta_{2}',
        'eta_diff_3' : 'Reco - True #eta_{3}',
}


# Dictionary for variables without units
noUnitVairables = ['mu', 'NPV', 'njet']
noUnitVairables += ['reco_eta', 'true_eta']
noUnitVairables += ['reco_eta_pos_0', 'reco_eta_pos_1', 'reco_eta_pos_2', 'reco_eta_pos_3']
noUnitVairables += ['true_eta_pos_0', 'true_eta_pos_1', 'true_eta_pos_2', 'true_eta_pos_3']
noUnitVairables += ['eta_diff_0', 'eta_diff_1', 'eta_diff_2', 'eta_diff_3']

labels['xAxisNames'] = {}
for var in noUnitVairables:
    labels['xAxisNames'][var] = labels['varNames'][var]

gevUnitVariables = ['leading_true_pt', 'jet_ConstitPt', 'last_true_pt', 'last_reco_pt', 'leading_reco_pt', 'jet_E', 'last_true_E', 'last_reco_E', 'jet_pt', 'jet_true_pt', 'jet_true_e']
for var in gevUnitVariables:
    labels['xAxisNames'][var] = labels['varNames'][var] + ' [GeV]'


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
    