#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QWidget>
#include <QDebug>
#include <QTime>

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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::SendMessage *ui;
    QList< Message * > m_messageList;
    QList< Workspace * > m_workspaceList;
    void setUserInfo();
};

#endif // SENDMESSAGE_H
