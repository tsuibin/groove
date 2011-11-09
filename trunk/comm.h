#ifndef COMM_H
#define COMM_H

#include <QWidget>

namespace Ui {
    class Comm;
}

class SendMessage;

class Comm : public QWidget
{
    Q_OBJECT

public:
    explicit Comm(QWidget *parent = 0);
    ~Comm();

private:
    Ui::Comm *ui;
    SendMessage *m_sendMessage;
};

#endif // COMM_H
