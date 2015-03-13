#include "trojanchecksettingpart.h"

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
#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QtWidgets>

TrojanCheckSettingPart::TrojanCheckSettingPart(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initUI();
    initConnect();
}

TrojanCheckSettingPart::~TrojanCheckSettingPart()
{
}

void TrojanCheckSettingPart::initUI()
{
    this->setFixedSize(707, 554);
    this->move(193, 46);

    int y = 80;

    QLabel* statusname = new QLabel(this);
    statusname->setText("木马检查");
    statusname->setObjectName("tc_statusname");
    statusname->move(53, 120 - y);

    statusbtn = new CheckButton(":image/onekeycheck/setting/statusbtn", this);
    statusbtn->changeToUnChecked();
    statusbtn->move(160, 115 - y);

    QLabel* hline0 = new QLabel(this);
    hline0->move(0, 160 - y);
    hline0->setPixmap(QPixmap(":image/filecheck/hline"));

    QLabel* description = new QLabel(this);
    description->setText("请先设置相关参数，再启用此功能。");
    description->setObjectName("fcs_description");
    description->move(53, 180 - y);

    y = 30;

    //    QLabel* typeIcon = new QLabel(this);
    //    typeIcon->setPixmap(QPixmap(":image/trojancheck/typeIcon"));
    //    typeIcon->move(53, 184 - y);
    //    QLabel* typeDes = new QLabel(this);
    //    typeDes->move(82, 184 - y);
    //    typeDes->setText("检查类型");
    //    QLabel* typeLabel = new QLabel(this);
    //    typeLabel->move(0, 0);
    //    typeLabel->setText("选择检查类型");
    //    typeLabel->move(757, 180 - y);
    //    QLabel* hline1 = new QLabel(this);
    //    hline1->move(0, 209 - y);
    //    hline1->setPixmap(QPixmap(":image/filecheck/hline"));
    //    typeLE = new QLineEdit(this);
    //    typeLE->setText("威胁文档;网络武器");
    //    typeLE->setPlaceholderText("请选择检查类型");
    //    typeLE->move(51, 218 - y);
    //    typeLE->setReadOnly(true);

    //    threatdocumentCheck = new QCheckBox("威胁文档", this);
    //    threatdocumentCheck->setCheckState(Qt::Checked);
    //    threatdocumentCheck->move(177, 181 - y);
    //    networkweaponCheck = new QCheckBox("网络武器", this);
    //    networkweaponCheck->setCheckState(Qt::Checked);
    //    networkweaponCheck->move(277, 181 - y);

    QLabel* pathIcon = new QLabel(this);
    pathIcon->move(53, 184 - y);
    pathIcon->setPixmap(QPixmap(":image/trojancheck/pathIcon"));
    QLabel* pathDes = new QLabel(this);
    pathDes->move(82, 184 - y);
    pathDes->setText("检查路径");
    pathBrowserBtn = new StaticButton(":image/trojancheck/pathBrowserBtn", 3, this);
    pathBrowserBtn->move(575, 180 - y);
    QLabel* hline2 = new QLabel(this);
    hline2->move(0, 208 - y);
    hline2->setPixmap(QPixmap(":image/trojancheck/hline"));
    pathLE = new QLineEdit(this);
    pathLE->setPlaceholderText("请设置检查路径");
    pathLE->move(51, 218 - y);
}
void TrojanCheckSettingPart::initConnect()
{
    connect(pathBrowserBtn, &StaticButton::buttonClicked, this, &TrojanCheckSettingPart::setFolderPath);

    //connect(threatdocumentCheck, &QCheckBox::stateChanged, this, &TrojanCheckSettingPart::setCheckType);
    //connect(networkweaponCheck, &QCheckBox::stateChanged, this, &TrojanCheckSettingPart::setCheckType);

    //connect(threatdocumentCheck, &QCheckBox::stateChanged, [=](int status) {
    //    if(status  == Qt::Unchecked){
    //         //emit disableThreatDocument();
    //    }
    //    if(status  == Qt::Checked){
    //         //emit enableThreatDocument();
    //     }
    // });

    //connect(networkweaponCheck, &QCheckBox::stateChanged, [=](int status) {
    //   if(status  == Qt::Unchecked){
    //        //emit disableNetworkWeapon();
    //    }
    //    if(status  == Qt::Checked){
    //        //emit enableNetworkWeapon();
    //    }
    //});

    connect(pathLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        if(!validateParameter()){
            statusbtn->changeToUnChecked();
        }else{
            statusbtn->changeToChecked();
        }
        emit setParameter("path", newValue.trimmed());
    });
    //connect(typeLE, &QLineEdit::textChanged, [=](const QString& newValue) {
    //    emit setParameter("type", newValue);
    //});
    connect(statusbtn, &CheckButton::buttonClicked, [=]() {
        if(statusbtn->checkbtnstatus==DISABLED){
            if(validateParameter())
            statusbtn->changeToChecked();
        }else{
            statusbtn->changeToUnChecked();
        }
    });
}

bool TrojanCheckSettingPart::validateParameter()
{
    if (pathLE->text().trimmed().isEmpty()) {
        pathLE->setFocus();
        return false;
    }
}

void TrojanCheckSettingPart::setFolderPath()
{
    QString directory = QFileDialog::getExistingDirectory(this, "选择文件夹", QDir::currentPath());

    if (!directory.isEmpty()) {
        pathLE->setText(directory.trimmed());
        //        QString currentText = pathLE->text();
        //        if (currentText.trimmed().isEmpty()) {
        //            pathLE->setText(directory.trimmed());
        //        } else {
        //            pathLE->setText(currentText.trimmed().append(";").append(directory.trimmed()));
        //        }
    }
}

void TrojanCheckSettingPart::setCheckType()
{
    //    QString types;

    //    if (threatdocumentCheck->checkState() == Qt::Checked) {
    //        if (!types.isEmpty()) {
    //            types.append(";");
    //        }
    //        types.append("威胁文档");
    //    }
    //    if (networkweaponCheck->checkState() == Qt::Checked) {
    //        if (!types.isEmpty()) {
    //            types.append(";");
    //        }
    //        types.append("网络武器");
    //    }
    //    typeLE->setText(types);
}
