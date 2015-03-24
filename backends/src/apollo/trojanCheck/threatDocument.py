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
from apollo.commHandler import CommHandler,parameters
checkPathTemp=parameters['path'] 
checkPath = checkPathTemp.encode('utf-8')
logGenDir="/tmp/threatDocument.log" #日志生成目录
clamavPath=os.path.dirname(os.getcwd())+'/apollo/trojanCheck/clamav'
class ThreatDocument(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass
    def getThreatDocumentInfo(self):
        if os.path.exists(logGenDir): 
                os.remove(logGenDir)
        libc = ctypes.CDLL('libc.so.6')
        pid = os.fork()
        if not pid:
            libc.prctl(1, 15)       
#             strOrder = '/usr/local/clamav/bin/clamscan -r  '+checkPath+' '+' >>'+logGenDir
            strOrder = clamavPath+'/bin/clamscan -d'+clamavPath+'/updata'+' -r  '+checkPath+' '+' >>'+logGenDir            
            hw = os.popen(strOrder)
            hw.close()
        else:             
            log4py.info('********backends创建子进程('+str(pid)+")开始处理..")
            scanFileAndOrgProg(checkPath,logGenDir) #调用文件检查公共模块，并组织进度信息发送，该模块调用完毕说明文件检查已结束             
            if os.path.exists(logGenDir): 
                os.remove(logGenDir)                   
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
