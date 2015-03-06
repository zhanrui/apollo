#include "globals.h"

#include <QString>

/****************************************************************************
**
* dbus const
*
*
* service name: com.bmjc.backend,
* path name: /bmjc/backend,
* interface name: bmjc.backend;
*
* 场景名称
* 1 OneKeyCheck
* 2 CommonCheck
* 3 DeepCheck
* 4 FileCheck
* 5 TrojanCheck
*
* functions:
*1.基本信息
*   1-1.操作系统	operatingSystemInfo
*   1-2.CPU信息	cpuInfo
*   1-3.BIOS信息	biosInfo
*	 1-4.主板信息	motherboardInfo
*	 1-5.内存信息	memoryInfo
*	 1-6.显卡信息	graphicsCardInfo

*2.设备连接信息
*   2-1.硬盘信息	hardDiskInfo
*	 2-2.虚拟机信息	virtualMachineInfo
*	 2-3.网络配置	netConfig
*	 2-4.网卡设备	adapterDevice
*	 2-5.打印机设备	printDevice
*	 2-6.蓝牙设备	blueToothDevice
*
*3.系统安全信息
*   3-1.未安装补丁	patchNotInstalled
*	 3-2.系统服务	systemService
*	 3-3.系统进程	systemProcess
*	 3-4.外连产品	evenProduct
*	 3-5.开关机时间	timeSwitchMachine
*	 3-6.安全软件	securitySoftware
*
*4.安全隐患信息
*   4-1.安全策略	securityPolicy
*   4-2.开放端口	openPort
*	 4-3.共享信息	sharingInfo
*	 4-4.上网软件	networkSoftware
*	 4-5.组信息	groupInfo
*	 4-6.用户信息	userInfo
*	 4-7.数据库信息	databaseInfo
*	 4-8.事件日志	eventLog
*	 4-9.用户认证	userAuthentication
*5.USB设备记录
*   5-1.USB常规检查	usbRoutineCheck
*   5-2.USB深度检查	usbDepthCheck
*
*6.上网记录
*   6-1.上网记录常规检查	netRecordsRoutineCheck
*   6-2.上网记录深度检查	netRecordsDepthCheck
*7.文件检查
*   7-1.文件常规检查	fileRoutineCheck
*   7-2.已删除文件恢复	deletedFileRecovery
*   7-3.文件碎片检查	fileFragmentsCheck

*8.木马检查
*   8-1.网络武器	networkWeapon
*   8-2.威胁文档	threatDocument
*
*
****************************************************************************/

const QString RPT_PROGRESS="progressreport";
const QString RPT_DATA="datareport";
const QString RPT_ERROR="errorreport";

const QString ACTION_RUN="run";
const QString ACTION_STOP="stop";

const QString SCENE_ONEKEYCHECK = "OneKeyCheck";
const QString SCENE_COMMONCHECK = "CommonCheck";
const QString SCENE_DEEPCHECK = "DeepCheck";
const QString SCENE_FILECHECK = "FileCheck";
const QString SCENE_TROJANCHECK = "TrojanCheck";
const QString  SCENE_IMAGECHECK= "ImageCheck";
const QString SCENE_DEEP_USBCHECK= "DeepUsbCheck";
const QString SCENE_DEEP_NETRECCHECK= "DeepNetRecCheck";

const QString TOOL_SERVICE = "com.bmjc.backend";
const QString TOOL_PATH = "/bmjc/backend";
const QString TOOL_INTERFACE = "bmjc.backend";
const QString TOOL_FUNCTION = "reveiveFromUI";

const QString UI_SERVICE = "com.bmjc.ui";
const QString UI_PATH = "/bmjc/ui";
const QString UI_INTERFACE = "bmjc.ui";

//基本信息
const QString FUNC_OSINFO = "operatingSystemInfo";
const QString FUNC_CPUINFO = "cpuInfo";
const QString FUNC_BIOSINFO = "biosInfo";
const QString FUNC_MBINFO = "motherboardInfo";
const QString FUNC_MEMINFO = "memoryInfo";
const QString FUNC_GCINFO = "graphicsCardInfo";

//设备连接信息
const QString FUNC_HDINFO = "hardDiskInfo";
const QString FUNC_VMINFO = "virtualMachineInfo";
const QString FUNC_NCINFO = "netConfig";
const QString FUNC_NADEV = "adapterDevice";
const QString FUNC_PRIDEV = "printDevice";
const QString FUNC_BTDEV = "blueToothDevice";

//系统安全信息
const QString FUNC_PATCH = "patchNotInstalled";
const QString FUNC_SERVICE = "systemService";
const QString FUNC_PROCESS = "systemProcess";
const QString FUNC_OTHERPDT = "evenProduct";
const QString FUNC_SWITHTIME = "timeSwitchMachine";
const QString FUNC_SECSOFT = "securitySoftware";

//安全隐患信息
const QString FUNC_SECPLCY = "securityPolicy";
const QString FUNC_OPENPORT = "openPort";
const QString FUNC_SHARINFO = "sharingInfo";
const QString FUNC_NETSOFT = "networkSoftware";
const QString FUNC_GRPINFO = "groupInfo";
const QString FUNC_USERINFO = "userInfo";
const QString FUNC_DBNFO = "databaseInfo";
const QString FUNC_EVELOG = "eventLog";
const QString FUNC_USRAUTH = "userAuthentication";

//USB设备记录
const QString FUNC_USBCOMCHECK = "usbRoutineCheck";
const QString FUNC_USBDEPCHECK = "usbDepthCheck";

//上网记录
const QString FUNC_NETRECCOMCHECK = "netRecordsRoutineCheck";
const QString FUNC_NETRECDEPCHECK = "netRecordsDepthCheck";

//文件检查
const QString FUNC_FILECOMCHECK = "fileRoutineCheck";
const QString FUNC_FILEDELCHECK = "deletedFileRecovery";
const QString FUNC_FILEFRGCHECK = "fileFragmentsCheck";

//木马检查
const QString FUNC_MALWARECHECK = "networkWeapon";
const QString FUNC_TROJANCHECK = "threatDocument";

const QString FUNC_IMAGECHECK ="imageCheck";
