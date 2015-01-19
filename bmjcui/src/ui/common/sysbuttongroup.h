#ifndef SYSBUTTONGROUP_H
#define SYSBUTTONGROUP_H

#include <QWidget>
class StaticButton;
class SysButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit SysButtonGroup(QWidget *parent = 0);

signals:
    //void playVideo();
    //void showSkin();
   // void showMenu();
    void showMin();
    void closeWidget();

public:
    StaticButton *minButton;
    StaticButton *closeButton;
};

#endif // SYSBUTTONGROUP_H
