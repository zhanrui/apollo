#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
import re
import ctypes
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.killSubProcess import killSubProcess
from common.utils.log import log4py
from common.utils.scanFile import scanFileAndOrgProg
from apollo.commHandler import CommHandler 
from apollo.commHandler import parameters   
checkPath = str(parameters['path'])
keyword = str(parameters['keyword'])
logGenDir="/tmp/fileRoutineCheck.log" #日志生成目录
functionname="fileRoutineCheck"
class FileRoutineCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getFileRoutineCheckInfo(self):
        libc = ctypes.CDLL('libc.so.6')
        pid = os.fork()
        if not pid:
            libc.prctl(1, 15) #父进程over的同时随之over 
#             if os.path.isfile(logGenDir): 
#                 os.remove(logGenDir)
#             if os.path.isfile(logGenDir): 
#                 os.remove(logGenDir)
#             else:
#                 os.mknod(logGenDir)
                            
            strOrder = './CAFileScan '+checkPath+' '+keyword+' >>'+logGenDir
            print strOrder
            hw = os.popen(strOrder)#会产生以当前子进程id为父id的'./CAFileScan '+scanPath+' '+keyWord+' >>'+logGenDir进程，和另外一个./CAFileScan '+scanPath+' '+keyWord进程，这两个进程需要另外处理
            hw.close()
        else: 
            log4py.info('backends创建子进程('+str(pid)+")开始处理..")
            tempdict={}
            resultList=[]
            tempdict['found']=scanFileAndOrgProg(functionname,checkPath,logGenDir) #调用文件检查公共模块，并组织进度信息发送，该模块调用完毕说明文件检查已结束             

            logrs=open(logGenDir)  
            logrscon = logrs.read();
            logrs.close()                
            filetotal = re.findall("#TOTAL:(.*)",logrscon)    
            tempdict['filetotal'] = filetotal[0]
            resultList.append(tempdict)
            
            dataReportMsg=objectTemp.orgDataReportMsg(resultList)
            objectTemp.sendMsgToUI(dataReportMsg)
            
            progReportMsg=objectTemp.orgProgReportMsg("100", "文件常规信息检查完毕.")
            objectTemp.sendMsgToUI(progReportMsg)            
            
if __name__ == "__main__":
    objectTemp=FileRoutineCheck()  
    try: 
        objectTemp.getFileRoutineCheckInfo()        
    except Exception,e: 
        print e
        log4py.error("文件常规信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("文件常规信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
        killSubProcess("fileRoutineCheck",checkPath,keyword)
        
        
