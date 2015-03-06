#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
class MyDelegate  : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MyDelegate(QObject *parent = 0);
    ~MyDelegate();
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const;
    // painting


};

#endif // MYDELEGATE_H
