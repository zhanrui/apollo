
#include "mainwindow.h"

#include "src/ui/main/mainwidget.h"
#include "src/ui/commoncheck/commoncheckwidget.h"
#include "src/ui/filecheck/filecheckwidget.h"
#include "src/ui/trojancheck/trojancheckwidget.h"
#include "src/ui/imagecheck/imagecheckwidget.h"
#include "src/ui/deepcheck/deepcheckwidget.h"
#include "src/ui/deepcheck/netrecorddeepcheckwidget.h"
#include "src/ui/deepcheck/usbdeepcheckwidget.h"
#include "src/ui/checkreport/checkreportwidget.h"

#include "src/ui/common/sysbuttongroup.h"
#include "src/ui/detailreport/basicinforpt.h"
#include "src/ui/detailreport/deviceconnectrpt.h"
#include "src/ui/detailreport/netrecordcommonrpt.h"
#include "src/ui/detailreport/basereport.h"
#include "src/ui/detailreport/systemsecurityrpt.h"
#include "src/ui/detailreport/securitythreatrpt.h"
#include "src/ui/detailreport/usbrecordcommonrpt.h"
#include "src/ui/detailreport/filecheckcommonrpt.h"
#include "src/ui/detailreport/trojancheckrpt.h"
#include "src/ui/detailreport/imagecheckrpt.h"
#include "src/ui/detailreport/usbrecordallrpt.h"
#include "src/ui/detailreport/usbrecorddeeprpt.h"
#include "src/ui/detailreport/netrecordallrpt.h"
#include "src/ui/detailreport/netrecorddeeprpt.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/commoncheck/tabbutton.h"
#include <src/state/commoncheckstate.h>
#include <src/state/filecheckstate.h>
#include <src/state/trojancheckstate.h>
#include <src/state/imagecheckstate.h>
#include <src/state/netrecorddeepcheckstate.h>
#include <src/state/usbdeepcheckstate.h>
#include <src/util/toolutil.h>
#include <src/util/interfacefortool.h>
#include <src/util/rptcreator.h>
#include <src/ui/main/mainwindow.h>
#include <src/ui/common/taskbutton.h>
#include <src/common/common.h>
#include <QApplication>
#include <QFile>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QWindow>
#include <QIcon>
#include <QDebug>
#include <QEvent>
#include <QThread>
#include <QDBusConnection>
#include <QDBusError>
#include <QPushButton>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget* parent)
    : ShadowWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    this->initUI();
    this->initAnim();
    this->initConnect();
    this->initDBus();
}

void MainWindow::initUI()
{
    //this->setFixedSize(900, 600);
    setMaximumWidth(900);
    setMaximumHeight(600);
    this->setWindowTitle(tr("保密检查工具"));
    this->setWindowIcon(QIcon(":image/common/title/logo"));
    mainWidget = new MainWidget(this);
    mainWidget->setObjectName("mainwidget");


    commonCheckWidget = new CommonCheckWidget(this);
    commonCheckWidget->setObjectName("commonCheckWidget");
    commonCheckWidget->hide();

    ccBasicInfoRpt = new BasicInfoRpt(this, "常规检查——基本信息");
    ccBasicInfoRpt->setObjectName("ccBaiscInfo");
    ccBasicInfoRpt->hide();

    ccDeviceConnectRpt = new DeviceConnectRpt(this, "常规检查——设备连接信息");
    ccDeviceConnectRpt->setObjectName("ccDeviceConnectRpt");
    ccDeviceConnectRpt->hide();

    ccNetRecordRpt = new NetRecordCommonRpt(this, "常规检查——上网记录检查");
    ccNetRecordRpt->setObjectName("ccNetRecordRpt");
    ccNetRecordRpt->hide();

    ccSystemSecurityRpt = new SystemSecurityRpt(this, "常规检查——系统安全检查");
    ccSystemSecurityRpt->setObjectName("ccSystemSecurityRpt");
    ccSystemSecurityRpt->hide();

    ccSecurityThreatRpt = new SecurityThreatRpt(this, "常规检查——安全威胁检查");
    ccSecurityThreatRpt->setObjectName("ccSecurityThreatRpt");
    ccSecurityThreatRpt->hide();

    ccUsbRecordCommonRpt = new UsbRecordCommonRpt(this, "常规检查——USB记录检查");
    ccUsbRecordCommonRpt->setObjectName("ccUsbRecordCommonRpt");
    ccUsbRecordCommonRpt->hide();

    ccReports = QList<BaseReport*>();
    ccReports << ccBasicInfoRpt << ccDeviceConnectRpt << ccNetRecordRpt
              << ccSystemSecurityRpt << ccSecurityThreatRpt << ccUsbRecordCommonRpt;

    fileCheckWidget = new FileCheckWidget(this);
    fileCheckWidget->setObjectName("fileCheckWidget");
    fileCheckWidget->hide();

    fcFileCheckCommonRpt = new FileCheckCommonRpt(this, "文件检查");
    fcFileCheckCommonRpt->setObjectName("fcFileCheckCommonRpt");
    fcFileCheckCommonRpt->hide();
    fcReports << fcFileCheckCommonRpt;

    trojanCheckWidget = new TrojanCheckWidget(this);
    trojanCheckWidget->setObjectName("trojanCheckWidget");
    trojanCheckWidget->hide();

    tcTrojanCheckRpt = new TrojanCheckRpt(this, "木马检查");
    tcTrojanCheckRpt->setObjectName("tcTrojanCheckRpt");
    tcTrojanCheckRpt->hide();
    tcReports << tcTrojanCheckRpt;

    imageCheckWidget = new ImageCheckWidget(this);
    imageCheckWidget->setObjectName("imageCheckWidget");
    imageCheckWidget->hide();

    icImageCheckRpt = new ImageCheckRpt(this, "图片检查");
    icImageCheckRpt->setObjectName("icImageCheckRpt");
    icImageCheckRpt->hide();
    icReports << icImageCheckRpt;

    netRecordDeepCheckWidget = new NetRecordDeepCheckWidget(this);
    netRecordDeepCheckWidget->setObjectName("netRecordDeepCheckWidget");
    netRecordDeepCheckWidget->hide();

    nrdNetRecordDeepRpt = new NetRecordDeepRpt(this, "上网记录深度检查");
    nrdNetRecordDeepRpt->setObjectName("nrdNetRecordDeepRpt");
    nrdNetRecordDeepRpt->hide();
    nrdReports << nrdNetRecordDeepRpt;

    deepCheckWidget = new DeepCheckWidget(this);
    deepCheckWidget->setObjectName("deepCheckWidget");
    deepCheckWidget->hide();
    usbDeepCheckWidget = new UsbDeepCheckWidget(this);
    usbDeepCheckWidget->setObjectName("netRecordDeepCheckWidget");
    usbDeepCheckWidget->hide();

    udUsbRecordDeepRpt = new UsbRecordDeepRpt(this, "USB记录深度检查");
    udUsbRecordDeepRpt->setObjectName("udUsbRecordDeepRpt");
    udUsbRecordDeepRpt->hide();
    udReports << udUsbRecordDeepRpt;

    checkReportWidget = new CheckReportWidget(this);
    checkReportWidget->setObjectName("checkReportWidget");
    checkReportWidget->hide();

    widgetSwitchAnimation = new QParallelAnimationGroup(this);

    sysButtonGroup = new SysButtonGroup(this);
    sysButtonGroup->raise();
    sysButtonGroup->move(840, 1);

    //closeButton = new QPushButton("Hello",this);
    //connect(closeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

void MainWindow::initConnect()
{
    //Init System
    connect(sysButtonGroup->minButton, SIGNAL(buttonClicked()), this, SLOT(showMin()));
    connect(sysButtonGroup->closeButton, SIGNAL(buttonClicked()), this, SLOT(closeWidget()));

    //Main Sub Navi - OneKeyCheck
    connect(mainWidget->commonchecklogo, &StaticButton::buttonClicked,
            [=]() {   switchWidgetToLeft(mainWidget, commonCheckWidget); });
    connect(commonCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(commonCheckWidget, mainWidget); });

    connect(commonCheckWidget->deviceconnectionbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(commonCheckWidget, ccDeviceConnectRpt); });
    connect(ccDeviceConnectRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(ccDeviceConnectRpt, commonCheckWidget); });

    connect(commonCheckWidget->netbrowserbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(commonCheckWidget, ccNetRecordRpt); });
    connect(ccNetRecordRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(ccNetRecordRpt, commonCheckWidget); });

    connect(commonCheckWidget->basicinfobtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(commonCheckWidget, ccBasicInfoRpt); });
    connect(ccBasicInfoRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(ccBasicInfoRpt, commonCheckWidget); });

    connect(commonCheckWidget->systemsecuritybtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(commonCheckWidget, ccSystemSecurityRpt); });
    connect(ccSystemSecurityRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(ccSystemSecurityRpt, commonCheckWidget); });

    connect(commonCheckWidget->securitythreatbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(commonCheckWidget, ccSecurityThreatRpt); });
    connect(ccSecurityThreatRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(ccSecurityThreatRpt, commonCheckWidget); });

    connect(commonCheckWidget->usbcheckbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(commonCheckWidget, ccUsbRecordCommonRpt); });
    connect(ccUsbRecordCommonRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(ccUsbRecordCommonRpt, commonCheckWidget); });

    connect(commonCheckWidget->cancelcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:ccReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                if(taskbtn->taskstatus != TASK_PROBLEM)
                    taskbtn->changeToNoProblem();
            }
        }

    });

    connect(commonCheckWidget->startcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:ccReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                taskbtn->changeToRunning();
            }
            for(QStandardItemModel* model:baserpt->modellist ){
               model->removeRows(0,model->rowCount());
            }
        }

    });

    //Main Sub Navi - FileCheck
    connect(mainWidget->filechecklogo, &StaticButton::buttonClicked,
            [=]() {   switchWidgetToLeft(mainWidget, fileCheckWidget); });
    connect(fileCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(fileCheckWidget, mainWidget); });

    connect(fileCheckWidget->checkResultBtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(fileCheckWidget, fcFileCheckCommonRpt); });
    connect(fcFileCheckCommonRpt->returnbtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToRight(fcFileCheckCommonRpt, fileCheckWidget); });

    connect(fileCheckWidget->cancelcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:fcReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                if(taskbtn->taskstatus != TASK_PROBLEM)
                    taskbtn->changeToNoProblem();
            }
        }

    });
    connect(fileCheckWidget, &FileCheckWidget::startCheckSig,
            [=]() {

        for(BaseReport* baserpt:fcReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                taskbtn->changeToRunning();
            }
            for(QStandardItemModel* model:baserpt->modellist ){
               model->removeRows(0,model->rowCount());
            }
        }

    });

    //Main Sub Navi - TrojanCheck
    connect(mainWidget->tjchecklogo, &StaticButton::buttonClicked,
            [=]() {   switchWidgetToLeft(mainWidget, trojanCheckWidget); });
    connect(trojanCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(trojanCheckWidget, mainWidget); });

    connect(trojanCheckWidget->checkResultBtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(trojanCheckWidget, tcTrojanCheckRpt); });
    connect(tcTrojanCheckRpt->returnbtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToRight(tcTrojanCheckRpt, trojanCheckWidget); });

    connect(trojanCheckWidget->cancelcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:tcReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                if(taskbtn->taskstatus != TASK_PROBLEM)
                    taskbtn->changeToNoProblem();
            }
        }
    });

    connect(trojanCheckWidget, &TrojanCheckWidget::startCheckSig,
            [=]() {
        for(BaseReport* baserpt:tcReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                taskbtn->changeToRunning();
            }
            for(QStandardItemModel* model:baserpt->modellist ){
               model->removeRows(0,model->rowCount());
            }
        }

    });

    //Main Sub Navi - ImageCheck
    connect(mainWidget->imagechecklogo, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(mainWidget, imageCheckWidget); });
    connect(imageCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(imageCheckWidget, mainWidget); });
    connect(imageCheckWidget->checkResultBtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(imageCheckWidget, icImageCheckRpt); });
    connect(icImageCheckRpt->returnbtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToRight(icImageCheckRpt, imageCheckWidget); });

    connect(imageCheckWidget->cancelcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:icReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                if(taskbtn->taskstatus != TASK_PROBLEM)
                    taskbtn->changeToNoProblem();
            }
        }

    });
    connect(imageCheckWidget, &ImageCheckWidget::startCheckSig,
            [=]() {
        for(BaseReport* baserpt:icReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                taskbtn->changeToRunning();
            }
            for(QStandardItemModel* model:baserpt->modellist ){
               model->removeRows(0,model->rowCount());
            }
        }
    });

    //Main Sub Navi - NetRecordDeepCheck
    connect(mainWidget->deepchecklogo, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(mainWidget, deepCheckWidget); });
    connect(deepCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(deepCheckWidget, mainWidget); });

    connect(deepCheckWidget->deepNetRecCheckbtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(deepCheckWidget, netRecordDeepCheckWidget); });
    connect(netRecordDeepCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(netRecordDeepCheckWidget, deepCheckWidget); });

    connect(netRecordDeepCheckWidget->checkResultBtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(netRecordDeepCheckWidget, nrdNetRecordDeepRpt); });
    connect(nrdNetRecordDeepRpt->returnbtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToRight(nrdNetRecordDeepRpt, netRecordDeepCheckWidget); });

    connect(netRecordDeepCheckWidget->cancelcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:nrdReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                if(taskbtn->taskstatus != TASK_PROBLEM)
                    taskbtn->changeToNoProblem();
            }
        }

    });
    connect(netRecordDeepCheckWidget, &NetRecordDeepCheckWidget::startCheckSig,
            [=]() {
        for(BaseReport* baserpt:nrdReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                taskbtn->changeToRunning();
            }
            for(QStandardItemModel* model:baserpt->modellist ){
               model->removeRows(0,model->rowCount());
            }
        }
    });

    //Main Sub Navi - UsbDeepCheck

    connect(deepCheckWidget->deepUsbCheckbtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(deepCheckWidget, usbDeepCheckWidget); });
    connect(usbDeepCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(usbDeepCheckWidget, deepCheckWidget); });

    connect(usbDeepCheckWidget->checkResultBtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(usbDeepCheckWidget, udUsbRecordDeepRpt); });
    connect(udUsbRecordDeepRpt->returnbtn, &StaticButton::buttonClicked,
            [=]() { switchWidgetToRight(udUsbRecordDeepRpt, usbDeepCheckWidget); });

    connect(usbDeepCheckWidget->cancelcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:udReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                if(taskbtn->taskstatus != TASK_PROBLEM)
                    taskbtn->changeToNoProblem();
            }
        }
    });
    connect(usbDeepCheckWidget, &UsbDeepCheckWidget::startCheckSig,
            [=]() {
        for(BaseReport* baserpt:udReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                taskbtn->changeToRunning();
            }
            for(QStandardItemModel* model:baserpt->modellist ){
               model->removeRows(0,model->rowCount());
            }
        }
    });

    connect(mainWidget->checkrptlogo, &StaticButton::buttonClicked,
            [=]() { switchWidgetToLeft(mainWidget, checkReportWidget); });
    connect(checkReportWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(checkReportWidget, mainWidget); });

    //OneKeyCheck
    //connect(oneKeyCheckWidget->startcheckbtn, SIGNAL(buttonClicked()), toolUtil, SLOT(startOneKeyCheck()));
    //connect(oneKeyCheckWidget->cancelcheckbtn, SIGNAL(buttonClicked()), toolUtil, SLOT(cancelOneKeyCheck()));
}

void MainWindow::initAnim() {}

void MainWindow::switchWidgetToLeft(QWidget* currentWidget, QWidget* showWidget)
{

    showWidget->move(QPoint(900, 0));
    showWidget->show();

    widgetSwitchAnimation->clear();

    QPropertyAnimation* currentAnimation = new QPropertyAnimation(currentWidget, "pos");
    currentAnimation->setDuration(500);
    currentAnimation->setStartValue(currentWidget->pos());
    currentAnimation->setEndValue(QPoint(currentWidget->pos().x() - 900, currentWidget->pos().y()));

    QPropertyAnimation* showAnimation = new QPropertyAnimation(showWidget, "pos");
    showAnimation->setDuration(500);
    showAnimation->setStartValue(showWidget->pos());
    showAnimation->setEndValue(QPoint(showWidget->pos().x() - 900, showWidget->pos().y()));

    widgetSwitchAnimation->addAnimation(currentAnimation);
    widgetSwitchAnimation->addAnimation(showAnimation);
    widgetSwitchAnimation->start();
}

void MainWindow::switchWidgetToRight(QWidget* currentWidget, QWidget* showWidget)
{

    showWidget->move(QPoint(-900, 0));
    showWidget->show();

    widgetSwitchAnimation->clear();

    QPropertyAnimation* currentAnimation = new QPropertyAnimation(currentWidget, "pos");
    currentAnimation->setDuration(500);
    currentAnimation->setStartValue(currentWidget->pos());
    currentAnimation->setEndValue(QPoint(currentWidget->pos().x() + 900, currentWidget->pos().y()));

    QPropertyAnimation* showAnimation = new QPropertyAnimation(showWidget, "pos");
    showAnimation->setDuration(500);
    showAnimation->setStartValue(showWidget->pos());
    showAnimation->setEndValue(QPoint(showWidget->pos().x() + 900, showWidget->pos().y()));

    widgetSwitchAnimation->addAnimation(currentAnimation);
    widgetSwitchAnimation->addAnimation(showAnimation);
    widgetSwitchAnimation->start();
}

void MainWindow::showMin()
{
    showMinimized();
}

void MainWindow::closeWidget()
{
    qApp->quit();
}

void MainWindow::initDBus()
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
    }

    if (!connection.registerService("com.bmjc.ui")) {
        qDebug() << connection.lastError().message();
    }

    //Init State In Other Thread
    statethread = new QThread(this);
    statethread->start();
    interfaceForTool = new InterfaceForTool();
    if (!connection.registerObject("/bmjc/ui", interfaceForTool, QDBusConnection::ExportAllSlots)) {
        qDebug() << "connection.lastError().message()";
    }
    interfaceForTool->moveToThread(statethread);
    toolUtil = new ToolUtil();
    toolUtil->moveToThread(statethread);

    oneKeyCheckState = new CommonCheckState(0, this, interfaceForTool, toolUtil);
    oneKeyCheckState->moveToThread(statethread);
    fileCheckState = new FileCheckState(0, this, interfaceForTool, toolUtil);
    fileCheckState->moveToThread(statethread);
    trojanCheckState = new TrojanCheckState(0, this, interfaceForTool, toolUtil);
    trojanCheckState->moveToThread(statethread);
    imageCheckState = new ImageCheckState(0, this, interfaceForTool, toolUtil);
    imageCheckState->moveToThread(statethread);
    netRecordDeepCheckState = new NetRecordDeepCheckState(0, this, interfaceForTool, toolUtil);
    netRecordDeepCheckState->moveToThread(statethread);
    usbDeepCheckState = new UsbDeepCheckState(0, this, interfaceForTool, toolUtil);
    usbDeepCheckState->moveToThread(statethread);
    rptCreator = new RptCreator(0, this);
    rptCreator->moveToThread(statethread);
    connect(sysButtonGroup->closeButton, SIGNAL(buttonClicked()), toolUtil, SLOT(stopAll()));
    connect(statethread, SIGNAL(finished()), interfaceForTool, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), toolUtil, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), oneKeyCheckState, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), fileCheckState, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), trojanCheckState, SLOT(deleteLater()));

    connect(statethread, SIGNAL(finished()), netRecordDeepCheckState, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), usbDeepCheckState, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), rptCreator, SLOT(deleteLater()));
}
