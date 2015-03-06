#include "deepcheckwidget.h"

#include "src/ui/base/basestylewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/base/commonwidget.h"
#include "src/ui/commoncheck/tabbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
#include "src/common/globals.h"
#include "src/common/common.h"
#include <QLabel>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QBrush>
#include <QScrollBar>
#include <QAbstractItemView>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QFrame>
#include <QDateTime>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QMovie>
#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QtWidgets>

DeepCheckWidget::DeepCheckWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{


    initUI();
    initConnect();
}

DeepCheckWidget::~DeepCheckWidget()
{
}

void DeepCheckWidget::initUI()
{
    this->setFixedSize(900, 600);
    returnbtn = new StaticButton(":image/common/returnbtn", 3, this);
    returnbtn->move(0, 0);

    QLabel* filechecklogo = new QLabel(this);
    filechecklogo->setPixmap(QPixmap(":image/filecheck/filechecklogo"));
    filechecklogo->move(40, 55);
    QLabel* descriptiontitle = new QLabel(this);
    descriptiontitle->setText("文件检查");
    descriptiontitle->setObjectName("fc_descriptiontitle");
    descriptiontitle->move(130, 69);
    QLabel* description = new QLabel(this);
    description->setText("查看用户终端是否存在越级存储文件");
    description->setObjectName("fc_description");
    description->move(133, 109);




    CommonWidget * settings = new CommonWidget(this);
    settings->setFixedSize(900, 447);
    settings->setObjectName("deepchecksetting");
    int y = 153;
    settings->move(0, y);

    QLabel* hline = new QLabel(settings);
    hline->move(0, 209 - y);
    hline->setPixmap(QPixmap(":image/filecheck/hline"));

    QLabel* deepUsbCheckIcon = new QLabel(settings);
    deepUsbCheckIcon->move(53, 184 - y);
    deepUsbCheckIcon->setPixmap(QPixmap(":image/filecheck/pathIcon"));
    QLabel* deepUsbCheckDes = new QLabel(settings);
    deepUsbCheckDes->move(82, 184 - y);
    deepUsbCheckDes->setText("检查路径");
    deepUsbCheckbtn = new StaticButton(":image/filecheck/pathBrowserBtn", 3, settings);
    deepUsbCheckbtn->move(772, 180 - y);

    QLabel* deepNetRecCheckIcon = new QLabel(settings);
    deepNetRecCheckIcon->move(53, 184 - y);
    deepNetRecCheckIcon->setPixmap(QPixmap(":image/filecheck/pathIcon"));
    QLabel* deepNetRecCheckDes = new QLabel(settings);
    deepNetRecCheckDes->move(82, 184 - y);
    deepNetRecCheckDes->setText("检查路径");
    deepNetRecCheckbtn = new StaticButton(":image/filecheck/pathBrowserBtn", 3, settings);
    deepNetRecCheckbtn->move(772, 180 - y);




}
void DeepCheckWidget::initConnect()
{

}
