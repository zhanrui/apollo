#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class UserAuthentication(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getUserAuthentication(self):
        return ""
if __name__ == "__main__":
    objectTemp=UserAuthentication()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getUserAuthentication())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "用户认证信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("用户认证信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("用户认证信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
