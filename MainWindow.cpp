#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "ConfigWindow/ConfigWindow.h"
#include "AboutWindow/AboutWindow.h"
#include "LibraryWindow/LibraryWindow.h"
#include "AddEditDeviceForm.h"

#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
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
        QSqlQuery q;
        q.prepare("PRAGMA foreign_keys = ON;");
        if(q.exec())
        {
            this->ui->statusLabel->setText(tr("Gotowy"));
        }
        else
        {
            QMessageBox::critical(this,tr("Błąd"),tr("Silnik bazy danych nie wspiera operacji na kluczach obcych. Należy uważać."));
        }
    }
    else
    {
        this->ui->statusLabel->setText(db.lastError().text());
    }



    this->deviceModel = new QSqlQueryModel();
    this->deviceModel->setQuery("select "
                                "slownik_stanowisk.lokalizacja_stanowiska, "
                                "slownik_stanowisk.identyfikator_stanowiska, "
                                "urzadzenia.identyfikator_urzadzenia, "
                                "urzadzenia.typ_urzadzenia, "
                                "urzadzenia.opis "
                           "from "
                                "urzadzenia "
                           "left join slownik_stanowisk using(identyfikator_stanowiska);");
    this->deviceSortProxy = new QSortFilterProxyModel();
    this->deviceSortProxy->setSourceModel(this->deviceModel);
    this->ui->deviceTable->sortByColumn(0);
    this->deviceSortProxy->sort(0);
    this->ui->deviceTable->setModel(this->deviceSortProxy);
    this->ui->deviceTable->resizeColumnsToContents();
    this->ui->deviceTable->horizontalHeader()->setStretchLastSection(true);
    this->deviceModel->setHeaderData(0,Qt::Horizontal,tr("Lokalizacja"));
    this->deviceModel->setHeaderData(1,Qt::Horizontal,tr("Stanowisko"));
    this->deviceModel->setHeaderData(2,Qt::Horizontal,tr("Urządzenie"));
    this->deviceModel->setHeaderData(3,Qt::Horizontal,tr("Typ urządzenia"));
    this->deviceModel->setHeaderData(4,Qt::Horizontal,tr("Opis"));
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

void MainWindow::on_addDeviceButton_clicked()
{
    AddEditDeviceForm *w = new AddEditDeviceForm();
    this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshDeviceView()));
    w->addRecord();
}

void MainWindow::refreshDeviceView()
{
    this->deviceModel->setQuery("select "
                                "slownik_stanowisk.lokalizacja_stanowiska, "
                                "slownik_stanowisk.identyfikator_stanowiska, "
                                "urzadzenia.identyfikator_urzadzenia, "
                                "urzadzenia.typ_urzadzenia, "
                                "urzadzenia.opis "
                           "from "
                                "urzadzenia "
                           "left join slownik_stanowisk using(identyfikator_stanowiska);");
    this->ui->deviceTable->sortByColumn(0);
    this->deviceSortProxy->sort(0);
}

void MainWindow::on_editDeviceButton_clicked()
{
    if(!this->ui->deviceTable->selectionModel()->selectedRows().isEmpty())
    {
        AddEditDeviceForm *w = new AddEditDeviceForm();
        this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshDeviceView()));
        w->editRecord(this->ui->deviceTable->selectionModel()->selectedIndexes().at(2).data().toString());
    }

}

void MainWindow::on_deleteDeviceButton_clicked()
{
    if(!this->ui->deviceTable->selectionModel()->selectedRows().isEmpty())
    {
        int result = QMessageBox::question(this,tr("Usunięcie"),tr("Czy usunąć zaznaczony rekord?"),QMessageBox::Ok,QMessageBox::Cancel);
        if(result == QMessageBox::Ok)
        {
            QSqlQuery q;
            q.prepare("delete from urzadzenia where identyfikator_urzadzenia=:name");
            q.bindValue(":name",this->ui->deviceTable->selectionModel()->selectedIndexes().at(2).data().toString());
            if(!q.exec())
            {

                switch(q.lastError().number())
                {
                    case 19: QMessageBox::critical(this,"Błąd",tr("Nie jest możliwe usunięcie rekordu. Pozostały rekordy, które są z nim powiązane."));break;
                    default: QMessageBox::critical(this,"Błąd",q.lastError().text());
                }
            }
            else
            {
                this->refreshDeviceView();
            }
        }
    }
}
