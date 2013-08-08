#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "ConfigWindow/ConfigWindow.h"
#include "AboutWindow/AboutWindow.h"
#include "LibraryWindow/LibraryWindow.h"

#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlError>
#include <QPicture>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings s;

    QString hs = "<p align=\"right\">";
    hs.append(s.value("header/html").toString());
    hs.append("</p>");

    this->ui->headerEdit->setHtml(hs);

    this->ui->headerGraphic->setPixmap(QPixmap(s.value("header/path").toString()));


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(s.value("database/path").toString());
    if(db.open())
    {
        this->ui->statusLabel->setText(tr("Gotowy"));
    }
    else
    {
        this->ui->statusLabel->setText(db.lastError().text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_commandLinkButton_3_clicked()
{
    ConfigWindow *w = new ConfigWindow();
    w->show();
}

void MainWindow::on_commandLinkButton_4_clicked()
{
    AboutWindow *w = new AboutWindow();
    w->show();
}

void MainWindow::on_commandLinkButton_2_clicked()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::question(this,tr("Wyjście"),tr("Czy chcesz zakończyć pracę z programem?"),QMessageBox::Ok,QMessageBox::Cancel);
    if(result == QMessageBox::Cancel)
    {
        event->ignore();
    }
    else
    {
        if(result == QMessageBox::Ok)
        {
            event->accept();
        }
    }
}

void MainWindow::on_commandLinkButton_clicked()
{
    LibraryWindow *w = new LibraryWindow();
    w->show();
}
