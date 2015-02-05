#include "netrecordrpt.h"

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
NetRecordRpt::~NetRecordRpt()
{
}

NetRecordRpt::NetRecordRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent)  , BaseReport()
{
    initUI(title);
    initModel();
    netRecordsView->show();
}

void NetRecordRpt::initUI(const QString& titletext)
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

    netRecordsView = new QTableView(this);
    initViewDetail(netRecordsView);
    viewlist << netRecordsView;
}

void NetRecordRpt::initModel()
{

    netRecordsMod = new QStandardItemModel(this);
    ModelUtil::initIntenetHistoryCheckModel(netRecordsMod, netRecordsView);
    modellist << netRecordsMod;
}

void NetRecordRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(554);
    view->move(0, 46);
    initViewStyle(view);
}

void NetRecordRpt::addNetRecordsInfo(const QVariantList& result)
{
    ModelUtil::addIntenetHistoryCheckModel(netRecordsMod, result);
}
