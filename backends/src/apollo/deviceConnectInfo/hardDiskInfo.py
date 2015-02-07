#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from time import sleep
from apollo.commHandler import CommHandler
class HardDiskInfo(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getHardDiskInfo(self):
        return ""
if __name__ == "__main__":    
    objectTemp=HardDiskInfo()
    try:
        raise Exception        
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getHardDiskInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the HardDiskInfo completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查硬盘信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the HardDiskInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)
