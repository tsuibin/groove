#include "comm.h"
#include "sendmessage.h"
#include "ui_comm.h"
#include "login.h"

Comm::Comm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comm)
{
    ui->setupUi(this);

    Login l;
    l.show();

    //控制台
    this->m_sendMessage = new SendMessage();
    this->m_sendMessage->show();
    qDebug() << "comm";
}

Comm::~Comm()
{
    qDebug() << "comm de";
    delete this->m_sendMessage;
    delete ui;
}
