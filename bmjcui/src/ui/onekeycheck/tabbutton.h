#ifndef TABBUTTON_H
#define TABBUTTON_H
#include "src/ui/base/staticbutton.h"
class QString;
class TabButton : public StaticButton {
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
};

#endif // TABBUTTON_H
