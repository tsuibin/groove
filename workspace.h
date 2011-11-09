#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>

namespace Ui {
    class Workspace;
}

class Workspace : public QWidget
{
    Q_OBJECT

public:
    explicit Workspace(QWidget *parent = 0);
    ~Workspace();

private:
    Ui::Workspace *ui;
};

#endif // WORKSPACE_H
