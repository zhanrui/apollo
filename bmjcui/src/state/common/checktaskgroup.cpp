#include "checktaskgroup.h"
#include "checktask.h"
#include <QList>
CheckTaskGroup::CheckTaskGroup(QObject* parent,const QString& scenename, const int weight, const QList<CheckTask*> & tasks)
    : QObject(parent)
{

    this->enabled = true;
    this->weight = weight;
    this->scenename = scenename;

    this->start = false;

    currentstatus = QString();
    errorfind = false;

    totalproblems = 0;
    totalinfomations = 0;
    totalcompleteunit=0;
    currentcompleteunit=0;
    initConnect(tasks);
}

CheckTaskGroup::~CheckTaskGroup()
{
}

void CheckTaskGroup::initConnect(const QList<CheckTask*> & tasks)
{
    for (CheckTask* task : tasks) {
        connect(this, SIGNAL(startSig()), task, SLOT(startexecute()));
        connect(this, SIGNAL(stopSig()), task, SLOT(stopexecute()));
        connect(this, SIGNAL(disableSig()), task, SLOT(disabletask()));

        connect(task, SIGNAL(dataCountUpdateSig(const int  ,const int)), this, SLOT(dataCountUpdate(const int  ,const int)));
        connect(task, SIGNAL(progressUpdateSig(const int ,const QString &)), this, SLOT(progressUpdate(const int , const QString &)));
        this->totalcompleteunit += task->weight*100;
    }
}
//Call From State/UI
void CheckTaskGroup::startexecute()
{
    if (this->enabled) {
        this->start = true;
        this->currentcompleteunit = 0;
        currentstatus.clear();
        errorfind = false;
        totalproblems = 0;
        totalinfomations = 0;
    }
    emit startSig();
}
void CheckTaskGroup::stopexecute()
{
    this->start = false;
    emit stopSig();
}
void CheckTaskGroup::disablegroup()
{
    this->enabled = false;
    emit disableSig();
}


void CheckTaskGroup::progressUpdate(const int completeuint,const QString & status){

   this->currentcompleteunit +=completeuint;
   this->currentstatus = status;
   emit progressUpdateSig(completeuint*weight,status);
   emit completerateUpdateSig(currentcompleteunit*100/totalcompleteunit,status);
   if(this->currentcompleteunit == this->totalcompleteunit ){
        this->start = false;
        emit completeSig();
   }
}

void CheckTaskGroup::dataCountUpdate(const int totalproblems ,const int totalinfomations){
    this->totalproblems +=  totalproblems;
    this->totalinfomations +=  totalinfomations;
    if(totalproblems>0){
        if(!errorfind){
            errorfind = true;
            emit errorFindSig();
        }
    }
    emit dataCountUpdateSig(totalproblems, totalinfomations);
}



