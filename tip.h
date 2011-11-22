#ifndef TIP_H
#define TIP_H

#include <QWidget>

namespace Ui {
    class Tip;
}

class Tip : public QWidget
{
    Q_OBJECT

public:
    explicit Tip(QWidget *parent = 0);
    ~Tip();
    Ui::Tip *ui;
signals:
    void showtalkwindows(QString );
private slots:
    void on_pushButton_clicked();

private:

};

#endif // TIP_H
