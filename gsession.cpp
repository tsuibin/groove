#include "gsession.h"
#include <QDebug>

QString GSession::uname = "";
QSqlDatabase GSession::m_db;
QSqlDatabase GSession::ms_db;
QString  GSession::sipaddr = "";

QStringList GSession::ipList;

QString GSession::getTimeName()
{
    qDebug() << "getTimeName";
    //凌晨 1 - 5
    //早上 6 - 8
    //上午 9 - 11
    //中午 12
    //下午 13 - 18
    //晚上 19 - 23
    //午夜 0

    static QString timeName;
    switch( QTime::currentTime().hour() ) {
    case 0:
        timeName = "午夜";
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        timeName = "凌晨";
        break;
    case 6:
    case 7:
    case 8:
        timeName = "早上好";
        break;
    case 9:
    case 10:
    case 11:
        timeName = "上午好";
        break;
    case 12:
        timeName = "正午好";
        break;

    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        timeName = "下午好";
        break;

    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
        timeName = "晚上好";
        break;
    default:
        timeName = "";
        break;
    }

    return timeName;
}


void GSession::moveToCentre(QWidget *widget)
{
    qDebug() << "moveToCentre";
    QDesktopWidget* desktop = QApplication::desktop();
    widget->move((desktop->width() - widget->width())/2,
         (desktop->height() - widget->height())/2);
}

void GSession::openDatabase()
{
    qDebug() << "openDatabase";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("user.db");
    m_db.setUserName("dbname");
    m_db.setPassword("dbpwd");
    m_db.open();

}

void GSession::closeDatabase()
{
    qDebug() << "closeDatabase";
    m_db.close();
}

void GSession::openmsDatabase()
{
    qDebug() << "openmsDatabase";
    ms_db = QSqlDatabase::addDatabase("QSQLITE");
    ms_db.setHostName("localhost");
    ms_db.setDatabaseName("usermessage.db");
    ms_db.setUserName("dbname");
    ms_db.setPassword("dbpwd");
    ms_db.open();
}

void GSession::closemsDatabase()
{
    qDebug() << "closemsDatabase";
    ms_db.close();
}
