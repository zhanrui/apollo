#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class ThreatDocument(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getThreatDocument(self):
        return ""
if __name__ == "__main__":
    objectTemp=ThreatDocument()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getThreatDocument())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "威胁文档信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("威胁文档信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("威胁文档信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
