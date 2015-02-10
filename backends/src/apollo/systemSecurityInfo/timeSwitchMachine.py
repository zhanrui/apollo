#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
import time
monthDict={"Jan":"01","Feb":"02","Mar":"03","Apr":"04","May":"05","Jun":"06","Jul":"07","Aug":"08","Sep":"09","Oct":"10","Nov":"11","Dec":"12"}
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
        resultTemp={}
        YEAR=time.strftime('%Y',time.localtime(time.time()))
        if bootInfo :
            tmp = bootInfo.split("\n")
            for item in tmp:
                infoItem={}
                infoItem["TYPE"]="boot"
                monthTemp=item[43:46]
                MONTH=monthDict.get(monthTemp)
                DAY=item[47:49]
                DAY=DAY.strip()
                if len(DAY)==1:
                    DAY="0"+DAY 
                TIME=item[57:63]
                TIME=str(YEAR)+"."+str(MONTH)+"."+str(DAY)+""+str(TIME)
                infoItem["TIME"]=TIME #时间
                infoItem["HOSTNAME"]=hostname
                resultTemp[TIME]=infoItem
        if shutdownInfo :
            tmp = shutdownInfo.split("\n")
            for item in tmp:
                infoItem={}
                infoItem["TYPE"]="shutdown"
                monthTemp=item[43:46]
                MONTH=monthDict.get(monthTemp)
                DAY=item[47:49]
                DAY=DAY.strip()
                if len(DAY)==1:
                    DAY="0"+DAY                    
                TIME=item[57:63]
                TIME=str(YEAR)+"."+str(MONTH)+"."+str(DAY)+""+str(TIME)
                infoItem["TIME"]=TIME #时间
                infoItem["HOSTNAME"]=hostname
                resultTemp[TIME]=infoItem
        resultTemp=sorted(resultTemp.iteritems(),key=lambda asd:asd[0],reverse=False)
#         print resultTemp
        for x in range(len(resultTemp)):
            temp=resultTemp[x]
            infoList.append(temp[1])  
#         print infoList 
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
