#include "AddEditDeviceForm.h"
#include "ui_AddEditDeviceForm.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include <QDebug>

AddEditDeviceForm::AddEditDeviceForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditDeviceForm)
{
    ui->setupUi(this);

    QSqlQuery typeQuery;
    typeQuery.prepare("select * from slownik_typow;");
    if(typeQuery.exec())
    {
        while(typeQuery.next())
        {
            QString name = typeQuery.value(0).toString();
            QString description = typeQuery.value(1).toString();
            QString it;
            if(description.isEmpty())
            {
                it= name;
            }
            else
            {
                it=name;
                it.append("   ]").append(description).append("]");
            }
            this->ui->typeBox->addItem(it,name);
        }
    }

    QSqlQuery locationQuery;
    locationQuery.prepare("select * from slownik_stanowisk;");
    if(locationQuery.exec())
    {
        while(locationQuery.next())
        {
            QString name = locationQuery.value(0).toString();
            QString description = locationQuery.value(1).toString();
            QString it;
            if(description.isEmpty())
            {
                it= name;
            }
            else
            {
                it=name;
                it.append("   [").append(description).append("]");
            }
            this->ui->locationBox->addItem(it,name);
        }
    }
}

AddEditDeviceForm::~AddEditDeviceForm()
{
    delete ui;
}

void AddEditDeviceForm::addRecord()
{
    this->show();
}

void AddEditDeviceForm::editRecord(QString name)
{
    this->name=name;

    QSqlQuery q;
    q.prepare("select * from urzadzenia where "
              "identyfikator_urzadzenia==:name;");
    q.bindValue(":name",name);

    if(q.exec())
    {
        q.next();
        qDebug()<<q.value(0);
        this->ui->idEdit->setText(q.value(0).toString());
        this->ui->descriptionEdit->clear();
        this->ui->descriptionEdit->appendPlainText(q.value(3).toString());


        int index = this->ui->typeBox->findData(q.value(1).toString());
        if ( index != -1 ) { // -1 for not found
           this->ui->typeBox->setCurrentIndex(index);
        }

        index = this->ui->locationBox->findData(q.value(2).toString());
                if ( index != -1 ) { // -1 for not found
                   this->ui->locationBox->setCurrentIndex(index);
                }



    }
    this->show();
}

void AddEditDeviceForm::on_cancelButton_clicked()
{
    this->close();
}

void AddEditDeviceForm::on_okButton_clicked()
{
    if(this->name.isEmpty())
    {
        QSqlQuery q;
        q.prepare("insert into urzadzenia "
                         "values(:id, :type, :location, :desc);");
        q.bindValue(":id",this->ui->idEdit->text());
        q.bindValue(":type",this->ui->typeBox->itemData(this->ui->typeBox->currentIndex()));
        q.bindValue(":location",this->ui->locationBox->itemData(this->ui->locationBox->currentIndex()));
        q.bindValue(":desc",this->ui->descriptionEdit->toPlainText());


        if(!q.exec())
        {
            QMessageBox::critical(this,"Błąd",q.lastError().text());
        }
        else
        {
            emit(refreshView());
            this->close();
        }
    }
    else
    {
        QSqlQuery q;
        q.prepare("update urzadzenia set"
                  " identyfikator_urzadzenia=:id,"
                  " typ_urzadzenia=:type,"
                  " identyfikator_stanowiska=:location,"
                  " opis=:desc"
                  " where identyfikator_urzadzenia==:name");
        q.bindValue(":id",this->ui->idEdit->text());
        q.bindValue(":type",this->ui->typeBox->itemData(this->ui->typeBox->currentIndex()));
        q.bindValue(":location",this->ui->locationBox->itemData(this->ui->locationBox->currentIndex()));
        q.bindValue(":desc",this->ui->descriptionEdit->toPlainText());
        q.bindValue(":name",this->name);

        if(!q.exec())
        {
            QMessageBox::critical(this,"Błąd",q.lastError().text());
        }
        else
        {
            emit(refreshView());
            this->close();
        }
    }
}
