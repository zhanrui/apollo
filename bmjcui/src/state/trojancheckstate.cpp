#include "trojancheckstate.h"

#include <QDBusConnection>

#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/common/taskbutton.h"
#include "src/ui/trojancheck/trojancheckwidget.h"

#include "src/ui/detailreport/trojancheckrpt.h"
#include "src/ui/base/staticbutton.h"

#include "src/util/interfacefortool.h"
#include "src/util/toolutil.h"
#include <QDebug>
#include <QAbstractItemModel>

TrojanCheckState::TrojanCheckState(QObject* parent, MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
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

TrojanCheckState::~TrojanCheckState()
{
}

void TrojanCheckState::inittasks(ToolUtil* toolUtil)
{

    networkWeapon = new CheckTask(this, toolUtil, FUNC_MALWARECHECK, SCENE_TROJANCHECK, true, 1);

    threatDocument = new CheckTask(this, toolUtil, FUNC_TROJANCHECK, SCENE_TROJANCHECK, true, 1);

    trojanCheck = new CheckTaskGroup(this, SCENE_FILECHECK, 1,
                                     QList<CheckTask*>() << threatDocument << networkWeapon);
}
void TrojanCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << trojanCheck;
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

void TrojanCheckState::totalUnitChanged(const int value)
{
    totalcompleteunit += value;
}
void TrojanCheckState::initConUIState(MainWindow* mainwindow)
{
    TrojanCheckWidget* tc = mainwindow->trojanCheckWidget;

    connect(tc, SIGNAL(startCheckSig()), this, SLOT(startexcute()));
    connect(tc->cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(stopexcute()));
    connect(this, SIGNAL(completerateUpdateSig(const int, const QString&)), tc, SLOT(completerateUpdate(const int, const QString&)));
    connect(this, SIGNAL(dataCountUpdateSig(const int, const int)), tc, SLOT(dataCountUpdate(const int, const int)));
    connect(tc, &TrojanCheckWidget::setParameter, networkWeapon, &CheckTask::setParameters);
    connect(tc, &TrojanCheckWidget::disableNetworkWeapon, networkWeapon, &CheckTask::disableTask);
    connect(tc, &TrojanCheckWidget::enableNetworkWeapon, networkWeapon, &CheckTask::enableTask);
    connect(tc, &TrojanCheckWidget::setParameter, threatDocument, &CheckTask::setParameters);
    connect(tc, &TrojanCheckWidget::disableThreatDocument, threatDocument, &CheckTask::disableTask);
    connect(tc, &TrojanCheckWidget::enableThreatDocument, threatDocument, &CheckTask::enableTask);

    //connect(fileCheck, SIGNAL(errorFindSig()), okc->basicinfobtn, SLOT(changeToProblem()));
    //connect(fileCheck, SIGNAL(completeSig()), okc->basicinfobtn, SLOT(changeToNoProblem()));

    TrojanCheckRpt* tcTrojanCheckRpt = mainwindow->tcTrojanCheckRpt;
    //connect(fileRoutineCheck, &CheckTask::completeSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToNoProblem);
    //connect(fileRoutineCheck, &CheckTask::errorFindSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToProblem);
    connect(threatDocument, &CheckTask::dataUpdateSig, tcTrojanCheckRpt, &TrojanCheckRpt::addThreatDocument);
    connect(networkWeapon, &CheckTask::dataUpdateSig, tcTrojanCheckRpt, &TrojanCheckRpt::addNetworkWeapon);
}
//Call UI
void TrojanCheckState::startexcute()
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
void TrojanCheckState::stopexcute()
{
    start = false;
    emit stopSig();
}
void TrojanCheckState::disablescene()
{
    enabled = false;
    emit disableSig();
}
//From Task
void TrojanCheckState::progressUpdate(const int completeunit, const QString& status)
{
    this->currentcompleteunit += completeunit;
    this->currentstatus = status;
    emit completerateUpdateSig(currentcompleteunit * 100 / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void TrojanCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
void TrojanCheckState::initConInterfaceTask(InterfaceForTool* interfaceForTool)
{

    //Basic Info
    connect(interfaceForTool, SIGNAL(t_threatdoccheck_progress(const int, const QString&)), threatDocument, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(t_threatdoccheck_error(const QString&)), threatDocument, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(t_threatdoccheck_data(const QVariantList&)), threatDocument, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(t_netweapon_progress(const int, const QString&)), networkWeapon, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(t_netweapon_error(const QString&)), networkWeapon, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(t_netweapon_data(const QVariantList&)), networkWeapon, SLOT(dataUpdate(const QVariantList&)));
}
