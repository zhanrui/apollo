#ifndef STATUSBUTTON_H
#define STATUSBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include "src/common/common.h"

class CheckButton : public QWidget {
    Q_OBJECT
public:
    ~CheckButton();
    explicit CheckButton(const QString& icon, QWidget* parent = 0);
    void updateStatus();
    void hideAll();

public:
    //QLabel* default_defaultstatus;
    //QLabel* default_mouseinstatus;
    //QLabel* default_mousepressstatus;
    QLabel* unchecked_defaultstatus;
    QLabel* unchecked_mouseinstatus;
    QLabel* unchecked_mousepressstatus;
    QLabel* checked_defaultstatus;
    QLabel* checked_mouseinstatus;
    QLabel* checked_mousepressstatus;


    QList<QLabel*> labellist;

    CHECKBUTTONSTAUS checkbtnstatus;
    BUTTONSTATUS buttonstatus;
    bool isselected;

signals:
    void buttonClicked();
    void enterSignal();
    void leaveSignal();
public slots:
    void select();
    void unselect();
    void setCheckBtnStatus(CHECKBUTTONSTAUS status);
    void changeToChecked();
    void changeToUnChecked();

    //void changeToNoProblem();
    //void changeToDefault();

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void changeEvent(QEvent* e);
};


#endif // STATUSBUTTON_H
