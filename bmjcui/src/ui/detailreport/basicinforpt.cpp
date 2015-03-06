#include "basicinforpt.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QVariantMap>
#include <QVariant>
#include <QLabel>

#include "src/ui/common/taskbutton.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
#include "src/util/modelutil.h"
#include "src/ui/detailreport/basereport.h"

BasicInfoRpt::BasicInfoRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent),BaseReport()
{
    initUI(title);
    initModel();
    initConnection();
    selectOSInfo();
}

BasicInfoRpt::~BasicInfoRpt()
{
}

void BasicInfoRpt::initUI(const QString& titletext)
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

    osInfoBtn = new TaskButton(":image/detailreport/basicinfo/osInfoBtn", this);
    osInfoBtn->move(27, 60);
    cpuInfoBtn = new TaskButton(":image/detailreport/basicinfo/cpuInfoBtn", this);
    cpuInfoBtn->move(27 + 142, 60);
    biosInfoBtn = new TaskButton(":image/detailreport/basicinfo/biosInfoBtn", this);
    biosInfoBtn->move(27 + 142 * 2, 60);
    motherBoardInfoBtn = new TaskButton(":image/detailreport/basicinfo/motherBoardInfoBtn", this);
    motherBoardInfoBtn->move(27 + 142 * 3, 60);
    memoryInfoBtn = new TaskButton(":image/detailreport/basicinfo/memoryInfoBtn", this);
    memoryInfoBtn->move(27 + 142 * 4, 60);
    graphicsCardInfoBtn = new TaskButton(":image/detailreport/basicinfo/graphicsCardInfoBtn", this);
    graphicsCardInfoBtn->move(27 + 142 * 5, 60);

    taskbtnlist << osInfoBtn << cpuInfoBtn << biosInfoBtn << motherBoardInfoBtn << memoryInfoBtn << graphicsCardInfoBtn;

    for (TaskButton* task : taskbtnlist) {
        task->running_movie->move((task->running_defaultstatus->width()) / 2 - 10, 50);
    }
    osView = new QTableView(this);
    //hardDiskInfoView->setModel(hardDiskInfoMod);
    initViewDetail(osView);

    cpuInfoView = new QTableView(this);
    //virtualMachineInfoView->setModel(virtualMachineInfoMod);
    initViewDetail(cpuInfoView);

    biosInfoView = new QTableView(this);
    //netConfigView->setModel(netConfigMod);
    initViewDetail(biosInfoView);

    motherBoardInfoView = new QTableView(this);
    //adapterDeviceView->setModel(adapterDeviceMod);
    initViewDetail(motherBoardInfoView);

    memoryInfoView = new QTableView(this);
    //printDeviceView->setModel(printDeviceMod);
    initViewDetail(memoryInfoView);

    graphicsCardInfoView = new QTableView(this);
    //blueToothDeviceView->setModel(blueToothDeviceMod);
    initViewDetail(graphicsCardInfoView);

    viewlist << osView << cpuInfoView << biosInfoView
             << motherBoardInfoView << memoryInfoView << graphicsCardInfoView;
}

void BasicInfoRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(447);
    view->move(0, 153);
    initViewStyle(view);
}

void BasicInfoRpt::initModel()
{
     osInfoMod = new QStandardItemModel(this);
    ModelUtil::initOSModel(osInfoMod, osView);
    cpuInfoMod = new QStandardItemModel(this);
    ModelUtil::initCPUModel(cpuInfoMod, cpuInfoView);
    biosInfoMod = new QStandardItemModel(this);
    ModelUtil::initBIOSModel(biosInfoMod, biosInfoView);
    motherBoardInfoMod = new QStandardItemModel(this);
    ModelUtil::initMainBoardModel(motherBoardInfoMod, motherBoardInfoView);
    memoryInfoMod = new QStandardItemModel(this);
    ModelUtil::initMemoryModel(memoryInfoMod, memoryInfoView);
    graphicsCardInfoMod = new QStandardItemModel(this);
    ModelUtil::initVideoCardModel(graphicsCardInfoMod, graphicsCardInfoView);

    modellist << osInfoMod << cpuInfoMod << biosInfoMod
              << motherBoardInfoMod << memoryInfoMod << graphicsCardInfoMod;
}

void BasicInfoRpt::initConnection()
{
    connect(osInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectOSInfo()));
    connect(cpuInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectCpuInfo()));
    connect(biosInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectBiosInfo()));
    connect(motherBoardInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectMotherBoardInfo()));
    connect(memoryInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectMemoryInfo()));
    connect(graphicsCardInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectGraphicsCardInfo()));
}

void BasicInfoRpt::addOSInfo(const QVariantList& result)
{
    ModelUtil::addOsInfo(osInfoMod, result);
}
void BasicInfoRpt::addCpuInfo(const QVariantList& result)
{
    ModelUtil::addCpuInfo(cpuInfoMod, result);
}
void BasicInfoRpt::addBiosInfo(const QVariantList& result)
{
    ModelUtil::addBiosInfo(biosInfoMod, result);
}
void BasicInfoRpt::addMotherBoardInfo(const QVariantList& result)
{
    ModelUtil::addMainBoardInfo(motherBoardInfoMod, result);
}
void BasicInfoRpt::addMemoryInfo(const QVariantList& result)
{
    ModelUtil::addMemoryInfo(memoryInfoMod, result);
}
void BasicInfoRpt::addGraphicsCardInfo(const QVariantList& result)
{
    ModelUtil::addVideoCardInfo(graphicsCardInfoMod, result);
}

void BasicInfoRpt::selectOSInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    osInfoBtn->select();
    osView->show();
}
void BasicInfoRpt::selectCpuInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    cpuInfoBtn->select();
    cpuInfoView->show();
}
void BasicInfoRpt::selectBiosInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    biosInfoBtn->select();
    biosInfoView->show();
}
void BasicInfoRpt::selectMotherBoardInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    motherBoardInfoBtn->select();
    motherBoardInfoView->show();
}
void BasicInfoRpt::selectMemoryInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    memoryInfoBtn->select();
    memoryInfoView->show();
}
void BasicInfoRpt::selectGraphicsCardInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    graphicsCardInfoBtn->select();
    graphicsCardInfoView->show();
}
