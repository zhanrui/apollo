#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class SharingInfo(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getSharingInfo(self):
        return ""
if __name__ == "__main__":    
    objectTemp=SharingInfo()
    try:
        raise Exception        
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getSharingInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "共享信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("共享信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("共享信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
