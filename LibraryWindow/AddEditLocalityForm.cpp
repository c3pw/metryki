#include "AddEditLocalityForm.h"
#include "ui_AddEditLocalityForm.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>



AddEditLocalityForm::AddEditLocalityForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditLocalityForm)
{
    ui->setupUi(this);
}

AddEditLocalityForm::~AddEditLocalityForm()
{
    delete ui;
}

void AddEditLocalityForm::addRecord()
{
    this->show();
}

void AddEditLocalityForm::editRecord(QString name)
{
    this->name=name;

    QSqlQuery q;
    q.prepare("select * from slownik_stanowisk where identyfikator_stanowiska==:name;");
    q.bindValue(":name",name);
    if(q.exec())
    {
        q.next();
        this->ui->nameEdit->setText(q.value(0).toString());
        this->ui->locationEdit->setText(q.value(1).toString());
        this->ui->descriptionEdit->clear();
        this->ui->descriptionEdit->appendPlainText(q.value(2).toString());
    }


    this->show();
}

void AddEditLocalityForm::on_cancelButton_clicked()
{
    this->close();
}

void AddEditLocalityForm::on_okButton_clicked()
{
    if(this->name.isEmpty())
    {
        QSqlQuery q;
        q.prepare("insert into slownik_stanowisk "
                         "values(:name, :locality, :desc);");
        q.bindValue(":name",this->ui->nameEdit->text());
        q.bindValue(":locality",this->ui->locationEdit->text());
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
        q.prepare("update slownik_stanowisk set identyfikator_stanowiska=:name, lokalizacja_stanowiska=:locality, opis_stanowiska=:desc where identyfikator_stanowiska=:n;");
        q.bindValue(":name",this->ui->nameEdit->text());
        q.bindValue(":locality",this->ui->locationEdit->text());
        q.bindValue(":desc",this->ui->descriptionEdit->toPlainText());
        q.bindValue(":n",this->name);
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
