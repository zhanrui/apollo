#include "mainwidget.h"
#include "src/ui/main/maintitlewidget.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QRect>


MainWidget::MainWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{
    //setWindowFlags( Qt::Window | Qt::FramelessWindowHint);
    this->initUI();
    this->initAnim();
    this->initConnect();
}

MainWidget::~MainWidget() {}

void MainWidget::initUI()
{
    this->setFixedSize(900, 600);
    //mainTitleWidget = new MainTitleWidget(this);

    //mainTitleWidget = new QWidget(this);
    //mainTitleWidget->setAttribute(Qt::WA_TranslucentBackground);
    //mainTitleWidget->setFixedWidth(900);
    //mainTitleWidget->move(0, 0);


    logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":image/common/title/logo"));
    logoLabel->move(13,1);
    textLabel = new QLabel(this);
    textLabel->setPixmap(QPixmap(":image/common/title/description"));
    textLabel->move(45,9);

    //QHBoxLayout *hLayout = new QHBoxLayout;
   // hLayout->addWidget(logoLabel);
   // hLayout->addWidget(textLabel);
  //  hLayout->addStretch();
   // mainTitleWidget->setLayout(hLayout);






    biglogoLabel = new QLabel(this);
    statusLabel = new QLabel(this);
    biglogoLabel->setPixmap(QPixmap(":image/main/biglogo"));
    biglogoLabel->move(80,100);
    statusLabel->setPixmap(QPixmap(":image/main/status"));
    statusLabel->move(236,136);




}

void MainWidget::initConnect() {}

void MainWidget::initAnim() {}
