#ifndef MAINTITLEWIDGET_H
#define MAINTITLEWIDGET_H
#include <src/ui/base/basestylewidget.h>
#include <src/ui/base/commonwidget.h>
class QLabel;
class StaticButton;
class CommonWidget;
class MainTitleWidget : public BaseStyleWidget {
    Q_OBJECT
public:
    explicit MainTitleWidget(QWidget* parent = 0);
    ~MainTitleWidget();

private:
    void initUI();
    void initConnect();
    void initAnim();
signals:

public slots:

public:



    StaticButton* minButton;
    CommonWidget* testButton;
};

#endif // MAINTITLEWIDGET_H
