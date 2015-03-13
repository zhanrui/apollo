#ifndef ONEKEYCHECKMAINWIDGET_H
#define ONEKEYCHECKMAINWIDGET_H

#include "src/ui/base/basestylewidget.h"
class QStandardItemModel;
class QTableView;
class StaticButton;
class QLabel;
class TabButton;
class MainWindow;

class OneKeyCheckSettingWidget;


class OneKeyCheckMainWidget : public BaseStyleWidget
{
    Q_OBJECT
public:
    explicit OneKeyCheckMainWidget( MainWindow* mainwindow);
    ~OneKeyCheckMainWidget();


private:
    void initUI();
    void initConnect();
    void initModel();

signals:

public slots:

    void startCheck();
    void cancelCheck();
    void updateCheckingElapsedTime();
    void completerateUpdate(const int completerate, const QString& status);
    void dataCountUpdate(const int totalproblems ,const int totalinfomations);

public:

    TabButton* basicinfobtn;
    TabButton* deviceconnectionbtn;
    TabButton* netbrowserbtn;
    TabButton* systemsecuritybtn;
    TabButton* securitythreatbtn;
    TabButton* usbcheckbtn;
    TabButton* filecheckbtn;
    TabButton* tjcheckbtn;
    TabButton* imagecheckbtn;


    QList< TabButton*> tabbuttonlist;


    StaticButton* returnbtn;
    StaticButton* startcheckbtn;
    StaticButton* cancelcheckbtn;
    StaticButton* settingbtn;

    QLabel* onekeychecklogo;
    QLabel* descriptiontitle;
    QLabel* description;

    QLabel* progressbar_background;
    QLabel* progressbar_front;
    QLabel* checkingElapsedTime;

    QTimer *checkingElapsedTimer;
    //QLabel* vline;
    //QLabel* hline;

    unsigned int checkingStartTime;


     MainWindow * mainwindow;
};

#endif // ONEKEYCHECKMAINWIDGET_H
