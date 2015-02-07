#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class SystemService(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getSystemService(self):
        hw = os.popen('systemctl list-unit-files')
        sysServiceInfo = hw.read()
        hw.close()
        UNITFILE,STATE= '',''
        tmp=[]
        infoItem={}
        infoList=[]
        if sysServiceInfo :
            tmp = sysServiceInfo.split("\n")
            tmp.remove(tmp[0])
            tmp.remove(tmp[len(tmp)-1])
            tmp.remove(tmp[len(tmp)-1])
            tmp.remove(tmp[len(tmp)-1])
            for item in tmp:
                infoItem={}
                UNITFILE=item[0:44]
                UNITFILE=UNITFILE.strip()
                infoItem["UNITFILE"]=UNITFILE #单元文件         
                STATE=item[44:]
                STATE=STATE.strip()
                infoItem["STATE"]=STATE #状态
                infoList.append(infoItem)
        print infoList 
        return infoList
if __name__ == "__main__":
    objectTemp=SystemService() 
    try:               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getSystemService())
        objectTemp.sendMsgToUI(dataReportMsg)
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the systemService completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查系统服务信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the systemService error.")
        objectTemp.sendMsgToUI(errReportMsg)     
