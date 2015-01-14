
#include "mainwindow.h"
#include "common/opacitywidget.h"
#include "common/videowidget.h"
#include <QApplication>
#include <QFile>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    ShadowWidget(parent)
{
    this->initUI();
    this->initAnim();
    this->initConnect();
}

void MainWindow::initUI()
{
    this->setFixedSize(900, 600);
    this->setWindowTitle(tr("保密检查工具"));

}

void MainWindow::initConnect()
{

}

void MainWindow::initAnim()
{

}



void MainWindow::showMenu()
{

}




void MainWindow::showMin()
{

}
