#ifndef DEEPCHECKWIDGET_H
#define DEEPCHECKWIDGET_H




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

class DeepCheckWidget : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit DeepCheckWidget(QWidget* parent = 0);
    ~DeepCheckWidget();


private:
    void initUI();
    void initConnect();


signals:


public slots:




public:
    StaticButton* returnbtn;
    StaticButton* deepUsbCheckbtn;
    StaticButton* deepNetRecCheckbtn;









};


#endif // DEEPCHECKWIDGET_H
