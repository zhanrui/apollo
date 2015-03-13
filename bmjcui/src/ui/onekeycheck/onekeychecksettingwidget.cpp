#include "onekeychecksettingwidget.h"

#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/base/commonwidget.h"

#include "src/ui/onekeycheck/commonchecksettingpart.h"
#include "src/ui/onekeycheck/filechecksettingpart.h"
#include "src/ui/onekeycheck/trojanchecksettingpart.h"
#include "src/ui/onekeycheck/imagechecksettingpart.h"
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

OneKeyCheckSettingWidget::OneKeyCheckSettingWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initUI();
    initConnect();
    //Select File Check
    unSelectAllSettingBtn();
    unSelectAllSettingPart();
    fileCheckBtn->select();
    fileCheckSettingPart->show();
}

OneKeyCheckSettingWidget::~OneKeyCheckSettingWidget()
{
}

void OneKeyCheckSettingWidget::initUI()
{
    this->setFixedSize(900, 600);

    QLabel* title = new QLabel("一键检查——设置", this);
    title->adjustSize();
    title->move(900 / 2 - title->width() / 2, 17);

    QLabel* icon = new QLabel(this);
    icon->setPixmap(QPixmap(":image/onekeycheck/setting/logo"));
    icon->adjustSize();
    icon->move(900 / 2 - title->width() / 2 - 3 - icon->width(), 12);

    returnbtn = new StaticButton(":image/onekeycheck/setting/returnbtn", 3, this);
    returnbtn->move(0, 0);

    QWidget* leftbackground = new QWidget(this);
    leftbackground->move(0, 47);
    leftbackground->setFixedSize(192, 553);
    leftbackground->setObjectName("okcs_leftbackground");

    commonCheckSettingPart = new CommonCheckSettingPart(this);
    commonCheckSettingPart->hide();
    fileCheckSettingPart = new FileCheckSettingPart(this);
    fileCheckSettingPart->hide();
    trojanCheckSettingPart = new TrojanCheckSettingPart(this);
    trojanCheckSettingPart->hide();
    imageCheckSettingPart = new ImageCheckSettingPart(this);
    imageCheckSettingPart->hide();

    settingpartList << commonCheckSettingPart << fileCheckSettingPart
                    << trojanCheckSettingPart << imageCheckSettingPart;

    int start = 47;
    int between = 49;
    int x = 1;
    commonCheckBtn = new StaticButton(":image/onekeycheck/setting/leftbtn/commoncheckbtn", 3, this);
    commonCheckBtn->move(x, start);
    fileCheckBtn = new StaticButton(":image/onekeycheck/setting/leftbtn/filecheckbtn", 3, this);
    fileCheckBtn->move(x, start + (between)*1);
    trojanCheckBtn = new StaticButton(":image/onekeycheck/setting/leftbtn/tjcheckbtn", 3, this);
    trojanCheckBtn->move(x, start + (between)*2);
    imageCheckBtn = new StaticButton(":image/onekeycheck/setting/leftbtn/imagecheckbtn", 3, this);
    imageCheckBtn->move(x, start + (between)*3);

    for (int i = 0; i < 4; i++) {
        QLabel* hline = new QLabel(this);
        hline->setPixmap(QPixmap(":image/onekeycheck/setting/hline"));
        hline->move(0, start + (between) * (i + 1));
    }


    QLabel* vline = new QLabel(this);
    vline->setPixmap(QPixmap(":image/onekeycheck/setting/vline"));
    vline->move(192, 47);


    settingBtnList << commonCheckBtn << fileCheckBtn << trojanCheckBtn << imageCheckBtn;
}

void OneKeyCheckSettingWidget::initConnect()
{
    connect(commonCheckBtn, &StaticButton::buttonClicked,
            [=]() {
        unSelectAllSettingBtn();
        unSelectAllSettingPart();
        commonCheckBtn->select();
        commonCheckSettingPart->show();
    });
    connect(fileCheckBtn, &StaticButton::buttonClicked,
            [=]() {
        unSelectAllSettingBtn();
        unSelectAllSettingPart();
        fileCheckBtn->select();
        fileCheckSettingPart->show();
    });
    connect(trojanCheckBtn, &StaticButton::buttonClicked,
            [=]() {
        unSelectAllSettingBtn();
        unSelectAllSettingPart();
        trojanCheckBtn->select();
        trojanCheckSettingPart->show();
    });
    connect(imageCheckBtn, &StaticButton::buttonClicked,
            [=]() {
        unSelectAllSettingBtn();
        unSelectAllSettingPart();
        imageCheckBtn->select();
        imageCheckSettingPart->show();
    });
}

void OneKeyCheckSettingWidget::unSelectAllSettingBtn()
{
    for (StaticButton* settingBtn : settingBtnList) {
        settingBtn->unselect();
    }
}
void OneKeyCheckSettingWidget::unSelectAllSettingPart()
{
    for (QWidget* settingpart : settingpartList) {
        settingpart->hide();
    }
}
