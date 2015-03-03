#ifndef IMAGECHECKSTATE_H
#define IMAGECHECKSTATE_H


#include <QObject>
class CheckTask;
class CheckTaskGroup;
class MainWindow;
class InterfaceForTool;
class ToolUtil;


class ImageCheckState: public QObject {
    Q_OBJECT

public:
    explicit ImageCheckState(QObject* parent , MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
                              ToolUtil* toolUtil);
    ~ImageCheckState();
    void inittasks(ToolUtil* toolUtil);
    void initConStateGroup();
    void initConInterfaceTask( InterfaceForTool* interfaceForTool);
    void initConUIState(MainWindow * mainwindow);

signals:
    void errorFindSig();// To UI
    void completeSig();// To UI

    //void progressUpdateSig(const int completeunit ,const QString & status);
    void completerateUpdateSig(const int completerate ,const QString & status);// To UI

    void dataCountUpdateSig(const int totalproblems ,const int totalinfomations );// To UI
    void startSig();// To Task/Group
    void stopSig();// To Task/Group
    void disableSig();// To Task/Group
public slots:
    //Call UI
    void startexcute();
    void stopexcute();
    void disablescene();
    //From Task

    void progressUpdate(const int completeunit ,const QString & status);
    void dataCountUpdate(const int totalproblems ,const int totalinfomations);

    void totalUnitChanged(const int value);


private:
    bool enabled;
    bool start;

    QString currentstatus;
    bool errorfind;

    int totalproblems;
    int totalinfomations;

    int totalcompleteunit;
    int currentcompleteunit;

public:


    CheckTaskGroup* imageCheck;
    CheckTask* imageRoutineCheck;

};

#endif // IMAGECHECKSTATE_H
