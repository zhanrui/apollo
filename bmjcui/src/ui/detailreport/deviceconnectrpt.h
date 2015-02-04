#ifndef DEVICECONNECTRPT_H
#define DEVICECONNECTRPT_H

#include <QWidget>

#include <QList>
#include <src/ui/base/basestylewidget.h>
class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;
class DeviceConnectRpt : public BaseStyleWidget {
    Q_OBJECT
public:
    explicit DeviceConnectRpt(QWidget* parent = 0);
    ~DeviceConnectRpt();
    void initUI();
    void initModel();
    void initConnection();
    void unselectAllTaskbtn();

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

    QList<TaskButton*> taskbtnlist;

    QStandardItemModel* hardDiskInfoMod;
    QStandardItemModel* virtualMachineInfoMod;
    QStandardItemModel* netConfigMod;
    QStandardItemModel* adapterDeviceMod;
    QStandardItemModel* printDeviceMod;
    QStandardItemModel* blueToothDeviceMod;

    QTableView* checkresult;

    StaticButton* returnbtn;
    StaticButton* startcheckbtn;
    StaticButton* cancelcheckbtn;
};

#endif // DEVICECONNECTRPT_H
