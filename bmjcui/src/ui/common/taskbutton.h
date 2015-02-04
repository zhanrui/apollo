#ifndef TASKBUTTON_H
#define TASKBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include "src/common/common.h"

class TaskButton : public QWidget {
    Q_OBJECT
public:
    ~TaskButton();
    explicit TaskButton(const QString& icon, QWidget* parent = 0);
    //explicit TaskButton(const QString& icon, bool isDivision, int num = 3, QWidget* parent = 0);
    //void setOneButtonInfo(const QString& icon, int num = 3);
    //void setDivisionButtonInfo(const QString& icon, int num = 3);
    //void setCursorEnabled(bool enalbed);
    void updateStatus();
    void setTaskStatus(TASKSTAUS taskstatus);
    void hideAll();

public:
    //QLabel* default_defaultstatus;
    //QLabel* default_mouseinstatus;
    //QLabel* default_mousepressstatus;
    QLabel* running_defaultstatus;
    QLabel* running_mouseinstatus;
    QLabel* running_mousepressstatus;
    QLabel* problem_defaultstatus;
    QLabel* problem_mouseinstatus;
    QLabel* problem_mousepressstatus;
    QLabel* noproblem_defaultstatus;
    QLabel* noproblem_mouseinstatus;
    QLabel* noproblem_mousepressstatus;
    QLabel* running_movie;

    QList<QLabel*> labellist;

    TASKSTAUS taskstatus;
    BUTTONSTATUS buttonstatus;
    bool isselected;

signals:
    void buttonClicked();
    void enterSignal();
    void leaveSignal();
public slots:
    void select();
    void unselect();
    void changeToRunning();
    void changeToProblem();
    void changeToNoProblem();
    //void changeToDefault();

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void changeEvent(QEvent* e);
};

#endif // TASKBUTTON_H
