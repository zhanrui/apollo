#ifndef COMMONWIDGET_H
#define COMMONWIDGET_H

#include <src/ui/common/basestylewidget.h>
class CommonWidget: public BaseStyleWidget
{
    Q_OBJECT
public:
   explicit CommonWidget(QWidget *parent = 0);
    ~CommonWidget();
};

#endif // COMMONWIDGET_H
