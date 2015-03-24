#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
import sqlite3
import time
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
from checkCommon import get_mozilla_path
from common.utils.scanFile import ProgressStatistics
objectTemp=None
class NetRecordsRoutineCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        self.filename = 'places.sqlite'
#         self.path = get_mozilla_path()
        self.userFinalPathDict=get_mozilla_path()
        pass 
    def getNetRecordsRoutineCheck(self):
        allResult = {}
        save=[]
        fileTotalNum=0
        print self.userFinalPathDict
        for key1,value1 in self.userFinalPathDict.items():
            sql_select = "SELECT moz_historyvisits.place_id, moz_places.url, moz_places.title, count(*),moz_historyvisits.visit_date FROM moz_historyvisits, moz_places WHERE moz_historyvisits.place_id=moz_places.id GROUP BY moz_historyvisits.place_id"
            if os.path.exists(value1):
                scan_browser_conn = sqlite3.connect(value1 + self.filename)
                scan_browser_cur = scan_browser_conn.cursor()
            #             sql_select = "SELECT moz_historyvisits.place_id, moz_places.url, moz_places.title, count(*),moz_historyvisits.visit_date FROM moz_historyvisits, moz_places WHERE moz_historyvisits.place_id=moz_places.id GROUP BY moz_historyvisits.place_id"
            #             sql_select = "SELECT name, sql FROM sqlite_master WHERE type='table' AND name = 'moz_historyvisits'"
                        
                scan_browser_cur.execute(sql_select)
                dictTemp={}
                sqlResult=scan_browser_cur.fetchall()
                fileTotalNum=fileTotalNum+len(sqlResult)
                allResult[key1]=sqlResult
#                 allResult.append(sqlResult)
        print fileTotalNum
        currentNum=0
        ps = ProgressStatistics()
        for key2,value2 in allResult.items():
#         for temp in allResult:
            sqlResultTemp=value2
            for eachvisit in sqlResultTemp:
                tmp = list(eachvisit)
                dictTemp['url']=tmp[1]
                dictTemp['title']=tmp[2]                
                timeTemp=str(tmp[4])
                timeStamp= timeTemp[0:len(timeTemp)-6]
                timeStamp=int(timeStamp)
                print timeStamp 
                t = time.localtime(timeStamp)
                timeArray = time.localtime(timeStamp)
                visitTime = time.strftime("%Y-%m-%d %H:%M:%S", timeArray)
                dictTemp['visitDate']=visitTime
                dictTemp['user']=key2
                save.append(dictTemp)
                dictTemp={}

                currentNum=currentNum+1
                
                dataReportMsg=objectTemp.orgDataReportMsg(save)
                objectTemp.sendMsgToUI(dataReportMsg) 
                
                prors = ps.getProgressStatisticsInfo(fileTotalNum, currentNum )  
                progReportMsg=objectTemp.orgProgReportMsg(prors, "上网记录常规信息已检查"+str(prors)+"%.")
                objectTemp.sendMsgToUI(progReportMsg)
                save=[]
        scan_browser_cur.close()
        scan_browser_conn.close()
    
if __name__ == "__main__":
    objectTemp=NetRecordsRoutineCheck()  
    try:              
        objectTemp.getNetRecordsRoutineCheck()
         
        progReportMsg=objectTemp.orgProgReportMsg("100", "上网记录常规信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("上网记录常规信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("上网记录常规信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
