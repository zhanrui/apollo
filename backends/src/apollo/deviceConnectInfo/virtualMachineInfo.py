#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from time import sleep
from apollo.commHandler import CommHandler
class VirtualMachineInfo(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getVirtualMachineInfo(self):
        return ""
if __name__ == "__main__":
    objectTemp=VirtualMachineInfo()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getVirtualMachineInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the VirtualMachineInfo completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查虚拟机信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the VirtualMachineInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)
