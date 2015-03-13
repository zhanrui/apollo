#ifndef FILECHECKSETTINGPART_H
#define FILECHECKSETTINGPART_H

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

class FileCheckSettingPart : public BaseStyleWidget {
    Q_OBJECT

public:
    explicit FileCheckSettingPart(QWidget* parent = 0);
    ~FileCheckSettingPart();
    bool validateParameter();



private:
    void initUI();
    void initConnect();
    void initModel();

signals:
    void setParameter(const QString& name, const QString& value);
    void enableFileCheck();
    void disableFileCheck();

public slots:

    void setFolderPath();
    void setFileType();

public:
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

    CheckButton* statusbtn;


};

#endif // FILECHECKSETTINGPART_H
