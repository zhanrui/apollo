#include <QDBusConnection>
#include "onekeycheckstate.h"
#include <QDebug>
#include <QAbstractItemModel>

//#include "onekeycheck_adaptor.h"
//#include "onekeycheck_interface.h"

OneKeyCheckState::OneKeyCheckState(QObject* parent)
    : QObject(parent)
{

    //QDBusConnection::sessionBus().connect("com.example.bmjc","/bmjc/onekeycheck","bmjc.onekeycheck","action",this,SLOT(actionSlot(QString &)));
    // add our D-Bus interface and connect to D-Bus
    //new OnekeycheckAdaptor(this);
    //QDBusConnection connection = QDBusConnection::sessionBus();
    //connection.registerService("org.example.bmjc");
    //connection.registerObject("/onekeycheck", this);

    //onekeycheck *iface;
    //iface = new onekeycheck(QString(), QString(), QDBusConnection::sessionBus(), this);

    //connect(iface, SIGNAL(action(QString)), this, SLOT(actionSlot(QString)));
}

void OneKeyCheckState::actionSlot(const QString& qs)
{

    qDebug() << "debug " << qs;
}

OneKeyCheckState::~OneKeyCheckState()
{
}
