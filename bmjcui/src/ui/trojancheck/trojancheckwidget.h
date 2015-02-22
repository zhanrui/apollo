#ifndef TROJANCHECKWIDGET_H
#define TROJANCHECKWIDGET_H

#include "src/ui/base/basestylewidget.h"
class QStandardItemModel;
class QTableView;
class StaticButton;
class QLabel;
class TabButton;
class QCheckBox;
class QComboBox;
class QLineEdit;
class CommonWidget;

class TrojanCheckWidget : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit TrojanCheckWidget(QWidget* parent = 0);
    ~TrojanCheckWidget();

private:
    void initUI();
    void initConnect();

signals:
    void setParameter(const QString& name, const QString& value);
    void enableThreatDocument();
    void disableThreatDocument();
    void enableNetworkWeapon();
    void disableNetworkWeapon();


public slots:
    void startCheck();
    void cancelCheck();
    void updateCheckingElapsedTime();
    void completerateUpdate(const int completerate, const QString& status);
    void dataCountUpdate(const int totalproblems, const int totalinfomations);

    void setFolderPath();
    void setCheckType();

public:
    StaticButton* returnbtn;
    StaticButton* startcheckbtn;
    StaticButton* cancelcheckbtn;


    QLabel* trojanchecklogo;
    QLabel* descriptiontitle;
    QLabel* description;

    QLabel* progressbar_background;
    QLabel* progressbar_front;
    QLabel* checkingElapsedTime;

    QTimer* checkingElapsedTimer;
    //QLabel* vline;
    //QLabel* hline;

    unsigned int checkingStartTime;

    CommonWidget* settings;

    StaticButton* pathBrowserBtn;
    QLineEdit* pathLE;


    QLineEdit* typeLE;
    QCheckBox* threatdocumentCheck;
    QCheckBox* networkweaponCheck;

    StaticButton* checkResultBtn;
};

#endif // TROJANCHECKWIDGET_H
