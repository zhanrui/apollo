#ifndef MODELUTIL_H
#define MODELUTIL_H

class QStandardItemModel;

class ModelUtil {
public:
    ModelUtil();
    ~ModelUtil();
    //Basic Info
    static void initCPUModel(QStandardItemModel* model);
    static void initOSModel(QStandardItemModel* model);
    static void initBIOSModel(QStandardItemModel* model);
    static void initMainBoardModel(QStandardItemModel* model);
    static void initMemoryModel(QStandardItemModel* model);
    static void initVideoCardModel(QStandardItemModel* model);
    //Device Connection Info
    static void initHardDiskModel(QStandardItemModel* model);
    static void initVMModel(QStandardItemModel* model);
    static void initNetConfigModel(QStandardItemModel* model);
    static void initNetworkAdapterModel(QStandardItemModel* model);
    static void initPrinterModel(QStandardItemModel* model);
    static void initBlueToothModel(QStandardItemModel* model);
    //System Security Info
    static void initUninstallPatchModel(QStandardItemModel* model);
    static void initSystemServiceModel(QStandardItemModel* model);
    static void initSystemProcessModel(QStandardItemModel* model);
    static void initExternalConnectionModel(QStandardItemModel* model);
    static void initStartShutdownTimeModel(QStandardItemModel* model);
    static void initSecuritySoftwareModel(QStandardItemModel* model);
    //System Security Info
    static void initSecurityStrategyModel(QStandardItemModel* model);
    static void initOpenPortModel(QStandardItemModel* model);
    static void initSharedInfoModel(QStandardItemModel* model);
    static void initInternetToolModel(QStandardItemModel* model);
    static void initUserGroupInfoModel(QStandardItemModel* model);
    static void initUserInfoModel(QStandardItemModel* model);
    static void initDataBaseInfoModel(QStandardItemModel* model);
    static void initEventLogModel(QStandardItemModel* model);
    static void initAuthenticatioInfonModel(QStandardItemModel* model);
    //System Usb Check Info
    static void initUsbCheckModel(QStandardItemModel* model);
    //System Usb Check Info
    static void initIntenetHistoryCheckModel(QStandardItemModel* model);
    //File Check Info
    static void initFileCheckModel(QStandardItemModel* model);
    static void initFileFragmentCheckModel(QStandardItemModel* model);
    //Virus Check Info
    static void initMalwareCheckModel(QStandardItemModel* model);
    static void initVirusCheckModel(QStandardItemModel* model);

};

#endif // MODELUTIL_H
