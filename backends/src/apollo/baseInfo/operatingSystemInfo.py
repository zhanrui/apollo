#!/usr/bin/env python
#encoding:utf8
'''
Created on 2015年2月4日

@author: hu
操作系统
'''
import platform
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
class OperatingSystemInfo(CommHandler):
    
    def __init__(self):
        CommHandler.__init__(self)
        pass
    def getOperatingSystemInfo(self):
        oplist = []
        opdic = {}
        opdic['platform'] = platform.platform() #    '''获取操作系统名称及版本号'''    
        opdic['version'] = platform.version()  # '''获取操作系统版本号'''    
        opdic['architecture'] = platform.architecture()[0]  #  '''获取操作系统的位数'''    
        opdic['machine'] = platform.machine()   # '''计算机类型'''
        opdic['node'] = platform.node() #'''计算机的网络名称'''
        opdic['processor'] = platform.processor()   #   '''计算机处理器信息'''
        opdic['system'] = platform.system()  #  '''获取操作系统类型'''
        opdic['uname'] = platform.uname()   # '''汇总信息'''
        oplist.append(opdic)
        return oplist
if __name__ == "__main__":
    objectTemp=OperatingSystemInfo()  
    try:      
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getOperatingSystemInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
        progReportMsg=objectTemp.orgProgReportMsg("100", "操作系统信息检查完毕")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        log4py.error("检查操作信息出错."   +str(e)) 
        errReportMsg=objectTemp.orgErrReportMsg("check the OperatingSystemInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)   