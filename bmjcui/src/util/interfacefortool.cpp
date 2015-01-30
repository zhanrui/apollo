#include "interfacefortool.h"
#include "src/common/globals.h"
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QVariant>

InterfaceForTool::InterfaceForTool(QObject* parent)
    : QObject(parent)
{
}

InterfaceForTool::~InterfaceForTool() {}

void InterfaceForTool::updateFromTool(const QString& messages)
{
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(messages.toUtf8(), &json_error);
    if (json_error.error != QJsonParseError::NoError) {
        return;
    }

    QVariantMap result = parse_doucment.toVariant().toMap();

    if (result["resulttype"].toString().compare(RPT_PROGRESS) == 0) {
        int currentcompletion = result["result"].toMap()["currentcompletion"].toString().toInt();
        QString currentstatus = result["result"].toMap()["currentstatus"].toString();
        emit progressUpdate(result["scenename"].toString(), result["functionname"].toString(),
                            currentcompletion, currentstatus);
    }

    if (result["resulttype"].toString().compare(RPT_ERROR) == 0) {
        QString errordescrition = result["result"].toMap()["errordescrition"].toString();
        emit errorUpdate(result["scenename"].toString(), result["functionname"].toString(),
                         errordescrition);
    }

    if (result["resulttype"].toString().compare(RPT_DATA) == 0) {
        emit dataUpdate(result["scenename"].toString(), result["functionname"].toString(),
                        result["result"].toList());
    }
}
