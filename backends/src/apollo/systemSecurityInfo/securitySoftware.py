#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
from time import sleep
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class SecuritySoftware(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getSecuritySoftware(self):
        return ""
if __name__ == "__main__":
    objectTemp=SecuritySoftware()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getSecuritySoftware())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "安全软件信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("安全软件信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("安全软件信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
