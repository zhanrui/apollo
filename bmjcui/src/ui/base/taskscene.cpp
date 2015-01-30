#include "taskscene.h"
#include <QString>
#include <QList>
#include <QVariantList>
TaskScene::TaskScene()
{

}

TaskScene::~TaskScene()
{

}

void TaskScene:: progressUpdate( const QString& functionname, const int currentcompletion, const QString& currentstatus){

}
void TaskScene:: errorUpdate( const QString& functionname, const QString& errordescrition){

}
void TaskScene:: dataUpdate( const QString& functionname, const QVariantList& result){

}

QString TaskScene::getSupportedScene(){
    return "default";
}
QList<QString> TaskScene::getSupportedFunctions(){
    return QList<QString>()<<"default";
}


