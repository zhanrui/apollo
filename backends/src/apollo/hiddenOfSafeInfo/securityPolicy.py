#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class SecurityPolicy(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getSecurityPolicy(self):
        return ""
if __name__ == "__main__":
    objectTemp=SecurityPolicy() 
    try:  
        raise Exception             
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getSecurityPolicy())
        objectTemp.sendMsgToUI(dataReportMsg)
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "安全策略信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("安全策略信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("安全策略信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)     
