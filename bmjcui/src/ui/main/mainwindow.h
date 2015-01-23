#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "src/ui/base/shadowwidget.h"

class MainWidget;
class OneKeyCheckWidget;
class QParallelAnimationGroup;

class SysButtonGroup;

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
    void maintoonekeycheck();
    void onekeychecktomain();

public:

    //Widgets
    MainWidget* mainWidget;
    OneKeyCheckWidget* oneKeyCheckWidget;

    QParallelAnimationGroup*  widgetSwitchAnimation;


    SysButtonGroup* sysButtonGroup;

    //Init State In Other Thread
    QThread* statethread;
    InterfaceForTool* interfaceForTool;
    OneKeyCheckState* oneKeyCheckState;


};

#endif // MAINWINDOW_H
