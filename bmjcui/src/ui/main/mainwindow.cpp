
#include "mainwindow.h"

#include "src/ui/main/mainwidget.h"
#include "src/ui/onekeycheck/onekeycheckwidget.h"
#include "src/ui/common/sysbuttongroup.h"
#include "src/ui/detailreport/basicinforpt.h"
#include "src/ui/detailreport/deviceconnectrpt.h"
#include "src/ui/detailreport/netrecordrpt.h"
#include "src/ui/detailreport/basereport.h"
#include "src/ui/detailreport/systemsecurityrpt.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/onekeycheck/tabbutton.h"
#include <src/state/onekeycheckstate.h>
#include <src/util/toolutil.h>
#include <src/util/interfacefortool.h>
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

    oneKeyCheckWidget = new OneKeyCheckWidget(this);
    oneKeyCheckWidget->setObjectName("onekeycheckwidget");
    oneKeyCheckWidget->hide();

    okcBasicInfoRpt = new BasicInfoRpt(this, "一键检查——基本信息");
    okcBasicInfoRpt->setObjectName("okcBaiscInfo");
    okcBasicInfoRpt->hide();

    okcDeviceConnectRpt = new DeviceConnectRpt(this, "一键检查——设备连接信息");
    okcDeviceConnectRpt->setObjectName("okcDeviceConnectRpt");
    okcDeviceConnectRpt->hide();

    okcNetRecordRpt = new NetRecordRpt(this, "一键检查——上网记录检查");
    okcNetRecordRpt->setObjectName("okcNetRecordRpt");
    okcNetRecordRpt->hide();

    okcSystemSecurityRpt = new SystemSecurityRpt(this, "一键检查——系统安全检查");
    okcSystemSecurityRpt->setObjectName("SystemSecurityRpt");
    okcSystemSecurityRpt->hide();

    okcReports = QList<BaseReport*>();
    okcReports << okcBasicInfoRpt << okcDeviceConnectRpt << okcNetRecordRpt << okcSystemSecurityRpt;

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

    //Main Sub Navi
    connect(mainWidget->onekeychecklogo, &StaticButton::buttonClicked,
            [=]() {   switchWidgetToLeft(mainWidget, oneKeyCheckWidget); });
    connect(oneKeyCheckWidget->returnbtn, &StaticButton::buttonClicked,
            [=]() {  switchWidgetToRight(oneKeyCheckWidget, mainWidget); });

    connect(oneKeyCheckWidget->deviceconnectionbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(oneKeyCheckWidget, okcDeviceConnectRpt); });
    connect(okcDeviceConnectRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(okcDeviceConnectRpt, oneKeyCheckWidget); });

    connect(oneKeyCheckWidget->netbrowserbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(oneKeyCheckWidget, okcNetRecordRpt); });
    connect(okcNetRecordRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(okcNetRecordRpt, oneKeyCheckWidget); });

    connect(oneKeyCheckWidget->basicinfobtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(oneKeyCheckWidget, okcBasicInfoRpt); });
    connect(okcBasicInfoRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(okcBasicInfoRpt, oneKeyCheckWidget); });

    connect(oneKeyCheckWidget->systemsecuritybtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToLeft(oneKeyCheckWidget, okcSystemSecurityRpt); });
    connect(okcSystemSecurityRpt->returnbtn, &TabButton::buttonClicked,
            [=]() { switchWidgetToRight(okcSystemSecurityRpt, oneKeyCheckWidget); });

    connect(oneKeyCheckWidget->cancelcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:okcReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                if(taskbtn->taskstatus != TASK_PROBLEM)
                    taskbtn->changeToNoProblem();
            }
        }

    });

    connect(oneKeyCheckWidget->startcheckbtn, &StaticButton::buttonClicked,
            [=]() {
        for(BaseReport* baserpt:okcReports){
            for(TaskButton* taskbtn:baserpt->taskbtnlist ){
                taskbtn->changeToRunning();
            }
            for(QStandardItemModel* model:baserpt->modellist ){
               model->removeRows(0,model->rowCount());
            }
        }

    });

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

    oneKeyCheckState = new OneKeyCheckState(0, this, interfaceForTool, toolUtil);
    oneKeyCheckState->moveToThread(statethread);

    connect(sysButtonGroup->closeButton, SIGNAL(buttonClicked()), toolUtil, SLOT(stopAll()));
    connect(statethread, SIGNAL(finished()), interfaceForTool, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), toolUtil, SLOT(deleteLater()));
    connect(statethread, SIGNAL(finished()), oneKeyCheckState, SLOT(deleteLater()));
}
