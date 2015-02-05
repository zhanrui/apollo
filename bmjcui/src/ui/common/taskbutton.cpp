#include "taskbutton.h"
#include "src/common/common.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QMovie>

TaskButton::TaskButton(const QString& icon, QWidget* parent)
    : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    //    QPixmap pixmap_default(icon + "_default");
    //    default_defaultstatus = new QLabel(this);
    //    default_defaultstatus->setPixmap(pixmap_default.copy(0 * (pixmap_default.width() / 3), 0, pixmap_default.width() / 3, pixmap_default.height()));
    //    default_defaultstatus->show();
    //    default_mouseinstatus = new QLabel(this);
    //    default_mouseinstatus->setPixmap(pixmap_default.copy(1 * (pixmap_default.width() / 3), 0, pixmap_default.width() / 3, pixmap_default.height()));
    //    default_mouseinstatus->hide();
    //    default_mousepressstatus = new QLabel(this);
    //    default_mousepressstatus->setPixmap(pixmap_default.copy(2 * (pixmap_default.width() / 3), 0, pixmap_default.width() / 3, pixmap_default.height()));
    //    default_mousepressstatus->hide();

    QPixmap pixmap_running(icon + "_running");
    running_defaultstatus = new QLabel(this);
    running_defaultstatus->setPixmap(pixmap_running.copy(0 * (pixmap_running.width() / 3), 0, pixmap_running.width() / 3, pixmap_running.height()));
    running_defaultstatus->hide();
    running_mouseinstatus = new QLabel(this);
    running_mouseinstatus->setPixmap(pixmap_running.copy(1 * (pixmap_running.width() / 3), 0, pixmap_running.width() / 3, pixmap_running.height()));
    running_mouseinstatus->hide();
    running_mousepressstatus = new QLabel(this);
    running_mousepressstatus->setPixmap(pixmap_running.copy(2 * (pixmap_running.width() / 3), 0, pixmap_running.width() / 3, pixmap_running.height()));
    running_mousepressstatus->hide();

    QMovie* movie = new QMovie(":image/detailreport/running_movie");
    movie->setParent(this);
    running_movie = new QLabel(this);
    running_movie->setMovie(movie);
    running_movie->move((pixmap_running.width() / 3) / 2 - 40, 50);
    running_movie->hide();

    QPixmap pixmap_noproblem(icon + "_noproblem");
    noproblem_defaultstatus = new QLabel(this);
    noproblem_defaultstatus->setPixmap(pixmap_noproblem.copy(0 * (pixmap_noproblem.width() / 3), 0, pixmap_noproblem.width() / 3, pixmap_noproblem.height()));
    noproblem_defaultstatus->hide();
    noproblem_mouseinstatus = new QLabel(this);
    noproblem_mouseinstatus->setPixmap(pixmap_noproblem.copy(1 * (pixmap_noproblem.width() / 3), 0, pixmap_noproblem.width() / 3, pixmap_noproblem.height()));
    noproblem_mouseinstatus->hide();
    noproblem_mousepressstatus = new QLabel(this);
    noproblem_mousepressstatus->setPixmap(pixmap_noproblem.copy(2 * (pixmap_noproblem.width() / 3), 0, pixmap_noproblem.width() / 3, pixmap_noproblem.height()));
    noproblem_mousepressstatus->hide();

    QPixmap pixmap_problem(icon + "_problem");
    problem_defaultstatus = new QLabel(this);
    problem_defaultstatus->setPixmap(pixmap_problem.copy(0 * (pixmap_problem.width() / 3), 0, pixmap_problem.width() / 3, pixmap_problem.height()));
    problem_defaultstatus->hide();
    problem_mouseinstatus = new QLabel(this);
    problem_mouseinstatus->setPixmap(pixmap_problem.copy(1 * (pixmap_problem.width() / 3), 0, pixmap_problem.width() / 3, pixmap_problem.height()));
    problem_mouseinstatus->hide();
    problem_mousepressstatus = new QLabel(this);
    problem_mousepressstatus->setPixmap(pixmap_problem.copy(2 * (pixmap_problem.width() / 3), 0, pixmap_problem.width() / 3, pixmap_problem.height()));
    problem_mousepressstatus->hide();

    labellist = QList<QLabel*>();
    labellist << running_defaultstatus << running_mouseinstatus << running_mousepressstatus
              << problem_defaultstatus << problem_mouseinstatus << problem_mousepressstatus
              << noproblem_defaultstatus << noproblem_mouseinstatus << noproblem_mousepressstatus
              << running_movie;

    taskstatus = TASK_RUNNING;
    buttonstatus = BUTTON_LEAVE;
    isselected = false;
    QWidget* cover = new QWidget(this);
    cover->setAttribute(Qt::WA_TranslucentBackground);
    cover->setFixedSize(pixmap_running.width() / 3, pixmap_running.height());
    cover->show();
    updateStatus();
}

TaskButton::~TaskButton()
{
}

void TaskButton::hideAll()
{
    for (QLabel* label : labellist) {
        label->hide();
    }
    running_movie->movie()->stop();
}

void TaskButton::setTaskStatus(TASKSTAUS taskstatus)
{
    this->taskstatus = taskstatus;
    updateStatus();
}

void TaskButton::updateStatus()
{
    hideAll();
    if (this->isEnabled()) {
        //        if (taskstatus == TASK_DEFAULT) {
        //            if (isselected) {
        //                default_mousepressstatus->show();
        //            } else if (buttonstatus == BUTTON_ENTER) {
        //                default_mouseinstatus->show();
        //            } else if (buttonstatus == BUTTON_LEAVE) {
        //                default_defaultstatus->show();
        //            } else if (buttonstatus == BUTTON_PRESSED) {
        //                default_mousepressstatus->show();
        //            }
        //        }

        if (taskstatus == TASK_RUNNING) {
            if (isselected) {
                running_mousepressstatus->show();
            } else if (buttonstatus == BUTTON_ENTER) {               
                running_mouseinstatus->show();
            } else if (buttonstatus == BUTTON_LEAVE) {               
                running_defaultstatus->show();
            } else if (buttonstatus == BUTTON_PRESSED) {
                running_mousepressstatus->show();
            }
            running_movie->show();
            running_movie->movie()->start();
        }

        if (taskstatus == TASK_PROBLEM) {
            if (isselected) {
                problem_mousepressstatus->show();
            } else if (buttonstatus == BUTTON_ENTER) {
                problem_mouseinstatus->show();
            } else if (buttonstatus == BUTTON_LEAVE) {
                problem_defaultstatus->show();
            } else if (buttonstatus == BUTTON_PRESSED) {
                problem_mousepressstatus->show();
            }
        }

        if (taskstatus == TASK_NOPROBLEM) {
            if (isselected) {
                noproblem_mousepressstatus->show();
            } else if (buttonstatus == BUTTON_ENTER) {
                noproblem_mouseinstatus->show();
            } else if (buttonstatus == BUTTON_LEAVE) {
                noproblem_defaultstatus->show();
            } else if (buttonstatus == BUTTON_PRESSED) {
                noproblem_mousepressstatus->show();
            }
        } else {
            running_defaultstatus->show();
        }
    }
}
void TaskButton::enterEvent(QEvent* event)
{
    if (buttonstatus != BUTTON_ENTER) {
    buttonstatus = BUTTON_ENTER;
    updateStatus();
    emit enterSignal();
    }
}

void TaskButton::leaveEvent(QEvent*)
{
    if (buttonstatus != BUTTON_LEAVE) {
        buttonstatus = BUTTON_LEAVE;
        updateStatus();
    }
    emit leaveSignal();
}

void TaskButton::mousePressEvent(QMouseEvent* e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }
    buttonstatus = BUTTON_PRESSED;
    updateStatus();
}

void TaskButton::mouseReleaseEvent(QMouseEvent* e)
{

    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }

    if (rect().contains(e->pos())) {
        if (this->isEnabled()) {
            //qDebug()<<"this  isEnabled";
            emit buttonClicked();
        }

        buttonstatus = BUTTON_ENTER;
        updateStatus();
        e->accept();
    } else {
        buttonstatus = BUTTON_LEAVE;
        updateStatus();
        e->ignore();
    }
}

void TaskButton::changeEvent(QEvent* e)
{
    // if (e->type() == QEvent::EnabledChange)
    //    if (!this->isEnabled() && (m_num == 4))
    //         setButtonStatus(BUTTON_DISABLE);
}

void TaskButton::select()
{
    isselected = true;
    updateStatus();
}
void TaskButton::unselect()
{
    isselected = false;
    updateStatus();
}

void TaskButton::changeToRunning()
{
    setTaskStatus(TASK_RUNNING);
}
void TaskButton::changeToProblem()
{
    setTaskStatus(TASK_PROBLEM);
}
void TaskButton::changeToNoProblem()
{
    setTaskStatus(TASK_NOPROBLEM);
}
//void TaskButton::changeToDefault()
//{
//    setTaskStatus(TASK_DEFAULT);
//}
