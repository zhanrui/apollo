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
from log import log4py
from common.enums.enumBusiness import scanType

class ProgressStatistics(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)

    def filenum(self,dir):  # 文件个数
        return sum([len(files) for root,dirs,files in os.walk(dir)])
    
    def getProgressStatisticsInfo(self,filenum,checknum):  # 文件个数，每秒读取个数  ，时间
        pro = 0
        if filenum == 0:
            return '0'
        else:
            pro =    (checknum*100//filenum)  #string.atof(a1)
            if pro >= 99:
                pro = 99
            return str(pro)

# 该方法主要实现扫描指定路径下的所有文件，并组织进度信息
def  scanFileAndOrgProg(scanTypePara,checkPathPara,logdirPara)   :   
#     try :
    scanTypeInfo=scanType[scanTypePara]
    checkPath=checkPathPara
    logdir=logdirPara
    checkord = 'cat '+logdir+' |wc -l'
    foundord = 'cat '+logdir+' |grep  FOUND'
    objectTemp = ProgressStatistics() 
    if len(checkPath) > 0: 
#                 创建日志文件 这个步骤要在fork 之前
        if not os.path.isfile(logdir): 
            os.mknod(logdir)
        filenum = objectTemp.filenum(checkPath)   # 扫描文件个数
        prors='0' # 进度
        lastReadrs=None
        while  1:
            readrs = ''   # 正在检查的文件
            if os.path.isfile(logdir): 
                logrs=open(logdir)  
                logrscon = logrs.read();
                logrs.close()
                scansummary = re.findall("----------- SCAN SUMMARY -----------",logrscon)
                if  len(scansummary)>0:
                    foundList=[]
                    hw = os.popen(foundord)
                    foundtemp = hw.read()
                    hw.close()
                    if foundtemp :
                        foundList = foundtemp.split("\n")           
                    return foundList  
                else:
                    logrs=open(logdir)  
                    logrscon = logrs.readlines();
                    logrs.close()
                    for readline  in logrscon:
                        readrs = readline.replace('\n','')
                    checktemp=os.popen(checkord)
                    checknumtemp = int (checktemp.read())
                    checktemp.close()
                    prors = objectTemp.getProgressStatisticsInfo(filenum, checknumtemp )
                    if lastReadrs != readrs:  
                        progReportMsg = objectTemp.orgProgReportMsg(prors, readrs )#
                        objectTemp.sendMsgToUI(progReportMsg)                    
                    lastReadrs=readrs
                    continue
            else :
                log4py.error(scanTypeInfo + " 出错： 缺失日志文件"+logdir )
                break   
    else:
        log4py.error(scanTypeInfo + " 出错：未指定扫描路径" )
         
 