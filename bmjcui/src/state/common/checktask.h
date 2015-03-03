#ifndef CHECKTASK_H
#define CHECKTASK_H
#include <QString>
#include <QVariantMap>

#include <QObject>
class ToolUtil;

class CheckTask : public QObject {

    Q_OBJECT

public:
    CheckTask(QObject* parent, const QString& tname, const QString& sname, bool bCheck, int weight);
    CheckTask(QObject* parent, ToolUtil* tool, const QString& tname, const QString& sname, bool bCheck, int weight);
    ~CheckTask();
public slots:
    //Call From UI/Goup/State
    void startExecute();
    void stopExecute();
    void disableTask();
    void enableTask();
    void setParameters(const QString& key, const QString& val);

    //From DBus
    void progressUpdate(const int currentcompletion, const QString& currentstatus);
    void errorUpdate(const QString& errordescrition);
    void dataUpdate(const QVariantList& result);

signals:

    void errorFindSig(); // To UI & Group
    void completeSig(); // To UI & Group

    void dataUpdateSig(const QVariantList& result); // To UI
    void dataCountUpdateSig(const int totalproblems, const int totalinfomations); //To Group

    void completerateUpdateSig(const int completerate, const QString& status); //To UI
    void progressUpdateSig(const int completeunit, const QString& status); //To Group

    //To Dus
    void startTaskSig(const QString& scenename, const QString& taskname, const QVariantMap &  parameters);
    void stopTaskSig(const QString& scenename, const QString& taskname);

    void totalUnitChangedSig(const int value);


public:
    bool enabled;
    bool badinfoCheck;
    int weight;
    QString taskname;
    QString scenename;

    bool start;
    int completerate;

    bool error;
    QString currentstatus;

    bool errorfind;
    int totalproblems;
    int totalinfomations;

    QVariantMap parameters;
};

#endif // CHECKTASK_H
