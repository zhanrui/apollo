#ifndef GLOBALS_H
#define GLOBALS_H


class QString;




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

extern const QString RPT_PROGRESS;
extern const QString RPT_DATA;
extern const QString RPT_ERROR;

extern const QString ACTION_RUN;
extern const QString ACTION_STOP;

extern const QString SCENE_COMMONCHECK;
extern const QString SCENE_DEEP_USBCHECK;
extern const QString SCENE_DEEP_NETRECCHECK;
extern const QString SCENE_FILECHECK;
extern const QString SCENE_TROJANCHECK;

extern const QString SCENE_ONEKEYCHECK;
extern const QString SCENE_COMMONCHECK;
extern const QString SCENE_DEEP_USBCHECK;
extern const QString SCENE_DEEP_NETRECCHECK;
extern const QString SCENE_FILECHECK;
extern const QString SCENE_TROJANCHECK;

extern const QString TOOL_SERVICE;
extern const QString TOOL_PATH;
extern const QString TOOL_INTERFACE;
extern const QString TOOL_FUNCTION;

extern const QString UI_SERVICE;
extern const QString UI_PATH;
extern const QString UI_INTERFACE;
extern const QString UI_FUNCTION;

//基本信息
extern const QString FUNC_OSINFO;
extern const QString FUNC_CPUINFO;
extern const QString FUNC_BIOSINFO;
extern const QString FUNC_MBINFO;
extern const QString FUNC_MEMINFO;
extern const QString FUNC_GCINFO;

//设备连接信息
extern const QString FUNC_HDINFO;
extern const QString FUNC_VMINFO;
extern const QString FUNC_NCINFO;
extern const QString FUNC_NADEV;
extern const QString FUNC_PRIDEV;
extern const QString FUNC_BTDEV;

//系统安全信息
extern const QString FUNC_PATCH;
extern const QString FUNC_SERVICE;
extern const QString FUNC_PROCESS;
extern const QString FUNC_OTHERPDT;
extern const QString FUNC_SWITHTIME;
extern const QString FUNC_SECSOFT;

//安全隐患信息
extern const QString FUNC_SECPLCY;
extern const QString FUNC_OPENPORT;
extern const QString FUNC_SHARINFO;
extern const QString FUNC_NETSOFT;
extern const QString FUNC_GRPINFO;
extern const QString FUNC_USERINFO;
extern const QString FUNC_DBNFO;
extern const QString FUNC_EVELOG;
extern const QString FUNC_USRAUTH;

//USB设备记录
extern const QString FUNC_USBCOMCHECK;
extern const QString FUNC_USBDEPCHECK;

//上网记录
extern const QString FUNC_NETRECCOMCHECK;
extern const QString FUNC_NETRECDEPCHECK;

//文件检查
extern const QString FUNC_FILECOMCHECK;
extern const QString FUNC_FILEDELCHECK;
extern const QString FUNC_FILEFRGCHECK;

//木马检查
extern const QString FUNC_MALWARECHECK;
extern const QString FUNC_TROJANCHECK;


#endif // GLOBALS_H
