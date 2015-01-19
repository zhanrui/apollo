#ifndef INTERFACEFORTOOL_H
#define INTERFACEFORTOOL_H

#include <QObject>
#include <QString>

class InterfaceForTool : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "bmjc.ui")
public:
    explicit InterfaceForTool(QObject* parent = 0);
    ~InterfaceForTool();

signals:
    void systemInfoUpdate(const QString& qs);

public slots:
    void updateFromTool(const QString& messages);
};

#endif // INTERFACEFORTOOL_H
