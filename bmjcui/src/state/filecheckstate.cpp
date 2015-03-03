#include "filecheckstate.h"

#include <QDBusConnection>

#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/filecheck/filecheckwidget.h"

#include "src/ui/detailreport/filecheckcommonrpt.h"
#include "src/ui/base/staticbutton.h"

#include "src/util/interfacefortool.h"
#include "src/util/toolutil.h"
#include <QDebug>
#include <QAbstractItemModel>

FileCheckState::FileCheckState(QObject* parent, MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
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

FileCheckState::~FileCheckState()
{
}

void FileCheckState::inittasks(ToolUtil* toolUtil)
{

    fileRoutineCheck = new CheckTask(this, toolUtil, FUNC_FILECOMCHECK, SCENE_FILECHECK, true, 1);

    fileCheck = new CheckTaskGroup(this, SCENE_FILECHECK, 1,
                                   QList<CheckTask*>() << fileRoutineCheck);
}
void FileCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << fileCheck;
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

void FileCheckState::totalUnitChanged(const int value)
{
    totalcompleteunit += value;
}
void FileCheckState::initConUIState(MainWindow* mainwindow)
{
    FileCheckWidget* fc = mainwindow->fileCheckWidget;

    //connect(fc->startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startexcute()));

    connect(fc, &FileCheckWidget::startCheckSig,this,&FileCheckState::startexcute);

    connect(fc->cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(stopexcute()));
    connect(fc, &FileCheckWidget::setParameter, fileRoutineCheck, &CheckTask::setParameters);
    connect(this, SIGNAL(completerateUpdateSig(const int, const QString&)), fc, SLOT(completerateUpdate(const int, const QString&)));
    connect(this, SIGNAL(dataCountUpdateSig(const int, const int)), fc, SLOT(dataCountUpdate(const int, const int)));

    //connect(fileCheck, SIGNAL(errorFindSig()), okc->basicinfobtn, SLOT(changeToProblem()));
    //connect(fileCheck, SIGNAL(completeSig()), okc->basicinfobtn, SLOT(changeToNoProblem()));

    FileCheckCommonRpt* fcFileCheckCommonRpt = mainwindow->fcFileCheckCommonRpt;
    //connect(fileRoutineCheck, &CheckTask::completeSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToNoProblem);
    //connect(fileRoutineCheck, &CheckTask::errorFindSig, fcFileCheckCommonRpt->osInfoBtn, &TaskButton::changeToProblem);
    connect(fileRoutineCheck, &CheckTask::dataUpdateSig, fcFileCheckCommonRpt, &FileCheckCommonRpt::addFileRoutineCheckInfo);
}
//Call UI
void FileCheckState::startexcute()
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
void FileCheckState::stopexcute()
{
    start = false;
    emit stopSig();
}
void FileCheckState::disablescene()
{
    enabled = false;
    emit disableSig();
}
//From Task
void FileCheckState::progressUpdate(const int completeunit, const QString& status)
{
    this->currentcompleteunit += completeunit;
    this->currentstatus = status;
    emit completerateUpdateSig(currentcompleteunit * 100 / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void FileCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
void FileCheckState::initConInterfaceTask(InterfaceForTool* interfaceForTool)
{

    //Basic Info
    connect(interfaceForTool, SIGNAL(f_filecomcheck_progress(const int, const QString&)), fileRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(f_filecomcheck_error(const QString&)), fileRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(f_filecomcheck_data(const QVariantList&)), fileRoutineCheck, SLOT(dataUpdate(const QVariantList&)));
}
