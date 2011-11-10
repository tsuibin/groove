#include "comm.h"
#include "sendmessage.h"
#include "commserver.h"
#include "ui_comm.h"
#include "login.h"
#include "gregister.h"
#include "gsession.h"

Comm::Comm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comm)
{
    ui->setupUi(this);

    //控制台
    GSession::openDatabase();

}

Comm::~Comm()
{
    qDebug() << "comm de";
    GSession::closeDatabase();
    delete this->m_sendMessage;
    delete this->m_login;
    delete ui;
}

void Comm::login()
{

    this->m_login = new Login();
    this->m_login->show();
    connect(this->m_login,SIGNAL(loginSuccess()),this,SLOT(createModule()));
    connect(this->m_login,SIGNAL(showRegister()),this,SLOT(showRegisterSlot()));


}
void Comm::createModule()
{

    this->m_sendMessage = new SendMessage();
    this->m_sendMessage->show();

}

void Comm::showRegisterSlot()
{
    this->m_gregister = new GRegister();
    this->m_gregister->show();
    connect(this->m_gregister,SIGNAL(gRegisterCancel()),this->m_login,SLOT(show()));
}
