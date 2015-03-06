#include "mydelegate.h"
#include <QStyledItemDelegate>

#include <QAbstractItemModel>

#include <QBrush>
#include <QPainter>
#include <QPalette>
#include <QModelIndex>
#include <QWidget>
#include <QStyle>
#include <QApplication>
#include <QDebug>
#include <QModelIndex>
#include <QModelIndex>

MyDelegate::MyDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

MyDelegate::~MyDelegate()
{
}

void MyDelegate:: paint(QPainter *painter,
           const QStyleOptionViewItem &option, const QModelIndex &index) const{
    //qDebug()<<option;
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    const QWidget *widget =option.widget;
    if(widget){
        //qDebug()<<"widget";
    } else {
         //qDebug()<<"QApplication";
    }

    QStyle *style = widget ? widget->style() : QApplication::style();
    //qDebug()<< style;
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);

}
