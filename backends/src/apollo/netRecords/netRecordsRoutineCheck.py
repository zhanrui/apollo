#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class NetRecordsRoutineCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getNetRecordsRoutineCheck(self):
        return ""
if __name__ == "__main__":
    objectTemp=NetRecordsRoutineCheck()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getNetRecordsRoutineCheck())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "上网记录常规信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("上网记录常规信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("上网记录常规信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
