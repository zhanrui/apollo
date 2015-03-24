#include "rptcreator.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QPrinter>
#include <QTextDocument>
#include <QTextBlock>
#include <QProcess>
#include <QDebug>

#include "src/ui/main/mainwindow.h"
#include "src/ui/checkreport/checkreportwidget.h"

RptCreator::RptCreator(QObject* parent, MainWindow* mainWindow)
    : QObject(parent)
{
    CheckReportWidget* checkReportWidget = mainWindow->checkReportWidget;
    connect(checkReportWidget, &CheckReportWidget::startCreateSig, this, &RptCreator::createReport);
    connect(this, &RptCreator::createCompleteSig, checkReportWidget, &CheckReportWidget::completerateUpdate);
}

RptCreator::~RptCreator()
{
}
void RptCreator::createReport(const QString& filename, const QString& html)
{
    qDebug() << filename;
    qDebug() << html;
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    printer.setFontEmbeddingEnabled(false);
    printer.setColorMode(QPrinter::Color);
    QTextDocument text_document;
    //text_document.setDefaultStyleSheet(stylesheetbootstrap+stylesheetbootstraptheme);
    text_document.setHtml(html);
    text_document.print(&printer);
    text_document.end();

    QStringList argo;
    QProcess* exec;
    exec = new QProcess();
    argo << "xdg-open"
         << filename;
    //list << "PATH=/sw/bin:/sw/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/X11/bin:/usr/X11R6/bin";
    //exec->setEnvironment(list);

    exec->start("/bin/bash", argo);
    connect(exec, static_cast<void (QProcess::*)(int)>(&QProcess::finished), this,
            [=](int exitCode) {
     delete exec;
    });
    emit createCompleteSig(100, "报告创建已完成,请查看");
}
