#ifndef USBRECORDCOMMONRPT_H
#define USBRECORDCOMMONRPT_H


class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;
#include <src/ui/base/basestylewidget.h>
#include <src/ui/detailreport/basereport.h>
class UsbRecordCommonRpt : public BaseStyleWidget , public BaseReport{
    Q_OBJECT
public:
    explicit UsbRecordCommonRpt(QWidget* parent, const QString& title);
    ~UsbRecordCommonRpt();

    void initUI(const QString& title);
    void initModel();
    void initViewDetail(QTableView* view);

public slots:
    void addUsbRecordsInfo(const QVariantList& result);

public:

    QStandardItemModel* usbRecordsMod;

    QTableView* usbRecordsView;

};

#endif // USBRECORDCOMMONRPT_H
