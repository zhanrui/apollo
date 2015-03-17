#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
import json
from _ast import keyword
# threatDocument1='/usr/local/clamav/bin/clamscan -r /root/clamav-0.98.5'
# threatDocument2='/bin/sh -c /usr/local/clamav/bin/clamscan -r  /root/clamav-0.98.5  >>/tmp/threatDocument.log'
# fileRoutineCheck1='./CAFileScan /root/clamav-0.98.5 def'
# fileRoutineCheck2='sh -c ./CAFileScan /root/clamav-0.98.5 def >>/tmp/fileRoutineCheck.log'
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
    
def killSubProcess(functionNamePara,pathPara,keywordPara):
    if "threatDocument"==functionNamePara:
        threatDocument1='/usr/local/clamav/bin/clamscan -r '+pathPara 
        threatDocument2='/bin/sh -c /usr/local/clamav/bin/clamscan -r  '+pathPara+'  >>/tmp/threatDocument.log'        
        pid1=getPid(threatDocument1)
        pid2=getPid(threatDocument2)
        cmd1 = "kill -9 %d" % int(pid1)
        cmd2 = "kill -9 %d" % int(pid2)
        rc = os.system(cmd1)
        rc = os.system(cmd2)
    elif "fileRoutineCheck"==functionNamePara:
        fileRoutineCheck1='./CAFileScan '+pathPara+' '+keywordPara
        fileRoutineCheck2='sh -c ./CAFileScan '+pathPara+' '+keywordPara+' >>/tmp/fileRoutineCheck.log'
        pid1=getPid(fileRoutineCheck1)
        pid2=getPid(fileRoutineCheck2)
        cmd1 = "kill -9 %d" % int(pid1)
        cmd2 = "kill -9 %d" % int(pid2)
        rc = os.system(cmd1)
        rc = os.system(cmd2)       

if __name__ == "__main__":
    arguments=sys.argv[1]
    args=json.loads(arguments)
    print args
    functionNameTemp=str(args["functionname"])
    parametersTemp=args['parameters']
    pathTemp=str(parametersTemp['path'])
    if "fileRoutineCheck"==functionNameTemp:
        keywordTemp=str(parametersTemp['keyword'])
    else:
        keywordTemp=""        
    killSubProcess(functionNameTemp,pathTemp,keywordTemp)