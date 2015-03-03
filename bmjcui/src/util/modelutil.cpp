#include "modelutil.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QDebug>

ModelUtil::ModelUtil()
{
}

ModelUtil::~ModelUtil()
{
}

//Basic Info
//	modelName			名称
//	vendorId			生产厂商
//	cacheSize			缓存大小(K)
//	CPU MHz				CPU MHz
void ModelUtil::initCPUModel(QStandardItemModel* model, QTableView* view)
{
    //ID CPU名称
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* modelName = new QStandardItem("CPU名称");
    model->setHorizontalHeaderItem(1, modelName);
    QStandardItem* vendorId = new QStandardItem("生产厂商");
    model->setHorizontalHeaderItem(2, vendorId);
    QStandardItem* cacheSize = new QStandardItem("缓存大小(K)");
    model->setHorizontalHeaderItem(3, cacheSize);
    QStandardItem* CPUMHz = new QStandardItem("CPU MHz");
    model->setHorizontalHeaderItem(4, CPUMHz);
}
//	modelName			名称
//	vendorId			生产厂商
//	cacheSize			缓存大小(K)
//	CPU MHz				CPU MHz
void ModelUtil::addCpuInfo(QStandardItemModel* model, const QVariantList& result)
{
    qDebug() << "result" << result.size();

    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* modelName = new QStandardItem(map["modelName"].toString());
        QStandardItem* vendorId = new QStandardItem(map["vendorId"].toString());
        QStandardItem* cacheSize = new QStandardItem(map["cacheSize"].toString());
        QStandardItem* CPUMHz = new QStandardItem(map["CPU MHz"].toString());
        model->appendRow(QList<QStandardItem*>() << id << modelName << vendorId
                                                 << cacheSize << CPUMHz);
    }
}
void ModelUtil::initOSModel(QStandardItemModel* model, QTableView* view)
{
    //#	platform 			获取操作系统名称及版本号
    //  #	version			  获取操作系统版本号
    // #	architecture 	获取操作系统的位数
    //#	machine 			计算机类型
    //#	node 					计算机的网络名称
    //#	system 				获取操作系统类型
    //#	unam          综合信息

    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* node = new QStandardItem("计算机名称");
    model->setHorizontalHeaderItem(1, node);
    QStandardItem* platform = new QStandardItem("系统名称");
    model->setHorizontalHeaderItem(2, platform);
    QStandardItem* ver = new QStandardItem("版本");
    model->setHorizontalHeaderItem(3, ver);
    QStandardItem* architecture = new QStandardItem("系统架构");
    model->setHorizontalHeaderItem(4, architecture);

    //QStandardItem* installfolder = new QStandardItem("安装时间");
    //model->setHorizontalHeaderItem(1, installfolder);
}
void ModelUtil::addOsInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* node = new QStandardItem(map["node"].toString());
        QStandardItem* platform = new QStandardItem(map["platform"].toString());
        QStandardItem* version = new QStandardItem(map["version"].toString());
        QStandardItem* architecture = new QStandardItem(map["architecture"].toString());
        model->appendRow(QList<QStandardItem*>() << id << node << platform
                                                 << version << architecture);
    }
}
void ModelUtil::initBIOSModel(QStandardItemModel* model, QTableView* view)
{
    //BioVendor		    BIOS产商
    //       #   BioVersion		    BIOS版本
    //      #   BioRelease		    发布日期
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* BioVendor = new QStandardItem("BIOS产商");
    model->setHorizontalHeaderItem(1, BioVendor);
    QStandardItem* BioVersion = new QStandardItem("BIOS版本");
    model->setHorizontalHeaderItem(2, BioVersion);
    QStandardItem* BioRelease = new QStandardItem("发布日期");
    model->setHorizontalHeaderItem(3, BioRelease);
}
void ModelUtil::addBiosInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* BioVendor = new QStandardItem(map["BioVendor"].toString());
        BioVendor->setToolTip(map["BioVendor"].toString());
        QStandardItem* BioVersion = new QStandardItem(map["BioVersion"].toString());
        QStandardItem* BioRelease = new QStandardItem(map["BioRelease"].toString());

        model->appendRow(QList<QStandardItem*>() << id << BioVendor << BioVersion
                                                 << BioRelease);
    }
}
void ModelUtil::initMainBoardModel(QStandardItemModel* model, QTableView* view)
{
    //#BoaProduct		主板型号
    //#BoaVendor		主板产商
    //#BoaSerial		序列号

    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* BoaProduct = new QStandardItem("主板型号");
    model->setHorizontalHeaderItem(1, BoaProduct);
    QStandardItem* BoaVendor = new QStandardItem("主板产商");
    model->setHorizontalHeaderItem(2, BoaVendor);
    QStandardItem* BoaSerial = new QStandardItem("序列号");
    model->setHorizontalHeaderItem(3, BoaSerial);
}
void ModelUtil::addMainBoardInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* BoaProduct = new QStandardItem(map["BoaProduct"].toString());
        QStandardItem* BoaVendor = new QStandardItem(map["BoaVendor"].toString());
        QStandardItem* BoaSerial = new QStandardItem(map["BoaSerial"].toString());

        model->appendRow(QList<QStandardItem*>() << id << BoaProduct << BoaVendor
                                                 << BoaSerial);
    }
}
void ModelUtil::initMemoryModel(QStandardItemModel* model, QTableView* view)
{
    // [{'Memnum': '1', 'MemInfo': 'DIMM DRAM EDO Unknown', 'MemProduct': 'Not Specified', 'MemSerial': 'Not Specified', 'MemSlot': 'RAM slot #0', 'MemWidth': '32 bits', 'MemVendor': 'Not Specified', 'MemSize': '2048 MB'}]

    int i = -1;

    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(++i, id);
    QStandardItem* MemInfo = new QStandardItem("内存条信息");
    model->setHorizontalHeaderItem(++i, MemInfo);
    QStandardItem* MemWidth = new QStandardItem("数据宽度");
    model->setHorizontalHeaderItem(++i, MemWidth);
    QStandardItem* MemSlot = new QStandardItem("插槽号");
    model->setHorizontalHeaderItem(++i, MemSlot);
    QStandardItem* MemProduct = new QStandardItem("内存型号");
    model->setHorizontalHeaderItem(++i, MemProduct);
    QStandardItem* MemVendor = new QStandardItem("制造商");
    model->setHorizontalHeaderItem(++i, MemVendor);
    QStandardItem* MemSize = new QStandardItem("内存大小");
    model->setHorizontalHeaderItem(++i, MemSize);
}
void ModelUtil::addMemoryInfo(QStandardItemModel* model, const QVariantList& result)
{
    //#Memnum         内存条个数
    //	#MemInfo        内存条信息
    //	#MemWidth       数据宽度
    //	#MemSlot 		插槽号
    //	#MemProduct		内存型号
    //	#MemVendor		制造商
    //	#MemSerial		序列号
    //	#MemSize 		内存大小

    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* MemInfo = new QStandardItem(map["MemInfo"].toString());
        QStandardItem* MemWidth = new QStandardItem(map["MemWidth"].toString());
        QStandardItem* MemSlot = new QStandardItem(map["MemSlot"].toString());
        QStandardItem* MemProduct = new QStandardItem(map["MemProduct"].toString());
        QStandardItem* MemVendor = new QStandardItem(map["MemVendor"].toString());
        QStandardItem* MemSerial = new QStandardItem(map["MemSerial"].toString());
        QStandardItem* MemSize = new QStandardItem(map["MemSize"].toString());

        model->appendRow(QList<QStandardItem*>() << id << MemInfo << MemWidth
                                                 << MemSlot << MemProduct << MemVendor << MemSerial << MemSize);
    }
}
void ModelUtil::initVideoCardModel(QStandardItemModel* model, QTableView* view)
{
    int i = 0;
    int j = 0;

    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(i++, id);
    view->setColumnWidth(j++, 30);
    QStandardItem* Vga_product = new QStandardItem("显卡型号");
    model->setHorizontalHeaderItem(i++, Vga_product);
    view->setColumnWidth(j++, 400);
    QStandardItem* Vga_vendor = new QStandardItem("显卡产商");
    model->setHorizontalHeaderItem(i++, Vga_vendor);
    view->setColumnWidth(j++, 100);
    QStandardItem* Vga_Drive = new QStandardItem("显卡驱动");
    model->setHorizontalHeaderItem(i++, Vga_Drive);
    view->setColumnWidth(j++, 100);
}
void ModelUtil::addVideoCardInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* Vga_product = new QStandardItem(map["Vga_product"].toString());
        QStandardItem* Vga_vendor = new QStandardItem(map["Vga_vendor"].toString());
        QStandardItem* Vga_Drive = new QStandardItem(map["Vga_Drive"].toString());

        model->appendRow(QList<QStandardItem*>() << id << Vga_product << Vga_vendor
                                                 << Vga_Drive);
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
    int i = 0;
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(i++, id);
    QStandardItem* NetProduct = new QStandardItem("网卡型号");
    model->setHorizontalHeaderItem(i++, NetProduct);
    QStandardItem* NetVendor = new QStandardItem("制造商");
    model->setHorizontalHeaderItem(i++, NetVendor);
    QStandardItem* NetLogicalname = new QStandardItem("设备名称");
    model->setHorizontalHeaderItem(i++, NetLogicalname);
    QStandardItem* NetSerial = new QStandardItem("MAC地址");
    model->setHorizontalHeaderItem(i++, NetSerial);
    QStandardItem* NetDrive = new QStandardItem("网卡驱动");
    model->setHorizontalHeaderItem(i++, NetDrive);
}
void ModelUtil::addNetworkAdapterDevice(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* NetProduct = new QStandardItem(map["NetProduct"].toString());
        QStandardItem* NetVendor = new QStandardItem(map["NetVendor"].toString());
        QStandardItem* NetLogicalname = new QStandardItem(map["NetLogicalname"].toString());
        QStandardItem* NetSerial = new QStandardItem(map["NetSerial"].toString());
        QStandardItem* NetDrive = new QStandardItem(map["NetDrive"].toString());
        model->appendRow(QList<QStandardItem*>() << id << NetProduct << NetVendor << NetLogicalname
                                                 << NetSerial << NetDrive);
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
void ModelUtil::addUninstallPatch(QStandardItemModel* model, const QVariantList& result)
{
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
    view->setColumnWidth(0, 50);
    QStandardItem* name = new QStandardItem("服务名称");
    model->setHorizontalHeaderItem(1, name);
    view->setColumnWidth(1, 500);
    QStandardItem* status = new QStandardItem("状态");
    model->setHorizontalHeaderItem(2, status);
}
void ModelUtil::addSystemService(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* UNITFILE = new QStandardItem(map["UNITFILE"].toString());
        QStandardItem* STATE = new QStandardItem(map["STATE"].toString());
        model->appendRow(QList<QStandardItem*>() << id << UNITFILE << STATE);
    }
}
void ModelUtil::initSystemProcessModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    int i = 0;
    int j = 0;
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(i++, id);
    view->setColumnWidth(j++, 30);
    QStandardItem* UID = new QStandardItem("用户ID");
    model->setHorizontalHeaderItem(i++, UID);
    view->setColumnWidth(j++, 70);
    QStandardItem* PID = new QStandardItem("进程ID");
    model->setHorizontalHeaderItem(i++, PID);
    view->setColumnWidth(j++, 70);
    QStandardItem* PPID = new QStandardItem("父进程ID");
    model->setHorizontalHeaderItem(i++, PPID);
    view->setColumnWidth(j++, 70);
    QStandardItem* STIME = new QStandardItem("开始时间");
    model->setHorizontalHeaderItem(i++, STIME);
    view->setColumnWidth(j++, 70);
    QStandardItem* TTY = new QStandardItem("终端名称");
    model->setHorizontalHeaderItem(i++, TTY);
    view->setColumnWidth(j++, 70);
    QStandardItem* TIME = new QStandardItem("执行时间");
    model->setHorizontalHeaderItem(i++, TIME);
    view->setColumnWidth(j++, 70);
    QStandardItem* CMD = new QStandardItem("命令");
    model->setHorizontalHeaderItem(i++, CMD);
    view->setColumnWidth(j++, 400);
}
void ModelUtil::addSystemProcess(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* UID = new QStandardItem(map["UID"].toString());
        QStandardItem* PID = new QStandardItem(map["PID"].toString());
        QStandardItem* PPID = new QStandardItem(map["PPID"].toString());
        QStandardItem* STIME = new QStandardItem(map["STIME"].toString());
        QStandardItem* TTY = new QStandardItem(map["TTY"].toString());
        QStandardItem* TIME = new QStandardItem(map["TIME"].toString());
        QStandardItem* CMD = new QStandardItem(map["CMD"].toString());

        model->appendRow(QList<QStandardItem*>() << id << UID << PID << PPID << STIME << TTY << TIME << CMD);
    }
}
void ModelUtil::initExternalConnectionModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addExternalConnection(QStandardItemModel* model, const QVariantList& result)
{
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
    QStandardItem* name = new QStandardItem("类型");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("时间");
    model->setHorizontalHeaderItem(2, provider);
    view->setColumnWidth(2, 200);
}
void ModelUtil::addStartShutdownTime(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* id = new QStandardItem(QString::number(model->rowCount()));
        QStandardItem* TYPE = new QStandardItem(map["TYPE"].toString());
        QStandardItem* TIME = new QStandardItem(map["TIME"].toString());
        model->appendRow(QList<QStandardItem*>() << id << TYPE << TIME);
    }
}
void ModelUtil::initSecuritySoftwareModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addSecuritySoftware(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
//System Security Info
void ModelUtil::initSecurityStrategyModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addSecurityStrategy(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initOpenPortModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addOpenPort(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initSharedInfoModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addSharedInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initInternetToolModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addInternetTool(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initUserGroupInfoModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addUserGroupInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initUserInfoModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addUserInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initDataBaseInfoModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addDataBaseInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initEventLogModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addEventLog(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initAuthenticatioInfoModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
}
void ModelUtil::addAuthenticatioInfo(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
//System Usb Check Info
void ModelUtil::initUsbCheckModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}

void ModelUtil::addUsbCheckModel(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
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
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addFileCheckModel(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initFileFragmentCheckModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addFileFragmentCheckModel(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}

void ModelUtil::initDeletedFileRecoveryModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addDeletedFileRecoveryModel(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}

//Virus Check Info
void ModelUtil::initMalwareCheckModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addMalwareCheckModel(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initVirusCheckModel(QStandardItemModel* model, QTableView* view)
{
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addVirusCheckModel(QStandardItemModel* model, const QVariantList& result)
{
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}
void ModelUtil::initImageCheckModel(QStandardItemModel* model, QTableView* view){
    view->setModel(model);
    QStandardItem* id = new QStandardItem("ID");
    model->setHorizontalHeaderItem(0, id);
    QStandardItem* name = new QStandardItem("名称");
    model->setHorizontalHeaderItem(1, name);
    QStandardItem* provider = new QStandardItem("供应商");
    model->setHorizontalHeaderItem(2, provider);
}
void ModelUtil::addImageCheckModel(QStandardItemModel* model, const QVariantList& result){
    for (QVariant var : result) {
        QVariantMap map = var.toMap();
        QStandardItem* test = new QStandardItem(map["test"].toString());
        model->appendRow(QList<QStandardItem*>() << test);
    }
}

