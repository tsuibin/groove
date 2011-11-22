#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
 #include <QTextCharFormat>
#include <QtGui>
#include <QtNetwork>
#include <QTcpServer>
#include "gsession.h"
#include "commserver.h"

#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QString>

namespace Ui {
    class Message;
}


class Message : public QWidget
{
    Q_OBJECT

public:
    explicit Message(QWidget *parent = 0);
    ~Message();
    QTcpServer *tcpserver;
    QString msg;
    Ui::Message *ui;
    void setLable(QString );
    QString peerIP;
    QString  getLable();

protected:
    void closeEvent(QCloseEvent *event);
private:

    QUdpSocket *udpSocket;
    qint16 port;
    QString fileName;
    QString getIP();
    bool saveFile(const QString& fileName);
    QColor color;
    QList < QTcpSocket* > userList;//QList为类名，相当于链表，userList为变量，保存的数据全为QTcpSocket*类型
    QTcpSocket *tcpSocket;

signals:
    void closetalkWidget(QString);
public slots:
    void on_close_clicked();
private slots:

    void connectedSlot();


    void on_textUnderline_clicked(bool checked);
    void on_clear_clicked();
    void on_save_clicked();

    void on_textcolor_clicked();
    void on_textitalic_clicked(bool checked);
    void on_textbold_clicked(bool checked);
    void on_fontComboBox_currentFontChanged(QFont f);
    void on_fontsizecomboBox_currentIndexChanged(QString );

    void on_send_clicked();
    void currentFormatChanged(const QTextCharFormat &format);
};
#endif // MESSAGE_H
