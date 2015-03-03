#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class GroupInfo(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getGroupInfo(self):
        groupInfolist = []
        groupname, groupid = '', '' 
        with open('/etc/group') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n'):
                        groupInfodic = {}  
                        groupname = line.rstrip('\n').split(':')[0]
                        groupid = line.rstrip('\n').split(':')[2]
                        groupInfodic['groupname'] = groupname 
                        groupInfodic['groupid'] = groupid 
                        groupInfolist.append(groupInfodic)
                         
        return groupInfolist
if __name__ == "__main__":
    objectTemp=GroupInfo()
    try:   
                
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getGroupInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "组信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        log4py.error("组信息检查出错:" + str(e))
        errReportMsg=objectTemp.orgErrReportMsg("组信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
