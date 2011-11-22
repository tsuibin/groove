#include "tip.h"
#include "ui_tip.h"
#include <QDesktopWidget>
#include <QDebug>
Tip::Tip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tip)
{
    ui->setupUi(this);
    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width()),desktop->height() - this->height());
    this->setWindowTitle("tips");
    ui->pushButton->setText("来消息啦！！");
}

Tip::~Tip()
{
    delete ui;
}

void Tip::on_pushButton_clicked()
{
    QString tmpip;
    QStringList tmpipList;
    tmpip.append(ui->pushButton->text());
    tmpipList = tmpip.split(" ");
    emit showtalkwindows(tmpipList.at(0));
    this->close();
}
