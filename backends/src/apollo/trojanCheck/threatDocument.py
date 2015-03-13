#!/usr/bin/env python
# encoding:utf8
import os
import time 
import re
import sys
import json

sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
# 获取父文件夹路径
def GetParentPath(strPath):    #
    if not strPath:  
        return None;  
    lsPath = os.path.split(strPath)
    if lsPath[1]:  
        return lsPath[0];  
    lsPath = os.path.split(lsPath[0])
    return lsPath[0]

scandir = ''  # scan路径
logdir = os.getcwd() +'/clamscan11.log'
filePathPara =GetParentPath( os.getcwd())+'/apollo/trojanCheck/threatDocfork.py'
sord = '/usr/local/clamav/bin/clamscan -r -v '+scandir+' --log='+logdir
checkord = 'cat '+logdir+' |grep  Scanning |wc -l'
foundord = 'cat '+logdir+' |grep  FOUND'
class ThreatDocument(CommHandler):
# class Ceshi():
    def __init__(self):
        CommHandler.__init__(self)
#         pass
    def filenum(self,dir):  # 文件个数
        return sum([len(files) for root,dirs,files in os.walk(dir)])
    def progress(self,filenum,checknum):  # 文件个数，每秒读取个数  ，时间
        pro = 0
        if filenum == 0:
            return '0'
        else:
            pro =    (checknum*100//filenum)  #string.atof(a1)
            if pro >= 99:
                pro = 99
            return str(pro)+'%'
if __name__ == "__main__":   

    try :
        objectTemp = ThreatDocument() 
        print  sys.argv[1]
        paradic= json.loads(sys.argv[1])
        paradic = paradic['parameters']
        scandir = paradic['parameter1'] # 获取扫描路径
        if len(scandir) > 0: 
#                 创建日志文件
            if os.path.isfile(logdir): 
                os.remove(logdir)
            os.mknod(logdir)
            pid = os.fork()
            if not pid: 
                os.execl("/usr/bin/python2.7", "python", filePathPara,scandir) 
            else: 
                rsdic = {}
                rslist = []
                filenum = objectTemp.filenum(scandir)   # 扫描文件个数
                knownviruses,scdirectories,scfiles,infectedfiles,totalerrors,datascanned,dataread,datareadtimesa\
                ='','','','','','','',''
                prors='0%' # 进度
                while  1:
                    time.sleep(2)
                    readrs = ''   # 正在检查的文件
                    if os.path.isfile(logdir): 
                        logrs=open(logdir)  
                        logrscon = logrs.read();
                        logrs.close()
                        knownviruses = re.findall("Known viruses: (.*)",logrscon)
                        scdirectories = re.findall("Scanned directories: (.*)",logrscon)
                        scfiles = re.findall("Scanned files: (.*)",logrscon)
                        infectedfiles = re.findall("Infected files: (.*)",logrscon)
                        totalerrors = re.findall("Total errors: (.*)",logrscon)
                        datascanned = re.findall("Data scanned: (.*)",logrscon)
                        dataread = re.findall("Data read: (.*)",logrscon)
                        timesa = re.findall("Time: (.*)",logrscon)
                        if len(knownviruses) >0 and len(scdirectories)>0:
#                             rsdic['knownviruses'] = knownviruses
                            rsdic['scdirectories'] = scdirectories[0]
                            rsdic['scfiles'] = scfiles[0]
                            rsdic['infectedfiles'] = infectedfiles[0]
#                             rsdic['totalerrors'] =    totalerrors[0]
#                             rsdic['datascanned'] = datascanned[0]
#                             rsdic['dataread'] =  dataread[0]
                            rsdic['timesa'] =  timesa[0]
                            foundtemp = os.popen(foundord)
                            foundcontemp = foundtemp.readlines()
                            foundtemp.close()
                            founlisttemp = []
                            for readline  in foundcontemp:
                                if readline :
                                    foundlinetemp = re.findall("(.*): ",readline)
                                    if foundlinetemp[0]:
                                            founlisttemp.append(foundlinetemp[0]) 
                            rsdic['found'] = founlisttemp 
                            rslist.append(rsdic) 
                            progReportMsg = objectTemp.orgProgReportMsg("100", "威胁文档检查完毕 ")
                            objectTemp.sendMsgToUI(progReportMsg)
                            dataReportMsg = objectTemp.orgDataReportMsg(rslist) # 返回结果
                            objectTemp.sendMsgToUI(dataReportMsg)
                            break
                        else:
                            logrs=open(logdir)  
                            logrscon = logrs.readlines();
                            logrs.close()
                            for readline  in logrscon:
                                readrs = readline.replace('\n','') 
                            checktemp=os.popen(checkord)
                            checknumtemp = int (checktemp.read())
                            checktemp.close()
                            prors = objectTemp.progress(filenum, checknumtemp )   
#                             dataReportMsg = objectTemp.orgDataReportMsg(rslist)
#                             objectTemp.sendMsgToUI(dataReportMsg)
                            progReportMsg = objectTemp.orgProgReportMsg(prors, readrs )#
                            objectTemp.sendMsgToUI(progReportMsg)
                            continue
                    else :
                        log4py.error("检查clamav出错: 缺失日志文件"+logdir )
                        errReportMsg = objectTemp.orgErrReportMsg("check the clamav error.")
                        objectTemp.sendMsgToUI(errReportMsg)
                        break   
        else:
            log4py.error("检查clamav出错: 未指定扫描路径")
            errReportMsg = objectTemp.orgErrReportMsg("check the clamav error.")
            objectTemp.sendMsgToUI(errReportMsg)
    except Exception,e:
         log4py.error("检查clamav出错:" + str(e) +logdir)
         errReportMsg = objectTemp.orgErrReportMsg("check the clamav error.")
         objectTemp.sendMsgToUI(errReportMsg)
         
 