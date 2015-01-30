#ifndef TASKSCENE_H
#define TASKSCENE_H

#include <QString>
#include <QVariantList>
class TaskScene
{

public:
    explicit TaskScene();
    ~TaskScene();
    virtual QString getSupportedScene();
    virtual QList<QString> getSupportedFunctions();
    virtual void progressUpdate( const QString& functionname, const int currentcompletion, const QString& currentstatus);
    virtual void errorUpdate( const QString& functionname, const QString& errordescrition);
    virtual void dataUpdate( const QString& functionname, const QVariantList& result);

signals:

public slots:
};

#endif // TASKSCENE_H
