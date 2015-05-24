#include "checkreportwidget.h"

#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/base/commonwidget.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/commoncheck/tabbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
#include "src/common/globals.h"
#include "src/common/common.h"
#include "src/ui/detailreport/basicinforpt.h"
#include "src/ui/detailreport/deviceconnectrpt.h"
#include "src/ui/detailreport/netrecordcommonrpt.h"
#include "src/ui/detailreport/basereport.h"
#include "src/ui/detailreport/systemsecurityrpt.h"
#include "src/ui/detailreport/securitythreatrpt.h"
#include "src/ui/detailreport/usbrecordcommonrpt.h"
#include "src/ui/detailreport/filecheckcommonrpt.h"
#include "src/ui/detailreport/trojancheckrpt.h"
#include "src/ui/detailreport/imagecheckrpt.h"
#include "src/ui/detailreport/usbrecorddeeprpt.h"
#include "src/ui/detailreport/netrecorddeeprpt.h"
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

CheckReportWidget::CheckReportWidget(MainWindow* parent)
    : BaseStyleWidget(parent)
{

    mainWindow = parent;
    initUI();
    initConnect();
}

CheckReportWidget::~CheckReportWidget()
{
}

void CheckReportWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);
    startcheckbtn = new StaticButton(":image/checkreport/createReportBtn", 3, this);
    startcheckbtn->move(703, 60);
    cancelcheckbtn = new StaticButton(":image/common/cancelcheckbtn", 3, this);
    cancelcheckbtn->move(739, 74);
    cancelcheckbtn->hide();
    filechecklogo = new QLabel(this);
    filechecklogo->setPixmap(QPixmap(":image/checkreport/checkreportlogo"));
    filechecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("检查报告");
    descriptiontitle->setObjectName("cr_descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("用于创建检查报告");
    description->setObjectName("cr_description");
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
    checkingElapsedTime->move(560, 82);
    checkingElapsedTime->setObjectName("cr_checkingelapsedtime");
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->hide();
    checkingElapsedTimer = new QTimer(this);

    settings = new CommonWidget(this);
    settings->setFixedSize(900, 447);
    settings->setObjectName("checkreportsetting");
    int y = 153;
    settings->move(0, y);

    QLabel* typeIcon = new QLabel(settings);
    typeIcon->move(53, 184 - y);
    typeIcon->setPixmap(QPixmap(":image/checkreport/typeIcon"));
    QLabel* typeDes = new QLabel(settings);
    typeDes->move(82, 184 - y);
    typeDes->setText("报告内容");
    QLabel* typeLabel = new QLabel(settings);
    typeLabel->move(757, 180 - y);
    typeLabel->setText("选择报告内容");
    QLabel* hline1 = new QLabel(settings);
    hline1->move(0, 209 - y);
    hline1->setPixmap(QPixmap(":image/checkreport/hline"));
    onekeyCheck = new QCheckBox("一键检查", settings);
    onekeyCheck->setCheckState(Qt::Unchecked);
    onekeyCheck->move(51, 222 - y);
    commonCheck = new QCheckBox("常规检查", settings);
    commonCheck->setCheckState(Qt::Checked);
    commonCheck->move(151, 222 - y);
    //deepCheck = new QCheckBox("深度检查", settings);
    //deepCheck->setCheckState(Qt::Checked);
    //deepCheck->move(251, 222 - y);
    fileCheck = new QCheckBox("文件检查", settings);
    fileCheck->setCheckState(Qt::Checked);
    fileCheck->move(251, 222 - y);
    tjCheck = new QCheckBox("木马检查", settings);
    tjCheck->setCheckState(Qt::Checked);
    tjCheck->move(351, 222 - y);
    imageCheck = new QCheckBox("图片检查", settings);
    imageCheck->setCheckState(Qt::Checked);
    imageCheck->move(451, 222 - y);

    QLabel* pathIcon = new QLabel(settings);
    pathIcon->move(53, 292 - y);
    pathIcon->setPixmap(QPixmap(":image/checkreport/pathIcon"));
    QLabel* pathDes = new QLabel(settings);
    pathDes->move(82, 292 - y);
    pathDes->setText("文件保存路径");
    pathBrowserBtn = new StaticButton(":image/checkreport/pathBrowserBtn", 3, settings);
    pathBrowserBtn->move(772, 288 - y);
    QLabel* hline2 = new QLabel(settings);
    hline2->move(0, 316 - y);
    hline2->setPixmap(QPixmap(":image/checkreport/hline"));
    pathLE = new QLineEdit(settings);
    pathLE->setPlaceholderText("请设置路径");
    pathLE->move(51, 326 - y);
    pathLE->setText("/tmp");

    QLabel* nameIcon = new QLabel(settings);
    nameIcon->move(53, 403 - y);
    nameIcon->setPixmap(QPixmap(":image/checkreport/nameIcon"));
    QLabel* nameDes = new QLabel(settings);
    nameDes->move(82, 403 - y);
    nameDes->setText("文件名");
    QLabel* nameLabel = new QLabel(settings);
    nameLabel->move(773, 406 - y);
    nameLabel->setText("设置文件名");
    QLabel* hline3 = new QLabel(settings);
    hline3->move(0, 316 - y);
    hline3->setPixmap(QPixmap(":image/checkreport/hline"));
    nameLE = new QLineEdit(settings);
    nameLE->setPlaceholderText("请设置文件名");
    nameLE->move(51, 440 - y);
    nameLE->setText("检测报告yyMMddhhmmss");

    checkResultBtn = new StaticButton(":image/checkreport/checkResultBtn", 3, settings);
    checkResultBtn->move(738, 488 - y);
    checkResultBtn->hide();
}
void CheckReportWidget::initConnect()
{
    connect(startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startCheck()));
    connect(cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(cancelCheck()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));
    connect(checkingElapsedTimer, SIGNAL(timeout()), this, SLOT(updateCheckingElapsedTime()));

    connect(pathBrowserBtn, &StaticButton::buttonClicked, this, &CheckReportWidget::setFolderPath);

    //connect(commonCheck, &QCheckBox::stateChanged, this, &CheckReportWidget::setFileType);
    //connect(deepCheck, &QCheckBox::stateChanged, this, &CheckReportWidget::setFileType);
    //connect(fileCheck, &QCheckBox::stateChanged, this, &CheckReportWidget::setFileType);
    //connect(tjCheck, &QCheckBox::stateChanged, this, &CheckReportWidget::setFileType);
    //connect(imageCheck, &QCheckBox::stateChanged, this, &CheckReportWidget::setFileType);
    // connect(zipCheck, &QCheckBox::stateChanged, this, &CheckReportWidget::setFileType);

    //connect(pathLE, &QLineEdit::textChanged, [=](const QString& newValue) {
    //    emit setParameter("path", newValue);
    //});
    //connect(typeLE, &QLineEdit::textChanged, [=](const QString& newValue) {
    //    emit setParameter("type", newValue);
    // });
    //connect(keyWordCB, static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::activated), [=](const QString& newValue) {
    //    emit setParameter("keyword", newValue);
    //});
}

void CheckReportWidget::setFolderPath()
{
    QString directory = QFileDialog::getExistingDirectory(this, "选择文件夹", QDir::currentPath());
    pathLE->setText(directory.trimmed());
}

void CheckReportWidget::startCheck()
{

    //if (typeLE->text().isEmpty()) {
    //    typeLE->setFocus();
    //    return;
    //}
    if (pathLE->text().isEmpty()) {
        pathLE->setFocus();
        return;
    }
    if (nameLE->text().isEmpty()) {
        nameLE->setFocus();
        return;
    }

    //emit setParameter("path", pathLE->text());
    //emit setParameter("type", typeLE->text());
    //emit setParameter("keyword", keyWordCB->currentText());

    //     keyWordCB->set

    //startcheckbtn->hide();
    //cancelcheckbtn->show();
    progressbar_background->show();
    progressbar_front->move(-900, 147);
    progressbar_front->show();
    descriptiontitle->setText("正在创建报告。。。");
    descriptiontitle->adjustSize();
    description->setText("还未检查出可疑问题");
    description->adjustSize();

    checkingElapsedTime->show();
    checkingElapsedTime->setText("已用时：00:00:00");
    checkingElapsedTime->adjustSize();
    checkingStartTime = (QDateTime::currentDateTime()).toTime_t();
    checkingElapsedTimer->start(1000);
    checkResultBtn->show();
    QString filefullpath;
    filefullpath.append(pathLE->text());
    filefullpath.append("/");
    QDateTime time = QDateTime::currentDateTime();
    filefullpath.append( time.toString(nameLE->text().trimmed()));
    filefullpath.append( ".pdf");
    emit startCreateSig(filefullpath, getHtml());
}

QString CheckReportWidget::getHtml()
{
    QString html;
    html += "<html>";
    html += "<head>";
    getCssString(html);
    html += "</head>";
    html += "<body>";
    html += "<div  align='center' style='font-weight:bold;font-size:250px' >LINUX保密检查报告</div>";
    html += "<p/><p/><p/>";

    if (onekeyCheck->checkState() == Qt::Checked) {
        getSubTitleString(html, "一键检查");
        getSectionTitleString(html, "基本信息");
        getTableString(mainWindow->okcBasicInfoRpt->osInfoMod, html, "操作系统");
        getTableString(mainWindow->okcBasicInfoRpt->cpuInfoMod, html, "CPU信息");
        getTableString(mainWindow->okcBasicInfoRpt->biosInfoMod, html, "BIOS信息");
        getTableString(mainWindow->okcBasicInfoRpt->motherBoardInfoMod, html, "主板信息");
        getTableString(mainWindow->okcBasicInfoRpt->memoryInfoMod, html, "内存信息");
        getTableString(mainWindow->okcBasicInfoRpt->graphicsCardInfoMod, html, "显卡信息");
        getSectionTitleString(html, "设备连接");
        getTableString(mainWindow->okcDeviceConnectRpt->hardDiskInfoMod, html, "硬盘信息");
        getTableString(mainWindow->okcDeviceConnectRpt->virtualMachineInfoMod, html, "虚拟机信息");
        getTableString(mainWindow->okcDeviceConnectRpt->netConfigMod, html, "网络配置");
        getTableString(mainWindow->okcDeviceConnectRpt->adapterDeviceMod, html, "网卡设备");
        getTableString(mainWindow->okcDeviceConnectRpt->printDeviceMod, html, "打印机设备");
        getTableString(mainWindow->okcDeviceConnectRpt->blueToothDeviceMod, html, "蓝牙设备");
        getSectionTitleString(html, "安全威胁");
        getTableString(mainWindow->okcSecurityThreatRpt->securityPolicyMod, html, "安全策略");
        getTableString(mainWindow->okcSecurityThreatRpt->openPortMod, html, "开放端口");
        getTableString(mainWindow->okcSecurityThreatRpt->sharingInfoMod, html, "共享信息");
        getTableString(mainWindow->okcSecurityThreatRpt->networkSoftwareMod, html, "网络软件");
        getTableString(mainWindow->okcSecurityThreatRpt->groupInfoMod, html, "组信息");
        getTableString(mainWindow->okcSecurityThreatRpt->userInfoMod, html, "用户信息");
        getTableString(mainWindow->okcSecurityThreatRpt->databaseInfoMod, html, "数据库信息");
        getTableString(mainWindow->okcSecurityThreatRpt->eventLogMod, html, "事件日志");
        getTableString(mainWindow->okcSecurityThreatRpt->userAuthenticationMod, html, "用户认证");
        getSectionTitleString(html, "系统安全");
        getTableString(mainWindow->okcSystemSecurityRpt->patchNotInstalledMod, html, "未安装补丁");
        getTableString(mainWindow->okcSystemSecurityRpt->systemServiceMod, html, "系统服务");
        getTableString(mainWindow->okcSystemSecurityRpt->systemProcessMod, html, "系统进程");
        getTableString(mainWindow->okcSystemSecurityRpt->evenProductMod, html, "操作系统");
        getTableString(mainWindow->okcSystemSecurityRpt->timeSwitchMachineMod, html, "开关机时间");
        getTableString(mainWindow->okcSystemSecurityRpt->securitySoftwareMod, html, "安全软件");
        getSectionTitleString(html, "网络记录");
        getTableString(mainWindow->okcNetRecordRpt->netRecordsMod, html, "网络记录常规信息");
        getSectionTitleString(html, "USB记录");
        getTableString(mainWindow->okcUsbRecordCommonRpt->usbRecordsMod, html, "USB记录常规信息");
        getSectionTitleString(html, "文件检查");
        getTableString(mainWindow->okcFileCheckCommonRpt->fileRoutineCheckMod, html, "文件检查信息");
        getSectionTitleString(html, "木马检查");
        getTableString(mainWindow->okcTrojanCheckRpt->threatDocumentMod, html, "威胁文档");
        //getTableString(mainWindow->okcTrojanCheckRpt->networkWeaponMod, html, "网络武器");
        getSectionTitleString(html, "图片检查");
        getTableString(mainWindow->okcImageCheckRpt->imageCheckMod, html, "图片检查信息");
    }

    if (commonCheck->checkState() == Qt::Checked) {
        getSubTitleString(html, "常规检查");
        getSectionTitleString(html, "基本信息");
        getTableString(mainWindow->ccBasicInfoRpt->osInfoMod, html, "操作系统");
        getTableString(mainWindow->ccBasicInfoRpt->cpuInfoMod, html, "CPU信息");
        getTableString(mainWindow->ccBasicInfoRpt->biosInfoMod, html, "BIOS信息");
        getTableString(mainWindow->ccBasicInfoRpt->motherBoardInfoMod, html, "主板信息");
        getTableString(mainWindow->ccBasicInfoRpt->memoryInfoMod, html, "内存信息");
        getTableString(mainWindow->ccBasicInfoRpt->graphicsCardInfoMod, html, "显卡信息");
        getSectionTitleString(html, "设备连接");
        getTableString(mainWindow->ccDeviceConnectRpt->hardDiskInfoMod, html, "硬盘信息");
        getTableString(mainWindow->ccDeviceConnectRpt->virtualMachineInfoMod, html, "虚拟机信息");
        getTableString(mainWindow->ccDeviceConnectRpt->netConfigMod, html, "网络配置");
        getTableString(mainWindow->ccDeviceConnectRpt->adapterDeviceMod, html, "网卡设备");
        getTableString(mainWindow->ccDeviceConnectRpt->printDeviceMod, html, "打印机设备");
        getTableString(mainWindow->ccDeviceConnectRpt->blueToothDeviceMod, html, "蓝牙设备");
        getSectionTitleString(html, "安全威胁");
        getTableString(mainWindow->ccSecurityThreatRpt->securityPolicyMod, html, "安全策略");
        getTableString(mainWindow->ccSecurityThreatRpt->openPortMod, html, "开放端口");
        getTableString(mainWindow->ccSecurityThreatRpt->sharingInfoMod, html, "共享信息");
        getTableString(mainWindow->ccSecurityThreatRpt->networkSoftwareMod, html, "网络软件");
        getTableString(mainWindow->ccSecurityThreatRpt->groupInfoMod, html, "组信息");
        getTableString(mainWindow->ccSecurityThreatRpt->userInfoMod, html, "用户信息");
        getTableString(mainWindow->ccSecurityThreatRpt->databaseInfoMod, html, "数据库信息");
        getTableString(mainWindow->ccSecurityThreatRpt->eventLogMod, html, "事件日志");
        getTableString(mainWindow->ccSecurityThreatRpt->userAuthenticationMod, html, "用户认证");
        getSectionTitleString(html, "系统安全");
        getTableString(mainWindow->ccSystemSecurityRpt->patchNotInstalledMod, html, "未安装补丁");
        getTableString(mainWindow->ccSystemSecurityRpt->systemServiceMod, html, "系统服务");
        getTableString(mainWindow->ccSystemSecurityRpt->systemProcessMod, html, "系统进程");
        getTableString(mainWindow->ccSystemSecurityRpt->evenProductMod, html, "操作系统");
        getTableString(mainWindow->ccSystemSecurityRpt->timeSwitchMachineMod, html, "开关机时间");
        getTableString(mainWindow->ccSystemSecurityRpt->securitySoftwareMod, html, "安全软件");
        getSectionTitleString(html, "网络记录");
        getTableString(mainWindow->ccNetRecordRpt->netRecordsMod, html, "网络记录常规信息");
        getSectionTitleString(html, "USB记录");
        getTableString(mainWindow->ccUsbRecordCommonRpt->usbRecordsMod, html, "USB记录常规信息");
    }

   // if (deepCheck->checkState() == Qt::Checked) {
   //     getSubTitleString(html, "深度检查");
    //    getTableString(mainWindow->nrdNetRecordDeepRpt->netRecordsMod, html, "网络记录深度检查信息");
    //    getTableString(mainWindow->udUsbRecordDeepRpt->usbRecordsMod, html, "USB记录深度检查信息");
   // }
    if (fileCheck->checkState() == Qt::Checked) {
        getSubTitleString(html, "文件检查");
        getTableString(mainWindow->fcFileCheckCommonRpt->fileRoutineCheckMod, html, "文件检查信息");
    }
    if (tjCheck->checkState() == Qt::Checked) {
        getSubTitleString(html, "木马检查");
        getTableString(mainWindow->tcTrojanCheckRpt->threatDocumentMod, html, "威胁文档");
        //getTableString(mainWindow->tcTrojanCheckRpt->networkWeaponMod, html, "网络武器");
    }
    if (imageCheck->checkState() == Qt::Checked) {
        getSubTitleString(html, "图片检查");
        getTableString(mainWindow->icImageCheckRpt->imageCheckMod, html, "图片检查信息");
    }

    html += "</body>";
    html += "</html>";

    return html;
}

void CheckReportWidget::cancelCheck()
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

void CheckReportWidget::updateCheckingElapsedTime()
{
    //qDebug() << "updateCheckingElapsedTime";
    unsigned int timedifference = (QDateTime::currentDateTime()).toTime_t() - checkingStartTime;
    checkingElapsedTime->setText("已用时：" + (QTime(0, 0)).addSecs(timedifference).toString("hh:mm:ss"));
}

void CheckReportWidget::completerateUpdate(const int completerate, const QString& status)
{
    //qDebug() << "completerate::" << completerate;
    progressbar_front->move(-895 + 900 * completerate / 100, 147);
    description->setText(status);
    description->adjustSize();
    if (completerate == 100) {
        startcheckbtn->show();
        cancelcheckbtn->hide();
        progressbar_background->hide();
        progressbar_front->hide();
        descriptiontitle->setText("报告创建完成!");
        //description->setText("请查看相关报告");
        descriptiontitle->adjustSize();
        description->adjustSize();
        checkingElapsedTime->hide();
        checkingElapsedTime->setText("");
        checkingElapsedTimer->stop();
    }
}

void CheckReportWidget::dataCountUpdate(const int totalproblems, const int totalinfomations)
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

void CheckReportWidget::getTableString(QStandardItemModel* model, QString& html, const QString& tablename)
{
    int columnnumber = model->columnCount();
    int rownumber = model->rowCount();

    html += "<br><table   width='100%'   >";
    html += "      <caption style='font-size:170px' >" + tablename + "</caption>";
    html += "      <thead>";
    html += "        <tr>";
    for (int i = 0; i < columnnumber; i++) {
        html += "         <th>" + model->headerData(i, Qt::Horizontal).toString() + "</th>";
    }
    html += "        </tr>";
    html += "      </thead>";
    html += "     <tbody>";
    for (int i = 0; i < rownumber; i++) {
        html += "      <tr>";
        for (int j = 0; j < columnnumber; j++) {
            html += "         <td >" + model->item(i, j)->text() + "</td>";
        }
        html += "      </tr>";
    }
    html += "     </tbody>";
    html += "     </table>";
}

void CheckReportWidget::getSubTitleString(QString& html, const QString& subtitle)
{
    html += "<div style='font-weight:bold;font-size:200px'><br><br>" + subtitle + " <hr></div>";
}

void CheckReportWidget::getSectionTitleString(QString& html, const QString& sectiontitle)
{
    html += "<div class='sectiontitle' style='TEXT-DECORATION: underline;font-size:180px' align='center'><br>" + sectiontitle + "</div>";
}
void CheckReportWidget::getCssString(QString& html)
{

    html += "<style type='text/css'>";
    //html += "  table, th, td {border-collapse: collapse;border-spacing: 0;border-width:6px; border-style: solid; border-color: red;color:#009900;}";
    html += "  table, th, td {border: none;color:#000000;}";
    html += "  th {font-family: 宋体,Microsoft YaHei,Verdana;font-size:150px}";

    html += " table{border:none;background:#ffffff;}";
    html += " th,td{border:none;padding:5px 15px;}";
    html += " th{font-weight:normal;background:#cfcfcf;;}";
    html += " td{background:#efefef;font-family: 宋体,Microsoft YaHei,Verdana;font-size:140px}}";
    html += " div.title{font-weight:bold;font-size:250px;}";
    html += " div.sectiontitle{}";
    html += " </style>";
}
