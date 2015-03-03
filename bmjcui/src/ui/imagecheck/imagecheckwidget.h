#ifndef IMAGECHECKWIDGET_H
#define IMAGECHECKWIDGET_H

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

class ImageCheckWidget : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit ImageCheckWidget(QWidget* parent = 0);
    ~ImageCheckWidget();

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
    QCheckBox* bmpCheck;
    QCheckBox* jpgCheck;
    QCheckBox* pngCheck;
    QCheckBox* gifCheck;
    QCheckBox* tifCheck;
    QCheckBox* dibCheck;

    StaticButton* checkResultBtn;
};

#endif // IMAGECHECKWIDGET_H
