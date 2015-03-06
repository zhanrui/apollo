#include "netrecorddeepcheckstate.h"

#include <QDBusConnection>

#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/deepcheck/netrecorddeepcheckwidget.h"

#include "src/ui/detailreport/netrecorddeeprpt.h"
#include "src/ui/base/staticbutton.h"

#include "src/util/interfacefortool.h"
#include "src/util/toolutil.h"
#include <QDebug>
#include <QAbstractItemModel>

NetRecordDeepCheckState::NetRecordDeepCheckState(QObject* parent, MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
                               ToolUtil* toolUtil)
    : QObject(parent)
{
    this->enabled = true;
    this->start = false;

    currentstatus = QString();
    errorfind = false;

    totalproblems = 0;
    totalinfomations = 0;
    currentcompleteunit = 0;
    totalcompleteunit = 0;
    inittasks(toolUtil);
    initConStateGroup();
    initConInterfaceTask(interfaceForTool);
    initConUIState(mainwindow);
    // initConnectionBtwStateAndGroup();
}

NetRecordDeepCheckState::~NetRecordDeepCheckState()
{
}

void NetRecordDeepCheckState::inittasks(ToolUtil* toolUtil)
{

    netRecDeepCheck = new CheckTask(this, toolUtil, FUNC_NETRECDEPCHECK, SCENE_DEEP_NETRECCHECK, true, 1);

    netRecDeepCheckGrp = new CheckTaskGroup(this, SCENE_DEEP_NETRECCHECK, 1,
                                   QList<CheckTask*>() << netRecDeepCheck);
}
void NetRecordDeepCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << netRecDeepCheckGrp;
    //<< trojanCheck << fileCheck
    for (CheckTaskGroup* taskGroup : taskGroups) {
        connect(this, SIGNAL(startSig()), taskGroup, SLOT(startExecute()));
        connect(this, SIGNAL(stopSig()), taskGroup, SLOT(stopExecute()));
        //connect(this, SIGNAL(disableSig()), taskGroup, SLOT(disableGroup()));

        connect(taskGroup, SIGNAL(dataCountUpdateSig(const int, const int)), this, SLOT(dataCountUpdate(const int, const int)));
        connect(taskGroup, SIGNAL(progressUpdateSig(const int, const QString&)), this, SLOT(progressUpdate(const int, const QString&)));
        connect(taskGroup, SIGNAL(totalUnitChangedSig(const int)), this, SLOT(totalUnitChanged(const int)));
        this->totalcompleteunit += taskGroup->totalcompleteunit * taskGroup->weight;
    }
}

void NetRecordDeepCheckState::totalUnitChanged(const int value)
{
    totalcompleteunit += value;
}
void NetRecordDeepCheckState::initConUIState(MainWindow* mainwindow)
{
    NetRecordDeepCheckWidget* nrdc = mainwindow->netRecordDeepCheckWidget;

    //connect(fc->startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startexcute()));

    connect(nrdc, &NetRecordDeepCheckWidget::startCheckSig,this,&NetRecordDeepCheckState::startexcute);

    connect(nrdc->cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(stopexcute()));
    connect(nrdc, &NetRecordDeepCheckWidget::setParameter, netRecDeepCheck, &CheckTask::setParameters);
    connect(this, SIGNAL(completerateUpdateSig(const int, const QString&)), nrdc, SLOT(completerateUpdate(const int, const QString&)));
    connect(this, SIGNAL(dataCountUpdateSig(const int, const int)), nrdc, SLOT(dataCountUpdate(const int, const int)));

    //connect(fileCheck, SIGNAL(errorFindSig()), cc->basicinfobtn, SLOT(changeToProblem()));
    //connect(fileCheck, SIGNAL(completeSig()), cc->basicinfobtn, SLOT(changeToNoProblem()));

    NetRecordDeepRpt* nrdNetRecordDeepRpt = mainwindow->nrdNetRecordDeepRpt;
    //connect(fileRoutineCheck, &CheckTask::completeSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToNoProblem);
    //connect(fileRoutineCheck, &CheckTask::errorFindSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToProblem);
    connect(netRecDeepCheck, &CheckTask::dataUpdateSig, nrdNetRecordDeepRpt, &NetRecordDeepRpt::addNetRecordsInfo);
}
//Call UI
void NetRecordDeepCheckState::startexcute()
{

    if (enabled) {
        start = true;
        currentstatus.clear();
        errorfind = false;
        totalproblems = 0;
        totalinfomations = 0;
        currentcompleteunit = 0;
        emit startSig();
    }
}
void NetRecordDeepCheckState::stopexcute()
{
    start = false;
    emit stopSig();
}
void NetRecordDeepCheckState::disablescene()
{
    enabled = false;
    emit disableSig();
}
//From Task
void NetRecordDeepCheckState::progressUpdate(const int completeunit, const QString& status)
{
    this->currentcompleteunit += completeunit;
    this->currentstatus = status;
    emit completerateUpdateSig(currentcompleteunit * 100 / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void NetRecordDeepCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
{
    this->totalproblems += totalproblems;
    this->totalinfomations += totalinfomations;
    //qDebug()<<totalinfomations;
    if (totalproblems > 0) {
        if (!errorfind) {
            errorfind = true;
            emit errorFindSig();
        }
    }
    emit dataCountUpdateSig(this->totalproblems, this->totalinfomations);
};
void NetRecordDeepCheckState::initConInterfaceTask(InterfaceForTool* interfaceForTool)
{
    //Basic Info
    connect(interfaceForTool, SIGNAL(n_netrecdeepcheck_progress(const int, const QString&)), netRecDeepCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(n_netrecdeepcheck_error(const QString&)), netRecDeepCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(n_netrecdeepcheck_data(const QVariantList&)), netRecDeepCheck, SLOT(dataUpdate(const QVariantList&)));
}


