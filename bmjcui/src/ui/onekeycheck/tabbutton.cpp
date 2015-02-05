#include "tabbutton.h"
#include "src/common/common.h"

TabButton::TabButton(const QString& icon, QWidget* parent)
    : StaticButton(parent)
{
    this->iconname = icon;
    taskstaus = TASK_DEFAULT;
    changeToDefault();
}

TabButton::~TabButton()
{
}
void TabButton::changeToRunning()
{
    taskstaus = TASK_RUNNING;
    this->setOneButtonInfo(iconname + "_running", 3);
    this->update();
}
void TabButton::changeToProblem()
{
    taskstaus = TASK_PROBLEM;
    this->setOneButtonInfo(iconname + "_problem", 3);
    this->update();
}
void TabButton::changeToNoProblem()
{
    taskstaus = TASK_NOPROBLEM;
    this->setOneButtonInfo(iconname + "_noproblem", 3);
    this->update();
}
void TabButton::changeToDefault()
{
    taskstaus = TASK_DEFAULT;
    this->setOneButtonInfo(iconname + "_default", 3);
    this->update();
}
