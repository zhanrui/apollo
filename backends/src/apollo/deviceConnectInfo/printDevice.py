#! /usr/bin/python
#-*-coding:utf-8-*- 

'''
Created on 2015年2月4日

@author: hu
打印机设备
'''
import os
import re
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from apollo import commHandler 
from common.utils.log import log4py

class PrintDevice(commHandler.CommHandler): 
    
    def __init__(self):
        commHandler.CommHandler.__init__(self)
        pass 

    def getPrintDevice(self):
            printDevice = {}
            printDeviceList = []
                #打印机的配置文件
            with open("/etc/cups/printers.conf", "r") as printers :
                for printer in printers :

                    if re.findall("DefaultPrinter (.*)",printer) :
                        printDevice['DefaultPrinter'] = re.findall("DefaultPrinter (.*)",printer)[0].replace(">","")
                    if re.findall("MakeModel (.*)",printer):
                        printDevice['MakeModel'] = re.findall("MakeModel (.*)",printer)[0]
                    if re.findall("Info (.*)",printer) :
                        printDevice['Info'] = re.findall("Info (.*)",printer)[0]
                    if re.findall("DeviceURI (.*)",printer):
                        printDevice['DeviceURI'] = re.findall("DeviceURI (.*)",printer)[0]
                    if re.findall("State (.*)",printer):
                        printDevice['State'] = re.findall("State (.*)",printer)[0]
                    if re.findall("StateTime (.*)",printer) :
                        printDevice['StateTime'] = re.findall("StateTime (.*)",printer)[0]
                    if re.findall("Type (.*)",printer):
                        printDevice['Type'] = re.findall("Type (.*)",printer)[0]
                    if re.findall("Accepting (.*)",printer):
                        printDevice['Accepting'] = re.findall("Accepting (.*)",printer)[0]
                    if re.findall("Shared (.*)",printer):
                        printDevice['Shared'] = re.findall("Shared (.*)",printer)[0]
                    if re.findall("JobSheets (.*)",printer):
                        printDevice['JobSheets'] = re.findall("JobSheets (.*)",printer)[0]
                    if re.findall("QuotaPeriod (.*)",printer) :
                        printDevice['QuotaPeriod'] = re.findall("QuotaPeriod (.*)",printer)[0]
                    if re.findall("PageLimit (.*)",printer):
                        printDevice['PageLimit'] = re.findall("PageLimit (.*)",printer)[0]
#                     if re.findall("KLimit (.*)",printer):
#                         printDevice['KLimit'] = re.findall("KLimit (.*)",printer)[0]
#                     if  re.findall("OpPolicy (.*)",printer):
#                         printDevice['OpPolicy'] = re.findall("OpPolicy (.*)",printer)[0]
                    if re.findall("ErrorPolicy (.*)",printer):
                        printDevice['ErrorPolicy'] = re.findall("ErrorPolicy (.*)",printer)[0]
                    #print("打印机的配置文件:%s"%printer)
                #打印机性能的配置文件
#             with open('/etc/printcap', "r") as printcap :
#                 for cap in printcap :            
#                     print("打印机性能的配置文件:%s"%cap)
                    #printDeviceList.append(cap)
            printDeviceList.append(printDevice)
            return printDeviceList     
if __name__ == "__main__":       
    temp=PrintDevice()   
    try:        
        print(temp.getPrintDevice())
        printDevice = temp.getPrintDevice()
        dictTemp=printDevice[0]
        dictLen=len(dictTemp)
        print dictLen 
        if(dictLen ==0):
            temp.sendMsgToUI(temp.orgProgReportMsg("100", "打印机设备信息检查完毕."))
        else:
            if printDevice[0]['Info'] !='' and printDevice[0]['DeviceURI'] != '' and printDevice[0]['Shared'] !='' \
                  and printDevice[0]['State'] !='' :
                #print("success")
                temp.sendMsgToUI(temp.orgDataReportMsg(temp.getPrintDevice())) 
                temp.sendMsgToUI(temp.orgProgReportMsg("100", "打印机设备信息检查完毕."))
            else :
                #print("login root")
                temp.sendMsgToUI(temp.orgErrReportMsg("检查失败，获取root权限失败."))
           
    except Exception as e:
        #print (str(e))
        if(re.findall("Permission denied",str(e))):
            temp.sendMsgToUI(temp.orgErrReportMsg("检查失败，获取root权限失败."))            
        else :
            log4py.error("打印机设备信息检查出错."  )
            temp.sendMsgToUI(temp.orgErrReportMsg("打印机设备信息检查出错."))  
