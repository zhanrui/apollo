#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class NetRecordsDepthCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getNetRecordsDepthCheck(self):
        return ""
if __name__ == "__main__":
    objectTemp=NetRecordsDepthCheck()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getNetRecordsDepthCheck())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "上网记录深度信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("上网记录深度信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("上网记录深度信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
