#include "usbdeepcheckstate.h"




#include <QDBusConnection>

#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/deepcheck/usbdeepcheckwidget.h"

#include "src/ui/detailreport/usbrecorddeeprpt.h"
#include "src/ui/base/staticbutton.h"

#include "src/util/interfacefortool.h"
#include "src/util/toolutil.h"
#include <QDebug>
#include <QAbstractItemModel>

UsbDeepCheckState::UsbDeepCheckState(QObject* parent, MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
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

UsbDeepCheckState::~UsbDeepCheckState()
{
}

void UsbDeepCheckState::inittasks(ToolUtil* toolUtil)
{

    usbDeepCheck = new CheckTask(this, toolUtil, FUNC_USBDEPCHECK, SCENE_DEEP_USBCHECK, true, 1);

    usbDeepCheckGrp = new CheckTaskGroup(this, SCENE_DEEP_USBCHECK, 1,
                                   QList<CheckTask*>() << usbDeepCheck);
}
void UsbDeepCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << usbDeepCheckGrp;
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

void UsbDeepCheckState::totalUnitChanged(const int value)
{
    totalcompleteunit += value;
}
void UsbDeepCheckState::initConUIState(MainWindow* mainwindow)
{
    UsbDeepCheckWidget* udc = mainwindow->usbDeepCheckWidget;

    //connect(fc->startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startexcute()));

    connect(udc, &UsbDeepCheckWidget::startCheckSig,this,&UsbDeepCheckState::startexcute);

    connect(udc->cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(stopexcute()));
    connect(udc, &UsbDeepCheckWidget::setParameter, usbDeepCheck, &CheckTask::setParameters);
    connect(this, SIGNAL(completerateUpdateSig(const int, const QString&)), udc, SLOT(completerateUpdate(const int, const QString&)));
    connect(this, SIGNAL(dataCountUpdateSig(const int, const int)), udc, SLOT(dataCountUpdate(const int, const int)));

    //connect(fileCheck, SIGNAL(errorFindSig()), cc->basicinfobtn, SLOT(changeToProblem()));
    //connect(fileCheck, SIGNAL(completeSig()), cc->basicinfobtn, SLOT(changeToNoProblem()));

    UsbRecordDeepRpt* udUsbRecordDeepRpt = mainwindow->udUsbRecordDeepRpt;
    //connect(fileRoutineCheck, &CheckTask::completeSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToNoProblem);
    //connect(fileRoutineCheck, &CheckTask::errorFindSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToProblem);
    connect(usbDeepCheck, &CheckTask::dataUpdateSig, udUsbRecordDeepRpt, &UsbRecordDeepRpt::addUsbRecordsInfo);
}
//Call UI
void UsbDeepCheckState::startexcute()
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
void UsbDeepCheckState::stopexcute()
{
    start = false;
    emit stopSig();
}
void UsbDeepCheckState::disablescene()
{
    enabled = false;
    emit disableSig();
}
//From Task
void UsbDeepCheckState::progressUpdate(const int completeunit, const QString& status)
{
    this->currentcompleteunit += completeunit;
    this->currentstatus = status;
    emit completerateUpdateSig(currentcompleteunit * 100 / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void UsbDeepCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
void UsbDeepCheckState::initConInterfaceTask(InterfaceForTool* interfaceForTool)
{
    //Basic Info
    connect(interfaceForTool, SIGNAL(u_usbdeepcheck_progress(const int, const QString&)), usbDeepCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(u_usbdeepcheck_error(const QString&)), usbDeepCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(u_usbdeepcheck_data(const QVariantList&)), usbDeepCheck, SLOT(dataUpdate(const QVariantList&)));
}


