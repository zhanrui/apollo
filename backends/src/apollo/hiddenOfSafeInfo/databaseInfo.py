#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class DatabaseInfo(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getUserInfo(self):
        return ""
if __name__ == "__main__":
    objectTemp=DatabaseInfo()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getDatabaseInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "数据库信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("数据库信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("数据库信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
