#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
import re
import json
import ctypes
import subprocess
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.killSubProcess import killSubProcess
from common.utils.log import log4py
from common.utils.scanFile import scanFileAndOrgProg
from apollo.commHandler import CommHandler 
from apollo.commHandler import parameters   
checkPath = str(parameters['path'])
strParameters = json.dumps(parameters)
logGenDir="/tmp/threatDocument.log" #日志生成目录
subProcFilePath=os.path.dirname(os.getcwd())+"/apollo/trojanCheck/clamscan.py"
functionname="threatDocument"
pid=None
class ThreatDocument(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass
    def getThreatDocumentInfo(self):
        libc = ctypes.CDLL('libc.so.6')
        pid = os.fork()
        if not pid:
            libc.prctl(1, 15)  
            if os.path.isfile(logGenDir): 
                os.remove(logGenDir)
            os.mknod(logGenDir)            
            
            strOrder = '/usr/local/clamav/bin/clamscan -r  '+checkPath+' '+' >>'+logGenDir
            print strOrder
            hw = os.popen(strOrder)
            hw.close()
        else:             
            log4py.info('********backends创建子进程('+str(pid)+")开始处理..")
            tempdict={}
            resultList=[]
            tempdict['found']=scanFileAndOrgProg(functionname,checkPath,logGenDir) #调用文件检查公共模块，并组织进度信息发送，该模块调用完毕说明文件检查已结束             
            
            if os.path.isfile(logGenDir): 
                logrs=open(logGenDir)  
                logrscon = logrs.read();
                logrs.close()
            knownviruses = re.findall("Known viruses: (.*)",logrscon)
            scdirectories = re.findall("Scanned directories: (.*)",logrscon)
            scfiles = re.findall("Scanned files: (.*)",logrscon)
            infectedfiles = re.findall("Infected files: (.*)",logrscon)
            otalerrors = re.findall("Total errors: (.*)",logrscon)
            datascanned = re.findall("Data scanned: (.*)",logrscon)
            dataread = re.findall("Data read: (.*)",logrscon)
            timesa = re.findall("Time: (.*)",logrscon)
            tempdict['scdirectories'] = scdirectories[0]
            tempdict['scfiles'] = scfiles[0]
            tempdict['infectedfiles'] = infectedfiles[0]
            tempdict['timesa'] =  timesa[0]
            resultList.append(tempdict)
            
            dataReportMsg=objectTemp.orgDataReportMsg(resultList)
            objectTemp.sendMsgToUI(dataReportMsg)
            
            progReportMsg=objectTemp.orgProgReportMsg("100", "木马信息检查完毕.")
            objectTemp.sendMsgToUI(progReportMsg)        
            
if __name__ == "__main__":
    objectTemp=ThreatDocument()  
    try: 
        objectTemp.getThreatDocumentInfo()            
    except Exception,e: 
        print e
        log4py.error("木马信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("木马信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
        killSubProcess("threatDocument",checkPath,'')
