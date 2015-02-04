/****************************************************************************
**
* This Class is for call the Tools ( for example : check the system info ,
* check file ,check Virus,
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

#ifndef TOOLUTIL_H
#define TOOLUTIL_H
#include <QObject>
#include <QString>
#include <QJsonObject>

class QDBusInterface;
class ToolUtil : public QObject {
    Q_OBJECT
public:
    explicit ToolUtil(QObject* parent = 0);
    ~ToolUtil();
public slots:
    void stopTask(const QString& scenename, const QString& taskname);
    void startTask(const QString& scenename, const QString& taskname, const QMap<QString, QString>& parameters);
    void stopAll();
    void sendMessage(const QJsonObject& json);

public:
    QDBusInterface* iface;
};

#endif // TOOLUTIL_H
