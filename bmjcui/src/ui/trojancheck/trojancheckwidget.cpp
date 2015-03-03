#include "trojancheckwidget.h"

#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/base/commonwidget.h"
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
#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QtWidgets>

TrojanCheckWidget::TrojanCheckWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initUI();
    initConnect();
}

TrojanCheckWidget::~TrojanCheckWidget()
{
}

void TrojanCheckWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);
    startcheckbtn = new StaticButton(":image/common/startcheckbtn", 3, this);
    startcheckbtn->move(703, 60);
    cancelcheckbtn = new StaticButton(":image/common/cancelcheckbtn", 3, this);
    cancelcheckbtn->move(739, 74);
    cancelcheckbtn->hide();
    trojanchecklogo = new QLabel(this);
    trojanchecklogo->setPixmap(QPixmap(":image/trojancheck/trojanchecklogo"));
    trojanchecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("木马检查");
    descriptiontitle->setObjectName("tc_descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("查看用户终端是否存在威胁文档和网络武器");
    description->setObjectName("tc_description");
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

    //progressbar_front->setPixmap(QPixmap(":image/onekeycheck/progressbar_front"));
    progressbar_front->move(-900, 147);
    progressbar_front->hide();

    checkingElapsedTime = new QLabel(this);
    checkingElapsedTime->move(584, 82);
    checkingElapsedTime->setObjectName("tc_checkingelapsedtime");
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->hide();
    checkingElapsedTimer = new QTimer(this);

    settings = new CommonWidget(this);
    settings->setFixedSize(900, 447);
    settings->setObjectName("trojanchecksetting");
    int y = 153;
    settings->move(0, y);

    QLabel* typeIcon = new QLabel(settings);
    typeIcon->setPixmap(QPixmap(":image/trojancheck/typeIcon"));
    typeIcon->move(53, 184 - y);
    QLabel* typeDes = new QLabel(settings);
    typeDes->move(82, 184 - y);
    typeDes->setText("检查类型");
    QLabel* typeLabel = new QLabel(settings);
    typeLabel->move(0, 0);
    typeLabel->setText("选择检查类型");
    typeLabel->move(757, 180 - y);
    QLabel* hline1 = new QLabel(settings);
    hline1->move(0, 209 - y);
    hline1->setPixmap(QPixmap(":image/filecheck/hline"));
    typeLE = new QLineEdit(settings);
    typeLE->setText("威胁文档;网络武器");
    typeLE->setPlaceholderText("请选择检查类型");
    typeLE->move(51, 218 - y);
    typeLE->setReadOnly(true);

    threatdocumentCheck = new QCheckBox("威胁文档", settings);
    threatdocumentCheck->setCheckState(Qt::Checked);
    threatdocumentCheck->move(177, 181 - y);
    networkweaponCheck = new QCheckBox("网络武器", settings);
    networkweaponCheck->setCheckState(Qt::Checked);
    networkweaponCheck->move(277, 181 - y);

    QLabel* pathIcon = new QLabel(settings);
    pathIcon->move(53, 292 - y);
    pathIcon->setPixmap(QPixmap(":image/trojancheck/pathIcon"));
    QLabel* pathDes = new QLabel(settings);
    pathDes->move(82, 292 - y);
    pathDes->setText("检查路径");
    pathBrowserBtn = new StaticButton(":image/trojancheck/pathBrowserBtn", 3, settings);
    pathBrowserBtn->move(772, 288 - y);
    QLabel* hline2 = new QLabel(settings);
    hline2->move(0, 316 - y);
    hline2->setPixmap(QPixmap(":image/trojancheck/hline"));
    pathLE = new QLineEdit(settings);
    pathLE->setPlaceholderText("请设置检查路径");
    pathLE->move(51, 326 - y);
    checkResultBtn = new StaticButton(":image/trojancheck/checkResultBtn", 3, settings);
    checkResultBtn->move(738, 380 - y);
    checkResultBtn->hide();
}
void TrojanCheckWidget::initConnect()
{
    connect(startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startCheck()));
    connect(cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(cancelCheck()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));

    connect(pathBrowserBtn, &StaticButton::buttonClicked, this, &TrojanCheckWidget::setFolderPath);

    connect(threatdocumentCheck, &QCheckBox::stateChanged, this, &TrojanCheckWidget::setCheckType);
    connect(networkweaponCheck, &QCheckBox::stateChanged, this, &TrojanCheckWidget::setCheckType);

    connect(threatdocumentCheck, &QCheckBox::stateChanged, [=](int status) {
        if(status  == Qt::Unchecked){
            emit disableThreatDocument();
        }
        if(status  == Qt::Checked){
            emit enableThreatDocument();
        }
    });

    connect(networkweaponCheck, &QCheckBox::stateChanged, [=](int status) {
        if(status  == Qt::Unchecked){
            emit disableNetworkWeapon();
        }
        if(status  == Qt::Checked){
            emit enableNetworkWeapon();
        }
    });

    connect(pathLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        emit setParameter("path", newValue);
    });
    connect(typeLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        emit setParameter("type", newValue);
    });
}

void TrojanCheckWidget::setFolderPath()
{
    QString directory = QFileDialog::getExistingDirectory(this, "选择文件夹", QDir::currentPath());

    if (!directory.isEmpty()) {
        QString currentText = pathLE->text();
        if (currentText.trimmed().isEmpty()) {
            pathLE->setText(directory.trimmed());
        } else {
            pathLE->setText(currentText.trimmed().append(";").append(directory.trimmed()));
        }
    }
}

void TrojanCheckWidget::setCheckType()
{
    QString types;

    if (threatdocumentCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append("威胁文档");
    }
    if (networkweaponCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append("网络武器");
    }
    typeLE->setText(types);
}

void TrojanCheckWidget::startCheck()
{

    if (pathLE->text().isEmpty()) {
        pathLE->setFocus();
        return;
    }
    if (typeLE->text().isEmpty()) {
        typeLE->setFocus();
        return;
    }
    emit setParameter("path", pathLE->text());
    emit setParameter("type", typeLE->text());

    //     keyWordCB->set

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

    checkResultBtn->show();
    emit startCheckSig();
}

void TrojanCheckWidget::cancelCheck()
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
}

void TrojanCheckWidget::updateCheckingElapsedTime()
{
    //qDebug() << "updateCheckingElapsedTime";
    unsigned int timedifference = (QDateTime::currentDateTime()).toTime_t() - checkingStartTime;
    checkingElapsedTime->setText("已用时：" + (QTime(0, 0)).addSecs(timedifference).toString("hh:mm:ss"));
}

void TrojanCheckWidget::completerateUpdate(const int completerate, const QString& status)
{
    qDebug() << "completerate::" << completerate;
    progressbar_front->move(-895 + 900 * completerate / 100, 147);
    description->setText(status);
    description->adjustSize();
}

void TrojanCheckWidget::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
