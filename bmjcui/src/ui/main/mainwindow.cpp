
#include "mainwindow.h"

#include "src/ui/main/mainwidget.h"
#include "src/ui/common/sysbuttongroup.h"
#include "src/ui/base/staticbutton.h"
#include <src/state/onekeycheckstate.h>
#include <src/util/toolutil.h>
#include <src/util/interfacefortool.h>
#include <src/ui/main/mainwindow.h>
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







MainWindow::MainWindow(QWidget* parent)
    : ShadowWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    this->initDBus();
    this->initUI();
    this->initAnim();
    this->initConnect();
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

    sysButtonGroup = new SysButtonGroup(this);
    sysButtonGroup->raise();
    sysButtonGroup->move(840, 1);


     //closeButton = new QPushButton("Hello",this);
     //connect(closeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

void MainWindow::initConnect()
{
    connect(sysButtonGroup->minButton, SIGNAL(buttonClicked()), this, SLOT(showMin()));
    connect(sysButtonGroup->closeButton, SIGNAL(buttonClicked()), this, SLOT(closeWidget()));

}

void MainWindow::initAnim() {}

void MainWindow::showMenu() {}

void MainWindow::showMin()
{

    //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint|  Qt::WindowMinimizeButtonHint );

   // this->show();

    showMinimized();

    //this->windowHandle()->showMinimized();
    //showNormal();
    //showMinimized();
    //qDebug()<<windowState();
    //setWindowState( Qt::WindowMinimized);
    //setVisible(true);
    //qDebug()<<windowState();
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

        if (!connection.registerService("com.example.bmjc")) {
            qDebug() << connection.lastError().message();
        }

        //Init State In Other Thread
        statethread = new QThread(this);
        interfaceForTool = new InterfaceForTool();
        if (!connection.registerObject("/bmjc/ui", interfaceForTool, QDBusConnection::ExportAllSlots)) {
            qDebug() << "connection.lastError().message()";

        }
        interfaceForTool->moveToThread(statethread);
        oneKeyCheckState = new OneKeyCheckState();
        oneKeyCheckState->moveToThread(statethread);
        statethread->start();
}



