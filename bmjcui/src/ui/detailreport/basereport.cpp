#include "basereport.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QVariantMap>
#include <QVariant>
#include <QLabel>

#include "src/ui/common/taskbutton.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
BaseReport::BaseReport()
{
    taskbtnlist = QList<TaskButton*>();
    modellist = QList<QStandardItemModel*>();
    viewlist = QList<QTableView*>();
}

BaseReport::~BaseReport()
{
}

void BaseReport::unselectAllTaskbtn()
{
    for (TaskButton* task : taskbtnlist) {
        task->unselect();
    }
}

void BaseReport::hideAllView()
{
    for (QTableView* view : viewlist) {
        view->hide();
    }
}

void BaseReport::initViewStyle(QTableView* view)
{
    view->verticalHeader()->hide();
    view->horizontalHeader()->setHighlightSections(false);
    view->horizontalHeader()->setFixedHeight(36);
    view->setGridStyle(Qt::NoPen);

    view->setShowGrid(false);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    view->setItemDelegate(new MyDelegate(view));
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::NoSelection);
    view->setFrameShape(QFrame::NoFrame);

    view->hide();
}
