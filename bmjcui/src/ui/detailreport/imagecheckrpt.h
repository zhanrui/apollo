#ifndef IMAGECHECKRPT_H
#define IMAGECHECKRPT_H


#include <QWidget>

#include <QList>
#include <QLabel>
#include <QString>
#include <src/ui/base/basestylewidget.h>
#include <src/ui/detailreport/basereport.h>
class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;

class ImageCheckRpt: public BaseStyleWidget , public BaseReport{
    Q_OBJECT

public:
    explicit ImageCheckRpt(QWidget* parent, const QString& title);
    ~ImageCheckRpt();

    void initUI(const QString& title);
    void initModel();
    void initViewDetail(QTableView* view);

public slots:
    void addImageCheckInfo(const QVariantList& result);

public:
    QStandardItemModel* imageCheckMod;
    QTableView* imageCheckView;
};


#endif // IMAGECHECKRPT_H
