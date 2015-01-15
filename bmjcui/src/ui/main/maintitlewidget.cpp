#include "maintitlewidget.h"
#include "src/ui/common/basestylewidget.h"
#include <src/ui/common/commonwidget.h>
#include <src/ui/common/staticbutton.h>
#include <QLabel>
#include <QHBoxLayout>



MainTitleWidget::MainTitleWidget(QWidget *parent) :BaseStyleWidget(parent)
{
    this->initUI();
    this->initAnim();
    this->initConnect();
}

MainTitleWidget::~MainTitleWidget()
{

}

void MainTitleWidget::initUI()
{
    logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":image/common/title/logo"));
    textLabel = new QLabel(this);
    textLabel->setPixmap(QPixmap(":image/common/title/description"));
    minButton=new StaticButton(":image/common/title/min",3);
    testButton= new CommonWidget;
    testButton->setObjectName("testbutton");
    testButton->setFixedSize(27,23);


   // textLabel->setText("国家保密技术检查专用系统");
    //textLabel->adjustSize();
    //StaticButton *updateButton = new StaticButton(":/main/update_btn");
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(logoLabel);
    hLayout->addWidget(textLabel);
     hLayout->addStretch();
    hLayout->addWidget(minButton);
    hLayout->addWidget(testButton);
    hLayout->addStretch();

    this->setLayout(hLayout);
}


void MainTitleWidget::initConnect()
{

}

void MainTitleWidget::initAnim()
{

}




