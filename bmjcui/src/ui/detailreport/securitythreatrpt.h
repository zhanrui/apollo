#ifndef SECURITYTHREATRPT_H
#define SECURITYTHREATRPT_H

#include <QWidget>

#include <QList>
#include <QLabel>
#include <QString>
#include <src/ui/base/basestylewidget.h>
#include <src/ui/detailreport/basereport.h>
class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;
class SecurityThreatRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit SecurityThreatRpt(QWidget* parent, const QString& title);
    ~SecurityThreatRpt();
    void initUI(const QString& title);
    void initModel();
    void initConnection();
    void initViewDetail(QTableView* view);

public slots:
    void addSecurityPolicy(const QVariantList& result);
    void addOpenPort(const QVariantList& result);
    void addSharingInfo(const QVariantList& result);
    void addNetworkSoftware(const QVariantList& result);
    void addGroupInfo(const QVariantList& result);
    void addUserInfo(const QVariantList& result);
    void addDatabaseInfo(const QVariantList& result);
    void addEventLog(const QVariantList& result);
    void addUserAuthentication(const QVariantList& result);

    void selectSecurityPolicy();
    void selectOpenPort();
    void selectSharingInfo();
    void selectNetworkSoftware();
    void selectGroupInfo();
    void selectUserInfo();
    void selectDatabaseInfo();
    void selectEventLog();
    void selectUserAuthentication();


public:

    TaskButton* securityPolicyBtn;
    TaskButton* openPortBtn;
    TaskButton* sharingInfoBtn;
    TaskButton* networkSoftwareBtn;
    TaskButton* groupInfoBtn;
    TaskButton* userInfoBtn;
    TaskButton* databaseInfoBtn;
    TaskButton* eventLogBtn;
    TaskButton* userAuthenticationBtn;

    QStandardItemModel* securityPolicyMod;
    QStandardItemModel* openPortMod;
    QStandardItemModel* sharingInfoMod;
    QStandardItemModel* networkSoftwareMod;
    QStandardItemModel* groupInfoMod;
    QStandardItemModel* userInfoMod;
    QStandardItemModel* databaseInfoMod;
    QStandardItemModel* eventLogMod;
    QStandardItemModel* userAuthenticationMod;

    QTableView* securityPolicyView;
    QTableView* openPortView;
    QTableView* sharingInfoView;
    QTableView* networkSoftwareView;
    QTableView* groupInfoView;
    QTableView* userInfoView;
    QTableView* databaseInfoView;
    QTableView* eventLogView;
    QTableView* userAuthenticationView;

};

#endif // SECURITYTHREATRPT_H
