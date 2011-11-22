#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QUdpSocket>
#include <QByteArray>
#include <QNetworkInterface>
#include <QMap>
#include <QTableWidgetItem>
#include "gsession.h"



namespace Ui {
    class SendMessage;
}


class Message;
class Workspace;

class SendMessage : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessage(QWidget *parent = 0);
    ~SendMessage();
signals:
    void talkshow();
    void closeALLtalkwidget();

private slots:
    void on_pushButton_5_clicked();

    void rec_log_notice();

    void broad_log_notice();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::SendMessage *ui;
    QList< Message * > m_messageList;
    QList< Workspace * > m_workspaceList;
    void setUserInfo();
    QUdpSocket *lognotice_broad_send;
    QUdpSocket *lognotice_broad_rec;
    QString host_ip,us,ipad;
    QMap<QString,QString> m_map;
    QString getIP();
    QByteArray datag;
};

#endif // SENDMESSAGE_H
