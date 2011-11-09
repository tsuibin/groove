#include "comm.h"
#include "sendmessage.h"
#include "commserver.h"
#include "ui_comm.h"


Comm::Comm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comm)
{
    ui->setupUi(this);
    //控制台


}


Comm::~Comm()
{
    qDebug() << "comm de";
    delete this->m_sendMessage;
    delete this->m_login;
    delete ui;
}

void Comm::login()
{
    this->m_login = new Login();
    this->m_login->show();
    connect(this->m_login,SIGNAL(loginSuccess()),this,SLOT(createModule()));


}
void Comm::createModule()
{
    this->m_sendMessage = new SendMessage();
    this->m_sendMessage->show();

}
