#!/usr/bin/env python
# encoding:utf8
import os
import re
import sys
import linecache
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler 

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
def  scanFileAndOrgProg(checkPathPara,logdirPara) :   
    checkPath=checkPathPara
    logdir=logdirPara
    ps = ProgressStatistics() 
    
    filenum = ps.filenum(checkPath)   # 扫描文件个数
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
                prors = ps.getProgressStatisticsInfo(filenum, lastNum )
                if found  in readrs:
                    foundDict['found']=readrs
                    temp=readrs.strip() 
                    tempFullpath=temp[0:len(temp)-6] 
                    resultList=[m.start() for m in re.finditer('/', tempFullpath)]
                    lenTemp=len(resultList)-1
                    pTemp=resultList[lenTemp]
                    tempFolderpath=tempFullpath[0:pTemp] 
                    foundDict['filefullpath']=tempFullpath
                    foundDict['filefolderpath']=tempFolderpath 
                    foundList.append(foundDict)
                    dataReportMsg=ps.orgDataReportMsg(foundList)
                    ps.sendMsgToUI(dataReportMsg) 
                    foundDict={}
                    foundList=[]                        
                readrs=readrs.strip()
                if ""==readrs:
                    continue                        
                progReportMsg = ps.orgProgReportMsg(prors, readrs )#
                ps.sendMsgToUI(progReportMsg)  
        else :
            continue   
         
 
