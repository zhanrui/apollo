#ifndef ONEKEYCHECKSTATE_H
#define ONEKEYCHECKSTATE_H

#include <QObject>
class CheckTask;
class CheckTaskGroup;


class OneKeyCheckState : public QObject {
    Q_OBJECT

public:
    explicit OneKeyCheckState(QObject* parent = 0);
    ~OneKeyCheckState();

signals:
    void startSig();// To Task
    void stopSig();// To Task
public slots:
   // void startexcute();
  //  void stopexcute();

private:
    bool complete;
    int completerate;
    int totalproblems;
    int totalinfomations;

public:
    CheckTaskGroup* deviceConnection;
    CheckTask* hardDiskInfo;
    CheckTask* virtualMachineInfo;
    CheckTask* netConfig;
    CheckTask* adapterDevice;
    CheckTask* printDevice;
    CheckTask* blueToothDevice;

    CheckTaskGroup* systemSecurity;
    CheckTask* patchNotInstalled;
    CheckTask* systemService;
    CheckTask* systemProcess;
    CheckTask* evenProduct;
    CheckTask* timeSwitchMachine;
    CheckTask* securitySoftware;

    CheckTaskGroup* securityThreat;
    CheckTask* securityPolicy;
    CheckTask* openPort;
    CheckTask* sharingInfo;
    CheckTask* networkSoftware;
    CheckTask* groupInfo;
    CheckTask* userInfo;
    CheckTask* databaseInfo;
    CheckTask* eventLog;
    CheckTask* userAuthentication;

    CheckTaskGroup* usbCheck;
    CheckTask* usbRoutineCheck;
    //CheckTask*	usbDepthCheck

    CheckTaskGroup* netRecordsCheck;
    CheckTask* netRecordsRoutineCheck;
    CheckTask* netRecordsDepthCheck;

    CheckTaskGroup* fileCheck;
    CheckTask* fileRoutineCheck;
    CheckTask* deletedFileRecovery;
    CheckTask* fileFragmentsCheck;

    CheckTaskGroup* trojanCheck;
    //CheckTask*	networkWeapon
    CheckTask* threatDocument;


};

#endif // ONEKEYCHECKSTATE_H
