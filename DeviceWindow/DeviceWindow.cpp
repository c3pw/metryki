#include "DeviceWindow.h"
#include "ui_DeviceWindow.h"

#include <QSqlQuery>

DeviceWindow::DeviceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceWindow)
{
    ui->setupUi(this);
}

DeviceWindow::~DeviceWindow()
{
    delete ui;
}
void DeviceWindow::showDevice(QString name)
{
    this->name = name;

    QSqlQuery q;
    q.prepare("select "
                                "slownik_stanowisk.lokalizacja_stanowiska, "
                                "slownik_stanowisk.identyfikator_stanowiska, "
                                "urzadzenia.identyfikator_urzadzenia, "
                                "urzadzenia.typ_urzadzenia, "
                                "urzadzenia.opis "
                           "from "
                                "urzadzenia "
                           "left join slownik_stanowisk using(identyfikator_stanowiska)"
                                " where urzadzenia.identyfikator_urzadzenia=:name;");
    q.bindValue(":name",name);

    if(q.exec())
    {
        q.next();
        this->ui->idEdit->setText(q.value(2).toString());
        this->ui->typeEdit->setText(q.value(3).toString());
        QString l = q.value(1).toString();
        if(!q.value(0).toString().isEmpty())
        {
            l.append(" - ").append(q.value(0).toString());
        }
        this->ui->locationEdit->setText(l);
        this->ui->descriptionEdit->appendPlainText(q.value(4).toString());
    }
    this->show();


    this->attrModel = new QSqlQueryModel();
    this->attrModel->setQuery("select * from ");
    this->attrSortProxy = new QSortFilterProxyModel();
    this->attrSortProxy->setSourceModel(this->attrModel);
    this->attrSortProxy->sort(0);
    this->ui->attrTable->setModel(this->attrSortProxy);
    this->ui->attrTable->resizeColumnsToContents();
    this->ui->attrTable->horizontalHeader()->setStretchLastSection(true);

}

void DeviceWindow::on_closeButton_clicked()
{
    this->close();
}
