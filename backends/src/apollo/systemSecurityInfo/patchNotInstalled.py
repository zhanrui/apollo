#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from time import sleep
from apollo.commHandler import CommHandler
class PatchNotInstalled(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getPatchNotInstalled(self):
        return ""
if __name__ == "__main__":    
    objectTemp=PatchNotInstalled()
    try:
        raise Exception        
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getPatchNotInstalled())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "未安装补丁信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("未安装补丁信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("未安装补丁信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
