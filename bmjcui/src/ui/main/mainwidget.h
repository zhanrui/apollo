#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QList>
#include <src/ui/base/basestylewidget.h>


class QLabel;
class MainTitleWidget;
class CommonWidget;
class StaticButton;
class QParallelAnimationGroup;
class TaskButton;
class MainWidget : public BaseStyleWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent = 0);
    ~MainWidget();

private:
    void initUI();
    void initConnect();
    void initAnim();

signals:

public slots:
    void toolbarSwitchLeft();
    void toolbarSwitchRight();

public:
    QWidget* mainTitleWidget;
    QLabel* logoLabel;
    QLabel* textLabel;
    QLabel* biglogoLabel;
    QLabel* statusLabel;

    StaticButton* toleft;
    StaticButton* toright;
    QLabel* version;
    QLabel* line;

    CommonWidget* toolbar;
    StaticButton *onekeychecklogo;
    QLabel* onekeychecktext;
    StaticButton *commonchecklogo;
    //TaskButton * commonchecklogo;
    QLabel* commonchecktext;
    StaticButton *deepchecklogo;
    QLabel* deepchecktext;


    StaticButton *filechecklogo;
    QLabel* filechecktext;
    StaticButton *tjchecklogo;
    QLabel* tjchecktext;
    StaticButton *toollogo;
    QLabel* tooltext;

    QList<QWidget*> * buttonlist;

    QParallelAnimationGroup*  toolbarSwitchAnimation;


};

#endif // MAINWIDGET_H
