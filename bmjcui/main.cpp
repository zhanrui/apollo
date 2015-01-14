#include <QApplication>
#include <QFile>
#include <QThread>
#include <src/main/mainwindow.h>
#include <src/state/onekeycheckstate.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":qss/default");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    MainWindow *w = new MainWindow;
    w->setObjectName("mainwindow");
    w->show();

    OneKeyCheckState  oneKeyCheckState =  new OneKeyCheckState;
    QThread *thread = new QThread;
    oneKeyCheckState->moveToThread(thread);
    thread->exec();


    return a.exec();
}
