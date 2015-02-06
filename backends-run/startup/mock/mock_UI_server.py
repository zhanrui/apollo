#!/usr/bin/env python
#-*-coding:utf-8-*- 
import gobject
import dbus.service
import dbus.mainloop.glib
import json

SERVICE_NAME="com.testModule.frontServer"
OBJECT_PATH="/com/testModule/frontServer/object"
INTERFACE="com.testModule.frontServerInterface"
def emit_signal2():
        loop.quit()
        return False
class MockFrontServerObject(dbus.service.Object):
    def __init__(self, conn, object_path=OBJECT_PATH):
        dbus.service.Object.__init__(self, conn, object_path)

    @dbus.service.method(INTERFACE,in_signature='s', out_signature='s')
    def updateFromTool(self,result1):
        strResulr = json.loads(result1)
        print "UI收到报文:"+str(strResulr)
        return "receive success.."        

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName(SERVICE_NAME, session_bus)
    object = MockFrontServerObject(session_bus)
    loop = gobject.MainLoop()
    print "mockUIServer启动成功.."
    loop.run()