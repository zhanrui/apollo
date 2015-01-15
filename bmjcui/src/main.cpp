
#include <QApplication>
#include <QFile>
#include <QThread>
#include <QDBusConnection>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusInterface>

#include <src/main/mainwindow.h>
#include <src/state/onekeycheckstate.h>
#include <src/util/toolutil.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    


    //Init QSS
    QFile qss(":qss/default");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();



    //Check Debus
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
        return 1;
    }

    if (!connection.registerService("com.example.bmjc")) {
        qDebug() << connection.lastError().message();
        exit(1);
    }


    //Init In Other Thread
    OneKeyCheckState  oneKeyCheckState;
    if(! connection.registerObject("/bmjc/onekeycheck", &oneKeyCheckState, QDBusConnection::ExportAllSlots)){
           qDebug() << "connection.lastError().message()";
           exit(1);
    }
    QThread thread ;
    oneKeyCheckState.moveToThread(&thread);
    thread.start();

    ToolUtil::getSystemBasicInfo();

    //Init MainWindow
   // MainWindow w;
    //w.setObjectName("mainwindow");
   // w.show();











    //Dbus Call Example


    //QDBusConnection::sessionBus().connect("com.example.bmjc","/onekeycheck","onekeycheckInterface","action",this,SLOT(actionSlot(QString &));





    //QDBusReply<int> reply = iface.call("checkIn", num_room);
    //if (reply.isValid()) {
    //        num_room = reply.value();
    //        printf("Got %d %s\n", num_room, (num_room > 1) ? "rooms" : "room");
    //} else {
    //       fprintf(stderr, "Check In fail!\n");
    //}


    return a.exec();
}
