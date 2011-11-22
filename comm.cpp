#include "comm.h"
#include "sendmessage.h"
#include "commserver.h"
#include "ui_comm.h"
#include "login.h"
#include "gregister.h"
#include "gsession.h"
#include "message.h"
#include "ui_message.h"
#include "tip.h"
#include "ui_tip.h"

Comm::Comm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Comm)
{
    ui->setupUi(this);

}

Comm::~Comm()
{
    qDebug() << "~Comm()";
    delete this->m_sendMessage;
    delete this->m_login;

    for(int i = 0; i < m_msgWidgetList.size(); i++){
        m_msgWidgetList.at(i)->close();
    }

    GSession::closemsDatabase();
    delete ui;
}

void Comm::login()
{
    GSession::openDatabase();
    this->m_login = new Login();
    this->m_login->show();
    connect(this->m_login,SIGNAL(loginSuccess()),this,SLOT(createModule()));
    connect(this->m_login,SIGNAL(showRegister()),this,SLOT(showRegisterSlot()));
}

void Comm::createModule()
{
    this->m_sendMessage = new SendMessage();
    this->m_commServer = new CommServer();
    this->m_message = new Message();
    this->m_sendMessage->show();

    GSession::closeDatabase();
    GSession::openmsDatabase();

    connect(m_sendMessage,SIGNAL(talkshow()),this,SLOT(sendtalkwidegt()));
    connect(m_sendMessage,SIGNAL(closeALLtalkwidget()),this,SLOT(closeALLslots()));
    connect(m_commServer,SIGNAL(newmessageemit(QString)),this,SLOT(tipshow(QString)));
    connect(m_commServer,SIGNAL(oldmessageemit(QString)),this,SLOT(talkMessage(QString)));
    connect(m_message,SIGNAL(closetalkWidget(QString)),this,SLOT(removeMsgWidgetList(QString)));
}

void Comm::showRegisterSlot()
{
    this->m_gregister = new GRegister();
    this->m_gregister->show();
    connect(this->m_gregister,SIGNAL(gRegisterCancel()),this->m_login,SLOT(show()));
    connect(this->m_gregister,SIGNAL(gRegisterSuccess()),this->m_login,SLOT(show()));
}

void Comm::sendtalkwidegt()
{
    this->m_message = new Message();
    connect(m_message,SIGNAL(closetalkWidget(QString)),this,SLOT(removeMsgWidgetList(QString)));
    this->m_message->show();
}

void Comm::talkwidegt(QString tmpip)
{
   qDebug() << "talkwidegt()";
   this->m_message = new Message();
   connect(m_message,SIGNAL(closetalkWidget(QString)),this,SLOT(removeMsgWidgetList(QString)));
   this->m_message->show();
   this->m_message->setLable(tmpip);
   QSqlQuery read_query;
   QSqlQuery updata_query;
   QString read_sql = "SELECT messagetmp FROM usermessage WHERE ip = '"+ tmpip +"' and flag = 1;";
   QString updata_sql;
   QString newmessage;
   qDebug() << read_sql;
   qDebug()<<read_query.exec( read_sql )<<"read_query.exec( read_sql )";
   if ( read_query.exec( read_sql ) ) {
       while(read_query.next()) {           
           newmessage .append( read_query.value(0).toString() );
           updata_sql.append("update usermessage set flag = 0 where flag = 1; ");
           updata_query.exec( updata_sql );
       }
       m_message->ui->textEdit1->append(newmessage);
   }
   m_msgWidgetList << m_message;
}

void Comm::talkMessage(QString tmpip)
{
    for(int i = 0; i <m_msgWidgetList.size(); i++){
        if ( m_msgWidgetList.at(i)->getLable() == tmpip ){
            m_message = m_msgWidgetList.at(i);
            break;
        }
    }

    QSqlQuery read_query;
    QSqlQuery updata_query;
    QString read_sql = "SELECT messagetmp FROM usermessage WHERE ip = '"+ tmpip +"' and flag = 1;";
    QString updata_sql;
    QString newmessage;
    qDebug() << read_sql;
    qDebug()<<read_query.exec( read_sql )<<"read_query.exec( read_sql )";
    if ( read_query.exec( read_sql ) ) {
        while(read_query.next()) {
            newmessage .append( read_query.value(0).toString() );
            updata_sql.append("update usermessage set flag = 0 where flag = 1; ");
            updata_query.exec( updata_sql );
        }
        m_message->ui->textEdit1->append(newmessage);
    }
}

void Comm::removeMsgWidgetList(QString lableip)
{
    qDebug()<< lableip<<"lableip";
    for(int i = 0; i <m_msgWidgetList.size(); i++)
    {
        if ( m_msgWidgetList.at(i)->getLable() == lableip )
        {
            qDebug()<<m_msgWidgetList.at(i)->getLable()<<"m_msgWidgetList.at(i)->getLable()";
            m_msgWidgetList.removeAt(i);
            break;
        }
    }

    for(int i = 0; i < GSession::ipList.count(); i ++){
        if(lableip == GSession::ipList.at(i)){
            qDebug()<< GSession::ipList.at(i)<<"GSession::ipList.at(i)";
            GSession::ipList.removeAt(i);
            break;
        }
    }
}

void Comm::closeALLslots()
{

    for(int i = 0; i < m_msgWidgetList.size(); i++){
        qDebug()<<"closeALL"<< i;
        m_msgWidgetList.at(i)->on_close_clicked();
    }

}

void Comm::tipshow(QString tmpip )
{
    this->m_tip = new Tip();
    this->m_tip->show();
     tmpip.append(" ");
     tmpip.append("来消息了！");
     m_tip->ui->pushButton->setText(tmpip);
     qDebug() << tmpip << "tmpip";
      connect(m_tip,SIGNAL(showtalkwindows(QString)),this,SLOT(talkwidegt(QString)));
}
