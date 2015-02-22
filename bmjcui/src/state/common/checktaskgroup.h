#ifndef CHECKTASKGROUP_H
#define CHECKTASKGROUP_H
#include "checktask.h"

#include <QObject>
class TabButton;
class QList<CheckTask>;
class CheckTask;

class CheckTaskGroup : public QObject {
    Q_OBJECT
public:
    explicit CheckTaskGroup(QObject* parent,const QString& scenename, const int weight,const QList<CheckTask*>& taskslist);

    ~CheckTaskGroup();
    void initConnect(const QList<CheckTask*> & tasks);
public slots:
    //Call From State/UI
    void startExecute();
    void stopExecute();
    void disableGroup();
    void enableGroup();
    //From Task

    void progressUpdate(const int completeunit ,const QString & status);
    void dataCountUpdate(const int totalproblems ,const int totalinfomations);
    void totalUnitChanged(const int value);
signals:
    void errorFindSig();// To UI
    void completeSig();// To UI

    void progressUpdateSig(const int completeunit ,const QString & status);
    void completerateUpdateSig(const int completerate ,const QString & status);

    void dataCountUpdateSig(const int totalproblems ,const int totalinfomations );
    void startSig();// To Task
    void stopSig();// To Task
    void disableSig();// To Task
    void enableSig();// To Task
    void totalUnitChangedSig(const int value);
public:

    bool enabled;
    int weight;
    QString scenename;


    bool start;

    QString currentstatus;
    bool errorfind;

    int totalproblems;
    int totalinfomations;

    int totalcompleteunit;
    int currentcompleteunit;
};

#endif // CHECKTASKGROUP_H
