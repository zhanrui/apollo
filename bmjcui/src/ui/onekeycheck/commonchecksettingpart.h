#ifndef COMMONCHECKSETTINGPART_H
#define COMMONCHECKSETTINGPART_H

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

class CommonCheckSettingPart: public BaseStyleWidget {
    Q_OBJECT

public:
    explicit CommonCheckSettingPart(QWidget* parent = 0);
    ~CommonCheckSettingPart();


private:
    void initUI();
    void initConnect();


signals:
    void enableBasicInfo();
    void enableDeviceConnection();
    void enableNetBrowser();
    void enableSystemSecurity();
    void enableSecurityThreat();
    void enableUsbCheck();

    void disableBasicInfo();
    void disableDeviceConnection();
    void disableNetBrowser();
    void disableSystemSecurity();
    void disableSecurityThreat();
    void disableUsbCheck();

public slots:





public:





    CheckButton* basicinfobtn;
    CheckButton* deviceconnectionbtn;
    CheckButton* netrecordbtn;
    CheckButton* systemsecuritybtn;
    CheckButton* securitythreatbtn;
    CheckButton* usbrecordbtn;






};
#endif // COMMONCHECKSETTINGPART_H
