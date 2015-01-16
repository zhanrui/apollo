#include "mainwidget.h"
#include <QLabel>
#include <QHBoxLayout>

MainWidget::MainWidget(QWidget *parent) : BaseStyleWidget(parent) {

  this->initUI();
  this->initAnim();
  this->initConnect();
}

MainWidget::~MainWidget() {}

void MainWidget::initUI() {
  this->setFixedSize(900, 600);
  mainTitleWidget = new MainTitleWidget(this);
}

void MainWidget::initConnect() {}

void MainWidget::initAnim() {}
