

#include <QApplication>
#include <QFile>
#include <QThread>
#include <QDBusConnection>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusInterface>
#include <QFontDatabase>
#include <QTextCodec>

#include <src/state/onekeycheckstate.h>
#include <src/util/toolutil.h>
#include <src/util/interfacefortool.h>
#include <src/ui/main/mainwindow.h>
#include <src/ui/common/sysbuttongroup.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    int returnvalue = QFontDatabase::addApplicationFont(":font/方正兰亭细黑.TTF");

    qDebug()<< "Font Load Result"<<returnvalue;

    //Init QSS
    QFile qss(":qss/default");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    MainWindow* w= new MainWindow();
    w->setObjectName("mainwindow");
    w->show();


    return a.exec();
}
