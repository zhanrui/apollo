#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class OpenPort(CommHandler):
    
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getOpenPort(self):
        openPortlist = []
        localadd,foreadd,pid='','',''
#         tcp   udp,raw,udplite
        hw = os.popen('netstat -tanp |grep tcp') 
        res = hw.readlines()
        hw.close()
        for line in  res :
            if line.strip():
                if line.rstrip('\n'):
                    i = 0
                    openPortdic = {}
                    for re in  line.split(' '):
                            if re.strip():
                                i=i+1
                                if i == 4:
                                    openPortdic['localadd'] = re.strip()
                                if i == 5:
                                    openPortdic['foreadd'] = re.strip()
                                if i == 7:
                                    openPortdic['pid'] = re.strip()
                    if len(openPortdic)==3:
                        openPortlist.append(openPortdic)
        return openPortlist            
                              
if __name__ == "__main__":
    objectTemp=OpenPort() 
    try:  
          
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getOpenPort())
        objectTemp.sendMsgToUI(dataReportMsg)
          
        progReportMsg=objectTemp.orgProgReportMsg("100", "开放端口信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        log4py.error("开放端口信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("开放端口信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)     
