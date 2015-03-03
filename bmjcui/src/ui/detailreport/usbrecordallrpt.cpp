#include "usbrecordallrpt.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QVariantMap>
#include <QVariant>
#include <QLabel>

#include "src/ui/common/taskbutton.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/onekeycheck/mydelegate.h"
#include "src/util/modelutil.h"
#include "src/ui/detailreport/basereport.h"
UsbRecordAllRpt::UsbRecordAllRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent),BaseReport()
{
    initUI(title);
    initModel();
    initConnection();
    selectUsbCommonInfo();
}

UsbRecordAllRpt::~UsbRecordAllRpt()
{
}

void UsbRecordAllRpt::initUI(const QString& titletext)
{
    this->setFixedSize(900, 600);

    QLabel* title = new QLabel(titletext, this);
    title->adjustSize();
    title->move(900 / 2 - title->width() / 2, 17);

    QLabel* icon = new QLabel(this);
    icon->setPixmap(QPixmap(":image/detailreport/logo"));
    icon->adjustSize();
    icon->move(900 / 2 - title->width() / 2 - 3 - icon->width(), 12);

    returnbtn = new StaticButton(":image/detailreport/returnbtn", 3, this);
    returnbtn->move(0, 0);

    usbCommonInfoBtn = new TaskButton(":image/detailreport/deviceconnect/hardDiskInfoBtn", this);
    usbCommonInfoBtn->move(27, 60);
    usbDeepInfoBtn = new TaskButton(":image/detailreport/deviceconnect/virtualMachineInfoBtn", this);
    usbDeepInfoBtn->move(27 + 142, 60);


    taskbtnlist << usbCommonInfoBtn << usbDeepInfoBtn ;

    usbCommonInfoView = new QTableView(this);
    //hardDiskInfoView->setModel(hardDiskInfoMod);
    initViewDetail(usbCommonInfoView);

    usbDeepInfoView = new QTableView(this);
    //virtualMachineInfoView->setModel(virtualMachineInfoMod);
    initViewDetail(usbDeepInfoView);

      viewlist << usbCommonInfoView << usbDeepInfoView;
}

void UsbRecordAllRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(447);
    view->move(0, 153);
    initViewStyle(view);
}

void UsbRecordAllRpt::initModel()
{

    usbCommonInfoMod = new QStandardItemModel(this);
    ModelUtil::initUsbCheckModel(usbCommonInfoMod, usbCommonInfoView);
    usbCommonInfoView->setColumnWidth(0, 200);
    usbDeepInfoMod = new QStandardItemModel(this);
    ModelUtil::initUsbCheckModel(usbDeepInfoMod, usbDeepInfoView);

    modellist << usbCommonInfoMod << usbDeepInfoMod ;
}

void UsbRecordAllRpt::initConnection()
{
    connect(usbCommonInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectUsbCommonInfo()));
    connect(usbDeepInfoBtn, SIGNAL(buttonClicked()), this, SLOT(selectUsbDeepInfo()));

}

void UsbRecordAllRpt::addUsbCommonInfo(const QVariantList& result)
{
    ModelUtil::addUsbCheckModel(usbCommonInfoMod, result);
}
void UsbRecordAllRpt::addUsbDeepInfo(const QVariantList& result)
{
    ModelUtil::addUsbCheckModel(usbDeepInfoMod, result);
}

void UsbRecordAllRpt::selectUsbCommonInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    usbCommonInfoBtn->select();
    usbCommonInfoView->show();
}
void UsbRecordAllRpt::selectUsbDeepInfo()
{
    unselectAllTaskbtn();
    hideAllView();
    usbDeepInfoBtn->select();
    usbDeepInfoView->show();
}



