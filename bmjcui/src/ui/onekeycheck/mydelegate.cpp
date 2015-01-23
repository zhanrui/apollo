#include "mydelegate.h"
#include <QItemDelegate>

#include <QAbstractItemModel>

#include <QBrush>
#include <QPainter>
#include <QPalette>
#include <QModelIndex>

MyDelegate::MyDelegate(QObject* parent)
    : QItemDelegate(parent)
{
}

MyDelegate::~MyDelegate()
{
}

void MyDelegate::drawDisplay(QPainter* painter, const QStyleOptionViewItem& option,
                             const QRect& rect, const QString& text) const
{
    QItemDelegate::drawDisplay(painter, option, rect, text);
}
