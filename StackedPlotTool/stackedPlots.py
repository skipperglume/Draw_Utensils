import os, sys, re, glob
import ROOT, uproot


def getFiles(path='list.txt'):
    with open(path) as f:
        files = f.readlines()
    return files


def mainScript():
    getFiles('MC23a_UFOCSSK_7GeV_TEST.txt')

    print('kek')

if __name__ == '__main__':
  mainScript()