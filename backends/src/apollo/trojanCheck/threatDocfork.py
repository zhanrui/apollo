#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
def GetParentPath(strPath):  
    if not strPath:  
        return None;  
    lsPath = os.path.split(strPath)
    if lsPath[1]:  
        return lsPath[0];  
    lsPath = os.path.split(lsPath[0])
    return lsPath[0]
logdir = GetParentPath(os.getcwd())
logdir = os.getcwd() +'/clamscan11.log'
scandir = sys.argv[1]
sord = '/usr/local/clamav/bin/clamscan -r -v '+scandir+' --log='+logdir
hw = os.popen(sord)
hw.close()
#  
 