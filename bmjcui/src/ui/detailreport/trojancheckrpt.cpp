#include "trojancheckrpt.h"

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
TrojanCheckRpt::TrojanCheckRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent)
    , BaseReport()
{
    initUI(title);
    initModel();
    initConnection();
    selectNetworkWeapon();
}

TrojanCheckRpt::~TrojanCheckRpt()
{
}

void TrojanCheckRpt::initUI(const QString& titletext)
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

    networkWeaponBtn = new TaskButton(":image/detailreport/trojancheck/networkWeaponBtn", this);
    networkWeaponBtn->move(250, 60);
    threatDocumentBtn = new TaskButton(":image/detailreport/trojancheck/threatDocumentBtn", this);
    threatDocumentBtn->move(465, 60);

    taskbtnlist << networkWeaponBtn << threatDocumentBtn;

    for (TaskButton* task : taskbtnlist) {
        task->running_movie->move((task->running_defaultstatus->width()) / 2 - 10, 50);
    }

    networkWeaponView = new QTableView(this);
    initViewDetail(networkWeaponView);

    threatDocumentView = new QTableView(this);
    initViewDetail(threatDocumentView);

    viewlist << networkWeaponView << threatDocumentView;
}

void TrojanCheckRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(447);
    view->move(0, 153);
    initViewStyle(view);
}

void TrojanCheckRpt::initModel()
{

    networkWeaponMod = new QStandardItemModel(this);
    ModelUtil::initMalwareCheckModel(networkWeaponMod, networkWeaponView);

    threatDocumentMod = new QStandardItemModel(this);
    ModelUtil::initVirusCheckModel(threatDocumentMod, threatDocumentView);

    modellist << networkWeaponMod << threatDocumentMod;
}

void TrojanCheckRpt::initConnection()
{
    connect(networkWeaponBtn, SIGNAL(buttonClicked()), this, SLOT(selectNetworkWeapon()));
    connect(threatDocumentBtn, SIGNAL(buttonClicked()), this, SLOT(selectThreatDocument()));
}

void TrojanCheckRpt::addNetworkWeapon(const QVariantList& result)
{
    ModelUtil::addMalwareCheckModel(networkWeaponMod, result);
}
void TrojanCheckRpt::addThreatDocument(const QVariantList& result)
{
    ModelUtil::addVirusCheckModel(threatDocumentMod, result);
}


void TrojanCheckRpt::selectNetworkWeapon()
{
    unselectAllTaskbtn();
    hideAllView();
    networkWeaponBtn->select();
    networkWeaponView->show();
}
void TrojanCheckRpt::selectThreatDocument()
{
    unselectAllTaskbtn();
    hideAllView();
    threatDocumentBtn->select();
    threatDocumentView->show();
}
