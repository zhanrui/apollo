/****************************************************************************
**
** This Class is for call the Tools ( for example : check the system info , check file ,check Virus
**
****************************************************************************/


#ifndef TOOLUTIL_H
#define TOOLUTIL_H
#include <QString>

class ToolUtil
{
public:
    ToolUtil();
    ~ToolUtil();
    static void getSystemBasicInfo();
    static void sendMessage(const QString & messages);
};

#endif // TOOLUTIL_H
