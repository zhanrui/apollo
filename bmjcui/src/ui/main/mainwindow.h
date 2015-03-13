#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "src/ui/base/shadowwidget.h"

class MainWidget;
class CommonCheckWidget;
class FileCheckWidget;
class FileCheckCommonRpt;
class TrojanCheckWidget;
class TrojanCheckRpt;

class NetRecordDeepCheckWidget;
class NetRecordDeepRpt;
class NetRecordDeepCheckState;
class UsbDeepCheckWidget;
class UsbRecordDeepRpt;
class UsbDeepCheckState;

class CheckReportWidget;
class RptCreator;

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
class CommonCheckState;
class FileCheckState;
class TrojanCheckState;
class ImageCheckState;
class BaseReport;

class ImageCheckWidget;
class ImageCheckRpt;

class DeepCheckWidget;

class OneKeyCheckState;
class OneKeyCheckMainWidget;
class OneKeyCheckSettingWidget;

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
    CommonCheckWidget* commonCheckWidget;
    BasicInfoRpt* ccBasicInfoRpt;
    DeviceConnectRpt* ccDeviceConnectRpt;
    NetRecordCommonRpt* ccNetRecordRpt;
    SystemSecurityRpt* ccSystemSecurityRpt;
    SecurityThreatRpt* ccSecurityThreatRpt;
    UsbRecordCommonRpt* ccUsbRecordCommonRpt;
    QList<BaseReport*> ccReports;

    FileCheckWidget* fileCheckWidget;
    FileCheckCommonRpt* fcFileCheckCommonRpt;
    QList<BaseReport*> fcReports;

    TrojanCheckWidget* trojanCheckWidget;
    TrojanCheckRpt* tcTrojanCheckRpt;
    QList<BaseReport*> tcReports;

    ImageCheckWidget* imageCheckWidget;
    ImageCheckRpt* icImageCheckRpt;
    QList<BaseReport*> icReports;

    DeepCheckWidget* deepCheckWidget;

    NetRecordDeepCheckWidget* netRecordDeepCheckWidget;
    NetRecordDeepRpt* nrdNetRecordDeepRpt;
    QList<BaseReport*> nrdReports;

    UsbDeepCheckWidget* usbDeepCheckWidget;
    UsbRecordDeepRpt* udUsbRecordDeepRpt;
    QList<BaseReport*> udReports;

    OneKeyCheckMainWidget* oneKeyCheckMainWidget;
    OneKeyCheckSettingWidget* oneKeyCheckSettingWidget;
    BasicInfoRpt* okcBasicInfoRpt;
    DeviceConnectRpt* okcDeviceConnectRpt;
    NetRecordCommonRpt* okcNetRecordRpt;
    SystemSecurityRpt* okcSystemSecurityRpt;
    SecurityThreatRpt* okcSecurityThreatRpt;
    UsbRecordCommonRpt* okcUsbRecordCommonRpt;
    FileCheckCommonRpt* okcFileCheckCommonRpt;
    TrojanCheckRpt* okcTrojanCheckRpt;
    ImageCheckRpt* okcImageCheckRpt;
    QList<BaseReport*> okcReports;

    //Animation
    QParallelAnimationGroup* widgetSwitchAnimation;

    //Init State In Other Thread
    QThread* statethread;
    InterfaceForTool* interfaceForTool;
    ToolUtil* toolUtil;
    CommonCheckState* commonCheckState;
    FileCheckState* fileCheckState;
    TrojanCheckState* trojanCheckState;
    ImageCheckState* imageCheckState;
    NetRecordDeepCheckState* netRecordDeepCheckState;
    UsbDeepCheckState* usbDeepCheckState;
    OneKeyCheckState* oneKeyCheckState;

    CheckReportWidget* checkReportWidget;
    RptCreator* rptCreator;

    //SceneMap
};

#endif // MAINWINDOW_H
