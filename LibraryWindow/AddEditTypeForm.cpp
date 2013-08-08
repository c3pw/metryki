#include "AddEditTypeForm.h"
#include "ui_AddEditTypeForm.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include <QDebug>

AddEditTypeForm::AddEditTypeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditTypeForm)
{
    ui->setupUi(this);
    this->name="";
}
AddEditTypeForm::~AddEditTypeForm()
{
    delete ui;
}
void AddEditTypeForm::addRecord()
{
    this->show();
}
void AddEditTypeForm::editRecord(QString name)
{
    this->name=name;

    QSqlQuery q;
    q.prepare("select * from slownik_typow where nazwa==:name;");
    q.bindValue(":name",name);
    if(q.exec())
    {
        q.next();
        this->ui->nameEdit->setText(q.value(0).toString());
        this->ui->descriptionEdit->clear();
        this->ui->descriptionEdit->appendPlainText(q.value(1).toString());
    }


    this->show();
}

void AddEditTypeForm::on_closeButton_clicked()
{
    this->close();
}

void AddEditTypeForm::on_okButton_clicked()
{
    if(this->name.isEmpty())
    {
        QSqlQuery q;
        q.prepare("insert into slownik_typow "
                         "values(:name, :desc);");
        q.bindValue(":name",this->ui->nameEdit->text());
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
        q.prepare("update slownik_typow set nazwa=:name, opis=:desc where nazwa=:n;");
        q.bindValue(":name",this->ui->nameEdit->text());
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
