#!/usr/bin/env python
#encoding:utf8
'''
Created on 2015年2月4日

@author: hu
硬盘信息
'''
import sys
import re
import os
sys.path.append(os.path.dirname(os.getcwd()))
from apollo.commHandler import CommHandler
from common.utils.log import log4py
class HardDiskInfo(CommHandler):
   
    def __init__(self):
        CommHandler.__init__(self)
        pass
#     def getHrdDiskInfo(self):
#         hdlist = []
#         hddic = {}  
#         hw = os.popen('smartctl -A /dev/sda')  #Power_On_Hours
#         hdlisttemp = hw.read()
#         hw.close()
#         temp = re.findall('Permission denied',hdlisttemp)
#         if len(temp)>0:
#             hddic['hours']='Permission denied'
#         else :
#             temp = re.findall('Power_On_Hours (.*)',hdlisttemp) #Temperature_Celsius
#             if len(temp)>0:
#                 hddic['hours']=temp[0].split('-')[1]+'H'
#             else:
#                 hddic['hours'] = ''
#             temp = re.findall('Temperature_Celsius (.*)',hdlisttemp) #Temperature_Celsius
#             if len(temp)>0:
#                 hddic['Temperature_Celsius']=temp[0].split('-')[1]
#             else:
#                 hddic['Temperature_Celsius'] = ''
#             temp = re.findall('Start_Stop_Count (.*)',hdlisttemp) #Temperature_Celsius Start_Stop_Count
#             if len(temp)>0:
#                 hddic['Start_Stop_Count']=temp[0].split('-')[1]+'H'
#             else:
#                 hddic['Start_Stop_Count'] = ''
#         disk = os.statvfs("/")  
#         hddic['available'] = str(int(disk.f_bsize * disk.f_bavail/1024) )+'K' 
#         hddic['capacity'] = str(int(disk.f_bsize * disk.f_blocks/1024))+'K'   
#         hddic['used'] = str(int(disk.f_bsize * disk.f_bfree/1024))+'K'  
#         hdlist.append(hddic) 
#         return hdlist
    def get_fs_info(self,path):
  
        hddinfo = os.statvfs(path)
        total = hddinfo.f_frsize * hddinfo.f_blocks
        free = hddinfo.f_frsize * hddinfo.f_bavail
        used = hddinfo.f_frsize * (hddinfo.f_blocks - hddinfo.f_bfree)
        return {'total': str(int(float(total)/1024/1024)),
                'free': str(int(float(free)/1024/1024)),
                'used': str(int(float(used)/1024/1024))}

    def getHrdDiskInfo(self):
        hdlist = []
        hddic = {}
        with open('/proc/mounts', 'r') as f:
            mounts = f.readlines()
            for mount in mounts:
                if mount.startswith('/dev/'):
                    mount = mount.split()
                    dev = mount[0]
                    target = mount[1]
    #                 if target == '/':
    #                     print 'root fs'
    #                 else:
    #                     print 'logical fs'
    #                 print '%(dev)s mounts to %(target)s' % locals()
                    hddic = self.get_fs_info(target)
                    hddic['realpath']= os.path.realpath(dev)
    #                 hdlist.append(get_fs_info(target))
                    hdlist.append(hddic)
        return hdlist
    
if __name__ == "__main__":
    objectTemp=HardDiskInfo()  
    try:      
        disklist = objectTemp.getHrdDiskInfo()
        dataReportMsg=objectTemp.orgDataReportMsg(disklist)
        objectTemp.sendMsgToUI(dataReportMsg)
        progReportMsg=objectTemp.orgProgReportMsg("100", "硬盘信息检查完毕")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        log4py.error("检查硬盘信息出错."  +str(e))
        errReportMsg=objectTemp.orgErrReportMsg("check the hardDiskInfo error.")
        objectTemp.sendMsgToUI(errReportMsg)          
