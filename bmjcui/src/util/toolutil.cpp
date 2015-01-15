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
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>
#include <QString>

ToolUtil::ToolUtil()
{

}

ToolUtil::~ToolUtil()
{

}

void ToolUtil::getSystemBasicInfo(){

    QJsonObject json;
    json.insert("functionname", QString("Qt"));

    QJsonObject parameters;
    parameters.insert("foldername", QString("hello"));

    json.insert("parameters", parameters);


    QJsonDocument document;
    document.setObject(json);
    QByteArray byte_array = document.toJson(QJsonDocument::Compact);
    QString json_str(byte_array);


    ToolUtil::sendMessage(json_str);

}

void ToolUtil::sendMessage(const QString & messages){
    QDBusInterface iface( "com.example.bmjc", "/bmjc/ui", "bmjc.ui",QDBusConnection::sessionBus());
    if (!iface.isValid()) {
          qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
         exit(1);
     }
     iface.call("updateFromTool",messages);
}

