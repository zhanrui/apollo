#! /usr/bin/python
#-*-coding:utf-8-*- 
import os
import json
import signal
import sys
from common.utils.log import log4py
from common.enums.enumSys import EnumSys
subPids={}
    
def chldhandler(signum , stackframe):
    while 1:
        try:
            result = os.waitpid(-1, os.WNOHANG)
            resultPid=result[0]
            for k in subPids:
                temp=str(resultPid)
                kTemp=str(k)
                if temp in kTemp:                    
                    log4py.info('子进程('+str(resultPid)+")处理结束，已销毁..")
                    subPids.pop(k)                    
                    break 
        except:
            break
         
def runSubProcess(cmdPara,filePathPara,scenenamePara,functionnamePara,jsonMsgPara): 
    signal.signal(signal.SIGCHLD,chldhandler)
    pid = os.fork()
    if not pid: 
        os.execl(cmdPara, "python", filePathPara, jsonMsgPara) 
    else: 
        log4py.info('backends创建子进程('+str(pid)+")开始处理..")
        key=scenenamePara+functionnamePara+str(pid)
        subPids[key]=pid 
    
def stopSubProcess(scenenamePara,functionnamePara):
    key=scenenamePara+functionnamePara
    for k in subPids:
        kTemp=str(k)
        if key in kTemp:            
            os.kill(subPids.get(k), 9) 
            subPids.pop(k)
            log4py.info("子进程("+str(k)+")终止成功.")
            break 

def stopAllSubProcess():
    tempSubPids=subPids
    print tempSubPids
    for k in tempSubPids:           
        os.kill(tempSubPids.get(k), 9)
        log4py.info("子进程("+str(k)+")终止成功.")

def handler(jsonMsgPara,mainloopPara):
    strMsg = json.loads(jsonMsgPara) #前端UI请求报文
    log4py.info("backends收到报文:"+str(strMsg))
    strPath=os.getcwd()[:len(os.getcwd())-7]+'apollo/'#取刨除当前项目实际路径   
    action=strMsg["action"]            #以action为分界点判断   
    if "run"==action:        
        scenename=strMsg["scenename"] 
        functionname=strMsg["functionname"]  
        filePath=strPath+EnumSys.sysModules[functionname]+"/"+functionname+'.py'               
        runSubProcess("/usr/bin/python2.7",filePath,scenename,functionname,jsonMsgPara)             
    elif "stop"==action:
        scenename=strMsg["scenename"] 
        functionname=strMsg["functionname"]
        stopSubProcess(scenename,functionname)           
    elif "stopall"==action:
        stopAllSubProcess()
        mainloopPara.quit()