#include "imagecheckrpt.h"



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
ImageCheckRpt::~ImageCheckRpt()
{
}

ImageCheckRpt::ImageCheckRpt(QWidget* parent, const QString& title)
    : BaseStyleWidget(parent)  , BaseReport()
{
    initUI(title);
    initModel();
    imageCheckView->show();
}

void ImageCheckRpt::initUI(const QString& titletext)
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

    imageCheckView = new QTableView(this);
    initViewDetail(imageCheckView);
    imageCheckView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(imageCheckView, SIGNAL(customContextMenuRequested(const QPoint&)),
            SLOT(showImageCheckContextMenu(const QPoint&)));
    viewlist << imageCheckView;

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

void ImageCheckRpt::showImageCheckContextMenu(const QPoint& pos)
{
    QModelIndex index = imageCheckView->indexAt(pos);
    //openfile->setData("/tmp");
    openfile->setData(index.data(FILEFULLPATH));
    //openfilepath->setData("/tmp");
    openfilepath->setData(index.data(FILEFOLDERPATH));
    qDebug()<<index.data().toString();
    contextmenu->popup(imageCheckView->viewport()->mapToGlobal(pos));

}
void ImageCheckRpt::initModel()
{

    imageCheckMod = new QStandardItemModel(this);
    ModelUtil::initImageCheckModel(imageCheckMod, imageCheckView);
    modellist << imageCheckMod;
}

void ImageCheckRpt::initViewDetail(QTableView* view)
{
    view->setMinimumWidth(900);
    view->setMinimumHeight(554);
    view->move(0, 46);
    initViewStyle(view);
}

void ImageCheckRpt::addImageCheckInfo(const QVariantList& result)
{
    ModelUtil::addImageCheckModel(imageCheckMod, result);
}


