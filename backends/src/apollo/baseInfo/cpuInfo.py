#!/usr/bin/env python
#encoding:utf8
'''
Created on 2015年2月4日

@author: hu
 CPU信息
'''
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
class CpuInfo(CommHandler):
    
    def __init__(self):
        CommHandler.__init__(self)
        pass
    def getCpuinfo(self):
        cpudic = {}
        cpulist =[]
        cputemplist = []
        vendorId,cpu_cores,modelName, cpuMHz, cacheSize ='','','','',''     
        with open('/proc/cpuinfo') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n').startswith('vendor_id'):
                        vendorId = line.rstrip('\n').split(':')[1]
#                     elif line.rstrip('\n').startswith('cpu cores'):
#                          cpu_cores = line.rstrip('\n').split(':')[1]
#                     elif line.rstrip('\n').startswith('siblings'):
#                          cpu_siblings = line.rstrip('\n').split(':')[1]
#                     elif line.rstrip('\n').startswith('clflush size'):
#                          clflush_size = line.rstrip('\n').split(':')[1]
# #                          clflush_size = filter(str.isdigit,clflush_size)
                    elif line.rstrip('\n').startswith('cache size'):
                        cacheSize = line.rstrip('\n').split(':')[1]
#                          cache_size = filter(str.isdigit,cache_size)
                    elif line.rstrip('\n').startswith('model name'):
                        modelName = line.rstrip('\n').split(':')[1]
#                          modelName = filter(str.isdigit,cache_size)
                    elif line.rstrip('\n').startswith('cpu MHz'):
                        cpuMHz = line.rstrip('\n').split(':')[1]
        cpudic['modelName'],cpudic['vendorId'],cpudic['cacheSize'],cpudic['cpuMHz'] = modelName,vendorId,cacheSize,cpuMHz
        cpulist.append(cpudic)
        return cpulist
if __name__ == "__main__": 
    objectTemp=CpuInfo()
    try :  
        cpulist=objectTemp.getCpuinfo()
        dataReportMsg=objectTemp.orgDataReportMsg(cpulist)
        objectTemp.sendMsgToUI(dataReportMsg)
        progReportMsg=objectTemp.orgProgReportMsg("100", "CPU信息检查完毕")
        objectTemp.sendMsgToUI(progReportMsg)
        
    except Exception,e:
        log4py.error("检查CPU信息出错."+str(e) )
        errReportMsg=objectTemp.orgErrReportMsg("check the CpuInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)     