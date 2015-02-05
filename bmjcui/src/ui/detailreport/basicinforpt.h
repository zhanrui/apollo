#ifndef BASICINFORPT_H
#define BASICINFORPT_H

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
class BasicInfoRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit BasicInfoRpt(QWidget* parent, const QString& title);
    ~BasicInfoRpt();
    void initUI(const QString& title);
    void initModel();
    void initConnection();
    void initViewDetail(QTableView* view);

public slots:



    void addOSInfo(const QVariantList& result);
    void addCpuInfo(const QVariantList& result);
    void addBiosInfo(const QVariantList& result);
    void addMotherBoardInfo(const QVariantList& result);
    void addMemoryInfo(const QVariantList& result);
    void addGraphicsCardInfo(const QVariantList& result);

    void selectOSInfo();
    void selectCpuInfo();
    void selectBiosInfo();
    void selectMotherBoardInfo();
    void selectMemoryInfo();
    void selectGraphicsCardInfo();

public:

    // *   1-1.操作系统	operatingSystemInfo
    //*   1-2.CPU信息	cpuInfo
    //*   1-3.BIOS信息	biosInfo
    //*	 1-4.主板信息	motherboardInfo
    //*	 1-5.内存信息	memoryInfo
    // *	 1-6.显卡信息	graphicsCardInfo

    TaskButton* osInfoBtn;
    TaskButton* cpuInfoBtn;
    TaskButton* biosInfoBtn;
    TaskButton* motherBoardInfoBtn;
    TaskButton* memoryInfoBtn;
    TaskButton* graphicsCardInfoBtn;



    QStandardItemModel* osInfoMod;
    QStandardItemModel* cpuInfoMod;
    QStandardItemModel* biosInfoMod;
    QStandardItemModel* motherBoardInfoMod;
    QStandardItemModel* memoryInfoMod;
    QStandardItemModel* graphicsCardInfoMod;



    QTableView* osView;
    QTableView* cpuInfoView;
    QTableView* biosInfoView;
    QTableView* motherBoardInfoView;
    QTableView* memoryInfoView;
    QTableView* graphicsCardInfoView;




};

#endif // BASICINFORPT_H
