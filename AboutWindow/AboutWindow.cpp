#include "AboutWindow.h"
#include "ui_AboutWindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    QString d = __DATE__;
    d.append("  ");
    d.append(__TIME__);
    this->ui->compilationLabel->setText(d);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
