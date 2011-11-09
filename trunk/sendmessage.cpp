#include "sendmessage.h"
#include "message.h"
#include "workspace.h"
#include "ui_sendmessage.h"

SendMessage::SendMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessage)
{
    ui->setupUi(this);
    this->setWindowTitle("Groove");
    qDebug() << "con";

}

SendMessage::~SendMessage()
{
    qDebug() << "des";
    for(int i = 0; i < m_messageList.size(); i++)
    {
        delete m_messageList.at(i);
    }

    for(int i = 0; i < m_workspaceList.size(); i++)
    {
        delete m_workspaceList.at(i);
    }

    delete ui;
}

void SendMessage::on_pushButton_clicked()
{
    Message * m_message = new Message();
    m_message->show();
    m_messageList << m_message;
}

void SendMessage::on_pushButton_5_clicked()
{
     Workspace * workspace = new Workspace();
     workspace->show();
     m_workspaceList << workspace;
}
