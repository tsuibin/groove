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

private:
    Ui::Tip *ui;
};

#endif // TIP_H
