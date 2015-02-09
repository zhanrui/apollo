#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class USBDepthCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getUSBDepthCheck(self):
        return ""
if __name__ == "__main__":
    objectTemp=USBDepthCheck()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getUSBDepthCheck())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "USB深度信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("USB深度信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("USB深度信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
