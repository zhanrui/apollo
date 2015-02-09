#include "interfacefortool.h"
#include "src/common/globals.h"
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QVariant>

InterfaceForTool::InterfaceForTool(QObject* parent)
    : QObject(parent)
{
}

InterfaceForTool::~InterfaceForTool() {}

int InterfaceForTool::i=1;
void InterfaceForTool::updateFromTool(const QString& messages)
{

    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(messages.toUtf8(), &json_error);
    if (json_error.error != QJsonParseError::NoError) {
        return;
    }

    QVariantMap result = parse_doucment.toVariant().toMap();
    QString resulttype = result["resulttype"].toString();
    QString scenename = result["scenename"].toString();
    QString functionname = result["functionname"].toString();
    if (scenename.compare(SCENE_ONEKEYCHECK) == 0) {
        if (resulttype.compare(RPT_PROGRESS) == 0) {
            int currentcompletion = result["result"].toMap()["currentcompletion"].toString().toInt();
            QString currentstatus = result["result"].toMap()["currentstatus"].toString();
            if (functionname.compare(FUNC_OSINFO) == 0)
                emit o_os_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_CPUINFO) == 0)
                emit o_cpu_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_BIOSINFO) == 0)
                emit o_bios_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_MBINFO) == 0)
                emit o_mb_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_MEMINFO) == 0)
                emit o_mem_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_GCINFO) == 0)
                emit o_gc_progress(currentcompletion, currentstatus);
            //设备连接信息
            if (functionname.compare(FUNC_HDINFO) == 0)
                emit o_hd_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_VMINFO) == 0)
                emit o_vm_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_NCINFO) == 0)
                emit o_nc_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_NADEV) == 0)
                emit o_na_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_PRIDEV) == 0)
                emit o_print_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_PRIDEV) == 0)
                emit o_bt_progress(currentcompletion, currentstatus);
            //系统安全信息
            if (functionname.compare(FUNC_PATCH) == 0)
                emit o_patch_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_SERVICE) == 0)
                emit o_service_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_PROCESS) == 0)
                emit o_process_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_OTHERPDT) == 0)
                emit o_otherpdt_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_SWITHTIME) == 0)
                emit o_swithtime_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_SECSOFT) == 0)
                emit o_secsoft_progress(currentcompletion, currentstatus);

            //安全隐患信息
            if (functionname.compare(FUNC_SECPLCY) == 0)
                emit o_secplcy_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_OPENPORT) == 0)
                emit o_openport_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_SHARINFO) == 0)
                emit o_sharinfo_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_NETSOFT) == 0)
                emit o_netsoft_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_GRPINFO) == 0)
                emit o_grpinfo_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_USERINFO) == 0)
                emit o_userinfo_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_GRPINFO) == 0)
                emit o_dbinfo_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_EVELOG) == 0)
                emit o_evelog_progress(currentcompletion, currentstatus);
            if (functionname.compare(FUNC_USRAUTH) == 0)
                emit o_usrauth_progress(currentcompletion, currentstatus);

            //USB设备记录
            if (functionname.compare(FUNC_USBCOMCHECK) == 0)
                emit o_usbcomcheck_progress(currentcompletion, currentstatus);

            //上网记录
            if (functionname.compare(FUNC_NETRECCOMCHECK) == 0)
                emit o_netreccomcheck_progress(currentcompletion, currentstatus);

            //文件检查
            if (functionname.compare(FUNC_FILECOMCHECK) == 0)
                emit o_filecomcheck_progress(currentcompletion, currentstatus);

            //木马检查
            if (functionname.compare(FUNC_TROJANCHECK) == 0)
                emit o_trojancheck_progress(currentcompletion, currentstatus);
        }
        if (resulttype.compare(RPT_ERROR) == 0) {
            QString errordescrition = result["result"].toMap()["errordescrition"].toString();
            if (functionname.compare(FUNC_OSINFO) == 0)
                emit o_os_error(errordescrition);
            if (functionname.compare(FUNC_CPUINFO) == 0)
                emit o_cpu_error(errordescrition);
            if (functionname.compare(FUNC_BIOSINFO) == 0)
                emit o_bios_error(errordescrition);
            if (functionname.compare(FUNC_MBINFO) == 0)
                emit o_mb_error(errordescrition);
            if (functionname.compare(FUNC_MEMINFO) == 0)
                emit o_mem_error(errordescrition);
            if (functionname.compare(FUNC_GCINFO) == 0)
                emit o_gc_error(errordescrition);
            //设备连接信息
            if (functionname.compare(FUNC_HDINFO) == 0)
                emit o_hd_error(errordescrition);
            if (functionname.compare(FUNC_VMINFO) == 0)
                emit o_vm_error(errordescrition);
            if (functionname.compare(FUNC_NCINFO) == 0)
                emit o_nc_error(errordescrition);
            if (functionname.compare(FUNC_NADEV) == 0)
                emit o_na_error(errordescrition);
            if (functionname.compare(FUNC_PRIDEV) == 0)
                emit o_print_error(errordescrition);
            if (functionname.compare(FUNC_PRIDEV) == 0)
                emit o_bt_error(errordescrition);
            //系统安全信息
            if (functionname.compare(FUNC_PATCH) == 0)
                emit o_patch_error(errordescrition);
            if (functionname.compare(FUNC_SERVICE) == 0)
                emit o_service_error(errordescrition);
            if (functionname.compare(FUNC_PROCESS) == 0)
                emit o_process_error(errordescrition);
            if (functionname.compare(FUNC_OTHERPDT) == 0)
                emit o_otherpdt_error(errordescrition);
            if (functionname.compare(FUNC_SWITHTIME) == 0)
                emit o_swithtime_error(errordescrition);
            if (functionname.compare(FUNC_SECSOFT) == 0)
                emit o_secsoft_error(errordescrition);

            //安全隐患信息
            if (functionname.compare(FUNC_SECPLCY) == 0)
                emit o_secplcy_error(errordescrition);
            if (functionname.compare(FUNC_OPENPORT) == 0)
                emit o_openport_error(errordescrition);
            if (functionname.compare(FUNC_SHARINFO) == 0)
                emit o_sharinfo_error(errordescrition);
            if (functionname.compare(FUNC_NETSOFT) == 0)
                emit o_netsoft_error(errordescrition);
            if (functionname.compare(FUNC_GRPINFO) == 0)
                emit o_grpinfo_error(errordescrition);
            if (functionname.compare(FUNC_USERINFO) == 0)
                emit o_userinfo_error(errordescrition);
            if (functionname.compare(FUNC_GRPINFO) == 0)
                emit o_dbinfo_error(errordescrition);
            if (functionname.compare(FUNC_EVELOG) == 0)
                emit o_evelog_error(errordescrition);
            if (functionname.compare(FUNC_USRAUTH) == 0)
                emit o_usrauth_error(errordescrition);

            //USB设备记录
            if (functionname.compare(FUNC_USBCOMCHECK) == 0)
                emit o_usbcomcheck_error(errordescrition);

            //上网记录
            if (functionname.compare(FUNC_NETRECCOMCHECK) == 0)
                emit o_netreccomcheck_error(errordescrition);

            //文件检查
            if (functionname.compare(FUNC_FILECOMCHECK) == 0)
                emit o_filecomcheck_error(errordescrition);

            //木马检查
            if (functionname.compare(FUNC_TROJANCHECK) == 0)
                emit o_trojancheck_error(errordescrition);
        }
        if (resulttype.compare(RPT_DATA) == 0) {

            QList<QVariant> data = result["result"].toList();
           // i=i+data.size();
           //qDebug()<<i<<" "<<functionname;
            if (functionname.compare(FUNC_OSINFO) == 0)
                emit o_os_data(data);
            if (functionname.compare(FUNC_CPUINFO) == 0)
                emit o_cpu_data(data);
            if (functionname.compare(FUNC_BIOSINFO) == 0)
                emit o_bios_data(data);
            if (functionname.compare(FUNC_MBINFO) == 0)
                emit o_mb_data(data);
            if (functionname.compare(FUNC_MEMINFO) == 0)
                emit o_mem_data(data);
            if (functionname.compare(FUNC_GCINFO) == 0)
                emit o_gc_data(data);
            //设备连接信息
            if (functionname.compare(FUNC_HDINFO) == 0)
                emit o_hd_data(data);
            if (functionname.compare(FUNC_VMINFO) == 0)
                emit o_vm_data(data);
            if (functionname.compare(FUNC_NCINFO) == 0)
                emit o_nc_data(data);
            if (functionname.compare(FUNC_NADEV) == 0)
                emit o_na_data(data);
            if (functionname.compare(FUNC_PRIDEV) == 0)
                emit o_print_data(data);
            if (functionname.compare(FUNC_PRIDEV) == 0)
                emit o_bt_data(data);
            //系统安全信息
            if (functionname.compare(FUNC_PATCH) == 0)
                emit o_patch_data(data);
            if (functionname.compare(FUNC_SERVICE) == 0)
                emit o_service_data(data);
            if (functionname.compare(FUNC_PROCESS) == 0)
                emit o_process_data(data);
            if (functionname.compare(FUNC_OTHERPDT) == 0)
                emit o_otherpdt_data(data);
            if (functionname.compare(FUNC_SWITHTIME) == 0)
                emit o_swithtime_data(data);
            if (functionname.compare(FUNC_SECSOFT) == 0)
                emit o_secsoft_data(data);

            //安全隐患信息
            if (functionname.compare(FUNC_SECPLCY) == 0)
                emit o_secplcy_data(data);
            if (functionname.compare(FUNC_OPENPORT) == 0)
                emit o_openport_data(data);
            if (functionname.compare(FUNC_SHARINFO) == 0)
                emit o_sharinfo_data(data);
            if (functionname.compare(FUNC_NETSOFT) == 0)
                emit o_netsoft_data(data);
            if (functionname.compare(FUNC_GRPINFO) == 0)
                emit o_grpinfo_data(data);
            if (functionname.compare(FUNC_USERINFO) == 0)
                emit o_userinfo_data(data);
            if (functionname.compare(FUNC_GRPINFO) == 0)
                emit o_dbinfo_data(data);
            if (functionname.compare(FUNC_EVELOG) == 0)
                emit o_evelog_data(data);
            if (functionname.compare(FUNC_USRAUTH) == 0)
                emit o_usrauth_data(data);

            //USB设备记录
            if (functionname.compare(FUNC_USBCOMCHECK) == 0)
                emit o_usbcomcheck_data(data);

            //上网记录
            if (functionname.compare(FUNC_NETRECCOMCHECK) == 0)
                emit o_netreccomcheck_data(data);

            //文件检查
            if (functionname.compare(FUNC_FILECOMCHECK) == 0)
                emit o_filecomcheck_data(data);

            //木马检查
            if (functionname.compare(FUNC_TROJANCHECK) == 0)
                emit o_trojancheck_data(data);
        }
    }



}
