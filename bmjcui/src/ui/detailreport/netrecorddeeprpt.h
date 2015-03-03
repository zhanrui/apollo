#ifndef NETRECORDDEEPRPT_H
#define NETRECORDDEEPRPT_H


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
class NetRecordDeepRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit NetRecordDeepRpt(QWidget* parent, const QString& title);
    ~NetRecordDeepRpt();

    void initUI(const QString& title);
    void initModel();
    void initViewDetail(QTableView* view);

public slots:
    void addNetRecordsInfo(const QVariantList& result);

public:

    QStandardItemModel* netRecordsMod;

    QTableView* netRecordsView;

};

#endif // NETRECORDDEEPRPT_H
