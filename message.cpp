#include "message.h"
#include "ui_message.h"
#include "commserver.h"
Message::Message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Message)
{
    ui->setupUi(this);
    this->setWindowTitle("Message");
    GSession::moveToCentre(this);

    ui->textEdit->setFocusPolicy(Qt::StrongFocus);
    ui->textEdit1->setFocusPolicy(Qt::NoFocus);

    ui->textEdit->setFocus();
    ui->textEdit->installEventFilter(this);

    ui->label->setText(GSession::sipaddr);

    connect(ui->textEdit,SIGNAL(currentCharFormatChanged(QTextCharFormat)),this,SLOT(currentFormatChanged(const QTextCharFormat)));
}

void Message::connectedSlot()
{
    qDebug() << "connect ok!";
    QByteArray tmp;
    qint64 len;
    if(ui->textEdit->toPlainText() == "")
    {
        QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
        return;
    }
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    tmp.append("[ " +GSession::uname+" ] "+ time+"\n");
    tmp.append(   ui->textEdit->toPlainText() );
    len = tcpSocket->write( tmp );
    ui->textEdit1->append(tmp);
    tcpSocket->flush();
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}

void Message::on_send_clicked()
{
    //发送消息给服务器

    QString lableip = ui->label->text();
    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost( lableip,5000);

    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connectedSlot()));
}

//修饰部分
void Message::currentFormatChanged(const QTextCharFormat &format)
{
    ui->fontComboBox->setCurrentFont(format.font());

    if(format.fontPointSize()<9)
        ui->fontsizecomboBox->setCurrentIndex(3);
    else ui->fontsizecomboBox->setCurrentIndex(
            ui->fontsizecomboBox->findText(QString::number(format.fontPointSize())));

    ui->textbold->setChecked(format.font().bold());
    ui->textitalic->setChecked(format.font().italic());
    ui->textUnderline->setChecked(format.font().underline());
    color = format.foreground().color();
}

Message::~Message()
{
    delete ui;
}

void Message::closeEvent(QCloseEvent *event)
{
    qDebug()<<"123";
    QString lableip = ui->label->text();
    emit closetalkWidget(lableip);
    QWidget::closeEvent(event);
}

QString Message::getIP()  //getipַ
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    return list.at(2).toString();
}

void Message::on_close_clicked()
{
    this->close();
}

void Message::on_fontComboBox_currentFontChanged(QFont f)
{
    ui->textEdit->setCurrentFont(f);
    ui->textEdit->setFocus();
}

void Message::on_fontsizecomboBox_currentIndexChanged(QString size)
{
   ui->textEdit->setFontPointSize(size.toDouble());
   ui->textEdit->setFocus();
}

void Message::on_textbold_clicked(bool checked)
{
    if(checked)
        ui->textEdit->setFontWeight(QFont::Bold);
    else
        ui->textEdit->setFontWeight(QFont::Normal);
    ui->textEdit->setFocus();
}

void Message::on_textitalic_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    ui->textEdit->setFocus();
}

void Message::on_textUnderline_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
    ui->textEdit->setFocus();
}

void Message::on_textcolor_clicked()
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
        ui->textEdit->setFocus();
    }
}

void Message::on_save_clicked()
{
    if(ui->textEdit1->document()->isEmpty())
        QMessageBox::warning(0,tr("警告"),tr("聊天内容为空！"),QMessageBox::Ok);
    else{
       QString fileName = QFileDialog::getSaveFileName(this,tr("保存聊天记录"),tr("聊天记录"),tr("文本(*.txt);;All File(*.*)"));
       if(!fileName.isEmpty())
           saveFile(fileName);
    }
}

bool Message::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,tr("保存文件"),
        tr("无法保存文件 %1:\n %2").arg(fileName)
        .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->textEdit1->toPlainText();

    return true;
}

void Message::on_clear_clicked()
{
    ui->textEdit1->clear();
}

void Message::setLable(QString tmpip)
{
    ui->label->setText(tmpip);
}

QString  Message::getLable()
{
    return ui->label->text();
}
