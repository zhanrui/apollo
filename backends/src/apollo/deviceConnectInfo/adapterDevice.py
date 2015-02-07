#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class AdapterDevice(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getAdapterDevice(self):
        return ""
if __name__ == "__main__":
    objectTemp=AdapterDevice() 
    try:  
        raise Exception             
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getAdapterDevice())
        objectTemp.sendMsgToUI(dataReportMsg)
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the AdapterDevice completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查网卡设备信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the AdapterDevice error.")
        objectTemp.sendMsgToUI(errReportMsg)     
