#! /usr/bin/python
#-*-coding:utf-8-*- 

'''
Created on 2015年2月4日

@author: hu
内存信息
'''
import re
import os
import binascii
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler

class MemoryInfo(CommHandler):    
    def __init__(self):
        CommHandler.__init__(self)
        pass 
    
    def ctoascii(self,buf):
        ch = str(buf)
        asci = binascii.b2a_hex(ch)
        asci = int(asci,16)
        return asci
      
    def strip(self, s):
        if(len(s) == 0):
            return s
        while len(s) > 0 and self.ctoascii(s[0]) <= 32:
            s = s[1: ]
        k = len(s)
        while len(s) > 0 and self.ctoascii(s[k-1]) <= 32:
            s = s[ :k-1]
            k = len(s)
        i = 0
        while i < len(s):
            if s[i] < 32:
                s = s[ :i] + s[i+1: ]
                i -= 1
            i += 1
        return s

    
    def getMemoryInfo(self):
        #Memory Device
        Mem = {}
        memList=[]
        MemInfo,MemWidth,Memnum,MemSlot,MemProduct,MemVendor,MemSerial,MemSize,BioVendor = "","","","","","",'','',''
        hw = os.popen("dmidecode -t memory")
        memory = hw.read()
        hw.close()
        num = 0
        q = re.findall('Memory Device\n',memory)
        if q :
            memory = memory[memory.index("Memory Device\n")+len("Memory Device\n"):]
        else :
            memory = ''
        if memory :
            mark = re.findall("Data Width: (.*)",memory)
            if mark :
                for k in mark :
                    if not k == 'Unknown':
                        num += 1
                        if MemWidth :
                            MemWidth += "<1_1>" + k
                        else :
                            MemWidth = k
            Memnum = str(num)
            tmp = re.findall("Bank Locator: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemSlot :
                            MemSlot +="<1_1>"+ tmp[i-1]
                        else :
                            MemSlot = tmp[i-1]
            tmp = re.findall("Part Number: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemProduct :
                            MemProduct += "<1_1>" + tmp[i-1]
                        else :
                            MemProduct = tmp[i-1]
            tmp = re.findall("Manufacturer: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemVendor :
                            MemVendor += "<1_1>" + tmp[i-1]
                        else :
                            MemVendor = tmp[i-1]
            tmp = re.findall("Serial Number: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemSerial :
                            MemSerial += "<1_1>" + tmp[i-1]
                        else :
                            MemSerial = tmp[i-1]
            tmp = re.findall("Size: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemSize :
                            MemSize += "<1_1>" + tmp[i-1]
                        else :
                            MemSize = tmp[i-1]
            tmp0 = self.strip(re.findall("Form Factor: (.*)",memory))
            tmp1 = self.strip(re.findall("Type: (.*)",memory))
            tmp2 = self.strip(re.findall("Type Detail: (.*)",memory))
            tmp3 = self.strip(re.findall("Speed: (.*)",memory))
            i = 0
            if tmp0 and tmp1 and tmp2 and tmp3 :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemInfo :
                            MemInfo += "<1_1>" + tmp0[i-1] + ' ' + tmp1[i-1] + ' ' + tmp2[i-1] + ' ' + tmp3[i-1]
                        else :
                            MemInfo = tmp0[i-1] + ' ' + tmp1[i-1] + ' ' + tmp2[i-1] + ' ' + tmp3[i-1]
        Mem["MemInfo"],Mem["MemWidth"],Mem["MemSlot"],Mem["MemProduct"],Mem["MemVendor"],Mem["MemSerial"],Mem["MemSize"],Mem["Memnum"] = MemInfo,self.strip(MemWidth),self.strip(MemSlot),self.strip(MemProduct),self.strip(MemVendor),self.strip(MemSerial),self.strip(MemSize),self.strip(Memnum)
        memList.append(Mem)
        return memList
 
if __name__ == "__main__":
    temp=MemoryInfo()  
    try:
        #print(temp.getMemoryInfo())
        memData = temp.getMemoryInfo()
        if(memData[0]['Memnum']!='' and memData[0]['MemInfo']!='' and memData[0]['MemProduct']!='' and memData[0]['MemSerial']!='' and  memData[0]['MemSlot']!='' and memData[0]['MemWidth']!='' and memData[0]['MemVendor']!='' and memData[0]['MemSize']!='' ) :     
            temp.sendMsgToUI(temp.orgDataReportMsg(temp.getMemoryInfo())) 
            temp.sendMsgToUI(temp.orgProgReportMsg("100", "内存信息检查完毕."))
        else :
            temp.sendMsgToUI(temp.orgErrReportMsg("check the MemoryInfo Permission denied,login by root ."))
    except:
        log4py.error("内存信息检查出错."  )
        temp.sendMsgToUI(temp.orgErrReportMsg("内存信息检查出错."))

        
