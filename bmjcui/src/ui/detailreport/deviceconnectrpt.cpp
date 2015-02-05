#include "deviceconnectrpt.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QVariantMap>
#include <QVariant>
#include <QLabel>

#include "src/ui/common/taskbutton.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/onekeycheck/mydelegate.h"
#include "src/util/modelutil.h"
#include "src/ui/detailreport/basereport.h"
DeviceConnectRpt::DeviceConnectRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent),BaseReport()
{
    initUI(title);
    initModel();
    initConnection();
    selectHardDiskInfo();
}

DeviceConnectRpt::~DeviceConnectRpt()
{
}

void DeviceConnectRpt::initUI(const QString& titletext)
{
    this->setFixedSize(900, 600);

    QLabel* title = new QLabel(titletext, this);
    title->adjustSize();
    title->move(900 / 2 - title->width() / 2, 17);

    QLabel* icon = new QLabel(this);
    icon->setPixmap(QPixmap(":image/detailreport/logo"));
    icon->adjustSize();
    icon->move(900 / 2 - title->width() / 2 - 3 - icon->width(), 12);

    returnbtn = new StaticButton(":image/detailreport/returnbtn", 3, this);
    returnbtn->move(0, 0);

    hardDiskInfoBtn = new TaskButton(":image/detailreport/deviceconnect/hardDiskInfoBtn", this);
    hardDiskInfoBtn->move(27, 60);
    virtualMachineInfoBtn = new TaskButton(":image/detailreport/deviceconnect/virtualMachineInfoBtn", this);
    virtualMachineInfoBtn->move(27 + 142, 60);
    netConfigBtn = new TaskButton(":image/detailreport/deviceconnect/netConfigBtn", this);
    netConfigBtn->move(27 + 142 * 2, 60);
    adapterDeviceBtn = new TaskButton(":image/detailreport/deviceconnect/adapterDeviceBtn", this);
    adapterDeviceBtn->move(27 + 142 * 3, 60);
    printDeviceBtn = new TaskButton(":image/detailreport/deviceconnect/printDeviceBtn", this);
    printDeviceBtn->move(27 + 142 * 4, 60);
    blueToothDeviceBtn = new TaskButton(":image/detailreport/deviceconnect/blueToothDeviceBtn", this);
    blueToothDeviceBtn->move(27 + 142 * 5, 60);

    taskbtnlist << hardDiskInfoBtn << virtualMachineInfoBtn << netConfigBtn << adapterDeviceBtn << printDeviceBtn << blueToothDeviceBtn;

    hardDiskInfoView = new QTableView(this);
    //hardDiskInfoView->setModel(hardDiskInfoMod);
    initViewDetail(hardDiskInfoView);

    virtualMachineInfoView = new QTableView(this);
    //virtualMachineInfoView->setModel(virtualMachineInfoMod);
    initViewDetail(virtualMachineInfoView);

    netConfigView = new QTableView(this);
    //netConfigView->setModel(netConfigMod);
    initViewDetail(netConfigView);

    adapterDeviceView = new QTableView(this);
    //adapterDeviceView->setModel(adapterDeviceMod);
    initViewDetail(adapterDeviceView);

    printDeviceView = new QTableView(this);
    //printDeviceView->setModel(printDeviceMod);
    initViewDetail(printDeviceView);

    blueToothDeviceView = new QTableView(this);
    //blueToothDeviceView->setModel(blueToothDeviceMod);
    initViewDetail(blueToothDeviceView);


    viewlist << hardDiskInfoView << virtualMachineInfoView << netConfigView
             << adapterDeviceView << printDeviceView << blueToothDeviceView;
}

void DeviceConnectRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(447);
    view->move(0, 153);
    initViewStyle(view);
}

void DeviceConnectRpt::initModel()
{

    hardDiskInfoMod = new QStandardItemModel(this);
    ModelUtil::initHardDiskModel(hardDiskInfoMod, hardDiskInfoView);
    hardDiskInfoView->setColumnWidth(0, 200);
    virtualMachineInfoMod = new QStandardItemModel(this);
    ModelUtil::initVMModel(virtualMachineInfoMod, virtualMachineInfoView);
    netConfigMod = new QStandardItemModel(this);
    ModelUtil::initNetConfigModel(netConfigMod, netConfigView);
    adapterDeviceMod = new QStandardItemModel(this);
    ModelUtil::initNetworkAdapterModel(adapterDeviceMod, adapterDeviceView);
    printDeviceMod = new QStandardItemModel(this);
    ModelUtil::initPrinterModel(printDeviceMod, printDeviceView);
    blueToothDeviceMod = new QStandardItemModel(this);
    ModelUtil::initBlueToothModel(blueToothDeviceMod, blueToothDeviceView);

    modellist << hardDiskInfoMod << virtualMachineInfoMod << netConfigMod
              << adapterDeviceMod << printDeviceMod << blueToothDeviceMod;
}

void DeviceConnectRpt::initConnection()
{
    connect(hardDiskInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectHardDiskInfo()));
    connect(virtualMachineInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectVirtualMachineInfo()));
    connect(netConfigBtn, SIGNAL(buttonClicked()), this, SLOT(selectNetConfig()));
    connect(adapterDeviceBtn, SIGNAL(buttonClicked()), this, SLOT(selectAdapterDevice()));
    connect(printDeviceBtn, SIGNAL(buttonClicked()), this, SLOT(selectPrintDevice()));
    connect(blueToothDeviceBtn, SIGNAL(buttonClicked()), this, SLOT(selectBlueToothDevice()));
}

void DeviceConnectRpt::addHardDiskInfo(const QVariantList& result)
{
    ModelUtil::addHardDiskInfo(hardDiskInfoMod, result);
}
void DeviceConnectRpt::addVirtualMachineInfo(const QVariantList& result)
{
    ModelUtil::addVMInfo(virtualMachineInfoMod, result);
}
void DeviceConnectRpt::addNetConfig(const QVariantList& result)
{
    ModelUtil::addNetConfig(netConfigMod, result);
}
void DeviceConnectRpt::addAdapterDevice(const QVariantList& result)
{
    ModelUtil::addNetworkAdapterDevice(adapterDeviceMod, result);
}
void DeviceConnectRpt::addPrintDevice(const QVariantList& result)
{
    ModelUtil::addPrinterDevice(printDeviceMod, result);
}
void DeviceConnectRpt::addBlueToothDevice(const QVariantList& result)
{
    ModelUtil::addBlueToothDevice(blueToothDeviceMod, result);
}

void DeviceConnectRpt::selectHardDiskInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    hardDiskInfoBtn->select();
    hardDiskInfoView->show();
}
void DeviceConnectRpt::selectVirtualMachineInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    virtualMachineInfoBtn->select();
    virtualMachineInfoView->show();
}
void DeviceConnectRpt::selectNetConfig()
{
    unselectAllTaskbtn();
    hideAllView();
    netConfigBtn->select();
    netConfigView->show();
}
void DeviceConnectRpt::selectAdapterDevice()
{
    unselectAllTaskbtn();
    hideAllView();
    adapterDeviceBtn->select();
    adapterDeviceView->show();
}
void DeviceConnectRpt::selectPrintDevice()
{
    unselectAllTaskbtn();
    hideAllView();
    printDeviceBtn->select();
    printDeviceView->show();
}
void DeviceConnectRpt::selectBlueToothDevice()
{
    unselectAllTaskbtn();
    hideAllView();
    blueToothDeviceBtn->select();
    blueToothDeviceView->show();
}
