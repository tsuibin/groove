#ifndef GREGISTER_H
#define GREGISTER_H

#include <QWidget>
#include <QSqlQuery>
#include "gsession.h"

namespace Ui {
    class GRegister;
}

class GRegister : public QWidget
{
    Q_OBJECT

public:
    explicit GRegister(QWidget *parent = 0);
    ~GRegister();
signals:
    void gRegisterCancel();
private slots:
    void on_pushButton_reg_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::GRegister *ui;
};

#endif // GREGISTER_H
