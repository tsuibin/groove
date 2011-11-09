#include "message.h"
#include "ui_message.h"

Message::Message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Message)
{
    ui->setupUi(this);
    this->setWindowTitle("Message");
}

Message::~Message()
{
    delete ui;
}
