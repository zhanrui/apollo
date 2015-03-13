#ifndef IMAGECHECKSETTINGPART_H
#define IMAGECHECKSETTINGPART_H

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

class ImageCheckSettingPart : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit ImageCheckSettingPart(QWidget* parent = 0);
    ~ImageCheckSettingPart();
    bool validateParameter();

private:
    void initUI();
    void initConnect();

signals:
    void setParameter(const QString& name, const QString& value);
    void enableImageCheck();
    void disableImageCheck();

public slots:

    void setFolderPath();
    void setFileType();

public:
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

    CheckButton* statusbtn;
};

#endif // IMAGECHECKSETTINGPART_H
