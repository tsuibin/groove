#ifndef GSESSION_H
#define GSESSION_H
#include <QString>
#include <QTime>
/*
 GSession 用户会话数据
*/

class GSession
{
public:
    GSession(){}
    static QString uname;
    static QString getTimeName();
};

#endif // GSESSION_H
