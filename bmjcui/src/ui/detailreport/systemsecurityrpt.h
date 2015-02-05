#ifndef SYSTEMSECURITYRPT_H
#define SYSTEMSECURITYRPT_H

#include <src/ui/base/basestylewidget.h>
#include <QWidget>

#include <QList>
#include <QLabel>
#include <QString>
#include <src/ui/detailreport/basereport.h>
class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;

class SystemSecurityRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit SystemSecurityRpt(QWidget* parent ,const QString & title);
    ~SystemSecurityRpt();
    void initUI(const QString & title);
    void initModel();
    void initConnection();
    void initViewDetail(QTableView* view);

public slots:
    //*   3-1.未安装补丁	patchNotInstalled
    //*	 3-2.系统服务	systemService
    //*	 3-3.系统进程	systemProcess
    //*	 3-4.外连产品	evenProduct
    //*	 3-5.开关机时间	timeSwitchMachine
    //*	 3-6.安全软件	securitySoftware


    void addPatchNotInstalled(const QVariantList& result);
    void addSystemService(const QVariantList& result);
    void addSystemProcess(const QVariantList& result);
    void addEvenProduct(const QVariantList& result);
    void addTimeSwitchMachine(const QVariantList& result);
    void addSecuritySoftware(const QVariantList& result);

    void selectPatchNotInstalled();
    void selectSystemService();
    void selectSystemProcess();
    void selectEvenProduct();
    void selectTimeSwitchMachine();
    void selectSecuritySoftware();

public:

    TaskButton* patchNotInstalledBtn;
    TaskButton* systemServiceBtn;
    TaskButton* systemProcessBtn;
    TaskButton* evenProductBtn;
    TaskButton* timeSwitchMachineBtn;
    TaskButton* securitySoftwareBtn;


    QStandardItemModel* patchNotInstalledMod;
    QStandardItemModel* systemServiceMod;
    QStandardItemModel* systemProcessMod;
    QStandardItemModel* evenProductMod;
    QStandardItemModel* timeSwitchMachineMod;
    QStandardItemModel* securitySoftwareMod;


    QTableView* patchNotInstalledView;
    QTableView* systemServiceView;
    QTableView* systemProcessView;
    QTableView* evenProductView;
    QTableView* timeSwitchMachineView;
    QTableView* securitySoftwareView;





};
#endif // SYSTEMSECURITYRPT_H
