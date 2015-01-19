#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <src/ui/base/basestylewidget.h>


class QLabel;
class MainTitleWidget;
class MainWidget : public BaseStyleWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent = 0);
    ~MainWidget();

private:
    void initUI();
    void initConnect();
    void initAnim();

signals:

public slots:

public:
    QWidget* mainTitleWidget;
    QLabel* logoLabel;
    QLabel* textLabel;
    QLabel* biglogoLabel;
    QLabel* statusLabel;


};

#endif // MAINWIDGET_H
