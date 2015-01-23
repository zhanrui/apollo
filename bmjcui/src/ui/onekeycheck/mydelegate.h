#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QObject>
#include <QItemDelegate>
class MyDelegate  : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MyDelegate(QObject *parent = 0);
    ~MyDelegate();
    // painting
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                     const QRect &rect, const QString &text) const;

};

#endif // MYDELEGATE_H
