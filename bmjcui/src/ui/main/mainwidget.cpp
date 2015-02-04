#include "mainwidget.h"
#include "src/ui/main/maintitlewidget.h"
#include "src/ui/base/staticbutton.h"
#include "src/ui/common/taskbutton.h"
#include "src/ui/base/commonwidget.h"
#include "src/ui/base/faderwidget.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QRect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <QtMath>

MainWidget::MainWidget(QWidget* parent)
    : BaseStyleWidget(parent)
{
    //setWindowFlags( Qt::Window | Qt::FramelessWindowHint);
    this->initUI();
    this->initAnim();
    this->initConnect();
}

MainWidget::~MainWidget()
{
    delete buttonlist;
}

void MainWidget::initUI()
{
    this->setFixedSize(900, 600);

    logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":image/common/title/logo"));
    logoLabel->move(13, 1);
    textLabel = new QLabel(this);
    textLabel->setPixmap(QPixmap(":image/common/title/description"));
    textLabel->move(45, 9);

    biglogoLabel = new QLabel(this);
    statusLabel = new QLabel(this);
    biglogoLabel->setPixmap(QPixmap(":image/main/biglogo"));
    biglogoLabel->move(80, 100);
    statusLabel->setPixmap(QPixmap(":image/main/status"));
    statusLabel->move(236, 136);

    version = new QLabel(this);
    version->setPixmap(QPixmap(":image/main/version"));
    version->move(26, 575);

    line = new QLabel(this);
    line->setPixmap(QPixmap(":image/main/line"));
    line->move(0, 562);

    toleft = new StaticButton(":image/main/toleft", 3, this);
    toleft->move(34, 324);
    toright = new StaticButton(":image/main/toright", 3, this);
    toright->move(807, 324);

    toolbar = new CommonWidget(this);
    toolbar->setFixedSize(700, 200);
    toolbar->move(100, 300);

    onekeychecklogo = new StaticButton(":image/main/onekeychecklogo", 3, toolbar);
    onekeychecklogo->move(37, 9);
    onekeychecktext = new QLabel(toolbar);
    onekeychecktext->setPixmap(QPixmap(":image/main/onekeychecktext"));
    onekeychecktext->move(77, 171);

    commonchecklogo = new StaticButton(":image/main/commonchecklogo", 3, toolbar);
    //commonchecklogo = new TaskButton(":image/main/commonchecklogo",  toolbar);
    commonchecklogo->move(271, 9);
    commonchecktext = new QLabel(toolbar);
    commonchecktext->setPixmap(QPixmap(":image/main/commonchecktext"));
    commonchecktext->move(316, 171);

    deepchecklogo = new StaticButton(":image/main/deepchecklogo", 3, toolbar);
    deepchecklogo->move(500, 9);
    deepchecktext = new QLabel(toolbar);
    deepchecktext->setPixmap(QPixmap(":image/main/deepchecktext"));
    deepchecktext->move(550, 171);

    //toolbar2 = new CommonWidget(this);
    //toolbar2->setFixedSize(700, 200);
    //toolbar2->move(100, 300);

    filechecklogo = new StaticButton(":image/main/filechecklogo", 3, toolbar);
    filechecklogo->move(37 + 700, 9);
    filechecktext = new QLabel(toolbar);
    filechecktext->setPixmap(QPixmap(":image/main/filechecktext"));
    filechecktext->move(77 + 700, 171);

    tjchecklogo = new StaticButton(":image/main/tjchecklogo", 3, toolbar);
    tjchecklogo->move(271 + 700, 9);
    tjchecktext = new QLabel(toolbar);
    tjchecktext->setPixmap(QPixmap(":image/main/tjchecktext"));
    tjchecktext->move(316 + 700, 171);

    toollogo = new StaticButton(":image/main/toollogo", 3, toolbar);
    toollogo->move(500 + 700, 9);
    tooltext = new QLabel(toolbar);
    tooltext->setPixmap(QPixmap(":image/main/tooltext"));
    tooltext->move(550 + 700, 171);

    buttonlist = new QList<QWidget*>();

    buttonlist->append(onekeychecklogo);
    buttonlist->append(onekeychecktext);
    buttonlist->append(commonchecklogo);
    buttonlist->append(commonchecktext);
    buttonlist->append(deepchecklogo);
    buttonlist->append(deepchecktext);

    buttonlist->append(filechecklogo);
    buttonlist->append(filechecktext);
    buttonlist->append(tjchecklogo);
    buttonlist->append(tjchecktext);
    buttonlist->append(toollogo);
    buttonlist->append(tooltext);

    toolbarSwitchAnimation = new QParallelAnimationGroup(this);
    //toolbar2->hide();
}

void MainWidget::initConnect()
{
    connect(toleft, SIGNAL(buttonClicked()), this, SLOT(toolbarSwitchLeft()));
    connect(toright, SIGNAL(buttonClicked()), this, SLOT(toolbarSwitchRight()));
}

void MainWidget::initAnim() {}

void MainWidget::toolbarSwitchLeft()
{
    int groups = qCeil((qreal)buttonlist->size()/6);
    for (int i = 0; i < buttonlist->size(); ++i) {
        if (buttonlist->at(i)->x() < 700*(groups-2)) {
            buttonlist->at(i)->move(buttonlist->at(i)->x() + 700*groups, buttonlist->at(i)->y());
        }
    }
    toolbarSwitchAnimation->clear();
    for (int i = 0; i < buttonlist->size(); ++i) {
        QPropertyAnimation* subnimation = new QPropertyAnimation(buttonlist->at(i), "pos");
        subnimation->setDuration(500);
        subnimation->setStartValue(buttonlist->at(i)->pos());
        subnimation->setEndValue(QPoint(buttonlist->at(i)->pos().x() - 700, buttonlist->at(i)->pos().y()));
        toolbarSwitchAnimation->addAnimation(subnimation);
    }
    toolbarSwitchAnimation->start();
}

void MainWidget::toolbarSwitchRight()
{

    int groups = qCeil((qreal)buttonlist->size()/6);
    for (int i = 0; i < buttonlist->size(); ++i) {
        if (buttonlist->at(i)->x() > 700*(groups-1)) {
            buttonlist->at(i)->move(buttonlist->at(i)->x() - 700*groups, buttonlist->at(i)->y());
        }
    }

    toolbarSwitchAnimation->clear();
    for (int i = 0; i < buttonlist->size(); ++i) {
        QPropertyAnimation* subnimation = new QPropertyAnimation(buttonlist->at(i), "pos");
        subnimation->setDuration(500);
        subnimation->setStartValue(buttonlist->at(i)->pos());
        subnimation->setEndValue(QPoint(buttonlist->at(i)->pos().x() + 700, buttonlist->at(i)->pos().y()));
        toolbarSwitchAnimation->addAnimation(subnimation);
    }
    toolbarSwitchAnimation->start();
}
