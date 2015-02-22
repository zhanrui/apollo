#!/bin/env python  
#--*-- coding=utf8 --*--  
import datetime  
import types  
import os
import time
#log编码全部按utf8处理  
loglevels = {'stdout':['info','debug','warn','error','fatal'],  
    'file':['info','debug','warn','error','fatal']  
    } 
logfile="logs_"+time.strftime('%Y%m%d',time.localtime(time.time()))+".txt"
class Log4py:  
    def __init__(self,modulename='gloabal', loglevel=loglevels, filename='log4py.txt'):  
        self.filename = filename  
        #self.flag = set(loglevel['stdout']+loglevel['file'])  
        self.loglevel = loglevel  
        self.modulename = modulename  
        self.fcname = None  
    class function():  
        def __init__(self,fcname,parent):  
            parent.debug('enter ',fcname)  
            self.fcname = fcname  
            self.parent = parent  
        def __del__(self):  
            self.parent.debug('exit ',self.fcname)  
    def dbgfc(self,fcname):  
        '''''set debug function name'''  
        f = None  
        if 'debug' in self.flag:  
            f = self.function(fcname,self)  
        return f  
    def _gettime(self):  
        return datetime.datetime.now().isoformat()  
    def outstd(self,*fmt):  
        s = self.fmtstr(*fmt)  
        print s  
    def outfile(self,*fmt):  
        s = self.fmtstr(*fmt)  
        #print 'before outfile '+s  
        if s:  
            #print 'outfile '+s  
            encoding = 'utf8'  
            out = open(logfile, 'a+')#, encoding  
            out.write(s)  
            out.write('\n')  
            out.close()  
    def fmtstr(self, *fmt):  
        str = ''  
        encoding = 'utf8'#缺省utf8编码  
        for i in fmt:  
            if not type(i) in [types.UnicodeType, types.StringTypes, types.StringType]:  
                s= repr(i)  
            else:  
                s = i  
            if type(s) == type(u''):  
                str += s.encode(encoding)  
            else:  
                str += s  
            str += '.'  
        #str += '/n'  
        #print 'fmtstr:'+str  
        return str  
    def debug(self,*fmt):  
        if 'debug' in self.loglevel['stdout']:  
            self.outstd(self._gettime(),'[DEBUG]',*fmt)  
        if 'debug' in self.loglevel['file']:  
            #print 'debug file ...'  
            self.outfile(self._gettime(),'[DEBUG]',*fmt)  
    def warn(self,*fmt):  
        if 'warn' in self.loglevel['stdout']:  
            self.outstd(self._gettime(),'[WARN]',*fmt)  
        if 'warn' in self.loglevel['file']:  
            self.outfile(self._gettime(),'[WARN]',*fmt)  
    def info(self,*fmt):  
        if 'info' in self.loglevel['stdout']:  
            self.outstd(self._gettime(),'[INFO]',*fmt)  
        if 'info' in self.loglevel['file']:  
            self.outfile(self._gettime(),'[INFO]',*fmt)  
    def error(self,*fmt):  
        #print '/033[0;30;41m',  
        if 'error' in self.loglevel['stdout']:  
            self.outstd(self._gettime(),'[ERROR]',*fmt)  
        if 'error' in self.loglevel['file']:  
            self.outfile(self._gettime(),'[ERROR]',*fmt)  
        #print '/033[0m'  
    def fatal(self,*fmt):  
        if 'fatal' in self.loglevel['stdout']:  
            self.outstd(self._gettime(),'[FATAL',*fmt)  
        if 'fatal' in self.loglevel['file']:  
            self.outfile(self._gettime(),'[FATAL',*fmt)  
#unit test  
# if __name__ == '__main__':  
#     log=Log4py()  
#     log.outstd('INFO','stdout','test')  
#     log.outfile('INFO','stdout','test')  
#     log.debug('debug information 调试')  
#     log.error('errorrrrrrrrrrrrrrr')  
#     log.debug('hello')
log4py=Log4py()