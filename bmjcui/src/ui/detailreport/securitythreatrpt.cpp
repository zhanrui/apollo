#include "securitythreatrpt.h"

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

SecurityThreatRpt::SecurityThreatRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent)
    , BaseReport()
{
    initUI(title);
    initModel();
    initConnection();
    selectSecurityPolicy();
}

SecurityThreatRpt::~SecurityThreatRpt()
{
}

void SecurityThreatRpt::initUI(const QString& titletext)
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

    securityPolicyBtn = new TaskButton(":image/detailreport/securitythreat/securityPolicyBtn", this);
    securityPolicyBtn->move(17, 60);
    openPortBtn = new TaskButton(":image/detailreport/securitythreat/openPortBtn", this);
    openPortBtn->move(17 + 97, 60);
    sharingInfoBtn = new TaskButton(":image/detailreport/securitythreat/sharingInfoBtn", this);
    sharingInfoBtn->move(17 + 97 * 2, 60);
    networkSoftwareBtn = new TaskButton(":image/detailreport/securitythreat/networkSoftwareBtn", this);
    networkSoftwareBtn->move(17 + 97 * 3, 60);
    groupInfoBtn = new TaskButton(":image/detailreport/securitythreat/groupInfoBtn", this);
    groupInfoBtn->move(17 + 97 * 4, 60);
    userInfoBtn = new TaskButton(":image/detailreport/securitythreat/userInfoBtn", this);
    userInfoBtn->move(17 + 97 * 5, 60);

    databaseInfoBtn = new TaskButton(":image/detailreport/securitythreat/databaseInfoBtn", this);
    databaseInfoBtn->move(17 + 97 * 6, 60);
    eventLogBtn = new TaskButton(":image/detailreport/securitythreat/eventLogBtn", this);
    eventLogBtn->move(17 + 97 * 7, 60);
    userAuthenticationBtn = new TaskButton(":image/detailreport/securitythreat/userAuthenticationBtn", this);
    userAuthenticationBtn->move(17 + 97 * 8, 60);

    taskbtnlist << securityPolicyBtn << openPortBtn << sharingInfoBtn
                << networkSoftwareBtn << groupInfoBtn << userInfoBtn
                << databaseInfoBtn << eventLogBtn << userAuthenticationBtn;

    for (TaskButton* task : taskbtnlist) {
        task->running_movie->move((task->running_defaultstatus->width()) / 2 - 10, 50);
    }

    securityPolicyView = new QTableView(this);
    initViewDetail(securityPolicyView);

    openPortView = new QTableView(this);
    initViewDetail(openPortView);

    sharingInfoView = new QTableView(this);
    initViewDetail(sharingInfoView);

    networkSoftwareView = new QTableView(this);
    initViewDetail(networkSoftwareView);

    groupInfoView = new QTableView(this);
    initViewDetail(groupInfoView);

    userInfoView = new QTableView(this);
    initViewDetail(userInfoView);

    databaseInfoView = new QTableView(this);
    initViewDetail(databaseInfoView);
    eventLogView = new QTableView(this);
    initViewDetail(eventLogView);
    userAuthenticationView = new QTableView(this);
    initViewDetail(userAuthenticationView);

    viewlist << securityPolicyView << openPortView << sharingInfoView
             << networkSoftwareView << groupInfoView << userInfoView
             << databaseInfoView << eventLogView << userAuthenticationView;
}

void SecurityThreatRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(447);
    view->move(0, 153);
    initViewStyle(view);
}

void SecurityThreatRpt::initModel()
{
    securityPolicyMod = new QStandardItemModel(this);
    ModelUtil::initSecurityStrategyModel(securityPolicyMod, securityPolicyView);
    openPortMod = new QStandardItemModel(this);
    ModelUtil::initOpenPortModel(openPortMod, openPortView);
    sharingInfoMod = new QStandardItemModel(this);
    ModelUtil::initSharedInfoModel(sharingInfoMod, sharingInfoView);
    networkSoftwareMod = new QStandardItemModel(this);
    ModelUtil::initInternetToolModel(networkSoftwareMod, networkSoftwareView);
    groupInfoMod = new QStandardItemModel(this);
    ModelUtil::initUserGroupInfoModel(groupInfoMod, groupInfoView);
    userInfoMod = new QStandardItemModel(this);
    ModelUtil::initUserInfoModel(userInfoMod, userInfoView);

    databaseInfoMod = new QStandardItemModel(this);
    ModelUtil::initDataBaseInfoModel(databaseInfoMod, databaseInfoView);
    eventLogMod = new QStandardItemModel(this);
    ModelUtil::initEventLogModel(eventLogMod, eventLogView);
    userAuthenticationMod = new QStandardItemModel(this);
    ModelUtil::initAuthenticatioInfoModel(userAuthenticationMod, userAuthenticationView);

    modellist << securityPolicyMod << openPortMod << sharingInfoMod
              << networkSoftwareMod << groupInfoMod << userInfoMod
              << databaseInfoMod << eventLogMod << userAuthenticationMod;
}

void SecurityThreatRpt::initConnection()
{
    connect(securityPolicyBtn, SIGNAL(buttonClicked()), this, SLOT(selectSecurityPolicy()));
    connect(openPortBtn, SIGNAL(buttonClicked()), this, SLOT(selectOpenPort()));
    connect(sharingInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectSharingInfo()));
    connect(networkSoftwareBtn, SIGNAL(buttonClicked()), this, SLOT(selectNetworkSoftware()));
    connect(groupInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectGroupInfo()));
    connect(userInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectUserInfo()));

    connect(databaseInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectDatabaseInfo()));
    connect(eventLogBtn, SIGNAL(buttonClicked()), this, SLOT(selectEventLog()));
    connect(userAuthenticationBtn, SIGNAL(buttonClicked()), this, SLOT(selectUserAuthentication()));
}

void SecurityThreatRpt::addSecurityPolicy(const QVariantList& result)
{
    ModelUtil::addSecurityStrategy(securityPolicyMod, result);
}
void SecurityThreatRpt::addOpenPort(const QVariantList& result)
{
    ModelUtil::addOpenPort(openPortMod, result);
}
void SecurityThreatRpt::addSharingInfo(const QVariantList& result)
{
    ModelUtil::addSharedInfo(sharingInfoMod, result);
}
void SecurityThreatRpt::addNetworkSoftware(const QVariantList& result)
{
    ModelUtil::addInternetTool(networkSoftwareMod, result);
}
void SecurityThreatRpt::addGroupInfo(const QVariantList& result)
{
    ModelUtil::addUserGroupInfo(groupInfoMod, result);
}
void SecurityThreatRpt::addUserInfo(const QVariantList& result)
{
    ModelUtil::addUserInfo(userInfoMod, result);
}

void SecurityThreatRpt::addDatabaseInfo(const QVariantList& result)
{
    ModelUtil::addDataBaseInfo(databaseInfoMod, result);
}
void SecurityThreatRpt::addEventLog(const QVariantList& result)
{
    ModelUtil::addEventLog(eventLogMod, result);
}
void SecurityThreatRpt::addUserAuthentication(const QVariantList& result)
{
    ModelUtil::addAuthenticatioInfo(userAuthenticationMod, result);
}

void SecurityThreatRpt::selectSecurityPolicy()
{
    unselectAllTaskbtn();
    hideAllView();
    securityPolicyBtn->select();
    securityPolicyView->show();
}
void SecurityThreatRpt::selectOpenPort()
{
    unselectAllTaskbtn();
    hideAllView();
    openPortBtn->select();
    openPortView->show();
}
void SecurityThreatRpt::selectSharingInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    sharingInfoBtn->select();
    sharingInfoView->show();
}
void SecurityThreatRpt::selectNetworkSoftware()
{
    unselectAllTaskbtn();
    hideAllView();
    networkSoftwareBtn->select();
    networkSoftwareView->show();
}
void SecurityThreatRpt::selectGroupInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    groupInfoBtn->select();
    groupInfoView->show();
}
void SecurityThreatRpt::selectUserInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    userInfoBtn->select();
    userInfoView->show();
}
void SecurityThreatRpt::selectDatabaseInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    databaseInfoBtn->select();
    databaseInfoView->show();
}
void SecurityThreatRpt::selectEventLog()
{
    unselectAllTaskbtn();
    hideAllView();
    eventLogBtn->select();
    eventLogView->show();
}
void SecurityThreatRpt::selectUserAuthentication()
{
    unselectAllTaskbtn();
    hideAllView();
    userAuthenticationBtn->select();
    userAuthenticationView->show();
}
