#include "commoncheckstate.h"
#include <QDBusConnection>

#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"
#include "src/ui/commoncheck/commoncheckwidget.h"
#include "src/ui/common/taskbutton.h"
#include "src/ui/detailreport/deviceconnectrpt.h"
#include "src/ui/detailreport/netrecordcommonrpt.h"
#include "src/ui/detailreport/systemsecurityrpt.h"
#include "src/ui/detailreport/securitythreatrpt.h"
#include "src/ui/detailreport/basicinforpt.h"
#include "src/ui/detailreport/usbrecordcommonrpt.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/commoncheck/tabbutton.h"
#include "src/util/interfacefortool.h"
#include "src/util/toolutil.h"
#include <QDebug>
#include <QAbstractItemModel>

//#include "onekeycheck_adaptor.h"
//#include "onekeycheck_interface.h"

CommonCheckState::CommonCheckState(QObject* parent, MainWindow* mainwindow, InterfaceForTool* interfaceForTool,
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
    initConUIState(mainwindow);
    // initConnectionBtwStateAndGroup();
}

CommonCheckState::~CommonCheckState()
{
}

void CommonCheckState::inittasks(ToolUtil* toolUtil)
{

    operatingSystemInfo = new CheckTask(this, toolUtil, FUNC_OSINFO, SCENE_COMMONCHECK, false, 1);
    cpuInfo = new CheckTask(this, toolUtil, FUNC_CPUINFO, SCENE_COMMONCHECK, false, 1);
    biosInfo = new CheckTask(this, toolUtil, FUNC_BIOSINFO, SCENE_COMMONCHECK, false, 1);
    motherboardInfo = new CheckTask(this, toolUtil, FUNC_MBINFO, SCENE_COMMONCHECK, false, 1);
    memoryInfo = new CheckTask(this, toolUtil, FUNC_MEMINFO, SCENE_COMMONCHECK, false, 1);
    graphicsCardInfo = new CheckTask(this, toolUtil, FUNC_GCINFO, SCENE_COMMONCHECK, false, 1);
    basicInfo = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                   QList<CheckTask*>() << operatingSystemInfo << cpuInfo
                                                       << biosInfo << motherboardInfo << memoryInfo
                                                       << graphicsCardInfo);

    hardDiskInfo = new CheckTask(this, toolUtil, FUNC_HDINFO, SCENE_COMMONCHECK, false, 1);
    virtualMachineInfo = new CheckTask(this, toolUtil, FUNC_VMINFO, SCENE_COMMONCHECK, false, 1);
    netConfig = new CheckTask(this, toolUtil, FUNC_NCINFO, SCENE_COMMONCHECK, false, 1);
    adapterDevice = new CheckTask(this, toolUtil, FUNC_NADEV, SCENE_COMMONCHECK, false, 1);
    printDevice = new CheckTask(this, toolUtil, FUNC_PRIDEV, SCENE_COMMONCHECK, false, 1);
    blueToothDevice = new CheckTask(this, toolUtil, FUNC_BTDEV, SCENE_COMMONCHECK, false, 1);
    deviceConnection = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                          QList<CheckTask*>() << hardDiskInfo << virtualMachineInfo
                                                              << netConfig << adapterDevice << printDevice
                                                              << blueToothDevice);

    patchNotInstalled = new CheckTask(this, toolUtil, FUNC_PATCH, SCENE_COMMONCHECK, false, 1);
    systemService = new CheckTask(this, toolUtil, FUNC_SERVICE, SCENE_COMMONCHECK, false, 2);
    systemProcess = new CheckTask(this, toolUtil, FUNC_PROCESS, SCENE_COMMONCHECK, false, 2);
    evenProduct = new CheckTask(this, toolUtil, FUNC_OTHERPDT, SCENE_COMMONCHECK, false, 1);
    timeSwitchMachine = new CheckTask(this, toolUtil, FUNC_SWITHTIME, SCENE_COMMONCHECK, false, 1);
    securitySoftware = new CheckTask(this, toolUtil, FUNC_SECSOFT, SCENE_COMMONCHECK, false, 1);
    systemSecurity = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                        QList<CheckTask*>() << patchNotInstalled << systemService
                                                            << systemProcess << evenProduct << timeSwitchMachine
                                                            << securitySoftware);

    securityPolicy = new CheckTask(this, toolUtil, FUNC_SECPLCY, SCENE_COMMONCHECK, false, 1);
    openPort = new CheckTask(this, toolUtil, FUNC_OPENPORT, SCENE_COMMONCHECK, false, 1);
    sharingInfo = new CheckTask(this, toolUtil, FUNC_SHARINFO, SCENE_COMMONCHECK, false, 1);
    networkSoftware = new CheckTask(this, toolUtil, FUNC_NETSOFT, SCENE_COMMONCHECK, false, 1);
    groupInfo = new CheckTask(this, toolUtil, FUNC_GRPINFO, SCENE_COMMONCHECK, false, 1);
    userInfo = new CheckTask(this, toolUtil, FUNC_USERINFO, SCENE_COMMONCHECK, false, 1);
    databaseInfo = new CheckTask(this, toolUtil, FUNC_DBNFO, SCENE_COMMONCHECK, false, 1);
    eventLog = new CheckTask(this, toolUtil, FUNC_EVELOG, SCENE_COMMONCHECK, false, 1);
    userAuthentication = new CheckTask(this, toolUtil, FUNC_USRAUTH, SCENE_COMMONCHECK, false, 1);
    securityThreat = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                        QList<CheckTask*>() << securityPolicy << openPort << sharingInfo
                                                            << networkSoftware << groupInfo << userInfo
                                                            << databaseInfo << eventLog << userAuthentication);

    usbRoutineCheck = new CheckTask(this, toolUtil, FUNC_USBCOMCHECK, SCENE_COMMONCHECK, false, 1);
    usbCheck = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                  QList<CheckTask*>() << usbRoutineCheck);
    //CheckTask*	usbDepthCheck
    netRecordsRoutineCheck = new CheckTask(this, toolUtil, FUNC_NETRECCOMCHECK, SCENE_COMMONCHECK, false, 1);
    netRecordsCheck = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                         QList<CheckTask*>() << usbRoutineCheck);

    fileRoutineCheck = new CheckTask(this, toolUtil, FUNC_FILECOMCHECK, SCENE_COMMONCHECK, true, 1);
    fileCheck = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                   QList<CheckTask*>() << fileRoutineCheck);

    //CheckTask* deletedFileRecovery;
    //CheckTask* fileFragmentsCheck;

    threatDocument = new CheckTask(this, toolUtil, FUNC_TROJANCHECK, SCENE_COMMONCHECK, true, 1);
    trojanCheck = new CheckTaskGroup(this, SCENE_COMMONCHECK, 1,
                                     QList<CheckTask*>() << threatDocument);
    ;
    //CheckTask*	networkWeapon
}
void CommonCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << basicInfo << deviceConnection << netRecordsCheck
               << usbCheck << securityThreat << systemSecurity << deviceConnection;
    //<< trojanCheck << fileCheck
    for (CheckTaskGroup* taskGroup : taskGroups) {
        connect(this, SIGNAL(startSig()), taskGroup, SLOT(startExecute()));
        connect(this, SIGNAL(stopSig()), taskGroup, SLOT(stopExecute()));
        //connect(this, SIGNAL(disableSig()), taskGroup, SLOT(disableGroup()));

        connect(taskGroup, SIGNAL(dataCountUpdateSig(const int, const int)), this, SLOT(dataCountUpdate(const int, const int)));
        connect(taskGroup, SIGNAL(progressUpdateSig(const int, const QString&)), this, SLOT(progressUpdate(const int, const QString&)));
        connect(taskGroup, SIGNAL(totalUnitChangedSig(const int)), this, SLOT(totalUnitChanged(const int)));
        this->totalcompleteunit += taskGroup->totalcompleteunit * taskGroup->weight;
    }
}

void CommonCheckState::totalUnitChanged(const int value){
    totalcompleteunit +=value;
}
void CommonCheckState::initConUIState(MainWindow* mainwindow)
{
    CommonCheckWidget* cc = mainwindow->commonCheckWidget;

    connect(cc->startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startexcute()));
    connect(cc->cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(stopexcute()));
    connect(this, SIGNAL(completerateUpdateSig(const int, const QString&)), cc, SLOT(completerateUpdate(const int, const QString&)));
    connect(this, SIGNAL(dataCountUpdateSig(const int, const int)), cc, SLOT(dataCountUpdate(const int, const int)));

    connect(basicInfo, SIGNAL(errorFindSig()), cc->basicinfobtn, SLOT(changeToProblem()));
    connect(basicInfo, SIGNAL(completeSig()), cc->basicinfobtn, SLOT(changeToNoProblem()));

    connect(deviceConnection, SIGNAL(errorFindSig()), cc->deviceconnectionbtn, SLOT(changeToProblem()));
    connect(deviceConnection, SIGNAL(completeSig()), cc->deviceconnectionbtn, SLOT(changeToNoProblem()));

    connect(systemSecurity, SIGNAL(errorFindSig()), cc->systemsecuritybtn, SLOT(changeToProblem()));
    connect(systemSecurity, SIGNAL(completeSig()), cc->systemsecuritybtn, SLOT(changeToNoProblem()));

    connect(securityThreat, SIGNAL(errorFindSig()), cc->securitythreatbtn, SLOT(changeToProblem()));
    connect(securityThreat, SIGNAL(completeSig()), cc->securitythreatbtn, SLOT(changeToNoProblem()));

    connect(usbCheck, SIGNAL(errorFindSig()), cc->usbcheckbtn, SLOT(changeToProblem()));
    connect(usbCheck, SIGNAL(completeSig()), cc->usbcheckbtn, SLOT(changeToNoProblem()));

    connect(netRecordsCheck, SIGNAL(errorFindSig()), cc->netbrowserbtn, SLOT(changeToProblem()));
    connect(netRecordsCheck, SIGNAL(completeSig()), cc->netbrowserbtn, SLOT(changeToNoProblem()));

    connect(netRecordsCheck, SIGNAL(errorFindSig()), cc->netbrowserbtn, SLOT(changeToProblem()));
    connect(netRecordsCheck, SIGNAL(completeSig()), cc->netbrowserbtn, SLOT(changeToNoProblem()));

    //connect(fileCheck, SIGNAL(errorFindSig()), cc->filecheckbtn, SLOT(changeToProblem()));
    //connect(fileCheck, SIGNAL(completeSig()), cc->filecheckbtn, SLOT(changeToNoProblem()));

    //connect(trojanCheck, SIGNAL(errorFindSig()), cc->tjcheckbtn, SLOT(changeToProblem()));
    //connect(trojanCheck, SIGNAL(completeSig()), cc->tjcheckbtn, SLOT(changeToNoProblem()));
    //Basic Info
    BasicInfoRpt* ccBasicInfoRpt = mainwindow->ccBasicInfoRpt;
    connect(operatingSystemInfo, &CheckTask::completeSig, ccBasicInfoRpt->osInfoBtn, &TaskButton::changeToNoProblem);
    connect(operatingSystemInfo, &CheckTask::errorFindSig, ccBasicInfoRpt->osInfoBtn, &TaskButton::changeToProblem);
    connect(operatingSystemInfo, &CheckTask::dataUpdateSig, ccBasicInfoRpt, &BasicInfoRpt::addOSInfo);

    connect(cpuInfo, &CheckTask::completeSig, ccBasicInfoRpt->cpuInfoBtn, &TaskButton::changeToNoProblem);
    connect(cpuInfo, &CheckTask::errorFindSig, ccBasicInfoRpt->cpuInfoBtn, &TaskButton::changeToProblem);
    connect(cpuInfo, &CheckTask::dataUpdateSig, ccBasicInfoRpt, &BasicInfoRpt::addCpuInfo);

    connect(biosInfo, &CheckTask::completeSig, ccBasicInfoRpt->biosInfoBtn, &TaskButton::changeToNoProblem);
    connect(biosInfo, &CheckTask::errorFindSig, ccBasicInfoRpt->biosInfoBtn, &TaskButton::changeToProblem);
    connect(biosInfo, &CheckTask::dataUpdateSig, ccBasicInfoRpt, &BasicInfoRpt::addBiosInfo);

    connect(motherboardInfo, &CheckTask::completeSig, ccBasicInfoRpt->motherBoardInfoBtn, &TaskButton::changeToNoProblem);
    connect(motherboardInfo, &CheckTask::errorFindSig, ccBasicInfoRpt->motherBoardInfoBtn, &TaskButton::changeToProblem);
    connect(motherboardInfo, &CheckTask::dataUpdateSig, ccBasicInfoRpt, &BasicInfoRpt::addMotherBoardInfo);

    connect(memoryInfo, &CheckTask::completeSig, ccBasicInfoRpt->memoryInfoBtn, &TaskButton::changeToNoProblem);
    connect(memoryInfo, &CheckTask::errorFindSig, ccBasicInfoRpt->memoryInfoBtn, &TaskButton::changeToProblem);
    connect(memoryInfo, &CheckTask::dataUpdateSig, ccBasicInfoRpt, &BasicInfoRpt::addMemoryInfo);

    connect(graphicsCardInfo, &CheckTask::completeSig, ccBasicInfoRpt->graphicsCardInfoBtn, &TaskButton::changeToNoProblem);
    connect(graphicsCardInfo, &CheckTask::errorFindSig, ccBasicInfoRpt->graphicsCardInfoBtn, &TaskButton::changeToProblem);
    connect(graphicsCardInfo, &CheckTask::dataUpdateSig, ccBasicInfoRpt, &BasicInfoRpt::addGraphicsCardInfo);

    DeviceConnectRpt* ccDeviceConnectRpt = mainwindow->ccDeviceConnectRpt;
    connect(hardDiskInfo, &CheckTask::completeSig, ccDeviceConnectRpt->hardDiskInfoBtn, &TaskButton::changeToNoProblem);
    connect(hardDiskInfo, &CheckTask::errorFindSig, ccDeviceConnectRpt->hardDiskInfoBtn, &TaskButton::changeToProblem);
    connect(hardDiskInfo, &CheckTask::dataUpdateSig, ccDeviceConnectRpt, &DeviceConnectRpt::addHardDiskInfo);

    connect(virtualMachineInfo, &CheckTask::completeSig, ccDeviceConnectRpt->virtualMachineInfoBtn, &TaskButton::changeToNoProblem);
    connect(virtualMachineInfo, &CheckTask::errorFindSig, ccDeviceConnectRpt->virtualMachineInfoBtn, &TaskButton::changeToProblem);
    connect(virtualMachineInfo, &CheckTask::dataUpdateSig, ccDeviceConnectRpt, &DeviceConnectRpt::addVirtualMachineInfo);

    connect(netConfig, &CheckTask::completeSig, ccDeviceConnectRpt->netConfigBtn, &TaskButton::changeToNoProblem);
    connect(netConfig, &CheckTask::errorFindSig, ccDeviceConnectRpt->netConfigBtn, &TaskButton::changeToProblem);
    connect(netConfig, &CheckTask::dataUpdateSig, ccDeviceConnectRpt, &DeviceConnectRpt::addNetConfig);

    connect(adapterDevice, &CheckTask::completeSig, ccDeviceConnectRpt->adapterDeviceBtn, &TaskButton::changeToNoProblem);
    connect(adapterDevice, &CheckTask::errorFindSig, ccDeviceConnectRpt->adapterDeviceBtn, &TaskButton::changeToProblem);
    connect(adapterDevice, &CheckTask::dataUpdateSig, ccDeviceConnectRpt, &DeviceConnectRpt::addAdapterDevice);

    connect(printDevice, &CheckTask::completeSig, ccDeviceConnectRpt->printDeviceBtn, &TaskButton::changeToNoProblem);
    connect(printDevice, &CheckTask::errorFindSig, ccDeviceConnectRpt->printDeviceBtn, &TaskButton::changeToProblem);
    connect(printDevice, &CheckTask::dataUpdateSig, ccDeviceConnectRpt, &DeviceConnectRpt::addPrintDevice);

    connect(blueToothDevice, &CheckTask::completeSig, ccDeviceConnectRpt->blueToothDeviceBtn, &TaskButton::changeToNoProblem);
    connect(blueToothDevice, &CheckTask::errorFindSig, ccDeviceConnectRpt->blueToothDeviceBtn, &TaskButton::changeToProblem);
    connect(blueToothDevice, &CheckTask::dataUpdateSig, ccDeviceConnectRpt, &DeviceConnectRpt::addBlueToothDevice);

    NetRecordCommonRpt* ccNetRecordRpt = mainwindow->ccNetRecordRpt;
    connect(netRecordsRoutineCheck, &CheckTask::dataUpdateSig, ccNetRecordRpt, &NetRecordCommonRpt::addNetRecordsInfo);

    SystemSecurityRpt* ccSystemSecurityRpt = mainwindow->ccSystemSecurityRpt;

    connect(patchNotInstalled, &CheckTask::completeSig, ccSystemSecurityRpt->patchNotInstalledBtn, &TaskButton::changeToNoProblem);
    connect(patchNotInstalled, &CheckTask::errorFindSig, ccSystemSecurityRpt->patchNotInstalledBtn, &TaskButton::changeToProblem);
    connect(patchNotInstalled, &CheckTask::dataUpdateSig, ccSystemSecurityRpt, &SystemSecurityRpt::addPatchNotInstalled);

    connect(systemService, &CheckTask::completeSig, ccSystemSecurityRpt->systemServiceBtn, &TaskButton::changeToNoProblem);
    connect(systemService, &CheckTask::errorFindSig, ccSystemSecurityRpt->systemServiceBtn, &TaskButton::changeToProblem);
    connect(systemService, &CheckTask::dataUpdateSig, ccSystemSecurityRpt, &SystemSecurityRpt::addSystemService);

    connect(systemProcess, &CheckTask::completeSig, ccSystemSecurityRpt->systemProcessBtn, &TaskButton::changeToNoProblem);
    connect(systemProcess, &CheckTask::errorFindSig, ccSystemSecurityRpt->systemProcessBtn, &TaskButton::changeToProblem);
    connect(systemProcess, &CheckTask::dataUpdateSig, ccSystemSecurityRpt, &SystemSecurityRpt::addSystemProcess);

    connect(evenProduct, &CheckTask::completeSig, ccSystemSecurityRpt->evenProductBtn, &TaskButton::changeToNoProblem);
    connect(evenProduct, &CheckTask::errorFindSig, ccSystemSecurityRpt->evenProductBtn, &TaskButton::changeToProblem);
    connect(evenProduct, &CheckTask::dataUpdateSig, ccSystemSecurityRpt, &SystemSecurityRpt::addEvenProduct);

    connect(timeSwitchMachine, &CheckTask::completeSig, ccSystemSecurityRpt->timeSwitchMachineBtn, &TaskButton::changeToNoProblem);
    connect(timeSwitchMachine, &CheckTask::errorFindSig, ccSystemSecurityRpt->timeSwitchMachineBtn, &TaskButton::changeToProblem);
    connect(timeSwitchMachine, &CheckTask::dataUpdateSig, ccSystemSecurityRpt, &SystemSecurityRpt::addTimeSwitchMachine);

    connect(securitySoftware, &CheckTask::completeSig, ccSystemSecurityRpt->securitySoftwareBtn, &TaskButton::changeToNoProblem);
    connect(securitySoftware, &CheckTask::errorFindSig, ccSystemSecurityRpt->securitySoftwareBtn, &TaskButton::changeToProblem);
    connect(securitySoftware, &CheckTask::dataUpdateSig, ccSystemSecurityRpt, &SystemSecurityRpt::addSecuritySoftware);

    UsbRecordCommonRpt* ccUsbRecordCommonRpt = mainwindow->ccUsbRecordCommonRpt;
    connect(usbRoutineCheck, &CheckTask::dataUpdateSig, ccUsbRecordCommonRpt, &UsbRecordCommonRpt::addUsbRecordsInfo);

    SecurityThreatRpt* ccSecurityThreatRpt = mainwindow->ccSecurityThreatRpt;

    connect(securityPolicy, &CheckTask::completeSig, ccSecurityThreatRpt->securityPolicyBtn, &TaskButton::changeToNoProblem);
    connect(securityPolicy, &CheckTask::errorFindSig, ccSecurityThreatRpt->securityPolicyBtn, &TaskButton::changeToProblem);
    connect(securityPolicy, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addSecurityPolicy);

    connect(openPort, &CheckTask::completeSig, ccSecurityThreatRpt->openPortBtn, &TaskButton::changeToNoProblem);
    connect(openPort, &CheckTask::errorFindSig, ccSecurityThreatRpt->openPortBtn, &TaskButton::changeToProblem);
    connect(openPort, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addOpenPort);

    connect(sharingInfo, &CheckTask::completeSig, ccSecurityThreatRpt->sharingInfoBtn, &TaskButton::changeToNoProblem);
    connect(sharingInfo, &CheckTask::errorFindSig, ccSecurityThreatRpt->sharingInfoBtn, &TaskButton::changeToProblem);
    connect(sharingInfo, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addSharingInfo);

    connect(networkSoftware, &CheckTask::completeSig, ccSecurityThreatRpt->networkSoftwareBtn, &TaskButton::changeToNoProblem);
    connect(networkSoftware, &CheckTask::errorFindSig, ccSecurityThreatRpt->networkSoftwareBtn, &TaskButton::changeToProblem);
    connect(networkSoftware, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addNetworkSoftware);

    connect(groupInfo, &CheckTask::completeSig, ccSecurityThreatRpt->groupInfoBtn, &TaskButton::changeToNoProblem);
    connect(groupInfo, &CheckTask::errorFindSig, ccSecurityThreatRpt->groupInfoBtn, &TaskButton::changeToProblem);
    connect(groupInfo, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addGroupInfo);

    connect(userInfo, &CheckTask::completeSig, ccSecurityThreatRpt->userInfoBtn, &TaskButton::changeToNoProblem);
    connect(userInfo, &CheckTask::errorFindSig, ccSecurityThreatRpt->userInfoBtn, &TaskButton::changeToProblem);
    connect(userInfo, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addUserInfo);

    connect(eventLog, &CheckTask::completeSig, ccSecurityThreatRpt->eventLogBtn, &TaskButton::changeToNoProblem);
    connect(eventLog, &CheckTask::errorFindSig, ccSecurityThreatRpt->eventLogBtn, &TaskButton::changeToProblem);
    connect(eventLog, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addEventLog);

    connect(databaseInfo, &CheckTask::completeSig, ccSecurityThreatRpt->databaseInfoBtn, &TaskButton::changeToNoProblem);
    connect(databaseInfo, &CheckTask::errorFindSig, ccSecurityThreatRpt->databaseInfoBtn, &TaskButton::changeToProblem);
    connect(databaseInfo, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addDatabaseInfo);

    connect(userAuthentication, &CheckTask::completeSig, ccSecurityThreatRpt->userAuthenticationBtn, &TaskButton::changeToNoProblem);
    connect(userAuthentication, &CheckTask::errorFindSig, ccSecurityThreatRpt->userAuthenticationBtn, &TaskButton::changeToProblem);
    connect(userAuthentication, &CheckTask::dataUpdateSig, ccSecurityThreatRpt, &SecurityThreatRpt::addUserAuthentication);

}
//Call UI
void CommonCheckState::startexcute()
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
void CommonCheckState::stopexcute()
{
    start = false;
    emit stopSig();
}
void CommonCheckState::disablescene()
{
    enabled = false;
    emit disableSig();
}
//From Task
void CommonCheckState::progressUpdate(const int completeunit, const QString& status)
{
    this->currentcompleteunit += completeunit;
    this->currentstatus = status;
    emit completerateUpdateSig(currentcompleteunit * 100 / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void CommonCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
{
    this->totalproblems += totalproblems;
    this->totalinfomations += totalinfomations;
    //qDebug()<<totalinfomations;
    if (totalproblems > 0) {
        if (!errorfind) {
            errorfind = true;
            emit errorFindSig();
        }
    }
    emit dataCountUpdateSig(this->totalproblems, this->totalinfomations);
};
void CommonCheckState::initConInterfaceTask(InterfaceForTool* interfaceForTool)
{

    //Basic Info
    connect(interfaceForTool, SIGNAL(o_cpu_progress(const int, const QString&)), cpuInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_cpu_error(const QString&)), cpuInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_cpu_data(const QVariantList&)), cpuInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_os_progress(const int, const QString&)), operatingSystemInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_os_error(const QString&)), operatingSystemInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_os_data(const QVariantList&)), operatingSystemInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_bios_progress(const int, const QString&)), biosInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_bios_error(const QString&)), biosInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_bios_data(const QVariantList&)), biosInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_mb_progress(const int, const QString&)), motherboardInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_mb_error(const QString&)), motherboardInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_mb_data(const QVariantList&)), motherboardInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_mem_progress(const int, const QString&)), memoryInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_mem_error(const QString&)), memoryInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_mem_data(const QVariantList&)), memoryInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_gc_progress(const int, const QString&)), graphicsCardInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_gc_error(const QString&)), graphicsCardInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_gc_data(const QVariantList&)), graphicsCardInfo, SLOT(dataUpdate(const QVariantList&)));

    //设备连接信息
    connect(interfaceForTool, SIGNAL(o_hd_progress(const int, const QString&)), hardDiskInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_hd_error(const QString&)), hardDiskInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_hd_data(const QVariantList&)), hardDiskInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_vm_progress(const int, const QString&)), virtualMachineInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_vm_error(const QString&)), virtualMachineInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_vm_data(const QVariantList&)), virtualMachineInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_nc_progress(const int, const QString&)), netConfig, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_nc_error(const QString&)), netConfig, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_nc_data(const QVariantList&)), netConfig, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_na_progress(const int, const QString&)), adapterDevice, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_na_error(const QString&)), adapterDevice, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_na_data(const QVariantList&)), adapterDevice, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_print_progress(const int, const QString&)), printDevice, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_print_error(const QString&)), printDevice, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_print_data(const QVariantList&)), printDevice, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_bt_progress(const int, const QString&)), blueToothDevice, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_bt_error(const QString&)), blueToothDevice, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_bt_data(const QVariantList&)), blueToothDevice, SLOT(dataUpdate(const QVariantList&)));

    //系统安全信息
    connect(interfaceForTool, SIGNAL(o_patch_progress(const int, const QString&)), patchNotInstalled, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_patch_error(const QString&)), patchNotInstalled, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_patch_data(const QVariantList&)), patchNotInstalled, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_service_progress(const int, const QString&)), systemService, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_service_error(const QString&)), systemService, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_service_data(const QVariantList&)), systemService, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_process_progress(const int, const QString&)), systemProcess, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_process_error(const QString&)), systemProcess, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_process_data(const QVariantList&)), systemProcess, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_otherpdt_progress(const int, const QString&)), evenProduct, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_otherpdt_error(const QString&)), evenProduct, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_otherpdt_data(const QVariantList&)), evenProduct, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_swithtime_progress(const int, const QString&)), timeSwitchMachine, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_swithtime_error(const QString&)), timeSwitchMachine, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_swithtime_data(const QVariantList&)), timeSwitchMachine, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_secsoft_progress(const int, const QString&)), securitySoftware, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_secsoft_error(const QString&)), securitySoftware, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_secsoft_data(const QVariantList&)), securitySoftware, SLOT(dataUpdate(const QVariantList&)));

    //安全隐患信息

    connect(interfaceForTool, SIGNAL(o_secplcy_progress(const int, const QString&)), securityPolicy, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_secplcy_error(const QString&)), securityPolicy, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_secplcy_data(const QVariantList&)), securityPolicy, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_openport_progress(const int, const QString&)), openPort, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_openport_error(const QString&)), openPort, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_openport_data(const QVariantList&)), openPort, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_sharinfo_progress(const int, const QString&)), sharingInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_sharinfo_error(const QString&)), sharingInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_sharinfo_data(const QVariantList&)), sharingInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_netsoft_progress(const int, const QString&)), networkSoftware, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_netsoft_error(const QString&)), networkSoftware, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_netsoft_data(const QVariantList&)), networkSoftware, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_grpinfo_progress(const int, const QString&)), groupInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_grpinfo_error(const QString&)), groupInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_grpinfo_data(const QVariantList&)), groupInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_userinfo_progress(const int, const QString&)), userInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_userinfo_error(const QString&)), userInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_userinfo_data(const QVariantList&)), userInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_dbinfo_progress(const int, const QString&)), databaseInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_dbinfo_error(const QString&)), databaseInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_dbinfo_data(const QVariantList&)), databaseInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_evelog_progress(const int, const QString&)), eventLog, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_evelog_error(const QString&)), eventLog, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_evelog_data(const QVariantList&)), eventLog, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(o_usrauth_progress(const int, const QString&)), userAuthentication, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_usrauth_error(const QString&)), userAuthentication, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_usrauth_data(const QVariantList&)), userAuthentication, SLOT(dataUpdate(const QVariantList&)));

    //USB设备记录
    connect(interfaceForTool, SIGNAL(o_usbcomcheck_progress(const int, const QString&)), usbRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_usbcomcheck_error(const QString&)), usbRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_usbcomcheck_data(const QVariantList&)), usbRoutineCheck, SLOT(dataUpdate(const QVariantList&)));

    //上网记录
    connect(interfaceForTool, SIGNAL(o_netreccomcheck_progress(const int, const QString&)), netRecordsRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(o_netreccomcheck_error(const QString&)), netRecordsRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(o_netreccomcheck_data(const QVariantList&)), netRecordsRoutineCheck, SLOT(dataUpdate(const QVariantList&)));

    //文件检查
    //connect(interfaceForTool, SIGNAL(o_filecomcheck_progress(const int, const QString&)), fileRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    //connect(interfaceForTool, SIGNAL(o_filecomcheck_error(const QString&)), fileRoutineCheck, SLOT(errorUpdate(const QString&)));
    //connect(interfaceForTool, SIGNAL(o_filecomcheck_data(const QVariantList&)), fileRoutineCheck, SLOT(dataUpdate(const QVariantList&)));

    //木马检查
    //connect(interfaceForTool, SIGNAL(o_trojancheck_progress(const int, const QString&)), threatDocument, SLOT(progressUpdate(const int, const QString&)));
    //connect(interfaceForTool, SIGNAL(o_trojancheck_error(const QString&)), threatDocument, SLOT(errorUpdate(const QString&)));
    //connect(interfaceForTool, SIGNAL(o_trojancheck_data(const QVariantList&)), threatDocument, SLOT(dataUpdate(const QVariantList&)));
}
