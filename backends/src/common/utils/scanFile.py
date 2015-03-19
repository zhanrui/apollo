#!/usr/bin/env python
# encoding:utf8
import os
import time 
import re
import sys
import json
import linecache
from _csv import reader
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
    objectTemp = ProgressStatistics() 
    if len(checkPath) > 0: 
#                 创建日志文件 这个步骤要在fork 之前
        filenum = objectTemp.filenum(checkPath)   # 扫描文件个数
        prors='0' # 进度
        lastNum=1
        currentNum=1
        found='FOUND'
        end='SCAN SUMMARY'
        foundDict={}
        foundList=[]
        while  1:
            readrs = ''   # 正在检查的文件
            if os.path.exists(logdir):                
                logrs=open(logdir)  
                currentNum=len(logrs.readlines())
                logrs.close()
                while lastNum<=currentNum:
                    linecache.clearcache()
                    readrs=linecache.getline(logdir, lastNum)
                    if end in readrs:
                        return
                    readrs=readrs.replace('\n','')
                    lastNum=lastNum+1
                    prors = objectTemp.getProgressStatisticsInfo(filenum, lastNum )
                    if found  in readrs:
                        foundDict['found']=readrs
                        foundList.append(foundDict)
                        dataReportMsg=objectTemp.orgDataReportMsg(foundList)
                        objectTemp.sendMsgToUI(dataReportMsg) 
                        foundDict={}
                        foundList=[]                        
                    progReportMsg = objectTemp.orgProgReportMsg(prors, readrs )#
                    objectTemp.sendMsgToUI(progReportMsg)  
            else :
                continue   
    else:
        log4py.error(scanTypeInfo + " 出错：未指定扫描路径" )

def  scanFileAndOrgProgForManyKeyword(scanTypePara,checkPathPara,logdirPara,keywordNumPara)   :   
#     try :
    scanTypeInfo=scanType[scanTypePara]
    checkPath=checkPathPara
    logdir=logdirPara
    objectTemp = ProgressStatistics() 
    if len(checkPath) > 0: 
#                 创建日志文件 这个步骤要在fork 之前
        filenum = objectTemp.filenum(checkPath)   # 扫描文件个数
        filenum = keywordNumPara*filenum
        prors='0' # 进度
        lastNum=1
        currentNum=1
        found='FOUND'
        end='SCAN SUMMARY'
        total='#TOTAL'
        endNum=1
        foundDict={}
        foundList=[]
        while  1:
            readrs = ''   # 正在检查的文件
            if os.path.exists(logdir):                
                logrs=open(logdir)  
                currentNum=len(logrs.readlines())
                logrs.close()
                while lastNum<=currentNum:
                    linecache.clearcache()
                    readrs=linecache.getline(logdir, lastNum)
                    if end in readrs:
                        if endNum>=keywordNumPara:
#                             print '&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&'
#                             print endNum
                            return
                        else:
                            endNum=endNum+1                           
                    readrs=readrs.replace('\n','')
                    lastNum=lastNum+1
                    prors = objectTemp.getProgressStatisticsInfo(filenum, lastNum )
                    if found  in readrs:
                        foundDict['found']=readrs
                        foundList.append(foundDict)
                        dataReportMsg=objectTemp.orgDataReportMsg(foundList)
                        objectTemp.sendMsgToUI(dataReportMsg) 
                        foundDict={}
                        foundList=[]
                    if total in readrs or end in readrs:
                        continue                        
                    progReportMsg = objectTemp.orgProgReportMsg(prors, readrs )#
                    objectTemp.sendMsgToUI(progReportMsg)  
            else :
                continue   
    else:
        log4py.error(scanTypeInfo + " 出错：未指定扫描路径" )
         
 