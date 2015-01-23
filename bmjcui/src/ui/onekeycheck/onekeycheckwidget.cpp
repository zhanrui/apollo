#include "onekeycheckwidget.h"
#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/onekeycheck/tabbutton.h"
#include "src/ui/onekeycheck/mydelegate.h"
#include <QLabel>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QBrush>
#include <QScrollBar>
#include <QAbstractItemView>
#include <QStyledItemDelegate>
#include <QItemDelegate>



OneKeyCheckWidget::OneKeyCheckWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{
    initModel();
    initUI();
    initConnect();
}

OneKeyCheckWidget::~OneKeyCheckWidget()
{
}

void OneKeyCheckWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);
    startcheckbtn = new StaticButton(":image/onekeycheck/startcheckbtn", 3, this);
    startcheckbtn->move(703, 60);
    onekeychecklogo = new QLabel(this);
    onekeychecklogo->setPixmap(QPixmap(":image/onekeycheck/onekeychecklogo"));
    onekeychecklogo->move(40, 55);
    descriptiontitle = new QLabel(this);
    descriptiontitle->setText("请至少选择一项检查");
    descriptiontitle->setObjectName("descriptiontitle");
    descriptiontitle->move(130, 69);
    description = new QLabel(this);
    description->setText("经常检查，让电脑保持最安全状态");
    description->setObjectName("description");
    description->move(133, 109);

    //hline = new QLabel(this);
    //hline->setPixmap(QPixmap(":image/onekeycheck/hline"));
    //hline->move(0,153);

    QLabel* vline = new QLabel(this);
    vline->setPixmap(QPixmap(":image/onekeycheck/vline"));
    vline->move(192, 153);

    int start = 153;
    int between = 57;
    int x = 1;
    deviceconnectionbtn = new TabButton(":image/onekeycheck/leftbutton/deviceconnectionbtn", this);
    deviceconnectionbtn->move(x, start);
    netbrowserbtn = new TabButton(":image/onekeycheck/leftbutton/netbrowserbtn", this);
    netbrowserbtn->move(x, start + (between)*1);
    systemsecuritybtn = new TabButton(":image/onekeycheck/leftbutton/systemsecuritybtn", this);
    systemsecuritybtn->move(x, start + (between)*2);
    securitythreatbtn = new TabButton(":image/onekeycheck/leftbutton/securitythreatbtn", this);
    securitythreatbtn->move(x, start + (between)*3);
    usbcheckbtn = new TabButton(":image/onekeycheck/leftbutton/usbcheckbtn", this);
    usbcheckbtn->move(x, start + (between)*4);
    filecheckbtn = new TabButton(":image/onekeycheck/leftbutton/filecheckbtn", this);
    filecheckbtn->move(x, start + (between)*5);
    tjcheckbtn = new TabButton(":image/onekeycheck/leftbutton/tjcheckbtn", this);
    tjcheckbtn->move(x, start + (between)*6);

    for (int i = 0; i < 7; i++) {
        QLabel* hline = new QLabel(this);
        hline->setPixmap(QPixmap(":image/onekeycheck/hline"));
        hline->move(0, start + (between) * (i + 1));
    }

    checkresult = new QTableView(this);
    checkresult->setMinimumWidth(707);
    checkresult->setMinimumHeight(447);
    checkresult->move(193, 153);
    checkresult->verticalHeader()->hide();
    checkresult->horizontalHeader()->setHighlightSections(false);
    checkresult->horizontalHeader()->setFixedHeight(36);
    checkresult->setGridStyle(Qt::NoPen);


    checkresult->setShowGrid(false);
    checkresult->setEditTriggers(QAbstractItemView::NoEditTriggers);
    checkresult->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    checkresult->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    //checkresult->setItemDelegate(new QItemDelegate(checkresult));

    checkresult->setModel(filecheckmodel);
}
void OneKeyCheckWidget::initConnect()
{
}
void OneKeyCheckWidget::initModel()
{
    filecheckmodel = new QStandardItemModel(this);
    //filecheck->setHeaderData(0, Qt::Horizontal, "姓名");
    //filecheck->setHeaderData(1, Qt::Horizontal, "性别");

    QStandardItem* nameHead = new QStandardItem("姓名");

    QStandardItem* sexHead = new QStandardItem("性别");

    filecheckmodel->setHorizontalHeaderItem(0, nameHead);
    filecheckmodel->setHorizontalHeaderItem(1, sexHead);

    QStandardItem* name = new QStandardItem("李磊");
    QStandardItem* sex = new QStandardItem("男");

    //sex->setCheckState( !section.hidden ? Qt::Checked : Qt::Unchecked );
    //visibilityItem->setData( QVariant::fromValue( section ), Qt::UserRole + 1 );
    //visibilityItem->setData("hello",);
    //filecheckmodel->appendRow(QList<QStandardItem*>() << name << sex);
    filecheckmodel->insertRows(0, 14);
    //tjcheck = new QStandardItemModel(this);
    //thcheck = new QStandardItemModel(this);
}
