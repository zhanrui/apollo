#ifndef MODELUTIL_H
#define MODELUTIL_H
#include <QVariantList>
class QStandardItemModel;
class QTableView;

class ModelUtil {
public:
    ModelUtil();
    ~ModelUtil();
    //Basic Info
    static void initCPUModel(QStandardItemModel* model, QTableView* view);
    static void addCpuInfo(QStandardItemModel* model, const QVariantList& result);
    static void initOSModel(QStandardItemModel* model, QTableView* view);
    static void addOsInfo(QStandardItemModel* model, const QVariantList& result);
    static void initBIOSModel(QStandardItemModel* model, QTableView* view);
    static void addBiosInfo(QStandardItemModel* model, const QVariantList& result);
    static void initMainBoardModel(QStandardItemModel* model, QTableView* view);
    static void addMainBoardInfo(QStandardItemModel* model, const QVariantList& result);
    static void initMemoryModel(QStandardItemModel* model, QTableView* view);
    static void addMemoryInfo(QStandardItemModel* model, const QVariantList& result);
    static void initVideoCardModel(QStandardItemModel* model, QTableView* view);
    static void addVideoCardInfo(QStandardItemModel* model, const QVariantList& result);
    //Device Connection Info
    static void initHardDiskModel(QStandardItemModel* model, QTableView* view);
    static void addHardDiskInfo(QStandardItemModel* model, const QVariantList& result);
    static void initVMModel(QStandardItemModel* model, QTableView* view);
    static void addVMInfo(QStandardItemModel* model, const QVariantList& result);
    static void initNetConfigModel(QStandardItemModel* model, QTableView* view);
    static void addNetConfig(QStandardItemModel* model, const QVariantList& result);
    static void initNetworkAdapterModel(QStandardItemModel* model, QTableView* view);
    static void addNetworkAdapterDevice(QStandardItemModel* model, const QVariantList& result);
    static void initPrinterModel(QStandardItemModel* model, QTableView* view);
    static void addPrinterDevice(QStandardItemModel* model, const QVariantList& result);
    static void initBlueToothModel(QStandardItemModel* model, QTableView* view);
    static void addBlueToothDevice(QStandardItemModel* model, const QVariantList& result);

    //System Security Info
    static void initUninstallPatchModel(QStandardItemModel* model, QTableView* view);
    static void addUninstallPatch(QStandardItemModel* model, const QVariantList& result);
    static void initSystemServiceModel(QStandardItemModel* model, QTableView* view);
    static void addSystemService(QStandardItemModel* model, const QVariantList& result);
    static void initSystemProcessModel(QStandardItemModel* model, QTableView* view);
    static void addSystemProcess(QStandardItemModel* model, const QVariantList& result);
    static void initExternalConnectionModel(QStandardItemModel* model, QTableView* view);
    static void addExternalConnection(QStandardItemModel* model, const QVariantList& result);
    static void initStartShutdownTimeModel(QStandardItemModel* model, QTableView* view);
    static void addStartShutdownTime(QStandardItemModel* model, const QVariantList& result);
    static void initSecuritySoftwareModel(QStandardItemModel* model, QTableView* view);
    static void addSecuritySoftware(QStandardItemModel* model, const QVariantList& result);
    //System Security Info
    static void initSecurityStrategyModel(QStandardItemModel* model, QTableView* view);
    static void initOpenPortModel(QStandardItemModel* model, QTableView* view);
    static void initSharedInfoModel(QStandardItemModel* model, QTableView* view);
    static void initInternetToolModel(QStandardItemModel* model, QTableView* view);
    static void initUserGroupInfoModel(QStandardItemModel* model, QTableView* view);
    static void initUserInfoModel(QStandardItemModel* model, QTableView* view);
    static void initDataBaseInfoModel(QStandardItemModel* model, QTableView* view);
    static void initEventLogModel(QStandardItemModel* model, QTableView* view);
    static void initAuthenticatioInfonModel(QStandardItemModel* model, QTableView* view);
    //System Usb Check Info
    static void initUsbCheckModel(QStandardItemModel* model, QTableView* view);
    //System Usb Check Info
    static void initIntenetHistoryCheckModel(QStandardItemModel* model, QTableView* view);
    static void addIntenetHistoryCheckModel(QStandardItemModel* model, const QVariantList& result);
    //File Check Info
    static void initFileCheckModel(QStandardItemModel* model, QTableView* view);
    static void initFileFragmentCheckModel(QStandardItemModel* model, QTableView* view);
    //Virus Check Info
    static void initMalwareCheckModel(QStandardItemModel* model, QTableView* view);
    static void initVirusCheckModel(QStandardItemModel* model, QTableView* view);
};

#endif // MODELUTIL_H
