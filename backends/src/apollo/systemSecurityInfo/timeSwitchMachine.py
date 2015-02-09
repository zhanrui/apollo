#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class TimeSwitchMachine(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getTimeSwitchMachine(self):
        hw = os.popen('hostname')
        hostname = hw.read()
        hostname = hostname.split("\n")
        hostname = hostname[0]
        hw.close()
        hw = os.popen('last -x|grep reboot')
        bootInfo = hw.read()
        hw.close()
        hw = os.popen('last -x|grep shutdown')
        shutdownInfo = hw.read()
        hw.close()
        TIME= ''
        tmp=[]
        infoItem={}
        infoList=[]
        print hostname 
        print bootInfo
        if bootInfo :
            tmp = bootInfo.split("\n")
            for item in tmp:
                infoItem={}
                infoItem["TYPE"]="boot"
                TIME1=item[39:50]
                TIME2=item[57:63]
                TIME=str(TIME1)+str(TIME2)
                infoItem["TIME"]=TIME #时间
                infoItem["HOSTNAME"]=hostname
                infoList.append(infoItem)
        if shutdownInfo :
            tmp = shutdownInfo.split("\n")
            for item in tmp:
                infoItem={}
                infoItem["TYPE"]="shutdown"
                TIME1=item[39:50]
                TIME2=item[57:63]
                TIME=str(TIME1)+str(TIME2)
                infoItem["TIME"]=TIME #时间
                infoItem["HOSTNAME"]=hostname
                infoList.append(infoItem)
        return infoList
if __name__ == "__main__":
    objectTemp=TimeSwitchMachine()
    try:               
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getTimeSwitchMachine())
        objectTemp.sendMsgToUI(dataReportMsg)
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "开关机时间信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e 
        log4py.error("开关机时间检查信息出错.")
        errReportMsg=objectTemp.orgErrReportMsg("开关机时间检查信息出错.")
        objectTemp.sendMsgToUI(errReportMsg)
