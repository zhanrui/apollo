#include "sysbuttongroup.h"
#include <QHBoxLayout>
#include "src/ui/base/staticbutton.h"
SysButtonGroup::SysButtonGroup(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *hLayout = new QHBoxLayout;

    minButton = new StaticButton(":image/common/title/min",3);
    //connect(minButton, SIGNAL(buttonClicked()), this, SIGNAL(showMin()));

    closeButton = new StaticButton(":image/common/title/close",3);
    //connect(closeButton, SIGNAL(buttonClicked()), this, SIGNAL(closeWidget()));

    hLayout->addWidget(minButton);
    hLayout->addWidget(closeButton);
    hLayout->setContentsMargins(1, 0, 1, 0);
    hLayout->setSpacing(0);

    this->setLayout(hLayout);
}
