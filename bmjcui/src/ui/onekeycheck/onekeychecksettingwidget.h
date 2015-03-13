#ifndef ONEKEYCHECKSETTINGWIDGET_H
#define ONEKEYCHECKSETTINGWIDGET_H


#include "src/ui/base/basestylewidget.h"
class QStandardItemModel;
class QTableView;
class StaticButton;
class QLabel;
class TabButton;
class CommonCheckSettingPart;
class FileCheckSettingPart;
class TrojanCheckSettingPart;
class ImageCheckSettingPart;

class OneKeyCheckSettingWidget : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit OneKeyCheckSettingWidget(QWidget* parent = 0);
    ~OneKeyCheckSettingWidget();


private:
    void initUI();
    void initConnect();
    void unSelectAllSettingBtn();
    void unSelectAllSettingPart();

signals:
    void setFileCheckParameter(const QString& name, const QString& value);


public slots:


public:

    StaticButton* returnbtn;

    CommonCheckSettingPart * commonCheckSettingPart;
    FileCheckSettingPart* fileCheckSettingPart;
    TrojanCheckSettingPart* trojanCheckSettingPart;
    ImageCheckSettingPart* imageCheckSettingPart;

    QList<QWidget*> settingpartList;

    StaticButton* commonCheckBtn;
    StaticButton* fileCheckBtn;
    StaticButton* trojanCheckBtn;
    StaticButton* imageCheckBtn;

    QList<StaticButton*> settingBtnList;

};

#endif // ONEKEYCHECKSETTINGWIDGET_H
