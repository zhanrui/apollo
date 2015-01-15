#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <src/ui/common/basestylewidget.h>
#include <src/ui/main/maintitlewidget.h>

class MainWidget : public BaseStyleWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
private:
    void initUI();
    void initConnect();
    void initAnim();

signals:

public slots:

public:
    MainTitleWidget   *mainTitleWidget;

};

#endif // MAINWIDGET_H
