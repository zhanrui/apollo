#include "filecheckcommonrpt.h"

#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QVariantMap>
#include <QVariant>
#include <QLabel>
#include <QAction>
#include <QProcess>
#include <QMenu>


#include "src/ui/common/taskbutton.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/commoncheck/mydelegate.h"
#include "src/util/modelutil.h"
#include "src/ui/detailreport/basereport.h"
FileCheckCommonRpt::~FileCheckCommonRpt()
{
}

FileCheckCommonRpt::FileCheckCommonRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent)
    , BaseReport()
{
    initUI(title);
    initModel();
    fileRoutineCheckView->show();
}

void FileCheckCommonRpt::initUI(const QString& titletext)
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

    fileRoutineCheckView = new QTableView(this);
    initViewDetail(fileRoutineCheckView);
    fileRoutineCheckView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(fileRoutineCheckView, SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(showFileCheckContextMenu(const QPoint&)));
    viewlist << fileRoutineCheckView;

    contextmenu = new QMenu(this);
    openfile = new QAction("打开文件", contextmenu);
    connect(openfile, &QAction::triggered,
            [=]() {
        QStringList argo;
        QProcess* exec ;
        exec = new QProcess();
        argo << "xdg-open"
             << openfile->data().toString();
        exec->start("/bin/bash", argo);
        connect(exec, static_cast<void (QProcess::*)(int)>(&QProcess::finished), this,
                [=](int exitCode) {
         delete exec;
        });
    });
    openfilepath = new QAction("打开文件所在文件夹", contextmenu);
    connect(openfilepath, &QAction::triggered,
            [=]() {
        QStringList argo;
        QProcess* exec ;
        exec = new QProcess();
        argo << "xdg-open"
             << openfilepath->data().toString();
        exec->start("/bin/bash", argo);
        connect(exec, static_cast<void (QProcess::*)(int)>(&QProcess::finished), this,
                [=](int exitCode) {
         delete exec;
        });
    });
    contextmenu->addAction(openfile);
    contextmenu->addAction(openfilepath);
}

void FileCheckCommonRpt::showFileCheckContextMenu(const QPoint& pos)
{
    QModelIndex index = fileRoutineCheckView->indexAt(pos);
    //openfile->setData("/home/arthur/backends/src/apollo/fileCheck/fileRoutineCheck.py");
    openfile->setData(index.data(FILEFULLPATH));
    //openfilepath->setData("/tmp");
    openfilepath->setData(index.data(FILEFOLDERPATH));
    qDebug()<<index.data(FILEFULLPATH);
    qDebug()<<index.data(FILEFOLDERPATH);
    contextmenu->popup(fileRoutineCheckView->viewport()->mapToGlobal(pos));
}

void FileCheckCommonRpt::initModel()
{

    fileRoutineCheckMod = new QStandardItemModel(this);
    ModelUtil::initFileCheckModel(fileRoutineCheckMod, fileRoutineCheckView);
    modellist << fileRoutineCheckMod;
}

void FileCheckCommonRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(554);
    view->move(0, 46);
    initViewStyle(view);
}

void FileCheckCommonRpt::addFileRoutineCheckInfo(const QVariantList& result)
{
    ModelUtil::addFileCheckModel(fileRoutineCheckMod, result);
}
