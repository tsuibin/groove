#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QDesktopWidget>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap pixmap("/home/akaedu/groove-read-only5/image/loginbk1.png");
    pixmap = pixmap.scaled(325,231,Qt::KeepAspectRatio);
    ui->label_login->setPixmap(pixmap);
    GSession::moveToCentre(this);

    ui->lineEdit_uname->setFocus();
    connect(ui->lineEdit_uname,SIGNAL(returnPressed()),ui->lineEdit_pwd,SLOT(setFocus()));
    connect(ui->lineEdit_pwd,SIGNAL(returnPressed()),this,SLOT(on_pushButton_login_clicked()));
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString uname,luname;
    QString pwd,lpwd;
    QSqlQuery query;
    luname = ui->lineEdit_uname->text();
    lpwd = ui->lineEdit_pwd->text();
    if (luname.isEmpty()) {
        ui->label_msg->setText("请输入用户名！");
        ui->lineEdit_uname->setFocus();
        return;
    }
    QString sql = "SELECT name,pwd FROM user WHERE name = '" + luname + "';";
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
            ui->lineEdit_pwd->setFocus();
            ui->lineEdit_pwd->selectAll();
        }
    } else {
        ui->label_msg->setText("登录失败，没有该用户！");
        ui->lineEdit_uname->setFocus();
        ui->lineEdit_uname->selectAll();
    }

}

void Login::on_pushButton_reg_clicked()
{
    this->close();
    GSession::moveToCentre(this);
    emit showRegister();
}
