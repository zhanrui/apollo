#include "systemsecurityrpt.h"

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
SystemSecurityRpt::SystemSecurityRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent),BaseReport()
{
    initUI(title);
    initModel();
    initConnection();
    selectPatchNotInstalled();
}

SystemSecurityRpt::~SystemSecurityRpt()
{
}

void SystemSecurityRpt::initUI(const QString& titletext)
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

    patchNotInstalledBtn = new TaskButton(":image/detailreport/deviceconnect/hardDiskInfoBtn", this);
    patchNotInstalledBtn->move(27, 60);
    systemServiceBtn = new TaskButton(":image/detailreport/deviceconnect/virtualMachineInfoBtn", this);
    systemServiceBtn->move(27 + 142, 60);
    systemProcessBtn = new TaskButton(":image/detailreport/deviceconnect/netConfigBtn", this);
    systemProcessBtn->move(27 + 142 * 2, 60);
    evenProductBtn = new TaskButton(":image/detailreport/deviceconnect/adapterDeviceBtn", this);
    evenProductBtn->move(27 + 142 * 3, 60);
    timeSwitchMachineBtn = new TaskButton(":image/detailreport/deviceconnect/printDeviceBtn", this);
    timeSwitchMachineBtn->move(27 + 142 * 4, 60);
    securitySoftwareBtn = new TaskButton(":image/detailreport/deviceconnect/blueToothDeviceBtn", this);
    securitySoftwareBtn->move(27 + 142 * 5, 60);

    taskbtnlist << patchNotInstalledBtn << systemServiceBtn << systemProcessBtn << evenProductBtn << timeSwitchMachineBtn << securitySoftwareBtn;

    patchNotInstalledView = new QTableView(this);
    //hardDiskInfoView->setModel(hardDiskInfoMod);
    initViewDetail(patchNotInstalledView);

    systemServiceView = new QTableView(this);
    //virtualMachineInfoView->setModel(virtualMachineInfoMod);
    initViewDetail(systemServiceView);

    systemProcessView = new QTableView(this);
    //netConfigView->setModel(netConfigMod);
    initViewDetail(systemProcessView);

    evenProductView = new QTableView(this);
    //adapterDeviceView->setModel(adapterDeviceMod);
    initViewDetail(evenProductView);

    timeSwitchMachineView = new QTableView(this);
    //printDeviceView->setModel(printDeviceMod);
    initViewDetail(timeSwitchMachineView);

    securitySoftwareView = new QTableView(this);
    //blueToothDeviceView->setModel(blueToothDeviceMod);
    initViewDetail(securitySoftwareView);

    viewlist << patchNotInstalledView << systemServiceView << systemProcessView
             << evenProductView << timeSwitchMachineView << securitySoftwareView;
}

void SystemSecurityRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(447);
    view->move(0, 153);
    initViewStyle(view);
}

void SystemSecurityRpt::initModel()
{

    patchNotInstalledMod = new QStandardItemModel(this);
    ModelUtil::initUninstallPatchModel(patchNotInstalledMod, patchNotInstalledView);
    patchNotInstalledView->setColumnWidth(0, 200);
    systemServiceMod = new QStandardItemModel(this);
    ModelUtil::initSystemServiceModel(systemServiceMod, systemServiceView);
    systemProcessMod = new QStandardItemModel(this);
    ModelUtil::initSystemProcessModel(systemProcessMod, systemProcessView);
    evenProductMod = new QStandardItemModel(this);
    ModelUtil::initExternalConnectionModel(evenProductMod, evenProductView);
    timeSwitchMachineMod = new QStandardItemModel(this);
    ModelUtil::initStartShutdownTimeModel(timeSwitchMachineMod, timeSwitchMachineView);
    securitySoftwareMod = new QStandardItemModel(this);
    ModelUtil::initSecuritySoftwareModel(securitySoftwareMod, securitySoftwareView);

    modellist << patchNotInstalledMod << systemServiceMod << systemProcessMod
              << evenProductMod << timeSwitchMachineMod << securitySoftwareMod;
}

void SystemSecurityRpt::initConnection()
{
    connect(patchNotInstalledBtn, SIGNAL(buttonClicked()), this, SLOT(selectPatchNotInstalled()));
    connect(systemServiceBtn, SIGNAL(buttonClicked()), this, SLOT(selectSystemService()));
    connect(systemProcessBtn, SIGNAL(buttonClicked()), this, SLOT(selectSystemProcess()));
    connect(evenProductBtn, SIGNAL(buttonClicked()), this, SLOT(selectEvenProduct()));
    connect(timeSwitchMachineBtn, SIGNAL(buttonClicked()), this, SLOT(selectTimeSwitchMachine()));
    connect(securitySoftwareBtn, SIGNAL(buttonClicked()), this, SLOT(selectSecuritySoftware()));
}

void SystemSecurityRpt::addPatchNotInstalled(const QVariantList& result)
{
    ModelUtil::addUninstallPatch(patchNotInstalledMod, result);
}
void SystemSecurityRpt::addSystemService(const QVariantList& result)
{
    ModelUtil::addSystemService(systemServiceMod, result);
}
void SystemSecurityRpt::addSystemProcess(const QVariantList& result)
{
    ModelUtil::addSystemProcess(systemProcessMod, result);
}
void SystemSecurityRpt::addEvenProduct(const QVariantList& result)
{
    ModelUtil::addExternalConnection(evenProductMod, result);
}
void SystemSecurityRpt::addTimeSwitchMachine(const QVariantList& result)
{
    ModelUtil::addStartShutdownTime(timeSwitchMachineMod, result);
}
void SystemSecurityRpt::addSecuritySoftware(const QVariantList& result)
{
    ModelUtil::addSecuritySoftware(securitySoftwareMod, result);
}



void SystemSecurityRpt::selectPatchNotInstalled()
{
    unselectAllTaskbtn();
    hideAllView();
    patchNotInstalledBtn->select();
    patchNotInstalledView->show();
}
void SystemSecurityRpt::selectSystemService()
{
    unselectAllTaskbtn();
    hideAllView();
    systemServiceBtn->select();
    systemServiceView->show();
}
void SystemSecurityRpt::selectSystemProcess()
{
    unselectAllTaskbtn();
    hideAllView();
    systemProcessBtn->select();
    systemProcessView->show();
}
void SystemSecurityRpt::selectEvenProduct()
{
    unselectAllTaskbtn();
    hideAllView();
    evenProductBtn->select();
    evenProductView->show();
}
void SystemSecurityRpt::selectTimeSwitchMachine()
{
    unselectAllTaskbtn();
    hideAllView();
    timeSwitchMachineBtn->select();
    timeSwitchMachineView->show();
}
void SystemSecurityRpt::selectSecuritySoftware()
{
    unselectAllTaskbtn();
    hideAllView();
    securitySoftwareBtn->select();
    securitySoftwareView->show();
}

