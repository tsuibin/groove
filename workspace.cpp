#include "workspace.h"
#include "ui_workspace.h"

Workspace::Workspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workspace)
{
    ui->setupUi(this);
    this->setWindowTitle("Workspace");
}

Workspace::~Workspace()
{
    delete ui;
}
