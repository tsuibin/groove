#ifndef GSESSION_H
#define GSESSION_H
#include <QString>
#include <QTime>
#include <QObject>
#include <QDesktopWidget>
#include <QApplication>
#include <QSqlDatabase>
#include <QByteArray>
/*
 GSession 用户会话数据
*/

class GSession
{
public:
    GSession(){}
    static QString uname;
    static QSqlDatabase m_db;
    static QString sipaddr;
    static QSqlDatabase ms_db;
    static QString getTimeName();
    static QStringList ipList;
    static void moveToCentre(QWidget *widget);
    static void openDatabase();
    static void closeDatabase();
    static void openmsDatabase();
    static void closemsDatabase();

};

#endif // GSESSION_H
