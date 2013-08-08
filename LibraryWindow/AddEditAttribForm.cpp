#include "AddEditAttribForm.h"
#include "ui_AddEditAttribForm.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include <QDebug>


AddEditAttribForm::AddEditAttribForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEditAttribForm)
{
    ui->setupUi(this);
}

AddEditAttribForm::~AddEditAttribForm()
{
    delete ui;
}
void AddEditAttribForm::addRecord()
{
    this->show();
}

void AddEditAttribForm::editRecord(QString name)
{
    this->name=name;

    qDebug()<<name;

    QSqlQuery q;
    q.prepare("select * from slownik_atrybutow where "
              "nazwa_atrybutu==:name;");
    q.bindValue(":name",name);

    if(q.exec())
    {
        q.next();
        this->ui->nameEdit->setText(q.value(0).toString());
        this->ui->descriptionEdit->clear();
        this->ui->descriptionEdit->appendPlainText(q.value(1).toString());
    }

    //qDebug()<<q.boundValues().value(":nazwa")<<q.lastQuery()<<q.lastError().text();

    this->show();
}

void AddEditAttribForm::on_pushButton_2_clicked()
{
    this->close();
}

void AddEditAttribForm::on_pushButton_clicked()
{
    if(this->name.isEmpty())
    {
        QSqlQuery q;
        q.prepare("insert into slownik_atrybutow "
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
        q.prepare("update  slownik_atrybutow set "
                  "nazwa_atrybutu=:name, opis=:desc where "
                  "nazwa_atrybutu=:n ;");
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
