#!/usr/bin/env python
# encoding:utf8
import os
import time 
import re
import sys
import json
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from apollo.commHandler import parameters   
from common.utils.log import log4py
class ThreatDocument(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)

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
            return str(pro)

msdic =  parameters
ordrtype = str(msdic['ordrtype']) #命令里种类    0 -关键字   1- 病毒 2-图片
scandir = str(msdic['checkPath']) # 获取扫描路径  
keyWord = str(msdic['keyWord']) #   关键字   这个日志中不用

if   ordrtype == '0'  :
    logdir = '/tmp/filecheck.log'
elif ordrtype == '1':
    logdir = '/tmp/clamscan333.log'
elif ordrtype == '2':
    logdir = '/tmp/checkimage.log'
checkord = 'cat '+logdir+' |wc -l'
foundord = 'cat '+logdir+' |grep  FOUND'

def  threatDocumentcopy()   :   
    try :
        objectTemp = ThreatDocument() 
        if len(scandir) > 0: 
#                 创建日志文件 这个步骤要在fork 之前
#             if os.path.isfile(logdir): 
#                 os.remove(logdir)
#             os.mknod(logdir)
            rsdic = {}
            rslist = []
            filenum = objectTemp.filenum(scandir)   # 扫描文件个数
            knownviruses,scdirectories,scfiles,infectedfiles,totalerrors,datascanned,dataread,datareadtimesa\
                ='','','','','','','',''
            prors='0' # 进度
            while  1:
                time.sleep(5)
                readrs = ''   # 正在检查的文件
                if os.path.isfile(logdir): 
                    logrs=open(logdir)  
                    logrscon = logrs.read();
                    logrs.close()
                    scansummary = re.findall("----------- SCAN SUMMARY -----------",logrscon)
                    if  len(scansummary)>0:
                        if ordrtype == '0' :  
                            filetotal = re.findall("#TOTAL: (.*)",logrscon)
                            rsdic['filetotal'] = filetotal[0]
                        elif ordrtype == '1':
                            knownviruses = re.findall("Known viruses: (.*)",logrscon)
                            scdirectories = re.findall("Scanned directories: (.*)",logrscon)
                            scfiles = re.findall("Scanned files: (.*)",logrscon)
                            infectedfiles = re.findall("Infected files: (.*)",logrscon)
                            totalerrors = re.findall("Total errors: (.*)",logrscon)
                            datascanned = re.findall("Data scanned: (.*)",logrscon)
                            dataread = re.findall("Data read: (.*)",logrscon)
                            timesa = re.findall("Time: (.*)",logrscon)
                            rsdic['scdirectories'] = scdirectories[0]
                            rsdic['scfiles'] = scfiles[0]
                            rsdic['infectedfiles'] = infectedfiles[0]
                            rsdic['timesa'] =  timesa[0]
                        elif ordrtype == '2' :
                            image = re.findall("#image: (.*)",logrscon)
                            rsdic['image'] = image[0]
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
                        progReportMsg = objectTemp.orgProgReportMsg("100", "检查完毕 ")
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
                        progReportMsg = objectTemp.orgProgReportMsg(prors, readrs )#
                        objectTemp.sendMsgToUI(progReportMsg)
                        continue
                else :
                    log4py.error("检查类型" +ordrtype + " 出错： 缺失日志文件"+logdir )
                    errReportMsg = objectTemp.orgErrReportMsg("check the clamav error.")
                    objectTemp.sendMsgToUI(errReportMsg)
                    break   
        else:
            log4py.error("检查类型" +ordrtype + " 出错：未指定扫描路径" )
            errReportMsg = objectTemp.orgErrReportMsg("check the clamav error.")
            objectTemp.sendMsgToUI(errReportMsg)
    except Exception,e:
         log4py.error("检查类型" + ordrtype + " 出错:" + str(e) +logdir)
         errReportMsg = objectTemp.orgErrReportMsg("check the clamav error.")
         objectTemp.sendMsgToUI(errReportMsg)
         
 