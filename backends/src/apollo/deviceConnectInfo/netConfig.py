#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class NetConfig(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getNetConfig(self):
        return ""
if __name__ == "__main__":  
    objectTemp=NetConfig()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getNetConfig())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the NetConfig completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查网络配置信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the NetConfig error.")
        objectTemp.sendMsgToUI(errReportMsg)  
