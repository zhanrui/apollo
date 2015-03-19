#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
import json
from _ast import keyword
import re
clamavPath=os.path.dirname(os.getcwd())+'/apollo/trojanCheck/clamav'
def getPid(process):
    import commands
    cmd1 = "ps aux | grep '%s' " % process
    
    print cmd1
    info = commands.getoutput(cmd1)
    print info
    infos = info.split()
    print infos
    if len(infos) > 1:
        return infos[1]
    else:
        return -1
    
def killSubProcess(functionNamePara,pathPara,keywordListPara):
    if "threatDocument"==functionNamePara:
        threatDocument1=clamavPath+'/bin/clamscan -d'+clamavPath+'/updata'+' -r '+pathPara 
        threatDocument2='/bin/sh -c '+clamavPath+'/bin/clamscan -d'+clamavPath+'/updata'+' -r  '+pathPara+'  >>/tmp/threatDocument.log'        
        pid1=getPid(threatDocument1)
        pid2=getPid(threatDocument2)
        cmd1 = "kill -9 %d" % int(pid1)
        cmd2 = "kill -9 %d" % int(pid2)
        rc = os.system(cmd1)
        rc = os.system(cmd2)
    elif "fileRoutineCheck"==functionNamePara:
        keywordNum=len(keywordListPara)    
        currentNum=0
        keywordNum=len(keywordListPara)
        while currentNum<keywordNum:
            fileRoutineCheck1='./CAFileScan '+pathPara+' '+keywordListPara[currentNum]
            fileRoutineCheck2='sh -c ./CAFileScan '+pathPara+' '+keywordListPara[currentNum]+' >>/tmp/fileRoutineCheck.log'
            pid1=getPid(fileRoutineCheck1)
            pid2=getPid(fileRoutineCheck2)
            cmd1 = "kill -9 %d" % int(pid1)
            cmd2 = "kill -9 %d" % int(pid2)
            rc = os.system(cmd1)
            rc = os.system(cmd2) 
            currentNum=currentNum+1 
              

if __name__ == "__main__":
    arguments=sys.argv[1]
    args=json.loads(arguments)
    print args
    functionNameTemp=str(args["functionname"])
    parametersTemp=args['parameters']
    pathTemp=str(parametersTemp['path'])
    keywordList=[]
    if "fileRoutineCheck"==functionNameTemp:
        keywordTemp=parametersTemp['keyword']
        keywordTemp = keywordTemp.encode('utf-8')
        keywordList=re.split(';',keywordTemp)
    else:
        keywordTemp=""        
    killSubProcess(functionNameTemp,pathTemp,keywordList)