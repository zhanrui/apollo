#include <QDBusConnection>
#include "onekeycheckstate.h"
#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"
#include "src/util/interfacefortool.h"
#include "src/util/toolutil.h"
#include <QDebug>
#include <QAbstractItemModel>

//#include "onekeycheck_adaptor.h"
//#include "onekeycheck_interface.h"

OneKeyCheckState::OneKeyCheckState(QObject* parent, MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
                                   ToolUtil* toolUtil)
    : QObject(parent)
{
    this->enabled = true;
    this->start = false;

    currentstatus = QString();
    errorfind = false;

    totalproblems = 0;
    totalinfomations = 0;
    currentcompleteunit = 0;
    totalcompleteunit = 0;
    inittasks(toolUtil);
    initConStateGroup();
    initConInterfaceTask(interfaceForTool);
   // initConnectionBtwStateAndGroup();
}

OneKeyCheckState::~OneKeyCheckState()
{
}

void OneKeyCheckState::inittasks(ToolUtil* toolUtil)
{

    hardDiskInfo = new CheckTask(this, toolUtil,FUNC_HDINFO, SCENE_ONEKEYCHECK, false, 1);
    virtualMachineInfo = new CheckTask(this,toolUtil, FUNC_VMINFO, SCENE_ONEKEYCHECK, false, 1);
    netConfig = new CheckTask(this, toolUtil,FUNC_NCINFO, SCENE_ONEKEYCHECK, false, 1);
    adapterDevice = new CheckTask(this, toolUtil,FUNC_NADEV, SCENE_ONEKEYCHECK, false, 1);
    printDevice = new CheckTask(this, toolUtil,FUNC_PRIDEV, SCENE_ONEKEYCHECK, false, 1);
    blueToothDevice = new CheckTask(this,toolUtil, FUNC_BTDEV, SCENE_ONEKEYCHECK, false, 1);
    deviceConnection = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                          QList<CheckTask*>() << hardDiskInfo << virtualMachineInfo
                                                              << netConfig << adapterDevice << printDevice
                                                              << blueToothDevice);

    patchNotInstalled = new CheckTask(this,toolUtil, FUNC_PATCH, SCENE_ONEKEYCHECK, false, 1);
    systemService = new CheckTask(this,toolUtil, FUNC_SERVICE, SCENE_ONEKEYCHECK, false, 2);
    systemProcess = new CheckTask(this, toolUtil,FUNC_PROCESS, SCENE_ONEKEYCHECK, false, 2);
    evenProduct = new CheckTask(this, toolUtil,FUNC_OTHERPDT, SCENE_ONEKEYCHECK, false, 1);
    timeSwitchMachine = new CheckTask(this, toolUtil,FUNC_SWITHTIME, SCENE_ONEKEYCHECK, false, 1);
    securitySoftware = new CheckTask(this,toolUtil, FUNC_SECSOFT, SCENE_ONEKEYCHECK, false, 1);
    systemSecurity = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                        QList<CheckTask*>() << patchNotInstalled << systemService
                                                            << systemProcess << evenProduct << timeSwitchMachine
                                                            << securitySoftware);

    securityPolicy = new CheckTask(this,toolUtil, FUNC_SECPLCY, SCENE_ONEKEYCHECK, false, 1);
    openPort = new CheckTask(this, toolUtil,FUNC_OPENPORT, SCENE_ONEKEYCHECK, false, 1);
    sharingInfo = new CheckTask(this, toolUtil,FUNC_SHARINFO, SCENE_ONEKEYCHECK, false, 1);
    networkSoftware = new CheckTask(this,toolUtil, FUNC_NETSOFT, SCENE_ONEKEYCHECK, false, 1);
    groupInfo = new CheckTask(this, toolUtil,FUNC_GRPINFO, SCENE_ONEKEYCHECK, false, 1);
    userInfo = new CheckTask(this, toolUtil,FUNC_USERINFO, SCENE_ONEKEYCHECK, false, 1);
    databaseInfo = new CheckTask(this, toolUtil,FUNC_DBNFO, SCENE_ONEKEYCHECK, false, 1);
    eventLog = new CheckTask(this, toolUtil,FUNC_EVELOG, SCENE_ONEKEYCHECK, false, 1);
    userAuthentication = new CheckTask(this, toolUtil,FUNC_USRAUTH, SCENE_ONEKEYCHECK, false, 1);
    securityThreat = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                        QList<CheckTask*>() << securityPolicy << openPort << sharingInfo
                                                            << networkSoftware << groupInfo << userInfo
                                                            << databaseInfo << eventLog << userAuthentication);

    usbRoutineCheck = new CheckTask(this,toolUtil, FUNC_USBCOMCHECK, SCENE_ONEKEYCHECK, false, 1);
    usbCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                  QList<CheckTask*>() << usbRoutineCheck);
    //CheckTask*	usbDepthCheck
    netRecordsRoutineCheck = new CheckTask(this,toolUtil,FUNC_NETRECCOMCHECK, SCENE_ONEKEYCHECK, false, 1);
    netRecordsCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                         QList<CheckTask*>() << usbRoutineCheck);

    fileRoutineCheck = new CheckTask(this, toolUtil,FUNC_FILECOMCHECK, SCENE_ONEKEYCHECK, false, 1);
    fileCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                               QList<CheckTask*>() << fileRoutineCheck);

    //CheckTask* deletedFileRecovery;
    //CheckTask* fileFragmentsCheck;

    threatDocument = new CheckTask(this, toolUtil,FUNC_TROJANCHECK, SCENE_ONEKEYCHECK, false, 1);
    trojanCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                 QList<CheckTask*>() << threatDocument);
    ;
    //CheckTask*	networkWeapon
}

void OneKeyCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << deviceConnection << trojanCheck << fileCheck << netRecordsCheck
               << usbCheck << securityThreat << systemSecurity << deviceConnection;
    for (CheckTaskGroup* taskGroup : taskGroups) {
        connect(this, SIGNAL(startSig()), taskGroup, SLOT(startexecute()));
        connect(this, SIGNAL(stopSig()), taskGroup, SLOT(stopexecute()));
        connect(this, SIGNAL(disableSig()), taskGroup, SLOT(disablegroup()));

        connect(taskGroup, SIGNAL(dataCountUpdateSig(const int, const int)), this, SLOT(dataCountUpdate(const int, const int)));
        connect(taskGroup, SIGNAL(progressUpdateSig(const int, const QString&)), this, SLOT(progressUpdate(const int, const QString&)));

        this->totalcompleteunit += taskGroup->totalcompleteunit * taskGroup->weight;
    }
}

//Call UI
void OneKeyCheckState::startexcute()
{
    if (enabled) {
        start = true;
        currentstatus.clear();
        errorfind = false;
        totalproblems = 0;
        totalinfomations = 0;
        currentcompleteunit = 0;
        emit startSig();
    }
}
void OneKeyCheckState::stopexcute()
{
    start = false;
    emit stopSig();
}
void OneKeyCheckState::disablescene()
{
    enabled = false;
    emit disableSig();
}
//From Task

void OneKeyCheckState::progressUpdate(const int completeunit, const QString& status)
{
    this->currentcompleteunit += completeunit;
    this->currentstatus = status;
    emit completerateUpdateSig(currentcompleteunit / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void OneKeyCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
{
    this->totalproblems += totalproblems;
    this->totalinfomations += totalinfomations;
    if (totalproblems > 0) {
        if (!errorfind) {
            errorfind = true;
            emit errorFindSig();
        }
    }
    emit dataCountUpdateSig(totalproblems, totalinfomations);
};

void OneKeyCheckState:: initConInterfaceTask( InterfaceForTool* interfaceForTool){

    //设备连接信息
    connect(interfaceForTool, SIGNAL(o_hd_progress(const int , const QString& )),hardDiskInfo, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_hd_error(const QString& )),hardDiskInfo,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_hd_data(const QVariantList& )),hardDiskInfo,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_vm_progress(const int , const QString& )),virtualMachineInfo, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_vm_error(const QString& )),virtualMachineInfo,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_vm_data(const QVariantList& )),virtualMachineInfo,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_nc_progress(const int , const QString& )),netConfig, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_nc_error(const QString& )),netConfig,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_nc_data(const QVariantList& )),netConfig,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_na_progress(const int , const QString& )),adapterDevice, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_na_error(const QString& )),adapterDevice,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_na_data(const QVariantList& )),adapterDevice,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_print_progress(const int , const QString& )),printDevice, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_print_error(const QString& )),printDevice,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_print_data(const QVariantList& )),printDevice,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_bt_progress(const int , const QString& )),blueToothDevice, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_bt_error(const QString& )),blueToothDevice,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_bt_data(const QVariantList& )),blueToothDevice,SLOT(dataUpdate(const QVariantList&)));

    //系统安全信息
    connect(interfaceForTool, SIGNAL(o_patch_progress(const int , const QString& )),patchNotInstalled, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_patch_error(const QString& )),patchNotInstalled,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_patch_data(const QVariantList& )),patchNotInstalled,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_service_progress(const int , const QString& )),systemService, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_service_error(const QString& )),systemService,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_service_data(const QVariantList& )),systemService,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_process_progress(const int , const QString& )),systemProcess, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_process_error(const QString& )),systemProcess,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_process_data(const QVariantList& )),systemProcess,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_otherpdt_progress(const int , const QString& )),evenProduct, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_otherpdt_error(const QString& )),evenProduct,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_otherpdt_data(const QVariantList& )),evenProduct,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_swithtime_progress(const int , const QString& )),timeSwitchMachine, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_swithtime_error(const QString& )),timeSwitchMachine,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_swithtime_data(const QVariantList& )),timeSwitchMachine,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_secsoft_progress(const int , const QString& )),securitySoftware, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_secsoft_error(const QString& )),securitySoftware,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_secsoft_data(const QVariantList& )),securitySoftware,SLOT(dataUpdate(const QVariantList&)));

    //安全隐患信息


    connect(interfaceForTool, SIGNAL(o_secplcy_progress(const int , const QString& )),securityPolicy, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_secplcy_error(const QString& )),securityPolicy,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_secplcy_data(const QVariantList& )),securityPolicy,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_openport_progress(const int , const QString& )),openPort, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_openport_error(const QString& )),openPort,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_sopenport_data(const QVariantList& )),openPort,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_sharinfo_progress(const int , const QString& )),sharingInfo, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_sharinfo_error(const QString& )),sharingInfo,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_sharinfo_data(const QVariantList& )),sharingInfo,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_netsoft_progress(const int , const QString& )),networkSoftware, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_netsoft_error(const QString& )),networkSoftware,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_netsoft_data(const QVariantList& )),networkSoftware,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_grpinfo_progress(const int , const QString& )),groupInfo, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_grpinfo_error(const QString& )),groupInfo,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_grpinfo_data(const QVariantList& )),groupInfo,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_userinfo_progress(const int , const QString& )),userInfo, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_userinfo_error(const QString& )),userInfo,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_userinfo_data(const QVariantList& )),userInfo,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_dbinfo_progress(const int , const QString& )),databaseInfo, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_dbinfo_error(const QString& )),databaseInfo,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_dbinfo_data(const QVariantList& )),databaseInfo,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_evelog_progress(const int , const QString& )),eventLog, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_evelog_error(const QString& )),eventLog,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_evelog_data(const QVariantList& )),eventLog,SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_usrauth_progress(const int , const QString& )),userAuthentication, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_usrauth_error(const QString& )),userAuthentication,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_usrauth_data(const QVariantList& )),userAuthentication,SLOT(dataUpdate(const QVariantList&)));

    //USB设备记录
    connect(interfaceForTool, SIGNAL(o_usbcomcheck_progress(const int , const QString& )),usbRoutineCheck, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_usbcomcheck_error(const QString& )),usbRoutineCheck,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_usbcomcheck_data(const QVariantList& )),usbRoutineCheck,SLOT(dataUpdate(const QVariantList&)));

    //上网记录
    connect(interfaceForTool, SIGNAL(o_netreccomcheck_progress(const int , const QString& )),netRecordsRoutineCheck, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_netreccomcheck_error(const QString& )),netRecordsRoutineCheck,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_netreccomcheck_data(const QVariantList& )),netRecordsRoutineCheck,SLOT(dataUpdate(const QVariantList&)));

    //文件检查
    connect(interfaceForTool, SIGNAL(o_filecomcheck_progress(const int , const QString& )),fileRoutineCheck, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_filecomcheck_error(const QString& )),fileRoutineCheck,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_filecomcheck_data(const QVariantList& )),fileRoutineCheck,SLOT(dataUpdate(const QVariantList&)));

    //木马检查
    connect(interfaceForTool, SIGNAL(o_trojancheck_progress(const int , const QString& )),threatDocument, SLOT( progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_trojancheck_error(const QString& )),threatDocument,SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_trojancheck_data(const QVariantList& )),threatDocument,SLOT(dataUpdate(const QVariantList&)));
}
