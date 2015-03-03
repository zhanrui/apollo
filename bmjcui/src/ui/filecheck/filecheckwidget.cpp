#include "filecheckwidget.h"

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

FileCheckWidget::FileCheckWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{


    initUI();
    initConnect();
}

FileCheckWidget::~FileCheckWidget()
{
}

void FileCheckWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);
    startcheckbtn = new StaticButton(":image/common/startcheckbtn", 3, this);
    startcheckbtn->move(703, 60);
    cancelcheckbtn = new StaticButton(":image/common/cancelcheckbtn", 3, this);
    cancelcheckbtn->move(739, 74);
    cancelcheckbtn->hide();
    filechecklogo = new QLabel(this);
    filechecklogo->setPixmap(QPixmap(":image/filecheck/filechecklogo"));
    filechecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("文件检查");
    descriptiontitle->setObjectName("fc_descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("查看用户终端是否存在越级存储文件");
    description->setObjectName("fc_description");
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
    checkingElapsedTime->setObjectName("fc_checkingelapsedtime");
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->hide();
    checkingElapsedTimer = new QTimer(this);

    settings = new CommonWidget(this);
    settings->setFixedSize(900, 447);
    settings->setObjectName("filechecksetting");
    int y = 153;
    settings->move(0, y);

    QLabel* pathIcon = new QLabel(settings);
    pathIcon->move(53, 184 - y);
    pathIcon->setPixmap(QPixmap(":image/filecheck/pathIcon"));
    QLabel* pathDes = new QLabel(settings);
    pathDes->move(82, 184 - y);
    pathDes->setText("检查路径");
    pathBrowserBtn = new StaticButton(":image/filecheck/pathBrowserBtn", 3, settings);
    pathBrowserBtn->move(772, 180 - y);
    QLabel* hline1 = new QLabel(settings);
    hline1->move(0, 209 - y);
    hline1->setPixmap(QPixmap(":image/filecheck/hline"));
    pathLE = new QLineEdit(settings);
    pathLE->setPlaceholderText("请设置检查路径");
    pathLE->move(51, 218 - y);

    QLabel* keyWordIcon = new QLabel(settings);
    keyWordIcon->move(53, 292 - y);
    keyWordIcon->setPixmap(QPixmap(":image/filecheck/keyWordIcon"));
    QLabel* keyWordDes = new QLabel(settings);
    keyWordDes->move(82, 292 - y);
    keyWordDes->setText("关键词");
    QLabel* keyWordLabel = new QLabel(settings);
    keyWordLabel->move(773, 288 - y);
    keyWordLabel->setText("设置关键词");
    QLabel* hline2 = new QLabel(settings);
    hline2->move(0, 316 - y);
    hline2->setPixmap(QPixmap(":image/filecheck/hline"));
    keyWordCB = new QComboBox(settings);
    keyWordCB->setEditable(true);
    keyWordCB->insertItem(0, " 秘密;机密;绝密");
    keyWordCB->setCurrentIndex(0);
    keyWordCB->move(51, 326 - y);

    QLabel* typeIcon = new QLabel(settings);
    typeIcon->move(53, 403 - y);
    typeIcon->setPixmap(QPixmap(":image/filecheck/typeIcon"));
    QLabel* typeDes = new QLabel(settings);
    typeDes->move(82, 403 - y);
    typeDes->setText("文件类型");
    QLabel* typeLabel = new QLabel(settings);
    typeLabel->move(757, 406 - y);
    typeLabel->setText("选择文件类型");
    QLabel* hline3 = new QLabel(settings);
    hline3->move(0, 316 - y);
    hline3->setPixmap(QPixmap(":image/filecheck/hline"));
    typeLE = new QLineEdit(settings);
    typeLE->setText(".doc;.docx;.xls;.xlsx;.ppt;.pptx;.pdf;.wps;.et;.rar;.zip;.7z");
    typeLE->setPlaceholderText("请选择文件类型");
    typeLE->move(51, 440 - y);

    docCheck = new QCheckBox("doc(x)", settings);
    docCheck->setCheckState(Qt::Checked);
    docCheck->move(177, 401 - y);
    xlsCheck = new QCheckBox("xls(x)", settings);
    xlsCheck->setCheckState(Qt::Checked);
    xlsCheck->move(254, 401 - y);
    pptCheck = new QCheckBox("ppt(x)", settings);
    pptCheck->setCheckState(Qt::Checked);
    pptCheck->move(324, 401 - y);
    pdfCheck = new QCheckBox("pdf", settings);
    pdfCheck->setCheckState(Qt::Checked);
    pdfCheck->move(390, 401 - y);
    wpsCheck = new QCheckBox("wps/et", settings);
    wpsCheck->setCheckState(Qt::Checked);
    wpsCheck->move(440, 401 - y);
    zipCheck = new QCheckBox("rar/zip/7z", settings);
    zipCheck->setCheckState(Qt::Checked);
    zipCheck->move(516, 401 - y);

    checkResultBtn = new StaticButton(":image/filecheck/checkResultBtn", 3, settings);
    checkResultBtn->move(738,488-y);
    checkResultBtn->hide();


}
void FileCheckWidget::initConnect()
{
    connect(startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startCheck()));
    connect(cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(cancelCheck()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));

    connect(pathBrowserBtn, &StaticButton::buttonClicked, this, &FileCheckWidget::setFolderPath);

    connect(docCheck, &QCheckBox::stateChanged, this, &FileCheckWidget::setFileType);
    connect(xlsCheck, &QCheckBox::stateChanged, this, &FileCheckWidget::setFileType);
    connect(pptCheck, &QCheckBox::stateChanged, this, &FileCheckWidget::setFileType);
    connect(pdfCheck, &QCheckBox::stateChanged, this, &FileCheckWidget::setFileType);
    connect(wpsCheck, &QCheckBox::stateChanged, this, &FileCheckWidget::setFileType);
    connect(zipCheck, &QCheckBox::stateChanged, this, &FileCheckWidget::setFileType);

    connect(pathLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        emit setParameter("path", newValue);
    });
    connect(typeLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        emit setParameter("type", newValue);
    });
    connect(keyWordCB, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::activated), [=](const QString& newValue) {
        emit setParameter("keyword", newValue);
    });
}

void FileCheckWidget::setFolderPath()
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

void FileCheckWidget::setFileType()
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

bool FileCheckWidget::validateParameter(){
    if (keyWordCB->currentText().isEmpty()) {
        keyWordCB->setFocus();
        return false;
    }
    if (pathLE->text().isEmpty()) {
        pathLE->setFocus();
        return false;
    }
    if (typeLE->text().isEmpty()) {
        typeLE->setFocus();
        return false;
    }
    return true;
}

void FileCheckWidget::startCheck()
{

    if (keyWordCB->currentText().isEmpty()) {
        keyWordCB->setFocus();
        return;
    }
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
    emit setParameter("keyword", keyWordCB->currentText());


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

void FileCheckWidget::cancelCheck()
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

void FileCheckWidget::updateCheckingElapsedTime()
{
    //qDebug() << "updateCheckingElapsedTime";
    unsigned int timedifference = (QDateTime::currentDateTime()).toTime_t() - checkingStartTime;
    checkingElapsedTime->setText("已用时：" + (QTime(0, 0)).addSecs(timedifference).toString("hh:mm:ss"));
}

void FileCheckWidget::completerateUpdate(const int completerate, const QString& status)
{
    qDebug() << "completerate::" << completerate;
    progressbar_front->move(-895 + 900 * completerate / 100, 147);
    description->setText(status);
    description->adjustSize();
}

void FileCheckWidget::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
