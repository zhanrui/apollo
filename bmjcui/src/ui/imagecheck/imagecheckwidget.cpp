#include "imagecheckwidget.h"

#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/base/commonwidget.h"
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
#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QtWidgets>

ImageCheckWidget::ImageCheckWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{

    initUI();
    initConnect();
}

ImageCheckWidget::~ImageCheckWidget()
{
}

void ImageCheckWidget::initUI()
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
    filechecklogo->setPixmap(QPixmap(":image/imagecheck/imagechecklogo"));
    filechecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("图片检查");
    descriptiontitle->setObjectName("ic_descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("检查用户终端上是否存在敏感的图片文件");
    description->setObjectName("ic_description");
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
    checkingElapsedTime->setObjectName("ic_checkingelapsedtime");
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->hide();
    checkingElapsedTimer = new QTimer(this);

    settings = new CommonWidget(this);
    settings->setFixedSize(900, 447);
    settings->setObjectName("imagechecksetting");
    int y = 153;
    settings->move(0, y);

    QLabel* pathIcon = new QLabel(settings);
    pathIcon->move(53, 184 - y);
    pathIcon->setPixmap(QPixmap(":image/imagecheck/pathIcon"));
    QLabel* pathDes = new QLabel(settings);
    pathDes->move(82, 184 - y);
    pathDes->setText("检查路径");
    pathBrowserBtn = new StaticButton(":image/imagecheck/pathBrowserBtn", 3, settings);
    pathBrowserBtn->move(772, 180 - y);
    QLabel* hline1 = new QLabel(settings);
    hline1->move(0, 209 - y);
    hline1->setPixmap(QPixmap(":image/imagecheck/hline"));
    pathLE = new QLineEdit(settings);
    pathLE->setPlaceholderText("请设置检查路径");
    pathLE->move(51, 218 - y);

    QLabel* keyWordIcon = new QLabel(settings);
    keyWordIcon->move(53, 292 - y);
    keyWordIcon->setPixmap(QPixmap(":image/imagecheck/keyWordIcon"));
    QLabel* keyWordDes = new QLabel(settings);
    keyWordDes->move(82, 292 - y);
    keyWordDes->setText("关键词");
    QLabel* keyWordLabel = new QLabel(settings);
    keyWordLabel->move(773, 288 - y);
    keyWordLabel->setText("设置关键词");
    QLabel* hline2 = new QLabel(settings);
    hline2->move(0, 316 - y);
    hline2->setPixmap(QPixmap(":image/imagecheck/hline"));
    keyWordCB = new QComboBox(settings);
    keyWordCB->setEditable(true);
    keyWordCB->insertItem(0, " 秘密;机密;绝密");
    keyWordCB->setCurrentIndex(0);
    keyWordCB->move(51, 326 - y);

    QLabel* typeIcon = new QLabel(settings);
    typeIcon->move(53, 403 - y);
    typeIcon->setPixmap(QPixmap(":image/imagecheck/typeIcon"));
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
    typeLE->setText(".bmp;.jpg;.png;.gif;.tif;.dib");
    typeLE->setPlaceholderText("请选择文件类型");
    typeLE->move(51, 440 - y);

    bmpCheck = new QCheckBox("bmp", settings);
    bmpCheck->setCheckState(Qt::Checked);
    bmpCheck->move(177, 401 - y);
    jpgCheck = new QCheckBox("jpg", settings);
    jpgCheck->setCheckState(Qt::Checked);
    jpgCheck->move(254, 401 - y);
    pngCheck = new QCheckBox("png", settings);
    pngCheck->setCheckState(Qt::Checked);
    pngCheck->move(324, 401 - y);
    gifCheck = new QCheckBox("gif", settings);
    gifCheck->setCheckState(Qt::Checked);
    gifCheck->move(390, 401 - y);
    tifCheck = new QCheckBox("tif", settings);
    tifCheck->setCheckState(Qt::Checked);
    tifCheck->move(440, 401 - y);
    dibCheck = new QCheckBox("dib", settings);
    dibCheck->setCheckState(Qt::Checked);
    dibCheck->move(516, 401 - y);

    checkResultBtn = new StaticButton(":image/imagecheck/checkResultBtn", 3, settings);
    checkResultBtn->move(738, 488 - y);
    checkResultBtn->hide();
}
void ImageCheckWidget::initConnect()
{
    connect(startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startCheck()));
    connect(cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(cancelCheck()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));

    connect(pathBrowserBtn, &StaticButton::buttonClicked, this, &ImageCheckWidget::setFolderPath);

    connect(bmpCheck, &QCheckBox::stateChanged, this, &ImageCheckWidget::setFileType);
    connect(jpgCheck, &QCheckBox::stateChanged, this, &ImageCheckWidget::setFileType);
    connect(pngCheck, &QCheckBox::stateChanged, this, &ImageCheckWidget::setFileType);
    connect(gifCheck, &QCheckBox::stateChanged, this, &ImageCheckWidget::setFileType);
    connect(tifCheck, &QCheckBox::stateChanged, this, &ImageCheckWidget::setFileType);
    connect(dibCheck, &QCheckBox::stateChanged, this, &ImageCheckWidget::setFileType);

    connect(pathLE, &QLineEdit::textChanged, [=](const QString& newValue) {
        emit setParameter("path", newValue.trimmed());
    });

    connect(typeLE, &QLineEdit::textChanged, [=](const QString& newValue) {
          emit setParameter("type", newValue.trimmed());
    });

    connect(keyWordCB, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::activated), [=](const QString& newValue) {
        emit setParameter("keyword", newValue.trimmed());
    });
}

void ImageCheckWidget::setFolderPath()
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

void ImageCheckWidget::setFileType()
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

void ImageCheckWidget::startCheck()
{

    if (keyWordCB->currentText().trimmed().isEmpty()) {
        keyWordCB->setFocus();
        return;
    }
    if (pathLE->text().trimmed().isEmpty()) {
        pathLE->setFocus();
        return;
    }

    if (typeLE->text().trimmed().isEmpty()) {
        typeLE->setFocus();
        return;
    }

    emit setParameter("path", pathLE->text().trimmed());
    emit setParameter("type", typeLE->text().trimmed());
    emit setParameter("keyword", keyWordCB->currentText().trimmed());

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

void ImageCheckWidget::cancelCheck()
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
}

void ImageCheckWidget::updateCheckingElapsedTime()
{
    //qDebug() << "updateCheckingElapsedTime";
    unsigned int timedifference = (QDateTime::currentDateTime()).toTime_t() - checkingStartTime;
    checkingElapsedTime->setText("已用时：" + (QTime(0, 0)).addSecs(timedifference).toString("hh:mm:ss"));
}

void ImageCheckWidget::completerateUpdate(const int completerate, const QString& status)
{
    qDebug() << "completerate::" << completerate;
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

void ImageCheckWidget::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
