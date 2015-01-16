
#include "mainwindow.h"

#include "src/ui/main/mainwidget.h"
#include <QApplication>
#include <QFile>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : ShadowWidget(parent)
{
    this->initUI();
    this->initAnim();
    this->initConnect();
}

void MainWindow::initUI()
{
    this->setFixedSize(900, 600);
    this->setWindowTitle(tr("保密检查工具"));
    this->setWindowIcon(QIcon(":image/common/title/logo"));
    mainWidget = new MainWidget(this);
    mainWidget->setObjectName("mainwidget");
    // mainWidget->setStyleSheet("background-color:blue;");
    // mainWidget->setGeometry(rect());
    // mainWidget->move(50,50);
    // mainWidget->raise();
    // qDebug()<<"uitest";

    // m_grayWidget = new OpacityWidget(this);
    // m_grayWidget->setGeometry(rect());
    // m_grayWidget->setColor(QColor(Qt::gray));

    // mainWidget->show();

    // mainWidget->move(50,50);
    //  mainWidget->move(mapToGlobal(QPoint(50,50)));//移动到与主窗口同一位置
}

void MainWindow::initConnect()
{
}

void MainWindow::initAnim() {}

void MainWindow::showMenu() {}

void MainWindow::showMin() {}
