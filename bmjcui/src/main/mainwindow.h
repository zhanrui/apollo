#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "common/shadowwidget.h"


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


};

#endif // MAINWINDOW_H
