#ifndef TROJANCHECKRPT_H
#define TROJANCHECKRPT_H

#include <src/ui/base/basestylewidget.h>
#include <QWidget>

#include <QList>
#include <QLabel>
#include <QString>
#include <src/ui/detailreport/basereport.h>
class TaskButton;
class StaticButton;
class QTableView;
class QStandardItemModel;

class TrojanCheckRpt : public BaseStyleWidget, public BaseReport {
    Q_OBJECT
public:
    explicit TrojanCheckRpt(QWidget* parent, const QString& title);
    ~TrojanCheckRpt();
    void initUI(const QString& title);
    void initModel();
    void initConnection();
    void initViewDetail(QTableView* view);

public slots:

    void addNetworkWeapon(const QVariantList& result);
    void addThreatDocument(const QVariantList& result);

    void selectNetworkWeapon();
    void selectThreatDocument();

public:
    TaskButton* networkWeaponBtn;
    TaskButton* threatDocumentBtn;

    QStandardItemModel* networkWeaponMod;
    QStandardItemModel* threatDocumentMod;

    QTableView* networkWeaponView;
    QTableView* threatDocumentView;
};

#endif // TROJANCHECKRPT_H
