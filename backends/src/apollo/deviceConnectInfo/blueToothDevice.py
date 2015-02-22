# #!/usr/bin/env python
# #encoding:utf8
'''
Created on 2015年2月4日

@author: hu
蓝牙设备
'''
import re
import sys
import os
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
class BlueToothDevice(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        pass
    def getBlueToothDevice(self):  
        bluelist = []
        bluedic = {}  
        bluetype,blueaddr,bluerun,bluename,bluepacket='','','','',''
        hw = os.popen('hciconfig -a ')  # local blue
        bluelisttemp = hw.read()
        hw.close()
        temp = re.findall('hci0:\t(.*)',bluelisttemp)
        if (re.findall('hci0:\t(.*)',bluelisttemp)) :
            if re.findall('Bus:(.*)',bluelisttemp):
                bluetype = re.findall('Bus:(.*)',bluelisttemp)[0]
            if re.findall('BD Address: (.*)',bluelisttemp):
                blueaddr = re.findall('BD Address: (.*)',bluelisttemp)[0].split(' ')[0]
            if re.findall('DOWN',bluelisttemp):
                bluerun = 'DOWN'
            elif re.findall('UP RUNNING',bluelisttemp):
                bluerun = 'UP RUNNING'
                if re.findall('Name: (.*)',bluelisttemp):
                    bluename =re.findall('Name: (.*)',bluelisttemp)[0].split(' ')[0]
            if re.findall('Packet type: (.*)',bluelisttemp):
                bluepacket = re.findall('Packet type: (.*)',bluelisttemp)[0]
        bluedic['bluetype'],bluedic['blueaddr'],bluedic['bluerun'],bluedic['bluename'],bluedic['bluepacket']=\
        bluetype,blueaddr,bluerun,bluename,bluepacket
        bluelist.append(bluedic)
        return bluelist   
if __name__ == "__main__":
    objectTemp=BlueToothDevice()  
    try:      
        bluelist = objectTemp.getBlueToothDevice()
        dataReportMsg=objectTemp.orgDataReportMsg(bluelist)
        objectTemp.sendMsgToUI(dataReportMsg)
        progReportMsg=objectTemp.orgProgReportMsg("100", "蓝牙设备信息检查完毕")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        log4py.error("检查蓝牙设备信息出错." +str(e) )
        errReportMsg=objectTemp.orgErrReportMsg("check the BlueToothDevice error.")
        objectTemp.sendMsgToUI(errReportMsg)      