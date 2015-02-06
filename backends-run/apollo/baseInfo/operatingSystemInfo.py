#!/usr/bin/env python
#encoding:utf8
'''
Created on 2015年2月4日

@author: hu
操作系统
'''
import platform
import commHandler
from log import log4py
class OperatingSystemInfo(commHandler.CommHandler):    
    def __init__(self):
        commHandler.CommHandler.__init__(self)
        pass
    def getOperatingSystemInfo(self):
        oplist = []
        oplist.append( {'platform':platform.platform()}) #    '''获取操作系统名称及版本号'''    
        oplist.append({'version': platform.version()}) # '''获取操作系统版本号'''    
        oplist.append({'architecture':platform.architecture()}) #  '''获取操作系统的位数'''    
        oplist.append({'machine':platform.machine()})  # '''计算机类型'''
        oplist.append({'node':platform.node()}) #'''计算机的网络名称'''
        oplist.append({'processor':platform.processor()})  #   '''计算机处理器信息'''
        oplist.append({'system':platform.system()}) #  '''获取操作系统类型'''
        oplist.append({'uname':platform.uname() }) # '''汇总信息'''
        return oplist
         
    
if __name__ == "__main__":
    objectTemp=OperatingSystemInfo()  
    try:      
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getOperatingSystemInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the OperatingSystemInfo completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查操作系统信息出错." ) 
        errReportMsg=objectTemp.orgErrReportMsg("check the OperatingSystemInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)   