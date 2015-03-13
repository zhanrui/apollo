#ifndef INTERFACEFORTOOL_H
#define INTERFACEFORTOOL_H

#include <QObject>
#include <QString>
#include <QVariantList>

class InterfaceForTool : public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "bmjc.ui")
public:
    explicit InterfaceForTool(QObject* parent = 0);
    ~InterfaceForTool();

signals:
    //基本信息
    void o_os_progress(const int currentcompletion, const QString& currentstatus);
    void o_os_error(const QString& errordescrition);
    void o_os_data(const QVariantList& result);

    void o_cpu_progress(const int currentcompletion, const QString& currentstatus);
    void o_cpu_error(const QString& errordescrition);
    void o_cpu_data(const QVariantList& result);

    void o_bios_progress(const int currentcompletion, const QString& currentstatus);
    void o_bios_error(const QString& errordescrition);
    void o_bios_data(const QVariantList& result);

    void o_mb_progress(const int currentcompletion, const QString& currentstatus);
    void o_mb_error(const QString& errordescrition);
    void o_mb_data(const QVariantList& result);

    void o_mem_progress(const int currentcompletion, const QString& currentstatus);
    void o_mem_error(const QString& errordescrition);
    void o_mem_data(const QVariantList& result);

    void o_gc_progress(const int currentcompletion, const QString& currentstatus);
    void o_gc_error(const QString& errordescrition);
    void o_gc_data(const QVariantList& result);

    //设备连接信息
    void o_hd_progress(const int currentcompletion, const QString& currentstatus);
    void o_hd_error(const QString& errordescrition);
    void o_hd_data(const QVariantList& result);

    void o_vm_progress(const int currentcompletion, const QString& currentstatus);
    void o_vm_error(const QString& errordescrition);
    void o_vm_data(const QVariantList& result);

    void o_nc_progress(const int currentcompletion, const QString& currentstatus);
    void o_nc_error(const QString& errordescrition);
    void o_nc_data(const QVariantList& result);

    void o_na_progress(const int currentcompletion, const QString& currentstatus);
    void o_na_error(const QString& errordescrition);
    void o_na_data(const QVariantList& result);

    void o_print_progress(const int currentcompletion, const QString& currentstatus);
    void o_print_error(const QString& errordescrition);
    void o_print_data(const QVariantList& result);

    void o_bt_progress(const int currentcompletion, const QString& currentstatus);
    void o_bt_error(const QString& errordescrition);
    void o_bt_data(const QVariantList& result);

    //系统安全信息
    void o_patch_progress(const int currentcompletion, const QString& currentstatus);
    void o_patch_error(const QString& errordescrition);
    void o_patch_data(const QVariantList& result);

    void o_service_progress(const int currentcompletion, const QString& currentstatus);
    void o_service_error(const QString& errordescrition);
    void o_service_data(const QVariantList& result);

    void o_process_progress(const int currentcompletion, const QString& currentstatus);
    void o_process_error(const QString& errordescrition);
    void o_process_data(const QVariantList& result);

    void o_otherpdt_progress(const int currentcompletion, const QString& currentstatus);
    void o_otherpdt_error(const QString& errordescrition);
    void o_otherpdt_data(const QVariantList& result);

    void o_swithtime_progress(const int currentcompletion, const QString& currentstatus);
    void o_swithtime_error(const QString& errordescrition);
    void o_swithtime_data(const QVariantList& result);

    void o_secsoft_progress(const int currentcompletion, const QString& currentstatus);
    void o_secsoft_error(const QString& errordescrition);
    void o_secsoft_data(const QVariantList& result);

    //安全隐患信息
    void o_secplcy_progress(const int currentcompletion, const QString& currentstatus);
    void o_secplcy_error(const QString& errordescrition);
    void o_secplcy_data(const QVariantList& result);

    void o_openport_progress(const int currentcompletion, const QString& currentstatus);
    void o_openport_error(const QString& errordescrition);
    void o_openport_data(const QVariantList& result);

    void o_sharinfo_progress(const int currentcompletion, const QString& currentstatus);
    void o_sharinfo_error(const QString& errordescrition);
    void o_sharinfo_data(const QVariantList& result);

    void o_netsoft_progress(const int currentcompletion, const QString& currentstatus);
    void o_netsoft_error(const QString& errordescrition);
    void o_netsoft_data(const QVariantList& result);

    void o_grpinfo_progress(const int currentcompletion, const QString& currentstatus);
    void o_grpinfo_error(const QString& errordescrition);
    void o_grpinfo_data(const QVariantList& result);

    void o_userinfo_progress(const int currentcompletion, const QString& currentstatus);
    void o_userinfo_error(const QString& errordescrition);
    void o_userinfo_data(const QVariantList& result);

    void o_dbinfo_progress(const int currentcompletion, const QString& currentstatus);
    void o_dbinfo_error(const QString& errordescrition);
    void o_dbinfo_data(const QVariantList& result);

    void o_evelog_progress(const int currentcompletion, const QString& currentstatus);
    void o_evelog_error(const QString& errordescrition);
    void o_evelog_data(const QVariantList& result);

    void o_usrauth_progress(const int currentcompletion, const QString& currentstatus);
    void o_usrauth_error(const QString& errordescrition);
    void o_usrauth_data(const QVariantList& result);

    //USB设备记录
    void o_usbcomcheck_progress(const int currentcompletion, const QString& currentstatus);
    void o_usbcomcheck_error(const QString& errordescrition);
    void o_usbcomcheck_data(const QVariantList& result);

    //上网记录
    void o_netreccomcheck_progress(const int currentcompletion, const QString& currentstatus);
    void o_netreccomcheck_error(const QString& errordescrition);
    void o_netreccomcheck_data(const QVariantList& result);

    //文件检查
    void o_filecomcheck_progress(const int currentcompletion, const QString& currentstatus);
    void o_filecomcheck_error(const QString& errordescrition);
    void o_filecomcheck_data(const QVariantList& result);

    //木马检查
    void o_trojancheck_progress(const int currentcompletion, const QString& currentstatus);
    void o_trojancheck_error(const QString& errordescrition);
    void o_trojancheck_data(const QVariantList& result);

    //文件检查
    void f_filecomcheck_progress(const int currentcompletion, const QString& currentstatus);
    void f_filecomcheck_error(const QString& errordescrition);
    void f_filecomcheck_data(const QVariantList& result);

    //木马检查
    void t_threatdoccheck_progress(const int currentcompletion, const QString& currentstatus);
    void t_threatdoccheck_error(const QString& errordescrition);
    void t_threatdoccheck_data(const QVariantList& result);
    void t_netweapon_progress(const int currentcompletion, const QString& currentstatus);
    void t_netweapon_error(const QString& errordescrition);
    void t_netweapon_data(const QVariantList& result);

    //imagecheck
    void i_imagecheck_progress(const int currentcompletion, const QString& currentstatus);
    void i_imagecheck_error(const QString& errordescrition);
    void i_imagecheck_data(const QVariantList& result);

    //netrecdeepcheck
    void n_netrecdeepcheck_progress(const int currentcompletion, const QString& currentstatus);
    void n_netrecdeepcheck_error(const QString& errordescrition);
    void n_netrecdeepcheck_data(const QVariantList& result);

    //usbdeepcheck
    void u_usbdeepcheck_progress(const int currentcompletion, const QString& currentstatus);
    void u_usbdeepcheck_error(const QString& errordescrition);
    void u_usbdeepcheck_data(const QVariantList& result);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //基本信息
    void okc_os_progress(const int currentcompletion, const QString& currentstatus);
    void okc_os_error(const QString& errordescrition);
    void okc_os_data(const QVariantList& result);

    void okc_cpu_progress(const int currentcompletion, const QString& currentstatus);
    void okc_cpu_error(const QString& errordescrition);
    void okc_cpu_data(const QVariantList& result);

    void okc_bios_progress(const int currentcompletion, const QString& currentstatus);
    void okc_bios_error(const QString& errordescrition);
    void okc_bios_data(const QVariantList& result);

    void okc_mb_progress(const int currentcompletion, const QString& currentstatus);
    void okc_mb_error(const QString& errordescrition);
    void okc_mb_data(const QVariantList& result);

    void okc_mem_progress(const int currentcompletion, const QString& currentstatus);
    void okc_mem_error(const QString& errordescrition);
    void okc_mem_data(const QVariantList& result);

    void okc_gc_progress(const int currentcompletion, const QString& currentstatus);
    void okc_gc_error(const QString& errordescrition);
    void okc_gc_data(const QVariantList& result);

    //设备连接信息
    void okc_hd_progress(const int currentcompletion, const QString& currentstatus);
    void okc_hd_error(const QString& errordescrition);
    void okc_hd_data(const QVariantList& result);

    void okc_vm_progress(const int currentcompletion, const QString& currentstatus);
    void okc_vm_error(const QString& errordescrition);
    void okc_vm_data(const QVariantList& result);

    void okc_nc_progress(const int currentcompletion, const QString& currentstatus);
    void okc_nc_error(const QString& errordescrition);
    void okc_nc_data(const QVariantList& result);

    void okc_na_progress(const int currentcompletion, const QString& currentstatus);
    void okc_na_error(const QString& errordescrition);
    void okc_na_data(const QVariantList& result);

    void okc_print_progress(const int currentcompletion, const QString& currentstatus);
    void okc_print_error(const QString& errordescrition);
    void okc_print_data(const QVariantList& result);

    void okc_bt_progress(const int currentcompletion, const QString& currentstatus);
    void okc_bt_error(const QString& errordescrition);
    void okc_bt_data(const QVariantList& result);

    //系统安全信息
    void okc_patch_progress(const int currentcompletion, const QString& currentstatus);
    void okc_patch_error(const QString& errordescrition);
    void okc_patch_data(const QVariantList& result);

    void okc_service_progress(const int currentcompletion, const QString& currentstatus);
    void okc_service_error(const QString& errordescrition);
    void okc_service_data(const QVariantList& result);

    void okc_process_progress(const int currentcompletion, const QString& currentstatus);
    void okc_process_error(const QString& errordescrition);
    void okc_process_data(const QVariantList& result);

    void okc_otherpdt_progress(const int currentcompletion, const QString& currentstatus);
    void okc_otherpdt_error(const QString& errordescrition);
    void okc_otherpdt_data(const QVariantList& result);

    void okc_swithtime_progress(const int currentcompletion, const QString& currentstatus);
    void okc_swithtime_error(const QString& errordescrition);
    void okc_swithtime_data(const QVariantList& result);

    void okc_secsoft_progress(const int currentcompletion, const QString& currentstatus);
    void okc_secsoft_error(const QString& errordescrition);
    void okc_secsoft_data(const QVariantList& result);

    //安全隐患信息
    void okc_secplcy_progress(const int currentcompletion, const QString& currentstatus);
    void okc_secplcy_error(const QString& errordescrition);
    void okc_secplcy_data(const QVariantList& result);

    void okc_openport_progress(const int currentcompletion, const QString& currentstatus);
    void okc_openport_error(const QString& errordescrition);
    void okc_openport_data(const QVariantList& result);

    void okc_sharinfo_progress(const int currentcompletion, const QString& currentstatus);
    void okc_sharinfo_error(const QString& errordescrition);
    void okc_sharinfo_data(const QVariantList& result);

    void okc_netsoft_progress(const int currentcompletion, const QString& currentstatus);
    void okc_netsoft_error(const QString& errordescrition);
    void okc_netsoft_data(const QVariantList& result);

    void okc_grpinfo_progress(const int currentcompletion, const QString& currentstatus);
    void okc_grpinfo_error(const QString& errordescrition);
    void okc_grpinfo_data(const QVariantList& result);

    void okc_userinfo_progress(const int currentcompletion, const QString& currentstatus);
    void okc_userinfo_error(const QString& errordescrition);
    void okc_userinfo_data(const QVariantList& result);

    void okc_dbinfo_progress(const int currentcompletion, const QString& currentstatus);
    void okc_dbinfo_error(const QString& errordescrition);
    void okc_dbinfo_data(const QVariantList& result);

    void okc_evelog_progress(const int currentcompletion, const QString& currentstatus);
    void okc_evelog_error(const QString& errordescrition);
    void okc_evelog_data(const QVariantList& result);

    void okc_usrauth_progress(const int currentcompletion, const QString& currentstatus);
    void okc_usrauth_error(const QString& errordescrition);
    void okc_usrauth_data(const QVariantList& result);

    //USB设备记录
    void okc_usbcomcheck_progress(const int currentcompletion, const QString& currentstatus);
    void okc_usbcomcheck_error(const QString& errordescrition);
    void okc_usbcomcheck_data(const QVariantList& result);

    //上网记录
    void okc_netreccomcheck_progress(const int currentcompletion, const QString& currentstatus);
    void okc_netreccomcheck_error(const QString& errordescrition);
    void okc_netreccomcheck_data(const QVariantList& result);

    //文件检查
    void okc_filecomcheck_progress(const int currentcompletion, const QString& currentstatus);
    void okc_filecomcheck_error(const QString& errordescrition);
    void okc_filecomcheck_data(const QVariantList& result);

    //木马检查
    void okc_threatdoccheck_progress(const int currentcompletion, const QString& currentstatus);
    void okc_threatdoccheck_error(const QString& errordescrition);
    void okc_threatdoccheck_data(const QVariantList& result);
    void okc_netweapon_progress(const int currentcompletion, const QString& currentstatus);
    void okc_netweapon_error(const QString& errordescrition);
    void okc_netweapon_data(const QVariantList& result);

    //imagecheck
    void okc_imagecheck_progress(const int currentcompletion, const QString& currentstatus);
    void okc_imagecheck_error(const QString& errordescrition);
    void okc_imagecheck_data(const QVariantList& result);




public slots:
    void updateFromTool(const QString& messages);
public :
    static int i;
};

#endif // INTERFACEFORTOOL_H
