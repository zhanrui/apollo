#include "interfacefortool.h"
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>


InterfaceForTool::InterfaceForTool(QObject *parent) : QObject(parent)
{

}

InterfaceForTool::~InterfaceForTool()
{

}

void InterfaceForTool::updateFromTool(const QString & messages){
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(messages.toUtf8(), &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
            QJsonObject obj = parse_doucment.object();
            QJsonValue name_value = obj.take("functionname");
            qDebug() << name_value.toString();
            emit systemInfoUpdate(name_value.toString());
    }
}
