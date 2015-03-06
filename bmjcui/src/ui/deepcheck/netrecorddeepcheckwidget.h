#ifndef NETRECORDDEEPCHECKWIDGET_H
#define NETRECORDDEEPCHECKWIDGET_H



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

class NetRecordDeepCheckWidget : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit NetRecordDeepCheckWidget(QWidget* parent = 0);
    ~NetRecordDeepCheckWidget();

private:
    void initUI();
    void initConnect();
    void initModel();

signals:
    void setParameter(const QString& name, const QString& value);
    void startCheckSig();

public slots:
    void startCheck();
    void cancelCheck();
    void updateCheckingElapsedTime();
    void completerateUpdate(const int completerate, const QString& status);
    void dataCountUpdate(const int totalproblems, const int totalinfomations);

    void setFolderPath();
    void setFileType();



public:
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

    CommonWidget * settings;

    StaticButton* pathBrowserBtn;
    QLineEdit* pathLE;

    QComboBox* keyWordCB;

    QLineEdit* typeLE;
    QCheckBox* docCheck;
    QCheckBox* xlsCheck;
    QCheckBox* pptCheck;
    QCheckBox* pdfCheck;
    QCheckBox* wpsCheck;
    QCheckBox* zipCheck;

    StaticButton* checkResultBtn;


};


#endif // NETRECORDDEEPCHECKWIDGET_H
