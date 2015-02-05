#include "modelutil.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>

ModelUtil::ModelUtil()
{
}

ModelUtil::~ModelUtil()
{
}

//Basic Info
void ModelUtil::initCPUModel(QStandardItemModel* model, QTableView* view)
{
    //ID CPU名称
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* cpuname = new QStandardItem("CPU名称");
    model->setHorizontalHeaderItem(1, cpuname);

}
void ModelUtil::addCpuInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initOSModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* seqid = new QStandardItem("序列号");
    model->setHorizontalHeaderItem(1, seqid);
    QStandardItem* ver = new QStandardItem("版本");
    model->setHorizontalHeaderItem(1, ver);
    QStandardItem* installtime = new QStandardItem("安装时间");
    model->setHorizontalHeaderItem(1, installtime);
    QStandardItem* installfolder = new QStandardItem("安装时间");
    model->setHorizontalHeaderItem(1, installfolder);
}
void ModelUtil::addOsInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initBIOSModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::addBiosInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initMainBoardModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::addMainBoardInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initMemoryModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::addMemoryInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initVideoCardModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::addVideoCardInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
//Device Connection Info
void ModelUtil::initHardDiskModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    view->setColumnWidth(0, 300);
    QStandardItem* seqnum = new QStandardItem("序列号");
    model->setHorizontalHeaderItem(1, seqnum);
    QStandardItem* size = new QStandardItem("大小");
    model->setHorizontalHeaderItem(2, size);
    QStandardItem* partition = new QStandardItem("分区");
    model->setHorizontalHeaderItem(3, partition);
    QStandardItem* starttimes = new QStandardItem("启动次数");
    model->setHorizontalHeaderItem(4, starttimes);
    QStandardItem* runningtime = new QStandardItem("运行时间（小时）");
    model->setHorizontalHeaderItem(5, runningtime);
    QStandardItem* partitioninfo = new QStandardItem("分区信息");
    model->setHorizontalHeaderItem(6, partitioninfo);
}

void ModelUtil::addHardDiskInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initVMModel(QStandardItemModel* model, QTableView* view)
{

    QStandardItem* id = new QStandardItem("ID");
    id->setSizeHint(QSize(10, 37));
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* version = new QStandardItem("版本");
    model->setHorizontalHeaderItem(2, version);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(3, provider);
    QStandardItem* installtime = new QStandardItem("安装时间");
    model->setHorizontalHeaderItem(4, installtime);
    QStandardItem* installfolder = new QStandardItem("安装目录");
    model->setHorizontalHeaderItem(5, installfolder);
    view->setModel(model);
}
void ModelUtil::addVMInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initNetConfigModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* connectionname = new QStandardItem("连接名称");
    model->setHorizontalHeaderItem(1, connectionname);
    QStandardItem* devicename = new QStandardItem("设备名称");
    model->setHorizontalHeaderItem(2, devicename);
    QStandardItem* mac = new QStandardItem("MAC");
    model->setHorizontalHeaderItem(3, mac);
    QStandardItem* ipaddress = new QStandardItem("IP地址");
    model->setHorizontalHeaderItem(4, ipaddress);
    QStandardItem* subnet = new QStandardItem("子网掩码");
    model->setHorizontalHeaderItem(5, subnet);
    QStandardItem* dns = new QStandardItem("DNS");
    model->setHorizontalHeaderItem(6, dns);
}
void ModelUtil::addNetConfig(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initNetworkAdapterModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* netadaptername = new QStandardItem("网卡名称");
    model->setHorizontalHeaderItem(1, netadaptername);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addNetworkAdapterDevice(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initPrinterModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* port = new QStandardItem("打印端口");
    model->setHorizontalHeaderItem(2, port);
}
void ModelUtil::addPrinterDevice(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initBlueToothModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addBlueToothDevice(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
//System Security Info
void ModelUtil::initUninstallPatchModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil:: addUninstallPatch(QStandardItemModel* model, const QVariantList& result){
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initSystemServiceModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil:: addSystemService(QStandardItemModel* model, const QVariantList& result){
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initSystemProcessModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil:: addSystemProcess(QStandardItemModel* model, const QVariantList& result){
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initExternalConnectionModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil:: addExternalConnection(QStandardItemModel* model, const QVariantList& result){
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initStartShutdownTimeModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil:: addStartShutdownTime(QStandardItemModel* model, const QVariantList& result){
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initSecuritySoftwareModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil:: addSecuritySoftware(QStandardItemModel* model, const QVariantList& result){
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
//System Security Info
void ModelUtil::initSecurityStrategyModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initOpenPortModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initSharedInfoModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initInternetToolModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initUserGroupInfoModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initUserInfoModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initDataBaseInfoModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initEventLogModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initAuthenticatioInfonModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
//System Usb Check Info
void ModelUtil::initUsbCheckModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
//System Usb Check Info
void ModelUtil::initIntenetHistoryCheckModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}

void ModelUtil::addIntenetHistoryCheckModel(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
//File Check Info
void ModelUtil::initFileCheckModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initFileFragmentCheckModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
//Virus Check Info
void ModelUtil::initMalwareCheckModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
void ModelUtil::initVirusCheckModel(QStandardItemModel* model, QTableView* view)
{
    model->setHorizontalHeaderLabels(QStringList() << "");
}
