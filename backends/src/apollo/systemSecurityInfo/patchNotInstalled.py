#! /usr/bin/python
#-*-coding:utf-8-*- 
from common.utils.log import log4py
from time import sleep
from apollo.commHandler import CommHandler
class PatchNotInstalled(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getPatchNotInstalled(self):
        sleep(10)
        return ""
if __name__ == "__main__":    
    objectTemp=PatchNotInstalled()
    try:
#         raise Exception        
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getPatchNotInstalled())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the patchNotInstalled completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查未安装补丁信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the patchNotInstalled error.")
        objectTemp.sendMsgToUI(errReportMsg)
