#include "netrecordallrpt.h"


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
NetRecordAllRpt::NetRecordAllRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent),BaseReport()
{
    initUI(title);
    initModel();
    initConnection();
    selectNetRecordCommonInfo();
}

NetRecordAllRpt::~NetRecordAllRpt()
{
}

void NetRecordAllRpt::initUI(const QString& titletext)
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

    netRecordCommonInfoBtn = new TaskButton(":image/detailreport/deviceconnect/hardDiskInfoBtn", this);
    netRecordCommonInfoBtn->move(27, 60);
    netRecordDeepInfoBtn = new TaskButton(":image/detailreport/deviceconnect/virtualMachineInfoBtn", this);
    netRecordDeepInfoBtn->move(27 + 142, 60);


    taskbtnlist << netRecordCommonInfoBtn << netRecordDeepInfoBtn;

    netRecordCommonInfoView = new QTableView(this);
    //hardDiskInfoView->setModel(hardDiskInfoMod);
    initViewDetail(netRecordCommonInfoView);

    netRecordDeepInfoView = new QTableView(this);
    //virtualMachineInfoView->setModel(virtualMachineInfoMod);
    initViewDetail(netRecordDeepInfoView);

      viewlist << netRecordCommonInfoView << netRecordDeepInfoView;
}

void NetRecordAllRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(447);
    view->move(0, 153);
    initViewStyle(view);
}

void NetRecordAllRpt::initModel()
{

    netRecordCommonInfoMod = new QStandardItemModel(this);
    ModelUtil::initIntenetHistoryCheckModel(netRecordCommonInfoMod, netRecordCommonInfoView);
    netRecordCommonInfoView->setColumnWidth(0, 200);
    netRecordDeepInfoMod = new QStandardItemModel(this);
    ModelUtil::initIntenetHistoryCheckModel(netRecordDeepInfoMod, netRecordDeepInfoView);

    modellist << netRecordCommonInfoMod << netRecordDeepInfoMod ;
}

void NetRecordAllRpt::initConnection()
{
    connect(netRecordCommonInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectNetRecordCommonInfo()));
    connect(netRecordDeepInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectNetRecordDeepInfo()));

}

void NetRecordAllRpt::addNetRecordCommonInfo(const QVariantList& result)
{
    ModelUtil::addIntenetHistoryCheckModel(netRecordCommonInfoMod, result);
}
void NetRecordAllRpt::addNetRecordDeepInfo(const QVariantList& result)
{
    ModelUtil::addIntenetHistoryCheckModel(netRecordDeepInfoMod, result);
}

void NetRecordAllRpt::selectNetRecordCommonInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    netRecordCommonInfoBtn->select();
    netRecordCommonInfoView->show();
}
void NetRecordAllRpt::selectNetRecordDeepInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    netRecordDeepInfoBtn->select();
    netRecordDeepInfoView->show();
}

