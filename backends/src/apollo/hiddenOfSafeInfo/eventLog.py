#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import sys


sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class EventLog(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    def getEventLog(self):
        eventLogList = []
        eventLogDir = {}
        #与邮件相关的日志信息 
        os.system("chmod +x /var/log/maillog")        
        maillog = os.popen("/var/log/maillog").read()
        eventLogDir['maillog'] = maillog
        #与定时任务相关的日志信息 
        os.system("chmod +x /var/log/cron")
        cronlog = os.popen("/var/log/cron").read()
        eventLogDir['cronlog'] = cronlog
        #与安全相关的日志信息
        os.system("chmod +x /var/log/secure")
        securelog = os.popen("/var/log/secure").read()
        eventLogDir['securelog'] = securelog
        #系统启动后的信息和错误日志
        os.system("chmod +x /var/log/messages")
        messageslog = os.popen("/var/log/messages").read()
        eventLogDir['messageslog'] = messageslog
        
        eventLogList.append(eventLogDir)
        return eventLogList
if __name__ =="__main__":
    objectTemp=EventLog()  
    temp = objectTemp.getEventLog()
    print("==========%s"%objectTemp.getEventLog())
    try: 
        if(temp[0]['maillog']!='' and  temp[0]['cronlog']!=''):
            #print("success.....")
            dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getEventLog()) 
            objectTemp.sendMsgToUI(dataReportMsg)
            progReportMsg=objectTemp.orgProgReportMsg("100", "事件日志信息检查完毕.")
            objectTemp.sendMsgToUI(progReportMsg)
        else:
                temp.sendMsgToUI(temp.orgErrReportMsg("check the EventLog Permission denied,login by root ."))
            #print("login by root")
    except Exception,e: 
        #print e
        log4py.error("事件日志信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("事件日志信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
