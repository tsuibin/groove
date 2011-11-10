#ifndef GSESSION_H
#define GSESSION_H
#include <QString>
#include <QTime>
#include <QObject>
#include <QDesktopWidget>
#include <QApplication>
#include <QSqlDatabase>
/*
 GSession 用户会话数据
*/

class GSession
{
public:
    GSession(){}
    static QString uname;
    static QSqlDatabase m_db;

    static QString getTimeName();
    static void moveToCentre(QWidget *widget);
    static void openDatabase();
    static void closeDatabase();

};

#endif // GSESSION_H
