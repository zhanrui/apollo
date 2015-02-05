#ifndef NETRECORDRPT_H
#define NETRECORDRPT_H

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
class NetRecordRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit NetRecordRpt(QWidget* parent, const QString& title);
    ~NetRecordRpt();

    void initUI(const QString& title);
    void initModel();
    void initViewDetail(QTableView* view);

public slots:
    void addNetRecordsInfo(const QVariantList& result);

public:

    QStandardItemModel* netRecordsMod;

    QTableView* netRecordsView;

};

#endif // NETRECORDRPT_H
