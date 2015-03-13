#include "checkbutton.h"

#include "src/common/common.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QMovie>

CheckButton::CheckButton(const QString& icon, QWidget* parent)
    : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    QPixmap pixmap_unchecked(icon + "_unchecked");
    unchecked_defaultstatus = new QLabel(this);
    unchecked_defaultstatus->setPixmap(pixmap_unchecked.copy(0 * (pixmap_unchecked.width() / 3), 0, pixmap_unchecked.width() / 3, pixmap_unchecked.height()));
    unchecked_defaultstatus->hide();
    unchecked_mouseinstatus = new QLabel(this);
    unchecked_mouseinstatus->setPixmap(pixmap_unchecked.copy(1 * (pixmap_unchecked.width() / 3), 0, pixmap_unchecked.width() / 3, pixmap_unchecked.height()));
    unchecked_mouseinstatus->hide();
    unchecked_mousepressstatus = new QLabel(this);
    unchecked_mousepressstatus->setPixmap(pixmap_unchecked.copy(2 * (pixmap_unchecked.width() / 3), 0, pixmap_unchecked.width() / 3, pixmap_unchecked.height()));
    unchecked_mousepressstatus->hide();

    QPixmap pixmap_checked(icon + "_checked");
    checked_defaultstatus = new QLabel(this);
    checked_defaultstatus->setPixmap(pixmap_checked.copy(0 * (pixmap_checked.width() / 3), 0, pixmap_checked.width() / 3, pixmap_checked.height()));
    checked_defaultstatus->hide();
    checked_mouseinstatus = new QLabel(this);
    checked_mouseinstatus->setPixmap(pixmap_checked.copy(1 * (pixmap_checked.width() / 3), 0, pixmap_checked.width() / 3, pixmap_checked.height()));
    checked_mouseinstatus->hide();
    checked_mousepressstatus = new QLabel(this);
    checked_mousepressstatus->setPixmap(pixmap_checked.copy(2 * (pixmap_checked.width() / 3), 0, pixmap_checked.width() / 3, pixmap_checked.height()));
    checked_mousepressstatus->hide();



    labellist = QList<QLabel*>();
    labellist << unchecked_defaultstatus << unchecked_mouseinstatus << unchecked_mousepressstatus
              << checked_defaultstatus << checked_mouseinstatus << checked_mousepressstatus
     ;

    checkbtnstatus = DISABLED;
    buttonstatus = BUTTON_LEAVE;
    isselected = false;
    QWidget* cover = new QWidget(this);
    cover->setAttribute(Qt::WA_TranslucentBackground);
    cover->setFixedSize(pixmap_unchecked.width() / 3, pixmap_unchecked.height());
    cover->show();
    updateStatus();
}

CheckButton::~CheckButton()
{
}

void CheckButton::hideAll()
{
    for (QLabel* label : labellist) {
        label->hide();
    }

}

void CheckButton::setCheckBtnStatus(CHECKBUTTONSTAUS status)
{
    this->checkbtnstatus = status;
    updateStatus();
}

void CheckButton::updateStatus()
{
    hideAll();
    if (this->isEnabled()) {


        if (checkbtnstatus == DISABLED) {
            if (isselected) {
                unchecked_mousepressstatus->show();
            } else if (buttonstatus == BUTTON_ENTER) {
               unchecked_mouseinstatus->show();
            } else if (buttonstatus == BUTTON_LEAVE) {
                unchecked_defaultstatus->show();
            } else if (buttonstatus == BUTTON_PRESSED) {
                unchecked_mousepressstatus->show();
            }

        }

        if (checkbtnstatus == ENABLED) {
            if (isselected) {
                checked_mousepressstatus->show();
            } else if (buttonstatus == BUTTON_ENTER) {
                checked_mouseinstatus->show();
            } else if (buttonstatus == BUTTON_LEAVE) {
                checked_defaultstatus->show();
            } else if (buttonstatus == BUTTON_PRESSED) {
                checked_mousepressstatus->show();
            }
        }

    }
}
void CheckButton::enterEvent(QEvent* event)
{
    if (buttonstatus != BUTTON_ENTER) {
        buttonstatus = BUTTON_ENTER;
        updateStatus();
        emit enterSignal();
    }
}

void CheckButton::leaveEvent(QEvent*)
{
    if (buttonstatus != BUTTON_LEAVE) {
        buttonstatus = BUTTON_LEAVE;
        updateStatus();
    }
    emit leaveSignal();
}

void CheckButton::mousePressEvent(QMouseEvent* e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }
    buttonstatus = BUTTON_PRESSED;
    updateStatus();
}

void CheckButton::mouseReleaseEvent(QMouseEvent* e)
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

void CheckButton::changeEvent(QEvent* e)
{
    // if (e->type() == QEvent::EnabledChange)
    //    if (!this->isEnabled() && (m_num == 4))
    //         setButtonStatus(BUTTON_DISABLE);
}

void CheckButton::select()
{
    isselected = true;
    updateStatus();
}
void CheckButton::unselect()
{
    isselected = false;
    updateStatus();
}

void CheckButton::changeToChecked()
{
    setCheckBtnStatus(ENABLED);

}
void CheckButton::changeToUnChecked()
{
    setCheckBtnStatus(DISABLED);

}
