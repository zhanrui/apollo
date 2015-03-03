#ifndef NETRECORDALLRPT_H
#define NETRECORDALLRPT_H

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

class NetRecordAllRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit NetRecordAllRpt(QWidget* parent ,const QString & title);
    ~NetRecordAllRpt();
    void initUI(const QString & title);
    void initModel();
    void initConnection();

    void initViewDetail(QTableView* view);

public slots:
    void addNetRecordCommonInfo(const QVariantList& result);
    void addNetRecordDeepInfo(const QVariantList& result);


    void selectNetRecordCommonInfo();
    void selectNetRecordDeepInfo();


public:

    TaskButton* netRecordCommonInfoBtn;
    TaskButton* netRecordDeepInfoBtn;



    QStandardItemModel* netRecordCommonInfoMod;
    QStandardItemModel* netRecordDeepInfoMod;




    QTableView* netRecordCommonInfoView;
    QTableView* netRecordDeepInfoView;





};
#endif // NETRECORDALLRPT_H
