#ifndef SHADOWWIDGET_H
#define SHADOWWIDGET_H

#include <QWidget>
#include <QWindow>

class ShadowWidget : public QWidget {
    Q_OBJECT
public:
    explicit ShadowWidget(QWidget* parent = 0);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);



private:
    QPoint m_movePoint; //移动的距离
    bool m_mousePress; //按下鼠标左键
};

#endif // SHADOWWIDGET_H
