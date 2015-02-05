#ifndef BASEREPORT_H
#define BASEREPORT_H

#include <QWidget>

#include <QList>
#include <QLabel>
#include <QString>
#include <src/ui/base/basestylewidget.h>
class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;

class BaseReport {
public:
    BaseReport();
    ~BaseReport();
    void initViewStyle(QTableView* view);
    void unselectAllTaskbtn();
    void hideAllView();

public:
    QList<TaskButton*> taskbtnlist;
    QList<QStandardItemModel*> modellist;
    QList<QTableView*> viewlist;
    StaticButton* returnbtn;
};

#endif // BASEREPORT_H
