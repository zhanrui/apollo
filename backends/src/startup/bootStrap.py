#!/usr/bin/env python
#-*-coding:utf-8-*- 
import gobject
import dbus.service
import dbus.mainloop.glib
import sys
import os
SERVICE_NAME="com.bmjc.backend"
OBJECT_PATH="/bmjc/backend"
INTERFACE="bmjc.backend"
mainloop=None
sys.path.append(os.path.dirname(os.getcwd()))
from common.utils.log import log4py
import msgHandler
class BootStrap(dbus.service.Object):        
    @dbus.service.method(INTERFACE,in_signature='s')
    def reveiveFromUI(self,jsonMsg):         
        msgHandler.handler(jsonMsg)

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)    
    session_bus = dbus.SessionBus()
    name = dbus.service.BusName(SERVICE_NAME, session_bus)
    object = BootStrap(session_bus,OBJECT_PATH)
    mainloop = gobject.MainLoop() 
    log4py.info("backends启动成功..")
    mainloop.run()