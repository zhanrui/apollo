#ifndef FILECHECKCOMMONRPT_H
#define FILECHECKCOMMONRPT_H

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
class QAction;
class QMenu;

class FileCheckCommonRpt: public BaseStyleWidget , public BaseReport{
    Q_OBJECT

public:
    explicit FileCheckCommonRpt(QWidget* parent, const QString& title);
    ~FileCheckCommonRpt();

    void initUI(const QString& title);
    void initModel();
    void initViewDetail(QTableView* view);

public slots:
    void addFileRoutineCheckInfo(const QVariantList& result);
    void showFileCheckContextMenu(const QPoint&);

public:
    QStandardItemModel* fileRoutineCheckMod;
    QTableView* fileRoutineCheckView;

    QMenu*  contextmenu;
    QAction* openfile;
    QAction* openfilepath ;
};

#endif // FILECHECKCOMMONRPT_H
