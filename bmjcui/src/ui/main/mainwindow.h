#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "src/ui/common/shadowwidget.h"

class MainWidget;
class OpacityWidget;

class MainWindow : public ShadowWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
private:
    void initUI();
    void initConnect();
    void initAnim();
private slots:

    void showMenu();
    void showMin();

public:
    MainWidget   *mainWidget;
    OpacityWidget *m_grayWidget;

};

#endif // MAINWINDOW_H
