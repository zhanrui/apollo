#ifndef DEVICECONNECTRPT_H
#define DEVICECONNECTRPT_H

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

class DeviceConnectRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit DeviceConnectRpt(QWidget* parent ,const QString & title);
    ~DeviceConnectRpt();
    void initUI(const QString & title);
    void initModel();
    void initConnection();

    void initViewDetail(QTableView* view);

public slots:
    void addHardDiskInfo(const QVariantList& result);
    void addVirtualMachineInfo(const QVariantList& result);
    void addNetConfig(const QVariantList& result);
    void addAdapterDevice(const QVariantList& result);
    void addPrintDevice(const QVariantList& result);
    void addBlueToothDevice(const QVariantList& result);

    void selectHardDiskInfo();
    void selectVirtualMachineInfo();
    void selectNetConfig();
    void selectAdapterDevice();
    void selectPrintDevice();
    void selectBlueToothDevice();

public:

    TaskButton* hardDiskInfoBtn;
    TaskButton* virtualMachineInfoBtn;
    TaskButton* netConfigBtn;
    TaskButton* adapterDeviceBtn;
    TaskButton* printDeviceBtn;
    TaskButton* blueToothDeviceBtn;



    QStandardItemModel* hardDiskInfoMod;
    QStandardItemModel* virtualMachineInfoMod;
    QStandardItemModel* netConfigMod;
    QStandardItemModel* adapterDeviceMod;
    QStandardItemModel* printDeviceMod;
    QStandardItemModel* blueToothDeviceMod;



    QTableView* hardDiskInfoView;
    QTableView* virtualMachineInfoView;
    QTableView* netConfigView;
    QTableView* adapterDeviceView;
    QTableView* printDeviceView;
    QTableView* blueToothDeviceView;




};

#endif // DEVICECONNECTRPT_H
