#include "imagecheckstate.h"

#include <QDBusConnection>

#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/imagecheck/imagecheckwidget.h"

#include "src/ui/detailreport/imagecheckrpt.h"
#include "src/ui/base/staticbutton.h"

#include "src/util/interfacefortool.h"
#include "src/util/toolutil.h"
#include <QDebug>
#include <QAbstractItemModel>

ImageCheckState::ImageCheckState(QObject* parent, MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
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

ImageCheckState::~ImageCheckState()
{
}

void ImageCheckState::inittasks(ToolUtil* toolUtil)
{

    imageRoutineCheck = new CheckTask(this, toolUtil, FUNC_IMAGECHECK, SCENE_IMAGECHECK, true, 1);

    imageCheck = new CheckTaskGroup(this, SCENE_IMAGECHECK, 1,
                                   QList<CheckTask*>() << imageRoutineCheck);
}
void ImageCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << imageCheck;
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

void ImageCheckState::totalUnitChanged(const int value)
{
    totalcompleteunit += value;
}
void ImageCheckState::initConUIState(MainWindow* mainwindow)
{
    ImageCheckWidget* ic = mainwindow->imageCheckWidget;

    connect(ic, SIGNAL(startCheckSig()), this, SLOT(startexcute()));
    connect(ic->cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(stopexcute()));
    connect(ic, &ImageCheckWidget::setParameter, imageRoutineCheck, &CheckTask::setParameters);
    connect(this, SIGNAL(completerateUpdateSig(const int, const QString&)), ic, SLOT(completerateUpdate(const int, const QString&)));
    connect(this, SIGNAL(dataCountUpdateSig(const int, const int)), ic, SLOT(dataCountUpdate(const int, const int)));

    //connect(fileCheck, SIGNAL(errorFindSig()), cc->basicinfobtn, SLOT(changeToProblem()));
    //connect(fileCheck, SIGNAL(completeSig()), cc->basicinfobtn, SLOT(changeToNoProblem()));

    ImageCheckRpt* icImageCheckRpt = mainwindow->icImageCheckRpt;
    //connect(fileRoutineCheck, &CheckTask::completeSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToNoProblem);
    //connect(fileRoutineCheck, &CheckTask::errorFindSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToProblem);
    connect(imageRoutineCheck, &CheckTask::dataUpdateSig, icImageCheckRpt, &ImageCheckRpt::addImageCheckInfo);
}
//Call UI
void ImageCheckState::startexcute()
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
void ImageCheckState::stopexcute()
{
    start = false;
    emit stopSig();
}
void ImageCheckState::disablescene()
{
    enabled = false;
    emit disableSig();
}
//From Task
void ImageCheckState::progressUpdate(const int completeunit, const QString& status)
{
    this->currentcompleteunit += completeunit;
    this->currentstatus = status;
    emit completerateUpdateSig(currentcompleteunit * 100 / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void ImageCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
void ImageCheckState::initConInterfaceTask(InterfaceForTool* interfaceForTool)
{
    //Basic Info
    connect(interfaceForTool, SIGNAL(i_imagecheck_progress(const int, const QString&)), imageRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(i_imagecheck_error(const QString&)), imageRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(i_imagecheck_data(const QVariantList&)), imageRoutineCheck, SLOT(dataUpdate(const QVariantList&)));
}

