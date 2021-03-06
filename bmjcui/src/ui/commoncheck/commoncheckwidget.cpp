#include "commoncheckwidget.h"
#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"

#include "src/ui/commoncheck/tabbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
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

CommonCheckWidget::CommonCheckWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initModel();
    initUI();
    initConnect();
}

CommonCheckWidget::~CommonCheckWidget()
{
}

void CommonCheckWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);
    startcheckbtn = new StaticButton(":image/common/startcheckbtn", 3, this);
    startcheckbtn->move(703, 60);
    cancelcheckbtn = new StaticButton(":image/common/cancelcheckbtn", 3, this);
    cancelcheckbtn->move(739, 74);
    cancelcheckbtn->hide();
    commonchecklogo = new QLabel(this);
    commonchecklogo->setPixmap(QPixmap(":image/commoncheck/commonchecklogo"));
    commonchecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("常规检查");
    descriptiontitle->setObjectName("cc_descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("一般检查项目包含设备信息，以及基本安全信息");
    description->setObjectName("cc_description");
    description->move(133, 109);

    progressbar_background = new QLabel(this);
    progressbar_background->setPixmap(QPixmap(":image/common/progressbar_background"));
    progressbar_background->move(0, 147);
    progressbar_background->hide();

    progressbar_front = new QLabel(this);
    QMovie* movie = new QMovie(":image/common/progressbar_front");
    movie->setParent(this);
    movie->start();
    progressbar_front->setMovie(movie);

    //progressbar_front->setPixmap(QPixmap(":image/commoncheck/progressbar_front"));
    progressbar_front->move(-900, 147);
    progressbar_front->hide();

    checkingElapsedTime = new QLabel(this);
    checkingElapsedTime->move(584, 82);
    checkingElapsedTime->setObjectName("cc_checkingelapsedtime");
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->hide();
    checkingElapsedTimer = new QTimer(this);

    //hline = new QLabel(this);
    //hline->setPixmap(QPixmap(":image/commoncheck/hline"));
    //hline->move(0,153);
    QWidget* leftbackground = new QWidget(this);
    leftbackground->move(0, 153);
    leftbackground->setFixedSize(192, 447);
    leftbackground->setObjectName("cc_leftbackground");

    QLabel* vline = new QLabel(this);
    vline->setPixmap(QPixmap(":image/commoncheck/vline"));
    vline->move(192, 153);

    int start = 153;
    int between = 57;
    int x = 1;

    basicinfobtn = new TabButton(":image/commoncheck/leftbutton/basicinfobtn", this);
    basicinfobtn->move(x, start);
    basicinfobtn->setEnabled(false);

    deviceconnectionbtn = new TabButton(":image/commoncheck/leftbutton/deviceconnectionbtn", this);
    deviceconnectionbtn->move(x, start + (between)*1);
    deviceconnectionbtn->setEnabled(false);

    netbrowserbtn = new TabButton(":image/commoncheck/leftbutton/netbrowserbtn", this);
    netbrowserbtn->move(x, start + (between)*2);
    netbrowserbtn->setEnabled(false);
    systemsecuritybtn = new TabButton(":image/commoncheck/leftbutton/systemsecuritybtn", this);
    systemsecuritybtn->move(x, start + (between)*3);
    systemsecuritybtn->setEnabled(false);
    securitythreatbtn = new TabButton(":image/commoncheck/leftbutton/securitythreatbtn", this);
    securitythreatbtn->move(x, start + (between)*4);
    securitythreatbtn->setEnabled(false);
    usbcheckbtn = new TabButton(":image/commoncheck/leftbutton/usbcheckbtn", this);
    usbcheckbtn->move(x, start + (between)*5);
    usbcheckbtn->setEnabled(false);
    filecheckbtn = new TabButton(":image/commoncheck/leftbutton/filecheckbtn", this);
    filecheckbtn->move(x, start + (between)*6);
    filecheckbtn->setEnabled(false);
    filecheckbtn->hide();
    tjcheckbtn = new TabButton(":image/commoncheck/leftbutton/tjcheckbtn", this);
    tjcheckbtn->move(x, start + (between)*7);
    tjcheckbtn->setEnabled(false);
    tjcheckbtn->hide();

    for (int i = 0; i < 6; i++) {
        QLabel* hline = new QLabel(this);
        hline->setPixmap(QPixmap(":image/commoncheck/hline"));
        hline->move(0, start + (between) * (i + 1));
    }

    tabbuttonlist = QList<TabButton*>();
    tabbuttonlist << basicinfobtn << deviceconnectionbtn << netbrowserbtn << systemsecuritybtn
                  << securitythreatbtn << usbcheckbtn << filecheckbtn << tjcheckbtn;

    QLabel* mainshieldlogo = new QLabel(this);
    mainshieldlogo->setPixmap(QPixmap(":image/commoncheck/description/mainshieldlogo"));
    mainshieldlogo->move(271, 252);

    QLabel* destitle = new QLabel(this);
    destitle->setObjectName("destitle");
    destitle->setText("常规检查");
    destitle->move(496, 259);

    QLabel* shorthline = new QLabel(this);
    shorthline->setPixmap(QPixmap(":image/commoncheck/description/shorthline"));
    shorthline->move(496, 290);

    QLabel* desdetail = new QLabel(this);
    desdetail->setObjectName("desdetail");
    desdetail->setText("查看用户终端系统配置、操作系统等基本信息，无线网卡、打印机等设备连接信息，上网记录和usb使用记录，系统服务、进程等系统安全信息，开放端口、共享、身份认证等安全隐患。");
    desdetail->move(496, 320);
    desdetail->setFixedWidth(300);
    desdetail->setWordWrap(true);
}
void CommonCheckWidget::initConnect()
{
    connect(startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startCheck()));
    connect(cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(cancelCheck()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));
}
void CommonCheckWidget::initModel()
{
}

void CommonCheckWidget::startCheck()
{
    startcheckbtn->hide();
    cancelcheckbtn->show();
    progressbar_background->show();
    progressbar_front->move(-900, 147);
    progressbar_front->show();
    descriptiontitle->setText("正在检查。。。");
    descriptiontitle->adjustSize();
    description->setText("还未检查出可疑问题");
    description->adjustSize();

    checkingElapsedTime->show();
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->adjustSize();
    checkingStartTime = (QDateTime::currentDateTime()).toTime_t();
    checkingElapsedTimer->start(1000);

    for (TabButton* btn : tabbuttonlist) {
        btn->setEnabled(true);
        btn->changeToRunning();
    }
}

void CommonCheckWidget::cancelCheck()
{
    startcheckbtn->show();
    cancelcheckbtn->hide();
    progressbar_background->hide();
    progressbar_front->hide();

    QString currentstatus=descriptiontitle->text();
    if(currentstatus.contains("发现")){
         descriptiontitle->setText(currentstatus+"检查取消!");
    }else{
         descriptiontitle->setText("检查已取消!");
    }
    descriptiontitle->adjustSize();

    checkingElapsedTime->hide();
    checkingElapsedTime->setText("");
    checkingElapsedTimer->stop();

    for (TabButton* btn : tabbuttonlist) {
        if (btn->taskstaus != TASK_PROBLEM)
            btn->changeToNoProblem();
    }
}

void CommonCheckWidget::updateCheckingElapsedTime()
{
    //qDebug() << "updateCheckingElapsedTime";
    unsigned int timedifference = (QDateTime::currentDateTime()).toTime_t() - checkingStartTime;
    checkingElapsedTime->setText("已用时：" + (QTime(0, 0)).addSecs(timedifference).toString("hh:mm:ss"));
}

QString CommonCheckWidget::getSupportedScene()
{
    return SCENE_COMMONCHECK;
}
QList<QString> CommonCheckWidget::getSupportedFunctions()
{
    return QList<QString>() << FUNC_HDINFO << FUNC_VMINFO << FUNC_NCINFO
                            << FUNC_NADEV << FUNC_PRIDEV << FUNC_BTDEV
                            << FUNC_PATCH << FUNC_SERVICE << FUNC_PROCESS
                            << FUNC_OTHERPDT << FUNC_SWITHTIME << FUNC_SECSOFT
                            << FUNC_USBCOMCHECK << FUNC_FILECOMCHECK
                            << FUNC_NETRECCOMCHECK << FUNC_TROJANCHECK;
}

void CommonCheckWidget::completerateUpdate(const int completerate, const QString& status)
{
   // qDebug() << "completerate::" << completerate;
    progressbar_front->move(-895 + 900 * completerate / 100, 147);
    description->setText(status);
    description->adjustSize();
    if(completerate ==100){
        startcheckbtn->show();
        cancelcheckbtn->hide();
        progressbar_background->hide();
        progressbar_front->hide();
        QString currentstatus=descriptiontitle->text();
        if(currentstatus.contains("发现")){
             descriptiontitle->setText(currentstatus+"检查完成!");
        }else{
             descriptiontitle->setText("检查完成!");
        }
        descriptiontitle->adjustSize();
        checkingElapsedTime->hide();
        checkingElapsedTime->setText("");
        checkingElapsedTimer->stop();
    }
}

void CommonCheckWidget::dataCountUpdate(const int totalproblems, const int totalinfomations)
{
    QString qs;
    if (totalproblems > 0)
        qs.append("已发现问题").append(QString::number(totalproblems)).append("条");
    if (qs.size() > 0 && totalinfomations > 0)
        qs.append(",");
    if (totalinfomations > 0)
        qs.append("发现信息").append(QString::number(totalinfomations)).append("条");
    if (qs.size() > 0)
        qs.append(".");
    if (qs.size() > 0)
        descriptiontitle->setText(qs);
    descriptiontitle->adjustSize();
}
