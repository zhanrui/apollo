#ifndef INTERFACEFORTOOL_H
#define INTERFACEFORTOOL_H

#include <QObject>
#include <QString>
#include <QVariantList>

class InterfaceForTool : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "bmjc.ui")
public:
    explicit InterfaceForTool(QObject* parent = 0);
    ~InterfaceForTool();

signals:

    void progressUpdate(const QString& scenename, const QString& functionname, const int currentcompletion, const QString& currentstatus);
    void errorUpdate(const QString& scenename, const QString& functionname, const QString& errordescrition);
    void dataUpdate(const QString& scenename, const QString& functionname, const QVariantList& result);

public slots:
    void updateFromTool(const QString& messages);
};

#endif // INTERFACEFORTOOL_H
