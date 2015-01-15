#include "buttonlabel.h"
#include <QCursor>
#include <QMouseEvent>
#include <QDebug>

ButtonLabel::ButtonLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setObjectName("buttonlabel");
}

void ButtonLabel::setMouseClicked(bool isClicked)
{
    if(isClicked)
    {
       this->setStyleSheet("color:black;font: bold;");
    }else
    {
        this->setStyleSheet("color:blue;");
    }
}

void ButtonLabel::setLabelText(const QString text)
{
    this->setText(text);
}

void ButtonLabel::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }

}

void ButtonLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }
    if(rect().contains(e->pos()))
    {
        emit labelClicked();
        e->accept();
    }else{
        e->ignore();
    }
}

void ButtonLabel::enterEvent(QEvent *)
{
    m_preCursor = cursor();
    setCursor(Qt::ArrowCursor);
   // QFont font = this->font();
    //font.setUnderline(true);
    //font.setBold(true);
    this->setStyleSheet("QLabel { color : blue; }");
    qDebug()<<"hello";
   // this->setStyleSheet("font-color:red");
    this->update();
    emit enterSignal();
}

void ButtonLabel::leaveEvent(QEvent *)
{
    setCursor(m_preCursor);
    QFont font = this->font();
    font.setUnderline(false);
    emit leaveSignal();
}
