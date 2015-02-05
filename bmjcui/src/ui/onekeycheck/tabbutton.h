#ifndef TABBUTTON_H
#define TABBUTTON_H
#include "src/ui/base/staticbutton.h"
#include "src/common/common.h"
class QString;
class TabButton : public StaticButton {
    Q_OBJECT
public:
    explicit TabButton(const QString& icon, QWidget* parent = 0);
    ~TabButton();
public slots:
    void changeToRunning();
    void changeToProblem();
    void changeToNoProblem();
    void changeToDefault();
public:
    QString iconname;
    TASKSTAUS taskstaus;
};

#endif // TABBUTTON_H
