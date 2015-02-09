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
        return ""
if __name__ == "__main__":
    objectTemp=OpenPort() 
    try:  
        raise Exception             
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getOpenPort())
        objectTemp.sendMsgToUI(dataReportMsg)
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "开放端口信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("开放端口信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("开放端口信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)     
