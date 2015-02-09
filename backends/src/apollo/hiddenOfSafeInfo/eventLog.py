#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class EventLog(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getEventLog(self):
        return ""
if __name__ == "__main__":
    objectTemp=EventLog()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getEventLog())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "事件日志信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("事件日志信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("事件日志信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
