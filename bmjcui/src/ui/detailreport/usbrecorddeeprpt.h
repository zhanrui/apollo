#ifndef USBRECORDDEEPRPT_H
#define USBRECORDDEEPRPT_H


class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;
#include <src/ui/base/basestylewidget.h>
#include <src/ui/detailreport/basereport.h>
class UsbRecordDeepRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit UsbRecordDeepRpt(QWidget* parent, const QString& title);
    ~UsbRecordDeepRpt();

    void initUI(const QString& title);
    void initModel();
    void initViewDetail(QTableView* view);

public slots:
    void addUsbRecordsInfo(const QVariantList& result);

public:

    QStandardItemModel* usbRecordsMod;

    QTableView* usbRecordsView;

};


#endif // USBRECORDDEEPRPT_H
