#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "src/ui/base/shadowwidget.h"

class MainWidget;
class OneKeyCheckWidget;
class DeviceConnectRpt;
class QParallelAnimationGroup;

class SysButtonGroup;
class ToolUtil;

class QThread;
class InterfaceForTool;
class OneKeyCheckState;

class MainWindow : public ShadowWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);

private:
    void initUI();
    void initDBus();
    void initConnect();
    void initAnim();
    void switchWidgetToLeft(QWidget* currentWidget,  QWidget* showWidget);
    void switchWidgetToRight(QWidget* currentWidget,  QWidget* showWidget);

public slots:

    void showMin();
    void closeWidget();

public:
   //Common Widgets
    SysButtonGroup* sysButtonGroup;

    //Window Widgets
    MainWidget* mainWidget;
    OneKeyCheckWidget* oneKeyCheckWidget;
    DeviceConnectRpt* okcDeviceConnectRpt;

    //Animation
    QParallelAnimationGroup*  widgetSwitchAnimation;

    //Init State In Other Thread
    QThread* statethread;
    InterfaceForTool* interfaceForTool;
    ToolUtil* toolUtil;
    OneKeyCheckState* oneKeyCheckState;

    //SceneMap
};

#endif // MAINWINDOW_H
