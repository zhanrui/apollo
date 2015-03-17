#! /usr/bin/python
#-*-coding:utf-8-*- 

'''
Created on 2015年2月4日

@author: hu
网络配置
'''
import re
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from apollo import commHandler 
from common.utils.log import log4py

class NetConfig(commHandler.CommHandler):
     
    def __init__(self):
        commHandler.CommHandler.__init__(self)
        pass 

    def getNetConfig(self):
        netdic = {}   
        netlist = []
        order = "cat /proc/net/dev | awk \'{if($2>0 && NR > 2) print substr($1, 0, index($1, \":\") - 1)}\'"    
        netname =  os.popen(order)  
        netnamecon = netname.readlines()
        netname.close()
        for readline in netnamecon:
            netname = readline.replace('\n','')
            netemp = os.popen('ifconfig '+netname)
            netcontemp = netemp.read()
            if netcontemp :
                if(re.findall('inet',netcontemp)):
                    networkList = netcontemp[netcontemp.index('inet'):].replace(":"," ").replace("\n","").split(" ")
                    netdic['netname'] = netname
                    netdic['IpAddr'] = networkList[1]
                    netdic['netmask'] =networkList[4]   # 子网掩码
#                     netdic['broadcast'] =networkList[7] 
                    macaddr = ''
                    if re.findall('HWaddr(.*)',netcontemp):
                        macaddr = re.findall('HWaddr(.*)',netcontemp)
                    netdic['macaddr'] =macaddr
                    netlist.append(netdic)
        dnsorder = 'cat /etc/resolv.conf | grep nameserver | awk \'{print $2}\''
        dnsopen = os.popen(dnsorder)
        dnsread = dnsopen.readlines()
        dnsopen.close()
        dns = ''
        for readline in dnsread:
            dns = readline.replace('\n','')+'/'+ dns  
        netdic['dns'] =dns
        return netlist


if __name__ == "__main__":    
    
    temp=NetConfig()   
    try:
        #print(temp.getNetConfig())
        temp.sendMsgToUI(temp.orgDataReportMsg(temp.getNetConfig())) 
        temp.sendMsgToUI(temp.orgProgReportMsg("100", "网络配置检查完毕."))
    except Exception as e:
        #print e
        log4py.error("检查网络配置出错."  ,str(e))
        temp.sendMsgToUI(temp.orgErrReportMsg("网络配置检查出错."))  