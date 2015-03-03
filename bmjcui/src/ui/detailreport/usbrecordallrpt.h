#ifndef USBRECORDALLRPT_H
#define USBRECORDALLRPT_H


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

class UsbRecordAllRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit UsbRecordAllRpt(QWidget* parent ,const QString & title);
    ~UsbRecordAllRpt();
    void initUI(const QString & title);
    void initModel();
    void initConnection();

    void initViewDetail(QTableView* view);

public slots:
    void addUsbCommonInfo(const QVariantList& result);
    void addUsbDeepInfo(const QVariantList& result);


    void selectUsbCommonInfo();
    void selectUsbDeepInfo();


public:

    TaskButton* usbCommonInfoBtn;
    TaskButton* usbDeepInfoBtn;



    QStandardItemModel* usbCommonInfoMod;
    QStandardItemModel* usbDeepInfoMod;




    QTableView* usbCommonInfoView;
    QTableView* usbDeepInfoView;





};

#endif // USBRECORDALLRPT_H
