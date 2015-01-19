#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "src/ui/base/shadowwidget.h"

class MainWidget;
class OpacityWidget;
class SysButtonGroup;

class QThread;
class InterfaceForTool;
class OneKeyCheckState;

class QPushButton;

class MainWindow : public ShadowWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);

private:
    void initUI();
    void initDBus();
    void initConnect();
    void initAnim();


public slots:

    void showMenu();
    void showMin();
    void closeWidget();


public:

    //Widgets
    MainWidget* mainWidget;
    OpacityWidget* m_grayWidget;
    SysButtonGroup* sysButtonGroup;

    //Init State In Other Thread
    QThread* statethread;
    InterfaceForTool* interfaceForTool;
    OneKeyCheckState* oneKeyCheckState;
    //TestButton
     QPushButton *closeButton;
};

#endif // MAINWINDOW_H
