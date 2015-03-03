#! /usr/bin/python
#-*-coding:utf-8-*- 
import sys
import os
import sqlite3
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
from apollo.commHandler import CommHandler
from checkCommon import get_mozilla_path
objectTemp=None
class NetRecordsRoutineCheck(CommHandler):
    def __init__(self):
        CommHandler.__init__(self)
        self.filename = 'places.sqlite'
        self.path = get_mozilla_path()
        pass 
    def getNetRecordsRoutineCheck(self):
        save = []
        if os.path.exists(self.path):
            scan_browser_conn = sqlite3.connect(self.path + self.filename)
            scan_browser_cur = scan_browser_conn.cursor()
            sql_select = "SELECT moz_historyvisits.place_id, moz_places.url, moz_places.title, count(*),moz_historyvisits.visit_date FROM moz_historyvisits, moz_places WHERE moz_historyvisits.place_id=moz_places.id GROUP BY moz_historyvisits.place_id"
#             sql_select = "SELECT moz_historyvisits.place_id, moz_places.url, moz_places.title, count(*),moz_historyvisits.visit_date FROM moz_historyvisits, moz_places WHERE moz_historyvisits.place_id=moz_places.id GROUP BY moz_historyvisits.place_id"
#             sql_select = "SELECT name, sql FROM sqlite_master WHERE type='table' AND name = 'moz_historyvisits'"
            
            scan_browser_cur.execute(sql_select)
            dictTemp={}
            sqlResult=scan_browser_cur.fetchall()
            print len(sqlResult)
            lenTmp=len(sqlResult)
            print lenTmp
            i=0
            proNum=0
            proNumLast=0
            flen=100.0/lenTmp
            ilen=int(flen)
            for eachvisit in sqlResult:
                tmp = list(eachvisit)
                dictTemp['url']=tmp[1]
                dictTemp['title']=tmp[2]                
                timeTemp=str(tmp[4])
                hw = os.popen('java DateChange '+timeTemp)
                visitTime = hw.read()                
                hw.close()              
#                 print visitTime 
                dictTemp['visitDate']=visitTime
                save.append(dictTemp)
                dictTemp={}
                i=i+1
                print i                
                print save
                log4py.info(str(i))
                log4py.info(save)
                if proNum<100:
                    proNum=int(flen*i)
                    if proNum!=proNumLast:
                        dataReportMsg=objectTemp.orgDataReportMsg(save)
                        objectTemp.sendMsgToUI(dataReportMsg)  
                        progReportMsg=objectTemp.orgProgReportMsg(str(proNum), "上网记录常规信息已检查"+str(proNum)+"%.")
                        objectTemp.sendMsgToUI(progReportMsg)
                        save=[]
                proNumLast=proNum
            scan_browser_cur.close()
            scan_browser_conn.close()
        return save
    
if __name__ == "__main__":
    objectTemp=NetRecordsRoutineCheck()  
    try:              
        dataReportMsg=objectTemp.orgDataReportMsg(objectTemp.getNetRecordsRoutineCheck())
        objectTemp.sendMsgToUI(dataReportMsg)
        
        progReportMsg=objectTemp.orgProgReportMsg("100", "上网记录常规信息检查完毕.")
        objectTemp.sendMsgToUI(progReportMsg)
    except Exception,e: 
        print e
        log4py.error("上网记录常规信息检查出错." )
        errReportMsg=objectTemp.orgErrReportMsg("上网记录常规信息检查出错.")
        objectTemp.sendMsgToUI(errReportMsg)
