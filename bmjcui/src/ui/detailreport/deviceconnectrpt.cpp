#include "deviceconnectrpt.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>

#include "src/ui/common/taskbutton.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/onekeycheck/mydelegate.h"

DeviceConnectRpt::DeviceConnectRpt(QWidget* parent)
    : BaseStyleWidget(parent)
{
    initModel();
    initUI();
    initConnection();
    selectHardDiskInfo();
}

DeviceConnectRpt::~DeviceConnectRpt()
{
}

void DeviceConnectRpt::initUI()
{
    this->setFixedSize(900, 600);
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
    taskbtnlist = QList<TaskButton*>();
    taskbtnlist << hardDiskInfoBtn << virtualMachineInfoBtn << netConfigBtn << adapterDeviceBtn << printDeviceBtn << blueToothDeviceBtn;

    checkresult = new QTableView(this);
    checkresult->setMinimumWidth(900);
    checkresult->setMinimumHeight(447);
    checkresult->move(0, 153);
    checkresult->verticalHeader()->hide();
    checkresult->horizontalHeader()->setHighlightSections(false);
    checkresult->horizontalHeader()->setFixedHeight(36);
    checkresult->setGridStyle(Qt::NoPen);

    checkresult->setShowGrid(false);
    checkresult->setEditTriggers(QAbstractItemView::NoEditTriggers);
    checkresult->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    checkresult->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    checkresult->setItemDelegate(new MyDelegate(checkresult));
    checkresult->setSelectionBehavior(QAbstractItemView::SelectRows);
    checkresult->setSelectionMode(QAbstractItemView::NoSelection);
    checkresult->setFrameShape(QFrame::NoFrame);

    checkresult->setModel(hardDiskInfoMod);
    checkresult->hide();
}
void DeviceConnectRpt::initModel()
{

    hardDiskInfoMod = new QStandardItemModel(this);
    hardDiskInfoMod->setHorizontalHeaderLabels(QStringList() << "");
    virtualMachineInfoMod = new QStandardItemModel(this);
    virtualMachineInfoMod->setHorizontalHeaderLabels(QStringList() << "");
    netConfigMod = new QStandardItemModel(this);
    netConfigMod->setHorizontalHeaderLabels(QStringList() << "");
    adapterDeviceMod = new QStandardItemModel(this);
    adapterDeviceMod->setHorizontalHeaderLabels(QStringList() << "");
    printDeviceMod = new QStandardItemModel(this);
    printDeviceMod->setHorizontalHeaderLabels(QStringList() << "");
    blueToothDeviceMod = new QStandardItemModel(this);
    blueToothDeviceMod->setHorizontalHeaderLabels(QStringList() << "");
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
}
void DeviceConnectRpt::addVirtualMachineInfo(const QVariantList& result)
{
}
void DeviceConnectRpt::addNetConfig(const QVariantList& result)
{
}
void DeviceConnectRpt::addAdapterDevice(const QVariantList& result)
{
}
void DeviceConnectRpt::addPrintDevice(const QVariantList& result)
{
}
void DeviceConnectRpt::addBlueToothDevice(const QVariantList& result)
{
}

void DeviceConnectRpt::unselectAllTaskbtn()
{
    for (TaskButton* task : taskbtnlist) {
        task->unselect();
    }
}

void DeviceConnectRpt::selectHardDiskInfo()
{
    unselectAllTaskbtn();
    hardDiskInfoBtn->select();
    checkresult->setModel(hardDiskInfoMod);
}
void DeviceConnectRpt::selectVirtualMachineInfo()
{
    unselectAllTaskbtn();
    virtualMachineInfoBtn->select();
    checkresult->setModel(virtualMachineInfoMod);
}
void DeviceConnectRpt::selectNetConfig()
{
    unselectAllTaskbtn();
    netConfigBtn->select();
    checkresult->setModel(netConfigMod);
}
void DeviceConnectRpt::selectAdapterDevice()
{
    unselectAllTaskbtn();
    adapterDeviceBtn->select();
    checkresult->setModel(adapterDeviceMod);
}
void DeviceConnectRpt::selectPrintDevice()
{
    unselectAllTaskbtn();
    printDeviceBtn->select();
    checkresult->setModel(printDeviceMod);
}
void DeviceConnectRpt::selectBlueToothDevice()
{
    unselectAllTaskbtn();
    blueToothDeviceBtn->select();
    checkresult->setModel(blueToothDeviceMod);
}
