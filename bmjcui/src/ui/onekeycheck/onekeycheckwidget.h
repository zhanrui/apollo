#ifndef ONEKEYCHECKWIDGET_H
#define ONEKEYCHECKWIDGET_H
#include "src/ui/base/basestylewidget.h"

class QStandardItemModel;
class QTableView;
class StaticButton;
class QLabel;
class TabButton;

class OneKeyCheckWidget : public BaseStyleWidget
{
    Q_OBJECT
public:
    explicit OneKeyCheckWidget(QWidget* parent = 0);
    ~OneKeyCheckWidget();

private:
    void initUI();
    void initConnect();
    void initModel();

signals:

public slots:
    //void toolbarSwitchLeft();
    //void toolbarSwitchRight();

public:

    TabButton* deviceconnectionbtn;
    TabButton* netbrowserbtn;
    TabButton* systemsecuritybtn;
    TabButton* securitythreatbtn;
    TabButton* usbcheckbtn;
    TabButton* filecheckbtn;
    TabButton* tjcheckbtn;

    QStandardItemModel * deviceconnectionmodel;
    QStandardItemModel * netbrowsermodel;
    QStandardItemModel * systemsecuritymodel;
    QStandardItemModel * securitythreatmodel;
    QStandardItemModel * usbcheckmodel;
    QStandardItemModel * filecheckmodel;
    QStandardItemModel * tjcheckmodel;

    QTableView *    checkresult ;

    StaticButton* returnbtn;
    StaticButton* startcheckbtn;

    QLabel* onekeychecklogo;
    QLabel* descriptiontitle;
    QLabel* description;
    //QLabel* vline;
    //QLabel* hline;
};

#endif // ONEKEYCHECKWIDGET_H
