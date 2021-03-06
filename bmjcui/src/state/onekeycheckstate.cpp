#include "onekeycheckstate.h"

#include <QDBusConnection>

#include "src/state/common/checktaskgroup.h"
#include "src/common/globals.h"
#include "src/ui/main/mainwindow.h"

#include "src/ui/onekeycheck/onekeycheckmainwidget.h"
#include "src/ui/onekeycheck/onekeychecksettingwidget.h"
#include "src/ui/common/taskbutton.h"
#include "src/ui/detailreport/deviceconnectrpt.h"
#include "src/ui/detailreport/netrecordcommonrpt.h"
#include "src/ui/detailreport/systemsecurityrpt.h"
#include "src/ui/detailreport/securitythreatrpt.h"
#include "src/ui/detailreport/basicinforpt.h"
#include "src/ui/detailreport/usbrecordcommonrpt.h"
#include "src/ui/detailreport/filecheckcommonrpt.h"
#include "src/ui/detailreport/trojancheckrpt.h"
#include "src/ui/detailreport/imagecheckrpt.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/commoncheck/tabbutton.h"
#include "src/ui/onekeycheck/commonchecksettingpart.h"
#include "src/ui/onekeycheck/filechecksettingpart.h"
#include "src/ui/onekeycheck/imagechecksettingpart.h"
#include "src/ui/onekeycheck/trojanchecksettingpart.h"
#include "src/ui/onekeycheck/onekeychecksettingwidget.h"
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
    initConUIState(mainwindow);
    // initConnectionBtwStateAndGroup();
}

OneKeyCheckState::~OneKeyCheckState()
{
}

void OneKeyCheckState::inittasks(ToolUtil* toolUtil)
{

    operatingSystemInfo = new CheckTask(this, toolUtil, FUNC_OSINFO, SCENE_ONEKEYCHECK, false, 1);
    cpuInfo = new CheckTask(this, toolUtil, FUNC_CPUINFO, SCENE_ONEKEYCHECK, false, 1);
    biosInfo = new CheckTask(this, toolUtil, FUNC_BIOSINFO, SCENE_ONEKEYCHECK, false, 1);
    motherboardInfo = new CheckTask(this, toolUtil, FUNC_MBINFO, SCENE_ONEKEYCHECK, false, 1);
    memoryInfo = new CheckTask(this, toolUtil, FUNC_MEMINFO, SCENE_ONEKEYCHECK, false, 1);
    graphicsCardInfo = new CheckTask(this, toolUtil, FUNC_GCINFO, SCENE_ONEKEYCHECK, false, 1);
    basicInfo = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                   QList<CheckTask*>() << operatingSystemInfo << cpuInfo
                                                       << biosInfo << motherboardInfo << memoryInfo
                                                       << graphicsCardInfo);

    hardDiskInfo = new CheckTask(this, toolUtil, FUNC_HDINFO, SCENE_ONEKEYCHECK, false, 1);
    virtualMachineInfo = new CheckTask(this, toolUtil, FUNC_VMINFO, SCENE_ONEKEYCHECK, false, 1);
    netConfig = new CheckTask(this, toolUtil, FUNC_NCINFO, SCENE_ONEKEYCHECK, false, 1);
    adapterDevice = new CheckTask(this, toolUtil, FUNC_NADEV, SCENE_ONEKEYCHECK, false, 1);
    printDevice = new CheckTask(this, toolUtil, FUNC_PRIDEV, SCENE_ONEKEYCHECK, false, 1);
    blueToothDevice = new CheckTask(this, toolUtil, FUNC_BTDEV, SCENE_ONEKEYCHECK, false, 1);
    deviceConnection = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                          QList<CheckTask*>() << hardDiskInfo << virtualMachineInfo
                                                              << netConfig << adapterDevice << printDevice
                                                              << blueToothDevice);

    patchNotInstalled = new CheckTask(this, toolUtil, FUNC_PATCH, SCENE_ONEKEYCHECK, false, 1);
    systemService = new CheckTask(this, toolUtil, FUNC_SERVICE, SCENE_ONEKEYCHECK, false, 2);
    systemProcess = new CheckTask(this, toolUtil, FUNC_PROCESS, SCENE_ONEKEYCHECK, false, 2);
    evenProduct = new CheckTask(this, toolUtil, FUNC_OTHERPDT, SCENE_ONEKEYCHECK, false, 1);
    timeSwitchMachine = new CheckTask(this, toolUtil, FUNC_SWITHTIME, SCENE_ONEKEYCHECK, false, 1);
    securitySoftware = new CheckTask(this, toolUtil, FUNC_SECSOFT, SCENE_ONEKEYCHECK, false, 1);
    systemSecurity = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                        QList<CheckTask*>() << patchNotInstalled << systemService
                                                            << systemProcess << evenProduct << timeSwitchMachine
                                                            << securitySoftware);

    securityPolicy = new CheckTask(this, toolUtil, FUNC_SECPLCY, SCENE_ONEKEYCHECK, false, 1);
    openPort = new CheckTask(this, toolUtil, FUNC_OPENPORT, SCENE_ONEKEYCHECK, false, 1);
    sharingInfo = new CheckTask(this, toolUtil, FUNC_SHARINFO, SCENE_ONEKEYCHECK, false, 1);
    networkSoftware = new CheckTask(this, toolUtil, FUNC_NETSOFT, SCENE_ONEKEYCHECK, false, 1);
    groupInfo = new CheckTask(this, toolUtil, FUNC_GRPINFO, SCENE_ONEKEYCHECK, false, 1);
    userInfo = new CheckTask(this, toolUtil, FUNC_USERINFO, SCENE_ONEKEYCHECK, false, 1);
    databaseInfo = new CheckTask(this, toolUtil, FUNC_DBINFO, SCENE_ONEKEYCHECK, false, 1);
    eventLog = new CheckTask(this, toolUtil, FUNC_EVELOG, SCENE_ONEKEYCHECK, false, 1);
    userAuthentication = new CheckTask(this, toolUtil, FUNC_USRAUTH, SCENE_ONEKEYCHECK, false, 1);
    securityThreat = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                        QList<CheckTask*>() << securityPolicy << openPort << sharingInfo
                                                            << networkSoftware << groupInfo << userInfo
                                                            << databaseInfo << eventLog << userAuthentication);

    usbRoutineCheck = new CheckTask(this, toolUtil, FUNC_USBCOMCHECK, SCENE_ONEKEYCHECK, false, 1);
    usbCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                  QList<CheckTask*>() << usbRoutineCheck);
    //CheckTask*	usbDepthCheck
    netRecordsRoutineCheck = new CheckTask(this, toolUtil, FUNC_NETRECCOMCHECK, SCENE_ONEKEYCHECK, false, 1);
    netRecordsCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                         QList<CheckTask*>() << netRecordsRoutineCheck);

    fileRoutineCheck = new CheckTask(this, toolUtil, FUNC_FILECOMCHECK, SCENE_ONEKEYCHECK, true, 1);
    fileCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                   QList<CheckTask*>() << fileRoutineCheck);

    //CheckTask* deletedFileRecovery;
    //CheckTask* fileFragmentsCheck;

    //CheckTask*	networkWeapon
    threatDocument = new CheckTask(this, toolUtil, FUNC_TROJANCHECK, SCENE_ONEKEYCHECK, true, 1);
    trojanCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                     QList<CheckTask*>() << threatDocument);
    ;

    imageRoutineCheck = new CheckTask(this, toolUtil, FUNC_IMAGECHECK, SCENE_ONEKEYCHECK, true, 1);
    imageCheck = new CheckTaskGroup(this, SCENE_ONEKEYCHECK, 1,
                                    QList<CheckTask*>() << imageRoutineCheck);
    ;
}
void OneKeyCheckState::initConStateGroup()
{
    QList<CheckTaskGroup*> taskGroups;
    taskGroups << basicInfo << deviceConnection << netRecordsCheck
               << usbCheck << securityThreat << systemSecurity
               << fileCheck << trojanCheck << imageCheck;
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

void OneKeyCheckState::totalUnitChanged(const int value)
{
    totalcompleteunit += value;
}
void OneKeyCheckState::initConUIState(MainWindow* mainwindow)
{
    OneKeyCheckMainWidget* okc = mainwindow->oneKeyCheckMainWidget;
    OneKeyCheckSettingWidget* okcs = mainwindow->oneKeyCheckSettingWidget;

    connect(okc->startcheckbtn, SIGNAL(buttonClicked()), this, SLOT(startexcute()));
    connect(okc->cancelcheckbtn, SIGNAL(buttonClicked()), this, SLOT(stopexcute()));
    connect(this, SIGNAL(completerateUpdateSig(const int, const QString&)), okc, SLOT(completerateUpdate(const int, const QString&)));
    connect(this, SIGNAL(dataCountUpdateSig(const int, const int)), okc, SLOT(dataCountUpdate(const int, const int)));

    connect(basicInfo, SIGNAL(errorFindSig()), okc->basicinfobtn, SLOT(changeToProblem()));
    connect(basicInfo, SIGNAL(completeSig()), okc->basicinfobtn, SLOT(changeToNoProblem()));
    connect(okcs->commonCheckSettingPart, SIGNAL(enableBasicInfo()), basicInfo, SLOT(enableGroup()));
    connect(okcs->commonCheckSettingPart, SIGNAL(disableBasicInfo()), basicInfo, SLOT(disableGroup()));

    connect(deviceConnection, SIGNAL(errorFindSig()), okc->deviceconnectionbtn, SLOT(changeToProblem()));
    connect(deviceConnection, SIGNAL(completeSig()), okc->deviceconnectionbtn, SLOT(changeToNoProblem()));
    connect(okcs->commonCheckSettingPart, SIGNAL(enableDeviceConnection()), deviceConnection, SLOT(enableGroup()));
    connect(okcs->commonCheckSettingPart, SIGNAL(disableDeviceConnection()), deviceConnection, SLOT(disableGroup()));

    connect(systemSecurity, SIGNAL(errorFindSig()), okc->systemsecuritybtn, SLOT(changeToProblem()));
    connect(systemSecurity, SIGNAL(completeSig()), okc->systemsecuritybtn, SLOT(changeToNoProblem()));
    connect(okcs->commonCheckSettingPart, SIGNAL(enableSystemSecurity()), systemSecurity, SLOT(enableGroup()));
    connect(okcs->commonCheckSettingPart, SIGNAL(disableSystemSecurity()), systemSecurity, SLOT(disableGroup()));

    connect(securityThreat, SIGNAL(errorFindSig()), okc->securitythreatbtn, SLOT(changeToProblem()));
    connect(securityThreat, SIGNAL(completeSig()), okc->securitythreatbtn, SLOT(changeToNoProblem()));
    connect(okcs->commonCheckSettingPart, SIGNAL(enableSecurityThreat()), securityThreat, SLOT(enableGroup()));
    connect(okcs->commonCheckSettingPart, SIGNAL(disableSecurityThreat()), securityThreat, SLOT(disableGroup()));


    connect(usbCheck, SIGNAL(errorFindSig()), okc->usbcheckbtn, SLOT(changeToProblem()));
    connect(usbCheck, SIGNAL(completeSig()), okc->usbcheckbtn, SLOT(changeToNoProblem()));
    connect(okcs->commonCheckSettingPart, SIGNAL(enableUsbCheck()), usbCheck, SLOT(enableGroup()));
    connect(okcs->commonCheckSettingPart, SIGNAL(disableUsbCheck()), usbCheck, SLOT(disableGroup()));

    connect(netRecordsCheck, SIGNAL(errorFindSig()), okc->netbrowserbtn, SLOT(changeToProblem()));
    connect(netRecordsCheck, SIGNAL(completeSig()), okc->netbrowserbtn, SLOT(changeToNoProblem()));
    connect(okcs->commonCheckSettingPart, SIGNAL(enableNetBrowser()), netRecordsCheck, SLOT(enableGroup()));
    connect(okcs->commonCheckSettingPart, SIGNAL(disableNetBrowser()), netRecordsCheck, SLOT(disableGroup()));


    connect(fileCheck, SIGNAL(errorFindSig()), okc->filecheckbtn, SLOT(changeToProblem()));
    connect(fileCheck, SIGNAL(completeSig()), okc->filecheckbtn, SLOT(changeToNoProblem()));

    connect(trojanCheck, SIGNAL(errorFindSig()), okc->tjcheckbtn, SLOT(changeToProblem()));
    connect(trojanCheck, SIGNAL(completeSig()), okc->tjcheckbtn, SLOT(changeToNoProblem()));

    connect(imageCheck, SIGNAL(errorFindSig()), okc->imagecheckbtn, SLOT(changeToProblem()));
    connect(imageCheck, SIGNAL(completeSig()), okc->imagecheckbtn, SLOT(changeToNoProblem()));

    //Basic Info
    BasicInfoRpt* okcBasicInfoRpt = mainwindow->okcBasicInfoRpt;
    connect(operatingSystemInfo, &CheckTask::completeSig, okcBasicInfoRpt->osInfoBtn, &TaskButton::changeToNoProblem);
    connect(operatingSystemInfo, &CheckTask::errorFindSig, okcBasicInfoRpt->osInfoBtn, &TaskButton::changeToProblem);
    connect(operatingSystemInfo, &CheckTask::dataUpdateSig, okcBasicInfoRpt, &BasicInfoRpt::addOSInfo);

    connect(cpuInfo, &CheckTask::completeSig, okcBasicInfoRpt->cpuInfoBtn, &TaskButton::changeToNoProblem);
    connect(cpuInfo, &CheckTask::errorFindSig, okcBasicInfoRpt->cpuInfoBtn, &TaskButton::changeToProblem);
    connect(cpuInfo, &CheckTask::dataUpdateSig, okcBasicInfoRpt, &BasicInfoRpt::addCpuInfo);

    connect(biosInfo, &CheckTask::completeSig, okcBasicInfoRpt->biosInfoBtn, &TaskButton::changeToNoProblem);
    connect(biosInfo, &CheckTask::errorFindSig, okcBasicInfoRpt->biosInfoBtn, &TaskButton::changeToProblem);
    connect(biosInfo, &CheckTask::dataUpdateSig, okcBasicInfoRpt, &BasicInfoRpt::addBiosInfo);

    connect(motherboardInfo, &CheckTask::completeSig, okcBasicInfoRpt->motherBoardInfoBtn, &TaskButton::changeToNoProblem);
    connect(motherboardInfo, &CheckTask::errorFindSig, okcBasicInfoRpt->motherBoardInfoBtn, &TaskButton::changeToProblem);
    connect(motherboardInfo, &CheckTask::dataUpdateSig, okcBasicInfoRpt, &BasicInfoRpt::addMotherBoardInfo);

    connect(memoryInfo, &CheckTask::completeSig, okcBasicInfoRpt->memoryInfoBtn, &TaskButton::changeToNoProblem);
    connect(memoryInfo, &CheckTask::errorFindSig, okcBasicInfoRpt->memoryInfoBtn, &TaskButton::changeToProblem);
    connect(memoryInfo, &CheckTask::dataUpdateSig, okcBasicInfoRpt, &BasicInfoRpt::addMemoryInfo);

    connect(graphicsCardInfo, &CheckTask::completeSig, okcBasicInfoRpt->graphicsCardInfoBtn, &TaskButton::changeToNoProblem);
    connect(graphicsCardInfo, &CheckTask::errorFindSig, okcBasicInfoRpt->graphicsCardInfoBtn, &TaskButton::changeToProblem);
    connect(graphicsCardInfo, &CheckTask::dataUpdateSig, okcBasicInfoRpt, &BasicInfoRpt::addGraphicsCardInfo);

    DeviceConnectRpt* okcDeviceConnectRpt = mainwindow->okcDeviceConnectRpt;
    connect(hardDiskInfo, &CheckTask::completeSig, okcDeviceConnectRpt->hardDiskInfoBtn, &TaskButton::changeToNoProblem);
    connect(hardDiskInfo, &CheckTask::errorFindSig, okcDeviceConnectRpt->hardDiskInfoBtn, &TaskButton::changeToProblem);
    connect(hardDiskInfo, &CheckTask::dataUpdateSig, okcDeviceConnectRpt, &DeviceConnectRpt::addHardDiskInfo);

    connect(virtualMachineInfo, &CheckTask::completeSig, okcDeviceConnectRpt->virtualMachineInfoBtn, &TaskButton::changeToNoProblem);
    connect(virtualMachineInfo, &CheckTask::errorFindSig, okcDeviceConnectRpt->virtualMachineInfoBtn, &TaskButton::changeToProblem);
    connect(virtualMachineInfo, &CheckTask::dataUpdateSig, okcDeviceConnectRpt, &DeviceConnectRpt::addVirtualMachineInfo);

    connect(netConfig, &CheckTask::completeSig, okcDeviceConnectRpt->netConfigBtn, &TaskButton::changeToNoProblem);
    connect(netConfig, &CheckTask::errorFindSig, okcDeviceConnectRpt->netConfigBtn, &TaskButton::changeToProblem);
    connect(netConfig, &CheckTask::dataUpdateSig, okcDeviceConnectRpt, &DeviceConnectRpt::addNetConfig);

    connect(adapterDevice, &CheckTask::completeSig, okcDeviceConnectRpt->adapterDeviceBtn, &TaskButton::changeToNoProblem);
    connect(adapterDevice, &CheckTask::errorFindSig, okcDeviceConnectRpt->adapterDeviceBtn, &TaskButton::changeToProblem);
    connect(adapterDevice, &CheckTask::dataUpdateSig, okcDeviceConnectRpt, &DeviceConnectRpt::addAdapterDevice);

    connect(printDevice, &CheckTask::completeSig, okcDeviceConnectRpt->printDeviceBtn, &TaskButton::changeToNoProblem);
    connect(printDevice, &CheckTask::errorFindSig, okcDeviceConnectRpt->printDeviceBtn, &TaskButton::changeToProblem);
    connect(printDevice, &CheckTask::dataUpdateSig, okcDeviceConnectRpt, &DeviceConnectRpt::addPrintDevice);

    connect(blueToothDevice, &CheckTask::completeSig, okcDeviceConnectRpt->blueToothDeviceBtn, &TaskButton::changeToNoProblem);
    connect(blueToothDevice, &CheckTask::errorFindSig, okcDeviceConnectRpt->blueToothDeviceBtn, &TaskButton::changeToProblem);
    connect(blueToothDevice, &CheckTask::dataUpdateSig, okcDeviceConnectRpt, &DeviceConnectRpt::addBlueToothDevice);

    NetRecordCommonRpt* okcNetRecordRpt = mainwindow->okcNetRecordRpt;
    connect(netRecordsRoutineCheck, &CheckTask::dataUpdateSig, okcNetRecordRpt, &NetRecordCommonRpt::addNetRecordsInfo);

    SystemSecurityRpt* okcSystemSecurityRpt = mainwindow->okcSystemSecurityRpt;

    connect(patchNotInstalled, &CheckTask::completeSig, okcSystemSecurityRpt->patchNotInstalledBtn, &TaskButton::changeToNoProblem);
    connect(patchNotInstalled, &CheckTask::errorFindSig, okcSystemSecurityRpt->patchNotInstalledBtn, &TaskButton::changeToProblem);
    connect(patchNotInstalled, &CheckTask::dataUpdateSig, okcSystemSecurityRpt, &SystemSecurityRpt::addPatchNotInstalled);

    connect(systemService, &CheckTask::completeSig, okcSystemSecurityRpt->systemServiceBtn, &TaskButton::changeToNoProblem);
    connect(systemService, &CheckTask::errorFindSig, okcSystemSecurityRpt->systemServiceBtn, &TaskButton::changeToProblem);
    connect(systemService, &CheckTask::dataUpdateSig, okcSystemSecurityRpt, &SystemSecurityRpt::addSystemService);

    connect(systemProcess, &CheckTask::completeSig, okcSystemSecurityRpt->systemProcessBtn, &TaskButton::changeToNoProblem);
    connect(systemProcess, &CheckTask::errorFindSig, okcSystemSecurityRpt->systemProcessBtn, &TaskButton::changeToProblem);
    connect(systemProcess, &CheckTask::dataUpdateSig, okcSystemSecurityRpt, &SystemSecurityRpt::addSystemProcess);

    connect(evenProduct, &CheckTask::completeSig, okcSystemSecurityRpt->evenProductBtn, &TaskButton::changeToNoProblem);
    connect(evenProduct, &CheckTask::errorFindSig, okcSystemSecurityRpt->evenProductBtn, &TaskButton::changeToProblem);
    connect(evenProduct, &CheckTask::dataUpdateSig, okcSystemSecurityRpt, &SystemSecurityRpt::addEvenProduct);

    connect(timeSwitchMachine, &CheckTask::completeSig, okcSystemSecurityRpt->timeSwitchMachineBtn, &TaskButton::changeToNoProblem);
    connect(timeSwitchMachine, &CheckTask::errorFindSig, okcSystemSecurityRpt->timeSwitchMachineBtn, &TaskButton::changeToProblem);
    connect(timeSwitchMachine, &CheckTask::dataUpdateSig, okcSystemSecurityRpt, &SystemSecurityRpt::addTimeSwitchMachine);

    connect(securitySoftware, &CheckTask::completeSig, okcSystemSecurityRpt->securitySoftwareBtn, &TaskButton::changeToNoProblem);
    connect(securitySoftware, &CheckTask::errorFindSig, okcSystemSecurityRpt->securitySoftwareBtn, &TaskButton::changeToProblem);
    connect(securitySoftware, &CheckTask::dataUpdateSig, okcSystemSecurityRpt, &SystemSecurityRpt::addSecuritySoftware);

    UsbRecordCommonRpt* okcUsbRecordCommonRpt = mainwindow->okcUsbRecordCommonRpt;
    connect(usbRoutineCheck, &CheckTask::dataUpdateSig, okcUsbRecordCommonRpt, &UsbRecordCommonRpt::addUsbRecordsInfo);

    SecurityThreatRpt* okcSecurityThreatRpt = mainwindow->okcSecurityThreatRpt;

    connect(securityPolicy, &CheckTask::completeSig, okcSecurityThreatRpt->securityPolicyBtn, &TaskButton::changeToNoProblem);
    connect(securityPolicy, &CheckTask::errorFindSig, okcSecurityThreatRpt->securityPolicyBtn, &TaskButton::changeToProblem);
    connect(securityPolicy, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addSecurityPolicy);

    connect(openPort, &CheckTask::completeSig, okcSecurityThreatRpt->openPortBtn, &TaskButton::changeToNoProblem);
    connect(openPort, &CheckTask::errorFindSig, okcSecurityThreatRpt->openPortBtn, &TaskButton::changeToProblem);
    connect(openPort, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addOpenPort);

    connect(sharingInfo, &CheckTask::completeSig, okcSecurityThreatRpt->sharingInfoBtn, &TaskButton::changeToNoProblem);
    connect(sharingInfo, &CheckTask::errorFindSig, okcSecurityThreatRpt->sharingInfoBtn, &TaskButton::changeToProblem);
    connect(sharingInfo, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addSharingInfo);

    connect(networkSoftware, &CheckTask::completeSig, okcSecurityThreatRpt->networkSoftwareBtn, &TaskButton::changeToNoProblem);
    connect(networkSoftware, &CheckTask::errorFindSig, okcSecurityThreatRpt->networkSoftwareBtn, &TaskButton::changeToProblem);
    connect(networkSoftware, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addNetworkSoftware);

    connect(groupInfo, &CheckTask::completeSig, okcSecurityThreatRpt->groupInfoBtn, &TaskButton::changeToNoProblem);
    connect(groupInfo, &CheckTask::errorFindSig, okcSecurityThreatRpt->groupInfoBtn, &TaskButton::changeToProblem);
    connect(groupInfo, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addGroupInfo);

    connect(userInfo, &CheckTask::completeSig, okcSecurityThreatRpt->userInfoBtn, &TaskButton::changeToNoProblem);
    connect(userInfo, &CheckTask::errorFindSig, okcSecurityThreatRpt->userInfoBtn, &TaskButton::changeToProblem);
    connect(userInfo, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addUserInfo);

    connect(eventLog, &CheckTask::completeSig, okcSecurityThreatRpt->eventLogBtn, &TaskButton::changeToNoProblem);
    connect(eventLog, &CheckTask::errorFindSig, okcSecurityThreatRpt->eventLogBtn, &TaskButton::changeToProblem);
    connect(eventLog, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addEventLog);

    connect(databaseInfo, &CheckTask::completeSig, okcSecurityThreatRpt->databaseInfoBtn, &TaskButton::changeToNoProblem);
    connect(databaseInfo, &CheckTask::errorFindSig, okcSecurityThreatRpt->databaseInfoBtn, &TaskButton::changeToProblem);
    connect(databaseInfo, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addDatabaseInfo);

    connect(userAuthentication, &CheckTask::completeSig, okcSecurityThreatRpt->userAuthenticationBtn, &TaskButton::changeToNoProblem);
    connect(userAuthentication, &CheckTask::errorFindSig, okcSecurityThreatRpt->userAuthenticationBtn, &TaskButton::changeToProblem);
    connect(userAuthentication, &CheckTask::dataUpdateSig, okcSecurityThreatRpt, &SecurityThreatRpt::addUserAuthentication);

    FileCheckCommonRpt* okcFileCheckCommonRpt = mainwindow->okcFileCheckCommonRpt;
    connect(fileRoutineCheck, &CheckTask::dataUpdateSig, okcFileCheckCommonRpt, &FileCheckCommonRpt::addFileRoutineCheckInfo);
    connect(okcs->fileCheckSettingPart, SIGNAL(enableFileCheck()), fileRoutineCheck, SLOT(enableTask()));
    connect(okcs->fileCheckSettingPart, SIGNAL(disableFileCheck()), fileRoutineCheck, SLOT(disableTask()));
    connect(okcs->fileCheckSettingPart, SIGNAL(setParameter( QString,  QString)), fileRoutineCheck, SLOT(setParameters( QString,  QString)));


    TrojanCheckRpt* okcTrojanCheckRpt = mainwindow->okcTrojanCheckRpt;
    connect(threatDocument, &CheckTask::dataUpdateSig, okcTrojanCheckRpt, &TrojanCheckRpt::addThreatDocument);
    //connect(networkWeapon, &CheckTask::dataUpdateSig, okcTrojanCheckRpt, &TrojanCheckRpt::addNetworkWeapon);
    connect(okcs->trojanCheckSettingPart, SIGNAL(enableThreatDocument()), threatDocument, SLOT(enableTask()));
    connect(okcs->trojanCheckSettingPart, SIGNAL(disableThreatDocument()), threatDocument, SLOT(disableTask()));
    connect(okcs->trojanCheckSettingPart, SIGNAL(setParameter(QString,  QString)), threatDocument, SLOT(setParameters(QString,  QString)));

    ImageCheckRpt* okcImageCheckRpt = mainwindow->okcImageCheckRpt;
    connect(imageRoutineCheck, &CheckTask::dataUpdateSig, okcImageCheckRpt, &ImageCheckRpt::addImageCheckInfo);
    connect(okcs->imageCheckSettingPart, SIGNAL(enableImageCheck()), imageRoutineCheck, SLOT(enableTask()));
    connect(okcs->imageCheckSettingPart, SIGNAL(disableImageCheck()), imageRoutineCheck, SLOT(disableTask()));
    connect(okcs->imageCheckSettingPart, SIGNAL(setParameter(QString,  QString)), imageRoutineCheck, SLOT(setParameters(QString,  QString)));

    //init Connection for disable enable and parameter
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
    emit completerateUpdateSig(currentcompleteunit * 100 / totalcompleteunit, status);
    if (this->currentcompleteunit == this->totalcompleteunit) {
        this->start = false;
        emit completeSig();
    }
};
void OneKeyCheckState::dataCountUpdate(const int totalproblems, const int totalinfomations)
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
void OneKeyCheckState::initConInterfaceTask(InterfaceForTool* interfaceForTool)
{

    //Basic Info
    connect(interfaceForTool, SIGNAL(okc_cpu_progress(const int, const QString&)), cpuInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_cpu_error(const QString&)), cpuInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_cpu_data(const QVariantList&)), cpuInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_os_progress(const int, const QString&)), operatingSystemInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_os_error(const QString&)), operatingSystemInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_os_data(const QVariantList&)), operatingSystemInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_bios_progress(const int, const QString&)), biosInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_bios_error(const QString&)), biosInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_bios_data(const QVariantList&)), biosInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_mb_progress(const int, const QString&)), motherboardInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_mb_error(const QString&)), motherboardInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_mb_data(const QVariantList&)), motherboardInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_mem_progress(const int, const QString&)), memoryInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_mem_error(const QString&)), memoryInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_mem_data(const QVariantList&)), memoryInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_gc_progress(const int, const QString&)), graphicsCardInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_gc_error(const QString&)), graphicsCardInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_gc_data(const QVariantList&)), graphicsCardInfo, SLOT(dataUpdate(const QVariantList&)));

    //设备连接信息
    connect(interfaceForTool, SIGNAL(okc_hd_progress(const int, const QString&)), hardDiskInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_hd_error(const QString&)), hardDiskInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_hd_data(const QVariantList&)), hardDiskInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_vm_progress(const int, const QString&)), virtualMachineInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_vm_error(const QString&)), virtualMachineInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_vm_data(const QVariantList&)), virtualMachineInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_nc_progress(const int, const QString&)), netConfig, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_nc_error(const QString&)), netConfig, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_nc_data(const QVariantList&)), netConfig, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_na_progress(const int, const QString&)), adapterDevice, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_na_error(const QString&)), adapterDevice, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_na_data(const QVariantList&)), adapterDevice, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_print_progress(const int, const QString&)), printDevice, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_print_error(const QString&)), printDevice, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_print_data(const QVariantList&)), printDevice, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_bt_progress(const int, const QString&)), blueToothDevice, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_bt_error(const QString&)), blueToothDevice, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_bt_data(const QVariantList&)), blueToothDevice, SLOT(dataUpdate(const QVariantList&)));

    //系统安全信息
    connect(interfaceForTool, SIGNAL(okc_patch_progress(const int, const QString&)), patchNotInstalled, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_patch_error(const QString&)), patchNotInstalled, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_patch_data(const QVariantList&)), patchNotInstalled, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_service_progress(const int, const QString&)), systemService, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_service_error(const QString&)), systemService, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_service_data(const QVariantList&)), systemService, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_process_progress(const int, const QString&)), systemProcess, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_process_error(const QString&)), systemProcess, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_process_data(const QVariantList&)), systemProcess, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_otherpdt_progress(const int, const QString&)), evenProduct, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_otherpdt_error(const QString&)), evenProduct, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_otherpdt_data(const QVariantList&)), evenProduct, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_swithtime_progress(const int, const QString&)), timeSwitchMachine, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_swithtime_error(const QString&)), timeSwitchMachine, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_swithtime_data(const QVariantList&)), timeSwitchMachine, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_secsoft_progress(const int, const QString&)), securitySoftware, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_secsoft_error(const QString&)), securitySoftware, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_secsoft_data(const QVariantList&)), securitySoftware, SLOT(dataUpdate(const QVariantList&)));

    //安全隐患信息

    connect(interfaceForTool, SIGNAL(okc_secplcy_progress(const int, const QString&)), securityPolicy, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_secplcy_error(const QString&)), securityPolicy, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_secplcy_data(const QVariantList&)), securityPolicy, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_openport_progress(const int, const QString&)), openPort, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_openport_error(const QString&)), openPort, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_openport_data(const QVariantList&)), openPort, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_sharinfo_progress(const int, const QString&)), sharingInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_sharinfo_error(const QString&)), sharingInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_sharinfo_data(const QVariantList&)), sharingInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_netsoft_progress(const int, const QString&)), networkSoftware, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_netsoft_error(const QString&)), networkSoftware, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_netsoft_data(const QVariantList&)), networkSoftware, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_grpinfo_progress(const int, const QString&)), groupInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_grpinfo_error(const QString&)), groupInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_grpinfo_data(const QVariantList&)), groupInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_userinfo_progress(const int, const QString&)), userInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_userinfo_error(const QString&)), userInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_userinfo_data(const QVariantList&)), userInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_dbinfo_progress(const int, const QString&)), databaseInfo, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_dbinfo_error(const QString&)), databaseInfo, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_dbinfo_data(const QVariantList&)), databaseInfo, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_evelog_progress(const int, const QString&)), eventLog, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_evelog_error(const QString&)), eventLog, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_evelog_data(const QVariantList&)), eventLog, SLOT(dataUpdate(const QVariantList&)));

    connect(interfaceForTool, SIGNAL(okc_usrauth_progress(const int, const QString&)), userAuthentication, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_usrauth_error(const QString&)), userAuthentication, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_usrauth_data(const QVariantList&)), userAuthentication, SLOT(dataUpdate(const QVariantList&)));

    //USB设备记录
    connect(interfaceForTool, SIGNAL(okc_usbcomcheck_progress(const int, const QString&)), usbRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_usbcomcheck_error(const QString&)), usbRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_usbcomcheck_data(const QVariantList&)), usbRoutineCheck, SLOT(dataUpdate(const QVariantList&)));

    //上网记录
    connect(interfaceForTool, SIGNAL(okc_netreccomcheck_progress(const int, const QString&)), netRecordsRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_netreccomcheck_error(const QString&)), netRecordsRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_netreccomcheck_data(const QVariantList&)), netRecordsRoutineCheck, SLOT(dataUpdate(const QVariantList&)));

    //文件检查
    connect(interfaceForTool, SIGNAL(okc_filecomcheck_progress(const int, const QString&)), fileRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_filecomcheck_error(const QString&)), fileRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_filecomcheck_data(const QVariantList&)), fileRoutineCheck, SLOT(dataUpdate(const QVariantList&)));

    //木马检查
    connect(interfaceForTool, SIGNAL(okc_threatdoccheck_progress(const int, const QString&)), threatDocument, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_threatdoccheck_error(const QString&)), threatDocument, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_threatdoccheck_data(const QVariantList&)), threatDocument, SLOT(dataUpdate(const QVariantList&)));

    //connect(interfaceForTool, SIGNAL(okc_netweapon_progress(const int, const QString&)), networkWeapon, SLOT(progressUpdate(const int, const QString&)));
    //connect(interfaceForTool, SIGNAL(okc_netweapon_error(const QString&)), networkWeapon, SLOT(errorUpdate(const QString&)));
    //connect(interfaceForTool, SIGNAL(okc_netweapon_data(const QVariantList&)), networkWeapon, SLOT(dataUpdate(const QVariantList&)));

    //Image检查
    connect(interfaceForTool, SIGNAL(okc_imagecheck_progress(const int, const QString&)), imageRoutineCheck, SLOT(progressUpdate(const int, const QString&)));
    connect(interfaceForTool, SIGNAL(okc_imagecheck_error(const QString&)), imageRoutineCheck, SLOT(errorUpdate(const QString&)));
    connect(interfaceForTool, SIGNAL(okc_imagecheck_data(const QVariantList&)), imageRoutineCheck, SLOT(dataUpdate(const QVariantList&)));
}
