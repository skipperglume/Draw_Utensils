
def displayHeader(message:str='PLACE_HOLDER'):
    '''
    This method displays the header of the step.
    '''
    message = '* ' + message + ' *'
    length = len(message)
    print('*'*length)
    print(message)
    print('*'*length)

def getJZValue(fileName:str, sliceList:str):
    '''
    Method finds the JZ value in the file name
    NOTE: Can use regex to find the JZ value in the file name?
    '''
    # re.search('JZ(\d+)', fileName  )
    countFoundDSID = []
    for sTag in sliceList:
        if sTag in fileName:
            countFoundDSID.append(sTag)
    if len(countFoundDSID) == 0:
        print(f'ERROR: found no DSID in [{fileName}]')
        print('Rename the files or rewrite the code to handle this case.')
        raise ValueError(f'ERROR: found no DSID in [{fileName}]')

    if len(countFoundDSID) > 1 :
        print(f'ERROR: found more than one in [{fileName}]')
        print(f'Found [{len(countFoundDSID)}] JZ tags are: {countFoundDSID}')
        print('Rename the files or rewrite the code to handle this case.')
        raise ValueError(f'ERROR: found more than one DSID in [{fileName}]')

    if len(countFoundDSID) == 1:
        return (sliceList.index(countFoundDSID[0]), countFoundDSID[0])
    return None