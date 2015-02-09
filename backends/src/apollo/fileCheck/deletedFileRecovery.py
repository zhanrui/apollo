#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class DeletedFileRecovery(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getDeletedFileRecovery(self):
        return ""
if __name__ == "__main__":
    objectTemp=DeletedFileRecovery()  
    try: 
        raise Exception               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getDeletedFileRecovery())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "已删除文件恢复信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("已删除文件恢复信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("已删除文件恢复信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
