#! /usr/bin/python
#-*-coding:utf-8-*- 

'''
Created on 2015年2月4日

@author: hu
显卡信息
'''
import os
import re
import binascii
import commHandler
from log import log4py

class GraphicsCardInfo(commHandler.CommHandler):
    '''
    classdocs
    '''
    def __init__(self):
        commHandler.CommHandler.__init__(self)
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
  

    def getGraphicsCardInfo(self):
        
        ret = {}
        graphicsCardInfoList = []
        '''
        with open('/var/log/Xorg.0.log','r') as fp:
            
            info = fp.read()
            
            tmp = re.findall('Monitor name: \s*(\w*)\s*(\w*)', info)
            if tmp:
                if tmp[0][1]:
                    ret["Mon_vendor"] = tmp[0][0]
                    ret["Mon_product"] = tmp[0][0] + " " + tmp[0][1]
                else:ret["Mon_product"] = tmp[0][0]
        
            tmp = re.findall("Manufacturer:\s*(\w*)\s*Model:\s*(\w*)", info)
            if tmp:
                if not ret.get("Mon_product"):
                    ret["Mon_product"] = tmp[0][0] + " " + tmp[0][1]
                if not ret.get("Mon_vendor"):
                    ret["Mon_vendor"] = tmp[0][0]

        tmp = re.findall("Year:\s*(\w*)\s*Week:\s*(\w*)", info)
        if tmp:
            ret["Mon_year"] = tmp[0][0]
            ret["Mon_week"] = tmp[0][1]
            tmp = re.findall("Image Size: \s*(\w*) x (\w*)", info)
        if tmp:
                x = float(tmp[0][0])/10
                y = float(tmp[0][1])/10
                d = math.sqrt(x**2 + y**2)/2.54

                ret["Mon_size"] = str(x) + "cm" + " x " + str(y) + "cm"
                ret["Mon_in"] = "%.1f" %d

        tmp = re.findall("Gamma: (\S*)", info)
        if tmp:
            ret["Mon_gamma"] = tmp[0]

        h = re.findall("h_active: (\d*)", info)
        v = re.findall("v_active: (\d*)", info)
        if h and v:
            ret["Mon_maxmode"] = h[0] + "x" + v[0]

        tmp = re.findall("EDID for output (.*)", info)
        if tmp:
            ret["Mon_support"] = str(tmp)

        tmp = re.findall("Output (.*).* connected", info)
        if tmp:
            ret["Mon_output"] = tmp[0]

        tmp = re.findall("Integrated Graphics Chipset: (.*)", info)
        if tmp:
            ret["Mon_chip"] = tmp[0]

            tmp = re.findall("Chipset: \"(.*)\"", info)
            if tmp:
                if not ret.get("Mon_chip"):
                    ret["Mon_chip"] = tmp[0]
                    '''
        n = os.popen('lspci -vvv')
        vga = n.read()
        n.close()
        
        Vga_num = 0
        Vga_product,Vga_vendor,Vga_businfo,Vga_Drive = '','','',''
        if vga :
            while re.findall('VGA compatible controller: ',vga) :
                tmp = vga[vga.index('VGA compatible controller: ') - 8:]
                vga = tmp[30:]
                if Vga_businfo:
                    Vga_businfo += "<1_1>" + 'pci@0000:' + tmp[:8]
                else :
                    Vga_businfo = 'pci@0000:' + tmp[:8]
                if Vga_product:
                    pro = re.findall('VGA compatible controller: (.*)',tmp)
                    Vga_product += "<1_1>" + pro[0]
                    Vga_vendor += "<1_1>" + self.get_url('',pro[0])
                else :
                    pro = re.findall('VGA compatible controller: (.*)',tmp)
                    Vga_product = pro[0]
                    Vga_vendor = self.get_url('',pro[0])
                Vga_num += 1
                tmp = re.findall('Kernel driver in use: (.*)',tmp)
                if Vga_Drive:
                    Vga_Drive += "<1_1>" + tmp[0]
                else :
                    Vga_Drive = tmp[0]

        if (ret.get('Mon_vendor')):
            if (ret.get('Mon_product')):
                ret['Mon_vendor'] = self.get_url(ret['Mon_vendor'],ret['Mon_product'])
            else :  
                ret['Mon_vendor'] = self.get_url(ret['Mon_vendor'],'')
        ret['Vga_num'],ret['Vga_businfo'],ret['Vga_product'],ret['Vga_vendor'],ret['Vga_Drive'] = self.strip(str(Vga_num)),self.strip(Vga_businfo),self.strip(Vga_product),self.strip(Vga_vendor),self.strip(Vga_Drive)
        graphicsCardInfoList.append(ret)  
        
        return graphicsCardInfoList


if __name__ == "__main__":     
    temp=GraphicsCardInfo()   
    try:
        #print(temp.getGraphicsCardInfo())
        temp.sendMsgToUI(temp.orgDataReportMsg(temp.getGraphicsCardInfo())) 
        temp.sendMsgToUI(temp.orgProgReportMsg("100", "check the GraphicsCardInfo completed."))
    except:
        log4py.error("检查显卡信息出错."  )        
        temp.sendMsgToUI(temp.orgErrReportMsg("check the GraphicsCardInfo error."))  