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
from apollo.commHandler import CommHandler,parameters
checkPathTemp=parameters['path'] 
keywordTemp=parameters['keyword']
checkPath = checkPathTemp.encode('utf-8')
keyword = keywordTemp.encode('utf-8')
keywordList=re.split(';',keyword)
logGenDir="/tmp/fileRoutineCheck.log" #日志生成目录


class FileRoutineCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getFileRoutineCheckInfo(self):
        if os.path.exists(logGenDir): 
            os.remove(logGenDir)
        libc = ctypes.CDLL('libc.so.6')
        keywordNum=len(keywordList)
        pid = os.fork()
        if not pid:
            libc.prctl(1, 15) #父进程over的同时随之over 
            currentNum=0
            strOrder='./CAFileScan '+checkPath+' '
            keywordTemp=''
            while currentNum<keywordNum:
                keywordTemp = keywordTemp+keywordList[currentNum]+' '
                print keywordTemp                
                currentNum=currentNum+1
            strOrder=strOrder+keywordTemp+'>>'+logGenDir 
            print strOrder
            hw = os.popen(strOrder)#会产生以当前子进程id为父id的'./CAFileScan '+scanPath+' '+keyWord+' >>'+logGenDir进程，和另外一个./CAFileScan '+scanPath+' '+keyWord进程，这两个进程需要另外处理
            hw.close()     
        else: 
            log4py.info('backends创建子进程('+str(pid)+")开始处理..")
                #调用文件检查公共模块，并组织进度信息发送，该模块调用完毕说明文件检查已结束
                #调用该方法可实现多个、单个关键词检查秘密
            scanFileAndOrgProg(checkPath,logGenDir) 

            if os.path.exists(logGenDir): 
                os.remove(logGenDir)
            
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
        killSubProcess("fileRoutineCheck",checkPath,keywordList)
        
        
