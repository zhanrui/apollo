#include "onekeycheckmainwidget.h"

#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"

#include "src/ui/commoncheck/tabbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
#include "src/common/globals.h"
#include "src/common/common.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/onekeycheck/checkbutton.h"
#include "src/ui/onekeycheck/commonchecksettingpart.h"
#include "src/ui/onekeycheck/filechecksettingpart.h"
#include "src/ui/onekeycheck/imagechecksettingpart.h"
#include "src/ui/onekeycheck/trojanchecksettingpart.h"
#include "src/ui/onekeycheck/onekeychecksettingwidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
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

OneKeyCheckMainWidget::OneKeyCheckMainWidget(MainWindow* parent)
    : BaseStyleWidget(parent)
{
    mainwindow = parent;

    initModel();
    initUI();
    initConnect();
}

OneKeyCheckMainWidget::~OneKeyCheckMainWidget()
{
}

void OneKeyCheckMainWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);
    startcheckbtn = new StaticButton(":image/common/startcheckbtn", 3, this);
    startcheckbtn->move(703, 60);
    cancelcheckbtn = new StaticButton(":image/common/cancelcheckbtn", 3, this);
    cancelcheckbtn->move(739, 74);
    cancelcheckbtn->hide();
    onekeychecklogo = new QLabel(this);
    onekeychecklogo->setPixmap(QPixmap(":image/onekeycheck/main/onekeychecklogo"));
    onekeychecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("一键检查");
    descriptiontitle->setObjectName("okc_descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("根据设置检查相关项目");
    description->setObjectName("okc_description");
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
    checkingElapsedTime->setObjectName("okc_checkingelapsedtime");
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->hide();
    checkingElapsedTimer = new QTimer(this);

    //hline = new QLabel(this);
    //hline->setPixmap(QPixmap(":image/commoncheck/hline"));
    //hline->move(0,153);
    QWidget* leftbackground = new QWidget(this);
    leftbackground->move(0, 153);
    leftbackground->setFixedSize(192, 447);
    leftbackground->setObjectName("okc_leftbackground");

    QLabel* vline = new QLabel(this);
    vline->setPixmap(QPixmap(":image/onekeycheck/main/vline"));
    vline->move(192, 153);

    int start = 153;
    int between = 49;
    int x = 1;

    basicinfobtn = new TabButton(":image/onekeycheck/main/leftbutton/basicinfobtn", this);
    basicinfobtn->move(x, start);
    basicinfobtn->setEnabled(false);

    deviceconnectionbtn = new TabButton(":image/onekeycheck/main/leftbutton/deviceconnectionbtn", this);
    deviceconnectionbtn->move(x, start + (between)*1);
    deviceconnectionbtn->setEnabled(false);

    netbrowserbtn = new TabButton(":image/onekeycheck/main/leftbutton/netbrowserbtn", this);
    netbrowserbtn->move(x, start + (between)*2);
    netbrowserbtn->setEnabled(false);
    systemsecuritybtn = new TabButton(":image/onekeycheck/main/leftbutton/systemsecuritybtn", this);
    systemsecuritybtn->move(x, start + (between)*3);
    systemsecuritybtn->setEnabled(false);
    securitythreatbtn = new TabButton(":image/onekeycheck/main/leftbutton/securitythreatbtn", this);
    securitythreatbtn->move(x, start + (between)*4);
    securitythreatbtn->setEnabled(false);
    usbcheckbtn = new TabButton(":image/onekeycheck/main/leftbutton/usbcheckbtn", this);
    usbcheckbtn->move(x, start + (between)*5);
    usbcheckbtn->setEnabled(false);
    filecheckbtn = new TabButton(":image/onekeycheck/main/leftbutton/filecheckbtn", this);
    filecheckbtn->move(x, start + (between)*6);
    filecheckbtn->setEnabled(false);
    tjcheckbtn = new TabButton(":image/onekeycheck/main/leftbutton/tjcheckbtn", this);
    tjcheckbtn->move(x, start + (between)*7);
    tjcheckbtn->setEnabled(false);
    imagecheckbtn = new TabButton(":image/onekeycheck/main/leftbutton/imagecheckbtn", this);
    imagecheckbtn->move(x, start + (between)*8);
    imagecheckbtn->setEnabled(false);

    for (int i = 0; i < 8; i++) {
        QLabel* hline = new QLabel(this);
        hline->setPixmap(QPixmap(":image/commoncheck/hline"));
        hline->move(0, start + (between) * (i + 1));
    }

    tabbuttonlist = QList<TabButton*>();
    tabbuttonlist << basicinfobtn << deviceconnectionbtn << netbrowserbtn << systemsecuritybtn
                  << securitythreatbtn << usbcheckbtn << filecheckbtn << tjcheckbtn << imagecheckbtn;

    QLabel* mainshieldlogo = new QLabel(this);
    mainshieldlogo->setPixmap(QPixmap(":image/onekeycheck/main/mainshieldlogo"));
    mainshieldlogo->move(271, 252);

    QLabel* destitle = new QLabel(this);
    destitle->setObjectName("destitle");
    destitle->setText("一键检查");
    destitle->move(496, 259);

    QLabel* shorthline = new QLabel(this);
    shorthline->setPixmap(QPixmap(":image/commoncheck/description/shorthline"));
    shorthline->move(496, 290);

    QLabel* desdetail = new QLabel(this);
    desdetail->setObjectName("desdetail");
    desdetail->setText("根据您设置的选项，完成常规检查，文件检查，木马检查，图片检查 。");
    desdetail->move(496, 320);
    desdetail->setFixedWidth(300);
    desdetail->setWordWrap(true);

    settingbtn = new StaticButton(":image/onekeycheck/main/settingbtn", 3, this);
    settingbtn->move(608, 257);
}
void OneKeyCheckMainWidget::initConnect()
{
    connect(startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startCheck()));
    connect(cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(cancelCheck()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));
}
void OneKeyCheckMainWidget::initModel()
{
}

void OneKeyCheckMainWidget::startCheck()
{
    OneKeyCheckSettingWidget* settingWidget = mainwindow->oneKeyCheckSettingWidget;
    if (settingWidget->commonCheckSettingPart->basicinfobtn->checkbtnstatus == ENABLED) {

        basicinfobtn->setEnabled(true);
        basicinfobtn->changeToRunning();
          emit settingWidget->commonCheckSettingPart->enableBasicInfo();
    } else {
        basicinfobtn->setEnabled(false);
        basicinfobtn->changeToDefault();
          emit settingWidget->commonCheckSettingPart->disableBasicInfo();
    }
    if (settingWidget->commonCheckSettingPart->deviceconnectionbtn->checkbtnstatus == ENABLED) {

        deviceconnectionbtn->setEnabled(true);
        deviceconnectionbtn->changeToRunning();
        emit settingWidget->commonCheckSettingPart->enableDeviceConnection();
    } else {
        deviceconnectionbtn->setEnabled(false);
        deviceconnectionbtn->changeToDefault();
        emit settingWidget->commonCheckSettingPart->disableDeviceConnection();
    }
    if (settingWidget->commonCheckSettingPart->netrecordbtn->checkbtnstatus == ENABLED) {
        netbrowserbtn->setEnabled(true);
        netbrowserbtn->changeToRunning();
        emit settingWidget->commonCheckSettingPart->enableNetBrowser();
    } else {
        netbrowserbtn->setEnabled(false);
        netbrowserbtn->changeToDefault();
        emit settingWidget->commonCheckSettingPart->disableNetBrowser();
    }

    if (settingWidget->commonCheckSettingPart->systemsecuritybtn->checkbtnstatus == ENABLED) {
        systemsecuritybtn->setEnabled(true);
        systemsecuritybtn->changeToRunning();
        emit settingWidget->commonCheckSettingPart->enableSystemSecurity();
    } else {
        systemsecuritybtn->setEnabled(false);
        systemsecuritybtn->changeToDefault();
        emit settingWidget->commonCheckSettingPart->disableSystemSecurity();
    }
    if (settingWidget->commonCheckSettingPart->securitythreatbtn->checkbtnstatus == ENABLED) {
        securitythreatbtn->setEnabled(true);
        securitythreatbtn->changeToRunning();
        emit settingWidget->commonCheckSettingPart->enableSecurityThreat();
    } else {
        securitythreatbtn->setEnabled(false);
        securitythreatbtn->changeToDefault();
        emit settingWidget->commonCheckSettingPart->disableSecurityThreat();
    }

    if (settingWidget->commonCheckSettingPart->usbrecordbtn->checkbtnstatus == ENABLED) {
        usbcheckbtn->setEnabled(true);
        usbcheckbtn->changeToRunning();
         emit settingWidget->commonCheckSettingPart->enableUsbCheck();
    } else {
        usbcheckbtn->setEnabled(false);
        usbcheckbtn->changeToDefault();
        emit settingWidget->commonCheckSettingPart->disableUsbCheck();
    }

    if (settingWidget->fileCheckSettingPart->statusbtn->checkbtnstatus == ENABLED) {
        filecheckbtn->setEnabled(true);
        filecheckbtn->changeToRunning();
        emit settingWidget->fileCheckSettingPart->enableFileCheck();
        emit settingWidget->fileCheckSettingPart->setParameter("path", settingWidget->fileCheckSettingPart->pathLE->text().trimmed());
        emit settingWidget->fileCheckSettingPart->setParameter("type", settingWidget->fileCheckSettingPart->typeLE->text().trimmed());
        emit settingWidget->fileCheckSettingPart->setParameter("keyword", settingWidget->fileCheckSettingPart->keyWordCB->currentText().trimmed());
    } else {
        filecheckbtn->setEnabled(false);
        filecheckbtn->changeToDefault();
         emit settingWidget->fileCheckSettingPart->disableFileCheck();
    }
    if (settingWidget->trojanCheckSettingPart->statusbtn->checkbtnstatus == ENABLED) {
        tjcheckbtn->setEnabled(true);
        tjcheckbtn->changeToRunning();
        emit settingWidget->trojanCheckSettingPart->enableThreatDocument();
        emit settingWidget->trojanCheckSettingPart->setParameter("path", settingWidget->trojanCheckSettingPart->pathLE->text().trimmed());

    } else {
        tjcheckbtn->setEnabled(false);
        tjcheckbtn->changeToDefault();
        emit settingWidget->trojanCheckSettingPart->disableThreatDocument();
    }
    if (settingWidget->imageCheckSettingPart->statusbtn->checkbtnstatus == ENABLED) {
        imagecheckbtn->setEnabled(true);
        imagecheckbtn->changeToRunning();
        emit settingWidget->imageCheckSettingPart->enableImageCheck();
        emit settingWidget->imageCheckSettingPart->setParameter("path", settingWidget->imageCheckSettingPart->pathLE->text().trimmed());
        emit settingWidget->imageCheckSettingPart->setParameter("type", settingWidget->imageCheckSettingPart->typeLE->text().trimmed());
        emit settingWidget->imageCheckSettingPart->setParameter("keyword", settingWidget->imageCheckSettingPart->keyWordCB->currentText().trimmed());

    } else {
        imagecheckbtn->setEnabled(false);
        imagecheckbtn->changeToDefault();
        emit settingWidget->imageCheckSettingPart->disableImageCheck();
    }

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

    //for (TabButton* btn : tabbuttonlist) {
    //    btn->setEnabled(true);
    //    btn->changeToRunning();
    //}
}

void OneKeyCheckMainWidget::cancelCheck()
{
    startcheckbtn->show();
    cancelcheckbtn->hide();
    progressbar_background->hide();
    progressbar_front->hide();

    QString currentstatus = descriptiontitle->text();
    if (currentstatus.contains("发现")) {
        descriptiontitle->setText(currentstatus + "检查取消!");
    } else {
        descriptiontitle->setText("检查已取消!");
    }
    descriptiontitle->adjustSize();

    checkingElapsedTime->hide();
    checkingElapsedTime->setText("");
    checkingElapsedTimer->stop();

    for (TabButton* btn : tabbuttonlist) {
        if (btn->taskstaus != TASK_PROBLEM && btn->isEnabled())
            btn->changeToNoProblem();
    }
}

void OneKeyCheckMainWidget::updateCheckingElapsedTime()
{
    //qDebug() << "updateCheckingElapsedTime";
    unsigned int timedifference = (QDateTime::currentDateTime()).toTime_t() - checkingStartTime;
    checkingElapsedTime->setText("已用时：" + (QTime(0, 0)).addSecs(timedifference).toString("hh:mm:ss"));
}

void OneKeyCheckMainWidget::completerateUpdate(const int completerate, const QString& status)
{
    // qDebug() << "completerate::" << completerate;
    progressbar_front->move(-895 + 900 * completerate / 100, 147);
    description->setText(status);
    description->adjustSize();
    if (completerate == 100) {
        startcheckbtn->show();
        cancelcheckbtn->hide();
        progressbar_background->hide();
        progressbar_front->hide();
        QString currentstatus = descriptiontitle->text();
        if (currentstatus.contains("发现")) {
            descriptiontitle->setText(currentstatus + "检查完成!");
        } else {
            descriptiontitle->setText("检查完成!");
        }
        descriptiontitle->adjustSize();
        checkingElapsedTime->hide();
        checkingElapsedTime->setText("");
        checkingElapsedTimer->stop();
    }
}

void OneKeyCheckMainWidget::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
