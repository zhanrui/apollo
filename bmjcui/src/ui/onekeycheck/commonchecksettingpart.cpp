#include "commonchecksettingpart.h"

#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/base/commonwidget.h"
#include "src/ui/commoncheck/tabbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
#include "src/ui/onekeycheck/checkbutton.h"
#include "src/common/globals.h"
#include "src/common/common.h"
#include <QLabel>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QBrush>
#include <QScrollBar>
#include <QAbstractItemView>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QFrame>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QMovie>

#include <QtWidgets>

CommonCheckSettingPart::CommonCheckSettingPart(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initUI();
    initConnect();
}

CommonCheckSettingPart::~CommonCheckSettingPart()
{
}

void CommonCheckSettingPart::initUI()
{
    this->setFixedSize(707, 554);
    this->move(193, 46);

    int y = 80;

    QLabel* statusname = new QLabel(this);
    statusname->setText("常规检查");
    statusname->setObjectName("cc_statusname");
    statusname->move(53, 120 - y);

    QLabel* mainhline = new QLabel(this);
    mainhline->move(0, 160 - y);
    mainhline->setFixedSize(900, 1);
    mainhline->setObjectName("mainhline");
    //hline0->setPixmap(QPixmap(":image/filecheck/hline"));

    QLabel* hline1 = new QLabel(this);
    hline1->move(0, 400 - y);
    hline1->setPixmap(QPixmap(":image/filecheck/hline"));

    QLabel* description = new QLabel(this);
    description->setText("查看用户终端系统基本信息，设备连接信息，上网记录等");
    description->setObjectName("ccs_description");
    description->move(170, 124 - y);

    y = 0;
    int x = 180;

    basicinfobtn = new CheckButton(":image/onekeycheck/setting/commoncheck", this);
    basicinfobtn->move(230 - x, 137 - y);
    QLabel* basicinfotitle = new QLabel(this);
    basicinfotitle->setText("基本信息");
    basicinfotitle->move(259 - x, 132 - y);
    basicinfotitle->setObjectName("basicinfotitle");
    QLabel* basicinfodescription = new QLabel(this);
    basicinfodescription->setText("检查操作系统，内存等基本配置");
    basicinfodescription->move(259 - x, 148 - y);
    basicinfodescription->setObjectName("basicinfodescription");
    basicinfodescription->setFixedWidth(150);
    basicinfodescription->setWordWrap(true);

    deviceconnectionbtn = new CheckButton(":image/onekeycheck/setting/commoncheck", this);
    deviceconnectionbtn->move(448 - x, 137 - y);
    QLabel* deviceconnectiontitle = new QLabel(this);
    deviceconnectiontitle->setText("设备连接");
    deviceconnectiontitle->move(476 - x, 132 - y);
    deviceconnectiontitle->setObjectName("deviceconnectiontitle");
    QLabel* deviceconnectiondescription = new QLabel(this);
    deviceconnectiondescription->setText("检查网卡，打印机等设备连接信息");
    deviceconnectiondescription->move(476 - x, 150 - y);
    deviceconnectiondescription->setObjectName("deviceconnectiondescription");
    deviceconnectiondescription->setFixedWidth(150);
    deviceconnectiondescription->setWordWrap(true);

    netrecordbtn = new CheckButton(":image/onekeycheck/setting/commoncheck", this);
    netrecordbtn->move(664 - x, 137 - y);
    QLabel* netrecordtitle = new QLabel(this);
    netrecordtitle->setText("上网记录");
    netrecordtitle->move(693 - x, 132 - y);
    netrecordtitle->setObjectName("netrecordtitle");
    QLabel* netrecorddescription = new QLabel(this);
    netrecorddescription->setText("检查上网记录信息");
    netrecorddescription->move(693 - x, 150 - y);
    netrecorddescription->setObjectName("netrecorddescription");
    netrecorddescription->setFixedWidth(150);
    netrecorddescription->setWordWrap(true);

    systemsecuritybtn = new CheckButton(":image/onekeycheck/setting/commoncheck", this);
    systemsecuritybtn->move(230 - x, 232 - y);
    QLabel* systemsecuritytitle = new QLabel(this);
    systemsecuritytitle->setText("系统安全");
    systemsecuritytitle->move(259 - x, 227 - y);
    systemsecuritytitle->setObjectName("systemsecuritytitle");
    QLabel* systemsecuritydescription = new QLabel(this);
    systemsecuritydescription->setText("检查服务进程等系统安全信息");
    systemsecuritydescription->move(259 - x, 245 - y);
    systemsecuritydescription->setObjectName("systemsecuritydescription");
    systemsecuritydescription->setFixedWidth(150);
    systemsecuritydescription->setWordWrap(true);

    securitythreatbtn = new CheckButton(":image/onekeycheck/setting/commoncheck", this);
    securitythreatbtn->move(448 - x, 232 - y);
    QLabel* securitythreattitle = new QLabel(this);
    securitythreattitle->setText("安全隐患");
    securitythreattitle->move(476 - x, 227 - y);
    securitythreattitle->setObjectName("securitythreattitle");
    QLabel* securitythreatdescription = new QLabel(this);
    securitythreatdescription->setText("检查开放端口，身份认证的等安全隐患");
    securitythreatdescription->move(476 - x, 245 - y);
    securitythreatdescription->setObjectName("securitythreatdescription");
    securitythreatdescription->setFixedWidth(150);
    securitythreatdescription->setWordWrap(true);

    usbrecordbtn = new CheckButton(":image/onekeycheck/setting/commoncheck", this);
    usbrecordbtn->move(664 - x, 232 - y);
    QLabel* usbrecordtitle = new QLabel(this);
    usbrecordtitle->setText("USB记录");
    usbrecordtitle->move(693 - x, 227 - y);
    usbrecordtitle->setObjectName("usbrecordtitle");
    QLabel* usbrecorddescription = new QLabel(this);
    usbrecorddescription->setText("检查USB使用记录");
    usbrecorddescription->move(693 - x, 245 - y);
    usbrecorddescription->setObjectName("usbrecorddescription");
    usbrecorddescription->setFixedWidth(150);
    usbrecorddescription->setWordWrap(true);
}
void CommonCheckSettingPart::initConnect()
{

    basicinfobtn->changeToChecked();
    connect(basicinfobtn, &CheckButton::buttonClicked, [=]() {
        if(basicinfobtn->checkbtnstatus==DISABLED){
            basicinfobtn->changeToChecked();
        }else{
            basicinfobtn->changeToUnChecked();
        }
    });

    deviceconnectionbtn->changeToChecked();
    connect(deviceconnectionbtn, &CheckButton::buttonClicked, [=]() {
        if(deviceconnectionbtn->checkbtnstatus==DISABLED){
            deviceconnectionbtn->changeToChecked();
        }else{
            deviceconnectionbtn->changeToUnChecked();
        }
    });

    netrecordbtn->changeToChecked();
    connect(netrecordbtn, &CheckButton::buttonClicked, [=]() {
        if(netrecordbtn->checkbtnstatus==DISABLED){
            netrecordbtn->changeToChecked();
        }else{
            netrecordbtn->changeToUnChecked();
        }
    });

    systemsecuritybtn->changeToChecked();
    connect(systemsecuritybtn, &CheckButton::buttonClicked, [=]() {
        if(systemsecuritybtn->checkbtnstatus==DISABLED){
            systemsecuritybtn->changeToChecked();
        }else{
            systemsecuritybtn->changeToUnChecked();
        }
    });

    securitythreatbtn->changeToChecked();
    connect(securitythreatbtn, &CheckButton::buttonClicked, [=]() {
        if(securitythreatbtn->checkbtnstatus==DISABLED){
            securitythreatbtn->changeToChecked();
        }else{
            securitythreatbtn->changeToUnChecked();
        }
    });

    usbrecordbtn->changeToChecked();
    connect(usbrecordbtn, &CheckButton::buttonClicked, [=]() {
        if(usbrecordbtn->checkbtnstatus==DISABLED){
            usbrecordbtn->changeToChecked();
        }else{
            usbrecordbtn->changeToUnChecked();
        }
    });

}
