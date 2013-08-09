#include "AddEditComponentForm.h"
#include "ui_AddEditComponentForm.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

AddEditComponentForm::AddEditComponentForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditComponentForm)
{
    ui->setupUi(this);
}

AddEditComponentForm::~AddEditComponentForm()
{
    delete ui;
}
void AddEditComponentForm::addRecord()
{
    this->show();
}

void AddEditComponentForm::editRecord(QString name)
{
    this->name = name;
    this->ui->nameEdit->setText(name);
    this->show();
}

void AddEditComponentForm::on_cancelButton_clicked()
{
    this->close();
}

void AddEditComponentForm::on_okButton_clicked()
{
    if(this->name.isEmpty())
    {
        QSqlQuery q;
        q.prepare("insert into slownik_podzespolow "
                         "values(:name);");
        q.bindValue(":name",this->ui->nameEdit->text());
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
        q.prepare("update  slownik_podzespolow set "
                  "nazwa=:name where "
                  "nazwa=:n ;");
        q.bindValue(":name",this->ui->nameEdit->text());
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
