#!/usr/bin/env python
#encoding:utf8
'''
Created on 2015年2月4日

@author: hu
 CPU信息
'''
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
class BlueToothDevice(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass
def getBlueToothDevice(self):
        return ""
if __name__ == "__main__": 
    objectTemp=BlueToothDevice()
    try: 
        raise Exception              
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getBlueToothDevice())
        objectTemp.sendMsgToUI(dataReportMsg)
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "check the BlueToothDevice completed.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("检查设备信息出错." )
        errReportMsg=objectTemp.orgErrReportMsg("check the BlueToothDevice error.")
        objectTemp.sendMsgToUI(errReportMsg)       
