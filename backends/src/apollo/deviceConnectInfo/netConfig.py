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
        net = {}       
        n = os.popen('ifconfig -a')
        network = n.read()
        n.close()
        if network :
            if(re.findall('inet',network)):
                networkList = network[network.index('inet'):].replace(":"," ").replace("\n","").split(" ")
                net['IpAddr'] = networkList[1]
                net['netmask'] =networkList[4] 
                net['broadcast'] =networkList[7] 

        return net


if __name__ == "__main__":    
    
    temp=NetConfig()   
    try:
        #print(temp.getNetConfig())
        temp.sendMsgToUI(temp.orgDataReportMsg(temp.getNetConfig())) 
        temp.sendMsgToUI(temp.orgProgReportMsg("100", "网络配置检查完毕."))
    except Exception as e:
        #print e
        log4py.error("检查网络配置出错."  )
        temp.sendMsgToUI(temp.orgErrReportMsg("网络配置检查出错."))  