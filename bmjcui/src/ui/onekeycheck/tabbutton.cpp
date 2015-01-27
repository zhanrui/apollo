#include "tabbutton.h"



TabButton::TabButton(const QString& icon,  QWidget* parent)
    : StaticButton(parent)
{
    this->iconname = icon;
    changeToDefault();
}

TabButton::~TabButton()
{

}
void TabButton::changeToRunning(){
    this->setOneButtonInfo(iconname+"_running",3);
    this->update();
}
void TabButton::changeToProblem(){
    this->setOneButtonInfo(iconname+"_problem",3);
     this->update();
}
void TabButton::changeToNoProblem(){
     this->setOneButtonInfo(iconname+"_noproblem",3);
     this->update();
}
void TabButton::changeToDefault(){
    this->setOneButtonInfo(iconname+"_default",3);
     this->update();
}

