#!/usr/bin/env python
#-*-coding:utf-8-*- 
class EnumSys:   
    sysModules={
             #基本信息
             "operatingSystemInfo":"baseInfo",
             "cpuInfo":"baseInfo",
             "biosInfo":"baseInfo",
             "motherboardInfo":"baseInfo",
             "memoryInfo":"baseInfo",
             "graphicsCardInfo":"baseInfo",
             # 设备连接信息
             "hardDiskInfo":"deviceConnectInfo",
             "virtualMachineInfo":"deviceConnectInfo",
             "netConfig":"deviceConnectInfo",
             "adapterDevice":"deviceConnectInfo",
             "printDevice":"deviceConnectInfo",    
             "blueToothDevice":"deviceConnectInfo",
             # 系统安全信息
             "patchNotInstalled":"systemSecurityInfo",
             "systemService":"systemSecurityInfo",
             "systemProcess":"systemSecurityInfo",
             "evenProduct":"systemSecurityInfo",
             "timeSwitchMachine":"systemSecurityInfo",
             "securitySoftware":"systemSecurityInfo",
             # 安全隐患信息
             "securityPolicy":"hiddenOfSafeInfo",
             "openPort":"hiddenOfSafeInfo",
             "sharingInfo":"hiddenOfSafeInfo",
             "networkSoftware":"hiddenOfSafeInfo",
             "groupInfo":"hiddenOfSafeInfo",
             "userInfo":"hiddenOfSafeInfo",
             "databaseInfo":"hiddenOfSafeInfo",
             "eventLog":"hiddenOfSafeInfo",
             "userAuthentication":"hiddenOfSafeInfo",
         # USB设备记录
             "usbRoutineCheck":"usbDeviceRecord",
             "usbDepthCheck":"usbDeviceRecord",
            # 上网记录
             "netRecordsRoutineCheck":"netRecords",
             "netRecordsDepthCheck":"netRecords",
            # 文件检查
             "fileRoutineCheck":"fileCheck",
             "deletedFileRecovery":"fileCheck",
             "fileFragmentsCheck":"fileCheck",
            # 木马检查
             "networkWeapon":"trojanCheck",
             "threatDocument":"trojanCheck"}  
    
    