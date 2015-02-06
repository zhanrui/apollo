#!/usr/bin/env python
#encoding:utf8
'''
Created on 2015年2月4日

@author: hu
 CPU信息
'''
import commHandler
from log import log4py
class CpuInfo(commHandler.CommHandler):
    
    def __init__(self):
        commHandler.CommHandler.__init__(self)
        pass
    def getCpuinfo(self):
        cpulist =[]
        with open('/proc/cpuinfo') as f:
            for line in f:
                if line.rstrip('\n'):
                    cpulist.append({ line.rstrip('\n').split(':')[0].rstrip('\t'):line.rstrip('\n').split(':')[1]})
        f.close()
        return cpulist
if __name__ == "__main__": 
    objectTemp=CpuInfo()
    try :  
        cpulist=objectTemp.getCpuinfo()
        dataReportMsg=objectTemp.orgDataReportMsg(cpulist)
        objectTemp.sendMsgToUI(dataReportMsg)
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the CpuInfo completed.")
        objectTemp.sendMsgToUI(progReportMsg)
        
    except Exception,e:
        log4py.error("检查CPU信息出错."  )
        errReportMsg=objectTemp.orgErrReportMsg("check the CpuInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)     