#include "checktask.h"
#include <QVariantList>
#include "src/util/toolutil.h"

CheckTask::CheckTask(QObject* parent, const QString& taskname, const QString& scenename, bool badinfoCheck, int weight)
    : QObject(parent)
{
    this->badinfoCheck = badinfoCheck;
    this->weight = weight;
    this->taskname = taskname;
    this->scenename = scenename;

    this->enabled = true;
    this->start = false;
    this->completerate = 0;

    this->error = false;
    this->currentstatus = QString();

    this->errorfind = false;

    this->totalproblems = 0;
    this->totalinfomations = 0;

    this->parameters = QMap<QString, QString>();
}

CheckTask::CheckTask(QObject* parent, ToolUtil* toolUtil, const QString& taskname, const QString& scenename, bool badinfoCheck, int weight)
    : QObject(parent)
{
    this->badinfoCheck = badinfoCheck;
    this->weight = weight;
    this->taskname = taskname;
    this->scenename = scenename;

    this->enabled = true;
    this->start = false;
    this->completerate = 0;

    this->error = false;
    this->currentstatus = QString();

    this->errorfind = false;

    this->totalproblems = 0;
    this->totalinfomations = 0;

    this->parameters = QMap<QString, QString>();
    connect(this, SIGNAL(startTaskSig(const QString&, const QString&, const QMap<QString, QString>&)),
            toolUtil, SLOT(startTask(const QString&, const QString&, const QMap<QString, QString>&)));
    connect(this, SIGNAL(stopTaskSig(const QString&, const QString&)),
            toolUtil, SLOT(stopTask(const QString&, const QString&)));
}

CheckTask::~CheckTask()
{
}

void CheckTask::startexecute()
{
    if (enabled) {
        this->enabled = true;
        this->start = true;
        this->completerate = 0;

        this->error = false;
        this->currentstatus.clear();

        this->errorfind = false;

        this->totalproblems = 0;
        this->totalinfomations = 0;

        emit startTaskSig(scenename, taskname, parameters);
    }
}

void CheckTask::stopexecute()
{

    this->start = false;
    emit stopTaskSig(scenename, taskname);
}

void CheckTask::disabletask()
{
    this->enabled = false;
}

void CheckTask::progressUpdate(const int completerate, const QString& currentstatus)
{
    int completeunit = (completerate - this->completerate) * weight;
    emit progressUpdateSig(completeunit, currentstatus);

    this->completerate = completerate;
    this->currentstatus = currentstatus;
    emit completerateUpdateSig(completerate, currentstatus);

    if (completerate == 100 && !error) {
        this->start = false;
        emit completeSig();
    }
}
void CheckTask::errorUpdate(const QString& errordescrition)
{
    int completeunit = (100 - this->completerate) * weight;
    emit progressUpdateSig(completeunit, errordescrition);

    completerate = 100;
    error = true;
    currentstatus = errordescrition;
    start = false;
    emit completerateUpdateSig(100, currentstatus);
    emit completeSig();
}
void CheckTask::dataUpdate(const QVariantList& result)
{
    if (badinfoCheck) {
        totalproblems += result.size();
        totalinfomations = 0;
        emit errorFindSig();
        emit dataCountUpdateSig(result.size(), 0);
    } else {
        totalinfomations += result.size();
        emit dataCountUpdateSig(0, result.size());
    }
    emit dataUpdateSig(result);
}

void CheckTask::setParameters(const QString& key, const QString& val)
{
    parameters.insert(key, val);
}
