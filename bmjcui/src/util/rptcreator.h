#ifndef RPTCREATOR_H
#define RPTCREATOR_H

#include <QObject>
class QStandardItemModel;
class MainWindow;
class RptCreator : public QObject
{
    Q_OBJECT
public:
    explicit RptCreator(QObject *parent ,MainWindow * mainWindow);
    ~RptCreator();
    //const QString getTableString(QStandardItemModel* model);

signals:
     void createCompleteSig(const int completerate, const QString& status);

public slots:
    void createReport(const QString & filename , const QString & html);


public:
//    QStandardItemModel* osInfoMod;
//    QStandardItemModel* cpuInfoMod;
//    QStandardItemModel* biosInfoMod;
//    QStandardItemModel* motherBoardInfoMod;
//    QStandardItemModel* memoryInfoMod;
//    QStandardItemModel* graphicsCardInfoMod;

//    QStandardItemModel* hardDiskInfoMod;
//    QStandardItemModel* virtualMachineInfoMod;
//    QStandardItemModel* netConfigMod;
//    QStandardItemModel* adapterDeviceMod;
//    QStandardItemModel* printDeviceMod;
//    QStandardItemModel* blueToothDeviceMod;

//    QStandardItemModel* fileRoutineCheckMod;

//    QStandardItemModel* imageCheckMod;

//    QStandardItemModel* netRecordCommonInfoMod;
//    QStandardItemModel* netRecordDeepInfoMod;

//    QStandardItemModel* securityPolicyMod;
//    QStandardItemModel* openPortMod;
//    QStandardItemModel* sharingInfoMod;
//    QStandardItemModel* networkSoftwareMod;
//    QStandardItemModel* groupInfoMod;
//    QStandardItemModel* userInfoMod;
//    QStandardItemModel* databaseInfoMod;
//    QStandardItemModel* eventLogMod;
//    QStandardItemModel* userAuthenticationMod;

//    QStandardItemModel* patchNotInstalledMod;
//    QStandardItemModel* systemServiceMod;
//    QStandardItemModel* systemProcessMod;
//    QStandardItemModel* evenProductMod;
//    QStandardItemModel* timeSwitchMachineMod;
//    QStandardItemModel* securitySoftwareMod;

//    QStandardItemModel* networkWeaponMod;
//    QStandardItemModel* threatDocumentMod;

//    QStandardItemModel* usbCommonInfoMod;
//    QStandardItemModel* usbDeepInfoMod;

};

#endif // RPTCREATOR_H
