#include "sendmessage.h"
#include "message.h"
#include "workspace.h"
#include "ui_sendmessage.h"
#include <QDesktopWidget>
#include <QTableWidgetItem>

#define PROT 66666
int flag = 1;
int j=0;

SendMessage::SendMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessage)
{
    ui->setupUi(this);

    GSession::sipaddr = getIP();

    lognotice_broad_send = new QUdpSocket(this);
    lognotice_broad_rec = new QUdpSocket(this);
    lognotice_broad_rec->bind(PROT, QUdpSocket::ShareAddress);
    broad_log_notice();

    connect(lognotice_broad_rec, SIGNAL(readyRead()), this, SLOT(rec_log_notice()));

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width()),0);

    this->setWindowTitle("Groove");

    this->setUserInfo();

    datag = "@";
    datag.append( GSession::uname );
    datag.append("@");
    datag.append(getIP());

}

SendMessage::~SendMessage()
{
    for(int i = 0; i < m_workspaceList.size(); i++){
        delete m_workspaceList.at(i);
    }
    delete ui;
}

void SendMessage::on_pushButton_5_clicked()
{
     Workspace * workspace = new Workspace();
     workspace->show();
     m_workspaceList << workspace;
}

void SendMessage::setUserInfo()
{
    ui->label_uinfo->setText( GSession::getTimeName() +"，" + GSession::uname+"....");
}

void SendMessage::broad_log_notice()
{
    QByteArray datagram;
    datagram = "#";
    datagram.append( GSession::uname );
    datagram.append("#");
    datagram.append(getIP());
    lognotice_broad_send->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, PROT);
}

void SendMessage::rec_log_notice()
{
    while (lognotice_broad_rec->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(lognotice_broad_rec->pendingDatagramSize());
        lognotice_broad_rec->readDatagram(datagram.data(), datagram.size());
        QList<QByteArray> list,list1,list2;
        if(datagram.startsWith("#"))
        {
            list = datagram.split('#');
            m_map.insert(list.at(1),list.at(2)); //向map里添加一对“键-值”
            QString peeraddress = list.at(2);
            if(flag == 2)//避免自己ip识别，造成无限循环
            {
                if( list.at(1) == GSession::uname ) return;
            }
            if( list.at(1) == GSession::uname ){
                flag = 2;
            }
            lognotice_broad_send->writeDatagram(datag, datag.size(), QHostAddress(peeraddress), PROT);
            us = list.at(1);
            ipad = list.at(2);

        }
        else if(datagram.startsWith("$"))
        {
            qDebug() << "out line";
            list1 = datagram.split('$');
            int rowNum = ui->tableWidget->findItems(list1.at(1),Qt::MatchExactly).first()->row();
            ui->tableWidget->removeRow(rowNum);

            j--;
            m_map.remove(list1.at(1));
            ui->onlineUser->setText(tr("在线人数%1").arg(ui->tableWidget->rowCount()));
            return;
        }else if(datagram.startsWith("@"))
        {

            list2 = datagram.split('@');
            if(flag == 2)//避免自己ip识别，造成无限循环
            {
                if( list2.at(1) == GSession::uname )
                    return;
            }
            us = list2.at(1);
            ipad = list2.at(2);
            m_map.insert(list2.at(1),list2.at(2));
        }
        QString user = us;
        QString ipaddr = ipad;
        QTableWidgetItem *name = new QTableWidgetItem(user);
        QTableWidgetItem *ip = new QTableWidgetItem(ipaddr);
        ui->tableWidget->insertRow(j);
        ui->tableWidget->setItem(j,0,name);
        ui->tableWidget->setItem(j,1,ip);
        j++;
        ui->onlineUser->setText(tr("在线人数%1").arg(ui->tableWidget->rowCount()));

    }
}

void SendMessage::closeEvent(QCloseEvent *event)
{
    QByteArray datagr = "$";
    datagr.append( GSession::uname );
    lognotice_broad_send->writeDatagram(datagr.data(), datagr.size(), QHostAddress::Broadcast, PROT);
    emit closeALLtalkwidget();
    QWidget::closeEvent(event);
}



QString SendMessage::getIP()//查找IP
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list){
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
            if(address.toString().contains("127.0.")){
                continue;
            }
            return address.toString();
        }
    }
    return 0;
}

void SendMessage::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
     GSession::sipaddr = m_map.value( item->text());
     GSession::ipList.append(GSession::sipaddr);
     emit talkshow();
}
