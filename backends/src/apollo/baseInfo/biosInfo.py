#!/usr/bin/env python
#encoding:utf8
'''
Created on 2015年2月4日

@author: hu
BIOS信息
'''
import os
import re
import binascii
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
class BiosInfo(CommHandler):
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
    def getBiosinfo(self):
        # BIOS
        bioslist = []
        biostdic = {}
        BioVendor,BioVersion,BioRelease = '','',''
        hw = os.popen("dmidecode -t bios")
        bios = hw.read()
        hw.close()  
        if bios :
            tmp = re.findall("Vendor: (.*)",bios)
            if len(tmp)<1:
                bioslist.append('Permission denied')
                return bioslist
            if tmp:
                BioVendor = tmp[0]
            tmp = re.findall("Version: (.*)",bios)
            if tmp:
                BioVersion = tmp[0]
            tmp = re.findall("Release Date: (.*)",bios)
            if tmp:
                BioRelease = tmp[0]
        biostdic['BioVendor']=self.strip(BioVendor)  # bios 
        biostdic['BioVersion']=self.strip(BioVersion)
        biostdic['BioRelease'] = self.strip(BioRelease)
        bioslist.append(biostdic)
        return bioslist

if __name__ == "__main__":
    objectTemp=BiosInfo()  
    try:      
        bioslist=objectTemp.getBiosinfo()
        if bioslist[0]=='Permission denied': # Permission denied
            log4py.error("检查bios信息权限不足"  )  
            errReportMsg=objectTemp.orgErrReportMsg("Permission denied")
            objectTemp.sendMsgToUI(errReportMsg)    
        else:
            dataReportMsg=objectTemp.orgDataReportMsg(bioslist)
            objectTemp.sendMsgToUI(dataReportMsg)
            progReportMsg=objectTemp.orgProgReportMsg("100", "BIOS信息检查完毕")
            objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        log4py.error("检查bios信息出错."  +str(e) )
        errReportMsg=objectTemp.orgErrReportMsg("check the BiosInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)          
