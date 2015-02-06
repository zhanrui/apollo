#include "shadowwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>
#include <QStyleOption>
#include <QPainter>

ShadowWidget::ShadowWidget(QWidget* parent)
    : QWidget(parent)
    , m_mousePress(false)
{
   //setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //Qt::WindowFlags  flags = Qt::CustomizeWindowHint | Qt::FramelessWindowHint ;

            //| Qt::WindowMinimizeButtonHint ;
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint);

    //this->setObjectName("basewidget");
    // setAttribute(Qt::WA_TranslucentBackground);
}




void ShadowWidget::mousePressEvent(QMouseEvent* event)
{
    //只能是鼠标左键移动和改变大小
    if (event->button() == Qt::LeftButton)
        m_mousePress = true;
    //窗口移动距离
    m_movePoint = event->globalPos() - pos();
}

void ShadowWidget::mouseReleaseEvent(QMouseEvent*)
{
    m_mousePress = false;
}

void ShadowWidget::mouseMoveEvent(QMouseEvent* event)
{
    //移动窗口
    if (m_mousePress) {
        QPoint movePpos = event->globalPos();
        move(movePpos - m_movePoint);
    }
}



