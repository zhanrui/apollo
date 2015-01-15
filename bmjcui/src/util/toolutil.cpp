/****************************************************************************
**
** This Class is for call the Tools ( for example : check the system info , check file ,check Virus
**
****************************************************************************/


#include "toolutil.h"
#include <QDebug>
#include <QDBusInterface>
#include <QDebug>
#include <QDBusMessage>

ToolUtil::ToolUtil()
{

}

ToolUtil::~ToolUtil()
{

}

void ToolUtil::getSystemBasicInfo(){
    QDBusInterface iface( "com.example.bmjc", "/bmjc/onekeycheck", "bmjc.onekeycheck",QDBusConnection::sessionBus());
    if (!iface.isValid()) {
          qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
         exit(1);
     }
    QDBusMessage reply =  iface.call("actionSlot", "hello");
}

