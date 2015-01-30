#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "src/ui/base/shadowwidget.h"

class MainWidget;
class OneKeyCheckWidget;
class QParallelAnimationGroup;

class SysButtonGroup;
class ToolUtil;

class QThread;
class InterfaceForTool;
class OneKeyCheckState;
class TaskScene;

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

    void progressUpdate(const QString& scenename, const QString& functionname, const int currentcompletion, const QString& currentstatus);
    void errorUpdate(const QString& scenename, const QString& functionname, const QString& errordescrition);
    void dataUpdate(const QString& scenename, const QString& functionname, const QVariantList& result);

public:
   //Common Widgets
    SysButtonGroup* sysButtonGroup;

    //Window Widgets
    MainWidget* mainWidget;
    OneKeyCheckWidget* oneKeyCheckWidget;

    //Animation
    QParallelAnimationGroup*  widgetSwitchAnimation;

    //Init State In Other Thread
    QThread* statethread;
    InterfaceForTool* interfaceForTool;
    ToolUtil* toolUtil;

    //SceneMap
     QMap<QString,QList<TaskScene *> >*  sceneMap;
};

#endif // MAINWINDOW_H
