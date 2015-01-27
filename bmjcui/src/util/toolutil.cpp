/****************************************************************************
**
** This Class is for call the Tools ( for example : check the system info ,
*check file ,check Virus
**
****************************************************************************/

#include "toolutil.h"
#include <QDebug>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonObject>
#include <QString>


ToolUtil::ToolUtil(QObject* parent)
    : QObject(parent)
{
    iface = new QDBusInterface("com.bmjc.ui", "/bmjc/ui", "bmjc.ui", QDBusConnection::sessionBus(),this);
    if (!iface->isValid()) {
        qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
        exit(1);
    }
}

ToolUtil::~ToolUtil() {}

void ToolUtil::startOneKeyCheck()
{
}
void ToolUtil::cancelOneKeyCheck()
{
}


void ToolUtil::getSystemBasicInfo()
{
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

void ToolUtil::sendMessage(const QString& messages)
{

    iface->call("updateFromTool", messages);
}
