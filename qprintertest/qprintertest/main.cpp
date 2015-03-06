#include <QApplication>
#include <QStringList>
#include <QString>
#include <QPrinter>
#include <QTextDocument>
#include <QTextBlock>
#include <QPainter>
#include <QDebug>
#include <QProcess>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    qDebug() << "1";
    QStringList title;
    title.push_back(QStringLiteral("名称"));
    title.push_back(QStringLiteral("修改日期"));
    title.push_back(QStringLiteral("类型"));
    title.push_back(QStringLiteral("大小"));

    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("print.pdf");
    printer.setColorMode(QPrinter::Color);

    QFile filebootstrap(":bootstrap.min.css");
    filebootstrap.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inbootstrap(&filebootstrap);
    QString stylesheetbootstrap;
    inbootstrap >> stylesheetbootstrap;

    QFile filebootstraptheme(":bootstrap-theme.min.css");
    filebootstraptheme.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inbootstraptheme(&filebootstrap);
    QString stylesheetbootstraptheme;
    inbootstraptheme >> stylesheetbootstraptheme;

    QString html;
    html += "<html>";
    html += "<head>";

    html += "<style type='text/css'>";
    //html += "  table, th, td {border-collapse: collapse;border-spacing: 0;border-width:6px; border-style: solid; border-color: red;color:#009900;}";
    html += "  table, th, td {border: none;color:#000000;}";

    html += " table{border:none;background:#ffffff;}";
    html += " th,td{border:none;padding:5px 15px;}";
    html += " th{font-weight:bold;background:#afafaf;;}";
    html += " td{background:#efefef;}";
    html += " div{font-weight:bold;font-size:250px;}";

    html += " </style>";
    html += "</head>";
    html += "<body>";
    html += "<div  align='center' >LINUX保密检查报告</div>";
     html += "<div  align='center' ><img src='test.jpg'  alt='上海鲜花港 - 郁金香' /></div>";
    html += "<p/><p/><p/>";
    html += "<table   width='100%'   >";
    html += "      <caption>Optional table caption.</caption>";
    html += "      <thead>";
    html += "        <tr>";
    html += "           <th>#</th>";
    html += "           <th>First Name</th>";
    html += "           <th>Last Name</th>";
    html += "           <th>Username</th>";
    html += "        </tr>";
    html += "      </thead>";
    html += "     <tbody>";
    html += "      <tr>";
    html += "         <th >1</th>";
    html += "         <td >ark</td>";
    html += "         <td>Otto</td>";
    html += "         <td>@mdo任城精英剿匪 战败 耗粮5969 获得返还粮草5372任城精英剿匪 战败 耗粮5969 获得返还粮草5372</td>";
    html += "      </tr>";
    html += "      </tbody>";
    html += "   </table>";
    html += "</body>";
    html += "</html>";

    qDebug() << html;

    QTextDocument text_document;
    //text_document.setDefaultStyleSheet(stylesheetbootstrap+stylesheetbootstraptheme);
    text_document.setHtml(html);
    text_document.print(&printer);
    text_document.end();

    //qDebug()<<"2";
    //QPainter painter;
    //if (!painter.begin(&printer)) { // failed to open file
    //    qWarning("failed to open file, is it writable?");
    //    return 1;
    //}
    //painter.drawText(10, 10, "Test");
    //if (!printer.newPage()) {
    //    qWarning("failed in flushing page to disk, disk full?");
    //    return 1;
    // }

    //  qDebug()<<"3";
    // painter.drawText(10, 10, "Test 2");
    //  bool status = painter.end();
    //   qDebug()<<status;

    QStringList argo, list;
    QProcess* exec;
    exec = new QProcess();
    argo << "xdg-open"
         << "print.pdf";
    //list << "PATH=/sw/bin:/sw/sbin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/X11/bin:/usr/X11R6/bin";
    //exec->setEnvironment(list);

    exec->start("/bin/bash", argo);

    return a.exec();
}
