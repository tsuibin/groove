#include "login.h"
#include "ui_login.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);


    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    m_db.setDatabaseName("user.db");
    m_db.setUserName("dbname");
    m_db.setPassword("dbpwd");
    m_db.open();


}

Login::~Login()
{
    m_db.close();
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString uname;
    QString pwd;
    QSqlQuery query;
    QString sql = "SELECT name,pwd FROM user WHERE name = '" + ui->lineEdit_uname->text() + "';";
    //qDebug() << sql;
    if ( query.exec( sql ) ) {
        while(query.next()) {
            uname = query.value(0).toString();
            pwd = query.value(1).toString();
        }
    }

    if (ui->lineEdit_uname->text() == uname)
    {
        if (ui->lineEdit_pwd->text() == pwd)
        {
            ui->label_msg->setText("登录成功！");
        } else {
            ui->label_msg->setText("登录失败，密码错误！");
        }
    } else {
        ui->label_msg->setText("登录失败，没有该用户！");
    }

}
