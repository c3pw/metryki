#include "LibraryWindow.h"
#include "ui_LibraryWindow.h"

#include "AddEditTypeForm.h"

#include <QModelIndexList>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

LibraryWindow::LibraryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibraryWindow)
{
    ui->setupUi(this);

    this->typeModel = new QSqlTableModel();
    this->typeModel->setTable("slownik_typow");
    this->typeSortProxy = new QSortFilterProxyModel();
    this->typeSortProxy->setSourceModel(this->typeModel);
    this->typeSortProxy->sort(0);
    this->ui->typeTable->setModel(this->typeSortProxy);
    this->typeModel->select();
    this->ui->typeTable->resizeColumnsToContents();
    this->ui->typeTable->horizontalHeader()->setStretchLastSection(true);


}

LibraryWindow::~LibraryWindow()
{
    delete ui;

    delete this->typeSortProxy;
    delete this->typeModel;
}

void LibraryWindow::on_addType_clicked()
{
    AddEditTypeForm *w = new AddEditTypeForm();
    this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshTypeView()));
    w->addRecord();
}

void LibraryWindow::on_editType_clicked()
{
    AddEditTypeForm *w = new AddEditTypeForm();
    this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshTypeView()));
    w->editRecord(this->typeSortProxy->mapToSource(this->ui->typeTable->selectionModel()->selectedRows().at(0)).data().toString());

}
void LibraryWindow::refreshTypeView()
{
    this->typeModel->select();
}

void LibraryWindow::on_deleteType_clicked()
{
    int result = QMessageBox::question(this,tr("Usunięcie"),tr("Czy usunąć zaznaczony rekord?"),QMessageBox::Ok,QMessageBox::Cancel);
    if(result == QMessageBox::Ok)
    {
        QSqlQuery q;
        q.prepare("delete from slownik_typow where nazwa=:name");
        q.bindValue(":name",this->typeSortProxy->mapToSource(this->ui->typeTable->selectionModel()->selectedRows().at(0)).data().toString() );
        if(!q.exec())
        {
            QMessageBox::critical(this,"Błąd",q.lastError().text());
        }
        else
        {
            this->refreshTypeView();
        }
    }
}











void LibraryWindow::on_typeTable_doubleClicked(const QModelIndex &index)
{
    this->on_editType_clicked();
}
