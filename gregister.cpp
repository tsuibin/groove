#include "gregister.h"
#include "ui_gregister.h"
#include <QDebug>

GRegister::GRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GRegister)
{
    ui->setupUi(this);
    GSession::moveToCentre(this);

}

GRegister::~GRegister()
{
    delete ui;
}

void GRegister::on_pushButton_reg_clicked()
{
    QSqlQuery query;
    QString uname = ui->lineEdit_uname->text();
    QString email = ui->lineEdit_email->text();
    QString tel = ui->lineEdit_tel->text();
    QString pwd = ui->lineEdit_pwd->text();
    QString checkpwd = ui->lineEdit_checkpwd->text();


    if ( checkpwd != pwd ) {
        ui->label_msg->setText("两次输入的密码不一致！");
        ui->lineEdit_pwd->setFocus();
        ui->lineEdit_pwd->selectAll();
        return;
    }

    if( uname.isEmpty() ) {
        ui->label_msg->setText("请输入用户名！");
        ui->lineEdit_uname->setFocus();
        return;
    }
    if (pwd.isEmpty()) {
        ui->label_msg->setText("请输入密码！");
        ui->lineEdit_pwd->setFocus();
        return;
    }


//insert into user(name,email,tel,pwd) values('lijia','aaa@akaedu.org','13888888888','bbb');
    QString sql = "insert into user(name,email,tel,pwd) values('";
    sql.append(uname + "','");
    sql.append(email + "','");
    sql.append(tel + "','");
    sql.append(pwd + "');");


    qDebug() << sql;
    if ( query.exec( sql ) ) {

        qDebug() << "insert ok";
        ui->label_msg->setText("恭喜您，注册成功，开始你的体验之旅吧！");
        emit gRegisterSuccess();
        this->close();
//        while(query.next()) {
//            qDebug() << query.value(0).toString();
//            qDebug() << query.value(1).toString();
//        }
    }
    else
    {
         ui->label_msg->setText("用户名已经存在！！！");
    }


}

void GRegister::on_pushButton_cancel_clicked()
{
    emit gRegisterCancel();
    this->close();
}


