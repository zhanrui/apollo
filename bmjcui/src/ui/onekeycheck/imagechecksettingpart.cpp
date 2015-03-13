#include "imagechecksettingpart.h"

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

ImageCheckSettingPart::ImageCheckSettingPart(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initUI();
    initConnect();
}

ImageCheckSettingPart::~ImageCheckSettingPart()
{
}

void ImageCheckSettingPart::initUI()
{
    this->setFixedSize(707, 554);
    this->move(193, 46);

    int y = 80;

    QLabel* statusname = new QLabel(this);
    statusname->setText("图像检查");
    statusname->setObjectName("ic_statusname");
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
    QLabel* pathIcon = new QLabel(this);
    pathIcon->move(53, 184 - y);
    pathIcon->setPixmap(QPixmap(":image/imagecheck/pathIcon"));
    QLabel* pathDes = new QLabel(this);
    pathDes->move(82, 184 - y);
    pathDes->setText("检查路径");
    pathBrowserBtn = new StaticButton(":image/imagecheck/pathBrowserBtn", 3, this);
    pathBrowserBtn->move(575, 180 - y);
    QLabel* hline1 = new QLabel(this);
    hline1->move(0, 209 - y);
    hline1->setPixmap(QPixmap(":image/imagecheck/hline"));
    pathLE = new QLineEdit(this);
    pathLE->setPlaceholderText("请设置检查路径");
    pathLE->move(51, 218 - y);

    QLabel* keyWordIcon = new QLabel(this);
    keyWordIcon->move(53, 292 - y);
    keyWordIcon->setPixmap(QPixmap(":image/imagecheck/keyWordIcon"));
    QLabel* keyWordDes = new QLabel(this);
    keyWordDes->move(82, 292 - y);
    keyWordDes->setText("关键词");
    QLabel* keyWordLabel = new QLabel(this);
    keyWordLabel->move(560, 288 - y);
    keyWordLabel->setText("设置关键词");
    QLabel* hline2 = new QLabel(this);
    hline2->move(0, 316 - y);
    hline2->setPixmap(QPixmap(":image/imagecheck/hline"));
    keyWordCB = new QComboBox(this);
    keyWordCB->setEditable(true);
    keyWordCB->insertItem(0, " 秘密;机密;绝密");
    keyWordCB->setCurrentIndex(0);
    keyWordCB->move(51, 326 - y);

    QLabel* typeIcon = new QLabel(this);
    typeIcon->move(53, 403 - y);
    typeIcon->setPixmap(QPixmap(":image/imagecheck/typeIcon"));
    QLabel* typeDes = new QLabel(this);
    typeDes->move(82, 403 - y);
    typeDes->setText("文件类型");
    QLabel* typeLabel = new QLabel(this);
    typeLabel->move(757, 406 - y);
    typeLabel->setText("选择文件类型");
    QLabel* hline3 = new QLabel(this);
    hline3->move(0, 316 - y);
    hline3->setPixmap(QPixmap(":image/filecheck/hline"));
    typeLE = new QLineEdit(this);
    typeLE->setText(".bmp;.jpg;.png;.gif;.tif;.dib");
    typeLE->setPlaceholderText("请选择文件类型");
    typeLE->move(51, 440 - y);

    bmpCheck = new QCheckBox("bmp", this);
    bmpCheck->setCheckState(Qt::Checked);
    bmpCheck->move(177, 401 - y);
    jpgCheck = new QCheckBox("jpg", this);
    jpgCheck->setCheckState(Qt::Checked);
    jpgCheck->move(254, 401 - y);
    pngCheck = new QCheckBox("png", this);
    pngCheck->setCheckState(Qt::Checked);
    pngCheck->move(324, 401 - y);
    gifCheck = new QCheckBox("gif", this);
    gifCheck->setCheckState(Qt::Checked);
    gifCheck->move(390, 401 - y);
    tifCheck = new QCheckBox("tif", this);
    tifCheck->setCheckState(Qt::Checked);
    tifCheck->move(440, 401 - y);
    dibCheck = new QCheckBox("dib", this);
    dibCheck->setCheckState(Qt::Checked);
    dibCheck->move(516, 401 - y);
}
void ImageCheckSettingPart::initConnect()
{
    connect(pathBrowserBtn, &StaticButton::buttonClicked, this, &ImageCheckSettingPart::setFolderPath);

    connect(bmpCheck, &QCheckBox::stateChanged, this, &ImageCheckSettingPart::setFileType);
    connect(jpgCheck, &QCheckBox::stateChanged, this, &ImageCheckSettingPart::setFileType);
    connect(pngCheck, &QCheckBox::stateChanged, this, &ImageCheckSettingPart::setFileType);
    connect(gifCheck, &QCheckBox::stateChanged, this, &ImageCheckSettingPart::setFileType);
    connect(tifCheck, &QCheckBox::stateChanged, this, &ImageCheckSettingPart::setFileType);
    connect(dibCheck, &QCheckBox::stateChanged, this, &ImageCheckSettingPart::setFileType);

    connect(pathLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        if(!validateParameter()){
            statusbtn->changeToUnChecked();
        }else{
            statusbtn->changeToChecked();
        }
        emit setParameter("path", newValue.trimmed());
    });

    connect(typeLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        if(!validateParameter()){
            statusbtn->changeToUnChecked();
        }else{
            statusbtn->changeToChecked();
        }
          emit setParameter("type", newValue.trimmed());
    });

    connect(keyWordCB, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::activated), [=](const QString& newValue) {
        if(!validateParameter()){
            statusbtn->changeToUnChecked();
        }else{
            statusbtn->changeToChecked();
        }
        emit setParameter("keyword", newValue.trimmed());
    });
    connect(typeLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        if(!validateParameter()){
            statusbtn->changeToUnChecked();
        }else{
            statusbtn->changeToChecked();
        }
        emit setParameter("type", newValue.trimmed());
    });

    connect(statusbtn, &CheckButton::buttonClicked, [=]() {
        if(statusbtn->checkbtnstatus==DISABLED){
            if(validateParameter())
            statusbtn->changeToChecked();
        }else{
            statusbtn->changeToUnChecked();
        }
    });
}
bool ImageCheckSettingPart::validateParameter()
{
    if (keyWordCB->currentText().trimmed().isEmpty()) {
        keyWordCB->setFocus();
        return false;
    }
    if (pathLE->text().trimmed().isEmpty()) {
        pathLE->setFocus();
        return false;
    }
    if (typeLE->text().trimmed().isEmpty()) {
        typeLE->setFocus();
        return false;
    }
    return true;
}
void ImageCheckSettingPart::setFolderPath()
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

void ImageCheckSettingPart::setFileType()
{
    QString types;

    if (bmpCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".bmp");
    }
    if (jpgCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".jpg");
    }
    if (pngCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".png");
    }
    if (gifCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".gif");
    }
    if (tifCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".tif");
    }
    if (dibCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".dib");
    }

    typeLE->setText(types);
}
