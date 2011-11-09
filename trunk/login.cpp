#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QDesktopWidget>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2,
         (desktop->height() - this->height())/2);


    ui->lineEdit_uname->setFocus();
    connect(ui->lineEdit_uname,SIGNAL(returnPressed()),ui->lineEdit_pwd,SLOT(setFocus()));
    connect(ui->lineEdit_pwd,SIGNAL(returnPressed()),this,SLOT(on_pushButton_login_clicked()));

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

    if (ui->lineEdit_uname->text() == uname) {
        if (ui->lineEdit_pwd->text() == pwd) {
            ui->label_msg->setText("登录成功！");
            GSession::uname = uname;
            emit loginSuccess();
            this->close();
        } else {
            ui->label_msg->setText("登录失败，密码错误！");
            ui->lineEdit_pwd->selectAll();
        }
    } else {
        ui->label_msg->setText("登录失败，没有该用户！");
        ui->lineEdit_uname->selectAll();
    }

}
