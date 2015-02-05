#include "onekeycheckwidget.h"
#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/base/taskscene.h"
#include "src/ui/onekeycheck/tabbutton.h"
#include "src/ui/onekeycheck/mydelegate.h"
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


OneKeyCheckWidget::OneKeyCheckWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initModel();
    initUI();
    initConnect();
}

OneKeyCheckWidget::~OneKeyCheckWidget()
{
}

void OneKeyCheckWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);
    startcheckbtn = new StaticButton(":image/onekeycheck/startcheckbtn", 3, this);
    startcheckbtn->move(703, 60);
    cancelcheckbtn = new StaticButton(":image/onekeycheck/cancelcheckbtn", 3, this);
    cancelcheckbtn->move(739, 74);
    cancelcheckbtn->hide();
    onekeychecklogo = new QLabel(this);
    onekeychecklogo->setPixmap(QPixmap(":image/onekeycheck/onekeychecklogo"));
    onekeychecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("一键检查");
    descriptiontitle->setObjectName("descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("一般检查项目包含设备信息，以及基本安全信息");
    description->setObjectName("description");
    description->move(133, 109);

    progressbar_background = new QLabel(this);
    progressbar_background->setPixmap(QPixmap(":image/onekeycheck/progressbar_background"));
    progressbar_background->move(0, 147);
    progressbar_background->hide();

    progressbar_front = new QLabel(this);
    QMovie* movie = new QMovie(":image/onekeycheck/progressbar_front");
    movie->setParent(this);
    movie->start();
    progressbar_front->setMovie(movie);

    //progressbar_front->setPixmap(QPixmap(":image/onekeycheck/progressbar_front"));
    progressbar_front->move(-900, 147);
    progressbar_front->hide();

    checkingElapsedTime = new QLabel(this);
    checkingElapsedTime->move(584, 82);
    checkingElapsedTime->setObjectName("checkingelapsedtime");
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->hide();
    checkingElapsedTimer = new QTimer(this);

    //hline = new QLabel(this);
    //hline->setPixmap(QPixmap(":image/onekeycheck/hline"));
    //hline->move(0,153);

    QLabel* vline = new QLabel(this);
    vline->setPixmap(QPixmap(":image/onekeycheck/vline"));
    vline->move(192, 153);

    int start = 153;
    int between = 56;
    int x = 1;


    basicinfobtn    = new TabButton(":image/onekeycheck/leftbutton/basicinfobtn", this);
    basicinfobtn->move(x, start);
    basicinfobtn->setEnabled(false);

    deviceconnectionbtn = new TabButton(":image/onekeycheck/leftbutton/deviceconnectionbtn", this);
    deviceconnectionbtn->move(x, start + (between)*1);
    deviceconnectionbtn->setEnabled(false);

    netbrowserbtn = new TabButton(":image/onekeycheck/leftbutton/netbrowserbtn", this);
    netbrowserbtn->move(x, start + (between)*2);
    netbrowserbtn->setEnabled(false);
    systemsecuritybtn = new TabButton(":image/onekeycheck/leftbutton/systemsecuritybtn", this);
    systemsecuritybtn->move(x, start + (between)*3);
    systemsecuritybtn->setEnabled(false);
    securitythreatbtn = new TabButton(":image/onekeycheck/leftbutton/securitythreatbtn", this);
    securitythreatbtn->move(x, start + (between)*4);
    securitythreatbtn->setEnabled(false);
    usbcheckbtn = new TabButton(":image/onekeycheck/leftbutton/usbcheckbtn", this);
    usbcheckbtn->move(x, start + (between)*5);
    usbcheckbtn->setEnabled(false);
    filecheckbtn = new TabButton(":image/onekeycheck/leftbutton/filecheckbtn", this);
    filecheckbtn->move(x, start + (between)*6);
    filecheckbtn->setEnabled(false);
    tjcheckbtn = new TabButton(":image/onekeycheck/leftbutton/tjcheckbtn", this);
    tjcheckbtn->move(x, start + (between)*7);
    tjcheckbtn->setEnabled(false);

    for (int i = 0; i < 7; i++) {
        QLabel* hline = new QLabel(this);
        hline->setPixmap(QPixmap(":image/onekeycheck/hline"));
        hline->move(0, start + (between) * (i + 1));
    }

    tabbuttonlist = QList<TabButton*>();
    tabbuttonlist <<basicinfobtn<< deviceconnectionbtn << netbrowserbtn << systemsecuritybtn
                  << securitythreatbtn << usbcheckbtn << filecheckbtn << tjcheckbtn;

    checkresult = new QTableView(this);
    checkresult->setMinimumWidth(707);
    checkresult->setMinimumHeight(447);
    checkresult->move(193, 153);
    checkresult->verticalHeader()->hide();
    checkresult->horizontalHeader()->setHighlightSections(false);
    checkresult->horizontalHeader()->setFixedHeight(36);
    checkresult->setGridStyle(Qt::NoPen);

    checkresult->setShowGrid(false);
    checkresult->setEditTriggers(QAbstractItemView::NoEditTriggers);
    checkresult->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    checkresult->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    checkresult->setItemDelegate(new MyDelegate(checkresult));
    checkresult->setSelectionBehavior(QAbstractItemView::SelectRows);
    checkresult->setSelectionMode(QAbstractItemView::NoSelection);
    checkresult->setFrameShape(QFrame::NoFrame);

    checkresult->setModel(cpumodel);
    checkresult->hide();
}
void OneKeyCheckWidget::initConnect()
{
    connect(startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startCheck()));
    connect(cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(cancelCheck()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));
}
void OneKeyCheckWidget::initModel()
{
    cpumodel = new QStandardItemModel(this);
    QStandardItem* nameHead = new QStandardItem("姓名");
    QStandardItem* sexHead = new QStandardItem("性别");
    cpumodel->setHorizontalHeaderItem(0, nameHead);
    cpumodel->setHorizontalHeaderItem(1, sexHead);
}

void OneKeyCheckWidget::startCheck()
{
    startcheckbtn->hide();
    cancelcheckbtn->show();
    progressbar_background->show();
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

    for(TabButton* btn: tabbuttonlist){
        btn->setEnabled(true);
        btn->changeToRunning();
    }
}

void OneKeyCheckWidget::cancelCheck()
{
    startcheckbtn->show();
    cancelcheckbtn->hide();
    progressbar_background->hide();
    progressbar_front->hide();

    descriptiontitle->setText("检查已取消");
    descriptiontitle->adjustSize();
    description->setText("还未检查出可疑问题");
    description->adjustSize();
    checkingElapsedTime->hide();
    checkingElapsedTime->setText("");
    checkingElapsedTimer->stop();

    for(TabButton* btn: tabbuttonlist){
       if(btn->taskstaus != TASK_PROBLEM)
       btn->changeToNoProblem();
    }

}

void OneKeyCheckWidget::updateCheckingElapsedTime()
{
    //qDebug() << "updateCheckingElapsedTime";
    unsigned int timedifference = (QDateTime::currentDateTime()).toTime_t() - checkingStartTime;
    checkingElapsedTime->setText("已用时：" + (QTime(0, 0)).addSecs(timedifference).toString("hh:mm:ss"));
}

QString OneKeyCheckWidget::getSupportedScene()
{
    return SCENE_ONEKEYCHECK;
}
QList<QString> OneKeyCheckWidget::getSupportedFunctions()
{
    return QList<QString>() << FUNC_HDINFO << FUNC_VMINFO << FUNC_NCINFO
                            << FUNC_NADEV << FUNC_PRIDEV << FUNC_BTDEV
                            << FUNC_PATCH << FUNC_SERVICE << FUNC_PROCESS
                            << FUNC_OTHERPDT << FUNC_SWITHTIME << FUNC_SECSOFT
                            << FUNC_USBCOMCHECK << FUNC_FILECOMCHECK
                            << FUNC_NETRECCOMCHECK << FUNC_TROJANCHECK;
}

void OneKeyCheckWidget::completerateUpdate(const int completerate, const QString& status)
{
    qDebug() << completerate;
    progressbar_front->move(-895 + 900 * completerate / 100, 147);
    descriptiontitle->setText(status);
    descriptiontitle->adjustSize();
}

void OneKeyCheckWidget::dataCountUpdate(const int totalproblems, const int totalinfomations)
{
    QString qs;
    if (totalproblems > 0)
        qs.append("已发现问题").append(QString::number(totalproblems)).append("条");
    if (qs.size() > 0 && totalinfomations > 0)
        qs.append(",");
    if (totalinfomations > 0)
        qs.append("发现信息").append(totalinfomations).append("条");
    if (qs.size() > 0)
        qs.append(".");
    if (qs.size() > 0)
        description->setText(qs);
    description->adjustSize();
}
