/****************************************************************************
**
** This Class is for call the Tools ( for example : check the system info , check file ,check Virus
**
****************************************************************************/

#ifndef TOOLUTIL_H
#define TOOLUTIL_H
#include <QObject>
#include <QString>

class QDBusInterface;
class ToolUtil : public QObject {
    Q_OBJECT
public:
    explicit ToolUtil(QObject* parent = 0);
    ~ToolUtil();
public slots:
    void startOneKeyCheck();
    void cancelOneKeyCheck();
    void getSystemBasicInfo();
    void sendMessage(const QString& messages);
public :
 QDBusInterface *iface;
};

#endif // TOOLUTIL_H
