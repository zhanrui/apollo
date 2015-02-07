#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class SystemProcess(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getProcessInfo(self):
        hw = os.popen('ps -ef')
        processInfo = hw.read()
        hw.close()
        UID,PID,PPID,STIME,TTY,TIME,CMD = '','','','','','',''
        tmp=[]
        infoItem={}
        infoList=[]
        if processInfo :
            tmp = processInfo.split("\n")
            tmp.remove(tmp[0])
            for item in tmp:
                infoItem={}
                UID=item[0:9]
                UID=UID.strip()
                infoItem["UID"]=UID #用户ID                
                PID=item[9:16]
                PID=PID.strip()
                infoItem["PID"]=PID #进程ID                     
                PPID=item[16:22]
                PPID=PPID.strip()
                infoItem["PPID"]=PPID #父进程ID
                STIME=item[24:30]
                STIME=STIME.strip()
                infoItem["STIME"]=STIME #开始时间
                TTY=item[30:39]
                TTY=TTY.strip().replace("?", "none")
                infoItem["TTY"]=TTY #终端名称                    
                TIME=item[39:47]
                infoItem["TIME"]=TIME #进程执行时间，进程启动所占用CPU时间                   
                CMD=item[48:]
                infoItem["CMD"]=CMD  #命令行输入
                infoList.append(infoItem)
        return infoList
if __name__ == "__main__":  
    objectTemp=SystemProcess()  
    try:                
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getProcessInfo())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the systemProcess completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查系统进程信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the systemProcess error.")
        objectTemp.sendMsgToUI(errReportMsg)  
