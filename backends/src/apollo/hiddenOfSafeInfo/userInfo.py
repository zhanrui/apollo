#!/usr/bin/env python
# encoding:utf8


#!/usr/bin/env python
# encoding:utf8
'''
Created on 2015年2月4日

@author: zzp
userinfo
'''
import re
import uuid
import binascii
import os
import sys
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
class UserInfo(CommHandler):
   
    def __init__(self):
#         commHandler.CommHandler.__init__(self)
        pass
    def getUserInfo(self):
        userinfolist = []
        username, uid, groupid, direct = '', '', '', ''
        with open('/etc/passwd') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n'):
                        userinfodic = {}  
                        username = line.rstrip('\n').split(':')[0]
                        uid = line.rstrip('\n').split(':')[2]
                        groupid = line.rstrip('\n').split(':')[3]
                        direct = line.rstrip('\n').split(':')[5]
                        userinfodic['username'] = username 
                        userinfodic['uid'] = uid 
                        userinfodic['groupid'] = groupid 
                        userinfodic['direct'] = direct
                        userinfolist.append(userinfodic)
                         
        return userinfolist
if __name__ == "__main__":
    objectTemp = UserInfo()  
    try:      
        userinfolist = objectTemp.getUserInfo()
        dataReportMsg = objectTemp.orgDataReportMsg(userinfolist)
        objectTemp.sendMsgToUI(dataReportMsg)
        progReportMsg = objectTemp.orgProgReportMsg("100", "用户信息检查完毕 ")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception, e: 
        log4py.error("用户信息检查出错:" + str(e))
        errReportMsg = objectTemp.orgErrReportMsg("check the UserInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)          

 

 
 
