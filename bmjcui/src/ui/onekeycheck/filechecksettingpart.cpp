#include "filechecksettingpart.h"

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

FileCheckSettingPart::FileCheckSettingPart(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initUI();
    initConnect();
}

FileCheckSettingPart::~FileCheckSettingPart()
{
}

void FileCheckSettingPart::initUI()
{
    this->setFixedSize(707, 554);
    this->move(193, 46);

    int y = 80;

    QLabel* statusname = new QLabel(this);
    statusname->setText("文件检查");
    statusname->setObjectName("fc_statusname");
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
    pathIcon->move(53, 184 - y);
    pathIcon->setPixmap(QPixmap(":image/filecheck/pathIcon"));
    QLabel* pathDes = new QLabel(this);
    pathDes->move(82, 184 - y);
    pathDes->setText("检查路径");
    pathBrowserBtn = new StaticButton(":image/filecheck/pathBrowserBtn", 3, this);
    pathBrowserBtn->move(575, 180 - y);
    QLabel* hline1 = new QLabel(this);
    hline1->move(0, 209 - y);
    hline1->setPixmap(QPixmap(":image/filecheck/hline"));
    pathLE = new QLineEdit(this);
    pathLE->setPlaceholderText("请设置检查路径");
    pathLE->move(51, 218 - y);

    QLabel* keyWordIcon = new QLabel(this);
    keyWordIcon->move(53, 292 - y);
    keyWordIcon->setPixmap(QPixmap(":image/filecheck/keyWordIcon"));
    QLabel* keyWordDes = new QLabel(this);
    keyWordDes->move(82, 292 - y);
    keyWordDes->setText("关键词");
    QLabel* keyWordLabel = new QLabel(this);
    keyWordLabel->move(576, 288 - y);
    keyWordLabel->setText("设置关键词");
    QLabel* hline2 = new QLabel(this);
    hline2->move(0, 316 - y);
    hline2->setPixmap(QPixmap(":image/filecheck/hline"));
    keyWordCB = new QComboBox(this);
    keyWordCB->setEditable(true);
    keyWordCB->insertItem(0, " 秘密;机密;绝密");
    keyWordCB->setCurrentIndex(0);
    keyWordCB->move(51, 326 - y);

    QLabel* typeIcon = new QLabel(this);
    typeIcon->move(53, 403 - y);
    typeIcon->setPixmap(QPixmap(":image/filecheck/typeIcon"));
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
    typeLE->setText(".doc;.docx;.xls;.xlsx;.ppt;.pptx;.pdf;.wps;.et;.rar;.zip;.7z");
    typeLE->setPlaceholderText("请选择文件类型");
    typeLE->move(51, 440 - y);

    docCheck = new QCheckBox("doc(x)", this);
    docCheck->setCheckState(Qt::Checked);
    docCheck->move(177, 401 - y);
    xlsCheck = new QCheckBox("xls(x)", this);
    xlsCheck->setCheckState(Qt::Checked);
    xlsCheck->move(254, 401 - y);
    pptCheck = new QCheckBox("ppt(x)", this);
    pptCheck->setCheckState(Qt::Checked);
    pptCheck->move(324, 401 - y);
    pdfCheck = new QCheckBox("pdf", this);
    pdfCheck->setCheckState(Qt::Checked);
    pdfCheck->move(390, 401 - y);
    wpsCheck = new QCheckBox("wps/et", this);
    wpsCheck->setCheckState(Qt::Checked);
    wpsCheck->move(440, 401 - y);
    zipCheck = new QCheckBox("rar/zip/7z", this);
    zipCheck->setCheckState(Qt::Checked);
    zipCheck->move(516, 401 - y);
}
void FileCheckSettingPart::initConnect()
{

    connect(pathBrowserBtn, &StaticButton::buttonClicked, this, &FileCheckSettingPart::setFolderPath);

    connect(docCheck, &QCheckBox::stateChanged, this, &FileCheckSettingPart::setFileType);
    connect(xlsCheck, &QCheckBox::stateChanged, this, &FileCheckSettingPart::setFileType);
    connect(pptCheck, &QCheckBox::stateChanged, this, &FileCheckSettingPart::setFileType);
    connect(pdfCheck, &QCheckBox::stateChanged, this, &FileCheckSettingPart::setFileType);
    connect(wpsCheck, &QCheckBox::stateChanged, this, &FileCheckSettingPart::setFileType);
    connect(zipCheck, &QCheckBox::stateChanged, this, &FileCheckSettingPart::setFileType);

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
    connect(keyWordCB, &QComboBox::editTextChanged, [=](const QString& newValue) {
        if(!validateParameter()){
            statusbtn->changeToUnChecked();
        }else{
            statusbtn->changeToChecked();
        }
        emit setParameter("keyword", newValue.trimmed());
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

bool FileCheckSettingPart::validateParameter()
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
void FileCheckSettingPart::setFolderPath()
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

void FileCheckSettingPart::setFileType()
{
    QString types;

    if (docCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".doc;.docx");
    }
    if (xlsCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".xls;.xlsx");
    }
    if (pptCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".ppt;.pptx");
    }
    if (pdfCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".pdf");
    }
    if (wpsCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".wps;.ef");
    }
    if (zipCheck->checkState() == Qt::Checked) {
        if (!types.isEmpty()) {
            types.append(";");
        }
        types.append(".rar;.zip;.7z");
    }

    typeLE->setText(types);
}
