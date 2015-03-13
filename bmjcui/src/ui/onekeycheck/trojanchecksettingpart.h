#ifndef TROJANCHECKSETTINGPART_H
#define TROJANCHECKSETTINGPART_H

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
class CheckButton;

class TrojanCheckSettingPart : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit TrojanCheckSettingPart(QWidget* parent = 0);
    ~TrojanCheckSettingPart();
    bool validateParameter();

private:
    void initUI();
    void initConnect();


signals:
    void setParameter(const QString& name, const QString& value);
    void setTaskEnableStatus(bool status);
    void enableThreatDocument();
    void disableThreatDocument();


public slots:

    void setFolderPath();
    void setCheckType();

public:
    StaticButton* pathBrowserBtn;
    QLineEdit* pathLE;

    //QLineEdit* typeLE;
    //QCheckBox* threatdocumentCheck;
    //QCheckBox* networkweaponCheck;

    CheckButton* statusbtn;
};

#endif // TROJANCHECKSETTINGPART_H
