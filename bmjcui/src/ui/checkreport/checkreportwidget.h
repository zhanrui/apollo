#ifndef CHECKREPORTWIDGET_H
#define CHECKREPORTWIDGET_H

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
class MainWindow;

class CheckReportWidget : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit CheckReportWidget(MainWindow* parent = 0);
    ~CheckReportWidget();
    void getTableString(QStandardItemModel* model, QString& html, const QString& tablename);
    void getSubTitleString(QString& html, const QString& subtitle);
    void getSectionTitleString(QString& html, const QString& sectiontitle);
    void getCssString(QString& html);
    QString getHtml();

private:
    void initUI();
    void initConnect();
    void initModel();

signals:
    void setParameter(const QString& name, const QString& value);
    void startCreateSig(const QString& filename, const QString& html);

public slots:
    void startCheck();
    void cancelCheck();
    void updateCheckingElapsedTime();
    void completerateUpdate(const int completerate, const QString& status);
    void dataCountUpdate(const int totalproblems, const int totalinfomations);

    void setFolderPath();

public:
    MainWindow* mainWindow;
    StaticButton* returnbtn;
    StaticButton* startcheckbtn;
    StaticButton* cancelcheckbtn;

    QLabel* filechecklogo;
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

    QLineEdit* typeLE;
    QCheckBox* onekeyCheck;
    QCheckBox* commonCheck;
    QCheckBox* deepCheck;
    QCheckBox* fileCheck;
    QCheckBox* tjCheck;
    QCheckBox* imageCheck;

    StaticButton* pathBrowserBtn;
    QLineEdit* pathLE;

    QLineEdit* nameLE;

    StaticButton* checkResultBtn;

    //    QStandardItemModel* osInfoMod;
    //    QStandardItemModel* cpuInfoMod;
    //    QStandardItemModel* biosInfoMod;
    //    QStandardItemModel* motherBoardInfoMod;
    //    QStandardItemModel* memoryInfoMod;
    //    QStandardItemModel* graphicsCardInfoMod;

    //    QStandardItemModel* hardDiskInfoMod;
    //    QStandardItemModel* virtualMachineInfoMod;
    //    QStandardItemModel* netConfigMod;
    //    QStandardItemModel* adapterDeviceMod;
    //    QStandardItemModel* printDeviceMod;
    //    QStandardItemModel* blueToothDeviceMod;

    //    QStandardItemModel* fileRoutineCheckMod;

    //    QStandardItemModel* imageCheckMod;

    //    QStandardItemModel* netRecordCommonInfoMod;
    //    QStandardItemModel* netRecordDeepInfoMod;

    //    QStandardItemModel* securityPolicyMod;
    //    QStandardItemModel* openPortMod;
    //    QStandardItemModel* sharingInfoMod;
    //    QStandardItemModel* networkSoftwareMod;
    //    QStandardItemModel* groupInfoMod;
    //    QStandardItemModel* userInfoMod;
    //    QStandardItemModel* databaseInfoMod;
    //    QStandardItemModel* eventLogMod;
    //    QStandardItemModel* userAuthenticationMod;

    //    QStandardItemModel* patchNotInstalledMod;
    //    QStandardItemModel* systemServiceMod;
    //    QStandardItemModel* systemProcessMod;
    //    QStandardItemModel* evenProductMod;
    //    QStandardItemModel* timeSwitchMachineMod;
    //    QStandardItemModel* securitySoftwareMod;

    //    QStandardItemModel* networkWeaponMod;
    //    QStandardItemModel* threatDocumentMod;

    //    QStandardItemModel* usbCommonInfoMod;
    //    QStandardItemModel* usbDeepInfoMod;
};

#endif // CHECKREPORTWIDGET_H
