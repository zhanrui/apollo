#! /usr/bin/python
#-*-coding:utf-8-*- 

'''
Created on 2015年2月4日

@author: hu
主板信息
'''
import binascii
import os
import re 
from common.utils.log import log4py
from apollo.commHandler import CommHandler

class MotherboardInfo(CommHandler):
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
     
    def get_url(self,v,p):
        vendors = {
#CPU产商
           "INTEL":["Intel"],
           "AMD":["AMD"],
           "VIMICRO":["Vimicro"],
#显卡产商
           "ATI":["ATI"],
           "1002":["ATI"],
           "SIS":["SIS"],
           "1039":["SIS"],
           "NVIDIA":["Nvidia"],
           "VIA":["VIA"],
           "XFX":["XFX"],
           "SUPERGRAPHIC":["Supergraphic"],
#显示器产商
           "AUO":["AUO"],
           "AOC":["AOC"],
           "PHILIPS":["Philips"],
           "PHL":["Philips"],
           "LEN":["Lenovo"],
           "SEC":["SAMSUNG"],
#电脑品牌
           "HASEE":["Hasee"],
           "FOUNDER":["Founder"],
           "TONGFANG":["Tongfang"],
           "TSINGHUA":["Tongfang"],
           "ACER":["Acer"],
           "LENOVO":["Lenovo"],
           "ASUSTEK":["ASUS"],
           "NEC":["NEC"],
           "HP":["HP"],
           "HEWLETT-PACKARD":["HP"],
           "SAMSUNG":["SAMSUNG"],
           "TOSHIBA":["TOSHIBA"],
           "APPLE":["Apple"],
           "DELL":["DELL"],
           "FUJITSU":["FUJITSU"],
           "PANASONIC":["Panasonic"],
           "SONY":["SONY"],
           "IBM":["IBM"],
#虚拟机
           "INNOTEK":["VirtualBox"],
           "VBOX":["VirtualBox"],
           "VIRTUALBOX":["VirtualBox"],
#网卡产商
           "3COM":["3COM"],
           "D-LINK":["D-LINK"],
           "RALINK":["Ralink"],
           "ATHEROS":["Atheros"],
           "MARVELL":["Marvell"],
           "BROADCOM":["Broadcom"],
#硬盘产商
           "EXCELSTOR":["Excelstor"],
           "HITACHI":["Hitachi"],
           "MAXTOR":["Maxtor"],
           "WESTERN":["Western Digital"],
           "LITEON":["Liteon"],
           "SEAGATE":["Seagate"],
           "QUANTUM":["Quantum"],
#光驱产商
           "PLDS":["PLDS"],
           "PBDS":["PLDS"],
           "HL-DT-ST":["LG"],
           "OPTIARC":["SONY"],
           "TSSTCORP":["TSSTcorp"],
           "PIONEER":["Pioneer"],
           "MATSHITA":["Panasonic"],
#声卡产商
           "REALTEK":["Realtek"],
           "CREATIVE":["Creative"],
#摄像头
           "SONIX":["Sonix"],
           "ETRON":["Etron"],
           "AVEO":["Aveo"],
           "SYNTEK":["Syntek"],
           "EMPIA":["Empia"],
           "CHICONY":["Chicony"],
           "OMNIVISION":["OmniVision"],
#鼠标产商
           "LOGITECH":["Logitech"],
           "SUNPLUS":["Sunplus"],
           "PRIMAX":["Primax"],
           "PIXART":["Pixart"],
           "TRUST":["Trust"],
           "1BCF":["Rapoo"],
           "AVAGO":["Avago"],
           "MICROSOFT":["Microsoft"],
#键盘产商
           "RAPOO":["Rapoo"],
#主板产商
           "GIGABYTE":["Gigabyte"],
           "BIOSTAR":["Biostar"],
           "COLORFUL":["Colorful"],
           "YESTON":["Yeston"],
#指纹识别
           "UPEK":["Authentec"],
           "AUTHENTEC":["Authentec"],
#闪存产商
           "KINGSTON":["Kingston"],
           "KINGMAX":["Kingmax"],
           "KINGBOX":["Kingbox"],
           "HYNIX":["Hynix"],
           "HYUNDAI":["Hynix"],
           "MICRON":["Micron"],
           "06C1":["Asint"],
           "ADATA":["ADATA"],
           "ZTE":["ZTE"],
           "EAGET":["Eaget"],
           "TEXAS":["Texas Instruments"],
           "MOTOROLA":["Motorola"],
#电源产商
           "SMP":["SMP"],
           "SIMPLO":["SMP"],
#BIOS产商
           "AMERICAN":["AMI"],
           "AWARD":["Phoenix"],
           "PHOENIX":["Phoenix"]
            }
        tmp = v.split(" ")[0]
        tmp = re.findall("([a-zA-Z0-9-]+)", tmp)
        if tmp :
            url = vendors.get(tmp[0].upper()) 
            if url:
                return url[0]
            else :
                k = p.split(" ")[0]
                url = vendors.get(k.upper())
                if url:
                    return url[0]
        else:
            tmp = p.split(" ")[0]
            url = vendors.get(tmp.upper())
            if url:
                return url[0]
        tmp = re.findall("ATI", v)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("SIS", v)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("Intel", v)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("ATI", p)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("SIS", p)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("Intel", p)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        return v
  
  
    def getMotherboardInfo(self):
        #Board and BIOS
        Boa = {}
        boaList = []

        hw = os.popen("dmidecode -t baseboard")
        board = hw.read()
        hw.close()
        BoaProduct,BoaVendor,BoaSerial,BioVendor,BioVersion,BioRelease = '','','','','',''
        if board :
            tmp = re.findall("Product Name: (.*)",board)
            if tmp :
                BoaProduct = tmp[0]
            tmp = re.findall("Manufacturer: (.*)",board)
            if tmp :
                BoaVendor = tmp[0]
            tmp = re.findall("Serial Number: (.*)",board)
            if tmp :
                BoaSerial = tmp[0]
        hw = os.popen("dmidecode -t bios")
        bios = hw.read()
        hw.close()
        if bios :
            tmp = re.findall("Vendor: (.*)",bios)
            if tmp:
                BioVendor = tmp[0]
            tmp = re.findall("Version: (.*)",bios)
            if tmp:
                BioVersion = tmp[0]
            tmp = re.findall("Release Date: (.*)",bios)
            if tmp:
                BioRelease = tmp[0]
        BoaVendor = self.get_url(BoaVendor,BoaProduct)
        BioVendor = self.get_url(BioVendor,BioVersion)

        Boa['BoaProduct'],Boa['BoaVendor'],Boa['BoaSerial'],Boa['BioVendor'],Boa['BioVersion'],Boa['BioRelease'] = self.strip(BoaProduct),self.strip(BoaVendor),self.strip(BoaSerial),self.strip(BioVendor),self.strip(BioVersion),self.strip(BioRelease)
        boaList.append(Boa)
        
        return boaList
        

if __name__ == "__main__":    
    temp=MotherboardInfo()
   
    try: 
        Boa = temp.getMotherboardInfo()
        print(Boa)
        if(Boa['result'][0]['BoaProduct']!='' and Boa['result'][0]['BoaVendor']!='' and Boa['result'][0]['BoaSerial']!='' and Boa['result'][0]['BioVendor']!='' and Boa['result'][0]['BioVersion']!='' and Boa['result'][0]['BioRelease']!=''):
            temp.sendMsgToUI(temp.orgDataReportMsg(Boa)) 
            temp.sendMsgToUI(temp.orgProgReportMsg("100", "check the MotherboardInfo completed."))
        else:
                #权限不够，请以root用户登录
            #print("login by root")
            temp.sendMsgToUI(temp.orgErrReportMsg("check the MotherboardInfo Permission denied,login by root ."))
         
    except Exception,e: 
            log4py.error("检查主板信息出错."  )         
            temp.sendMsgToUI(temp.orgErrReportMsg("check the MotherboardInfo error."))              