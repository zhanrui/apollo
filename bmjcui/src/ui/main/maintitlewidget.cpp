#include "maintitlewidget.h"
#include "src/ui/base/basestylewidget.h"
#include <src/ui/base/commonwidget.h>
#include <src/ui/base/staticbutton.h>
#include <QLabel>
#include <QHBoxLayout>

MainTitleWidget::MainTitleWidget(QWidget* parent)
    : BaseStyleWidget(parent)
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

    minButton = new StaticButton(":image/common/title/min", 3);
    testButton = new CommonWidget;

    // textLabel->setText("国家保密技术检查专用系统");
    //textLabel->adjustSize();
    //StaticButton *updateButton = new StaticButton(":/main/update_btn");
    QHBoxLayout* hLayout = new QHBoxLayout;

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
