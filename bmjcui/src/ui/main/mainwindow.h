#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "src/ui/base/shadowwidget.h"

class MainWidget;
class OneKeyCheckWidget;
class FileCheckWidget;
class FileCheckCommonRpt;
class TrojanCheckWidget;
class TrojanCheckRpt;

class BasicInfoRpt;
class DeviceConnectRpt;
class NetRecordCommonRpt;
class SystemSecurityRpt;
class SecurityThreatRpt;
class UsbRecordCommonRpt;

class QParallelAnimationGroup;

class SysButtonGroup;
class ToolUtil;

class QThread;
class InterfaceForTool;
class OneKeyCheckState;
class FileCheckState;
class TrojanCheckState;
class BaseReport;

class MainWindow : public ShadowWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);

private:
    void initUI();
    void initDBus();
    void initConnect();
    void initAnim();
    void switchWidgetToLeft(QWidget* currentWidget, QWidget* showWidget);
    void switchWidgetToRight(QWidget* currentWidget, QWidget* showWidget);

public slots:

    void showMin();
    void closeWidget();

public:
    //Common Widgets
    SysButtonGroup* sysButtonGroup;

    //Window Widgets
    MainWidget* mainWidget;
    OneKeyCheckWidget* oneKeyCheckWidget;
    BasicInfoRpt* okcBasicInfoRpt;
    DeviceConnectRpt* okcDeviceConnectRpt;
    NetRecordCommonRpt* okcNetRecordRpt;
    SystemSecurityRpt* okcSystemSecurityRpt;
    SecurityThreatRpt* okcSecurityThreatRpt;
    UsbRecordCommonRpt* okcUsbRecordCommonRpt;
    QList<BaseReport*> okcReports;

    FileCheckWidget* fileCheckWidget;
    FileCheckCommonRpt* fcFileCheckCommonRpt;
    QList<BaseReport*> fcReports;

    TrojanCheckWidget* trojanCheckWidget;
    TrojanCheckRpt* tcTrojanCheckRpt;
    QList<BaseReport*> tcReports;

    //Animation
    QParallelAnimationGroup* widgetSwitchAnimation;

    //Init State In Other Thread
    QThread* statethread;
    InterfaceForTool* interfaceForTool;
    ToolUtil* toolUtil;
    OneKeyCheckState* oneKeyCheckState;
    FileCheckState* fileCheckState;
    TrojanCheckState* trojanCheckState;

    //SceneMap
};

#endif // MAINWINDOW_H
