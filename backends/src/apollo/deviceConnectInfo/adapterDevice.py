# #!/usr/bin/env python
# #encoding:utf8
'''
Created on 2015年2月4日

@author: hu
网卡设备
'''
import re
import uuid
import binascii
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
class AdapterDevice(CommHandler):
    '''
    classdocs
    '''
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
    def getAdapterDevice(self):
        net = {}
        NetProduct,NetVendor,NetBusinfo,NetLogicalname,NetSerial,NetIp,NetLink,NetCapacity = '','','','','','','',''
        n = os.popen('lspci -vvv')
        network = n.read()
        n.close()
        if network :
            if re.findall('Ethernet controller: ',network):
                tmp = network[network.index('Ethernet controller: ')-8:] 
                NetBusinfo = 'pci@0000:' + tmp[:8]
                pro = re.findall('Ethernet controller: (.*)',tmp)
                NetProduct = pro[0]
                NetVendor = self.get_url('',pro[0])
                tmp =  re.findall('Kernel driver in use: (.*)',tmp)
                NetDrive = tmp[0]
        net['NetProduct'],net['NetVendor'],net['NetDrive']=NetProduct,NetDrive,NetDrive
                
                
        fp=os.popen("ifconfig -s|grep -v Iface|grep -v lo|awk '{print $1}'")
        interface=fp.readlines()
        fp.close()
        ip_dic={}
        for name in interface:
            name=name.strip()
            # remove 'wlan'
            if name.startswith('eth'):
                try:
                    sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
                    ipaddr=socket.inet_ntoa(fcntl.ioctl(
                        sk.fileno(),
                        0x8915, # SIOCGIFADDR
                        struct.pack('256s', name[:15]))[20:24])
                    ip_dic[name]=ipaddr
                except Exception as e:
                    print e
# ip 
#         if len(ip_dic) == 0:
#             NetLogicalname = 'N/A'
#             NetIp = 'N/A'
#         else:
#             NetLogicalname =  ip_dic.keys()[0]
#             NetIp =  ip_dic.values()[0]
#         net['NetLogicalname'],net['NetIp']=NetLogicalname,NetIp
        # -------------------get mac address-------------------
        mac_addr = uuid.UUID(int = uuid.getnode()).hex[-12:]
        NetSerial = ":".join([mac_addr[e:e+2] for e in range(0,11,2)])      
        net['NetSerial']=NetSerial  
        return net    
if __name__ == "__main__":
    objectTemp=AdapterDevice()  
    try:      
        adaplist=objectTemp.getAdapterDevice()
        dataReportMsg=objectTemp.orgDataReportMsg(adaplist)
        objectTemp.sendMsgToUI(dataReportMsg)
        progReportMsg=objectTemp.orgProgReportMsg("100", "网卡设备信息检查完毕")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        log4py.error("检查网卡信息出错." +str(e) )
        errReportMsg=objectTemp.orgErrReportMsg("check the adapterDevice error.")
        objectTemp.sendMsgToUI(errReportMsg)
        