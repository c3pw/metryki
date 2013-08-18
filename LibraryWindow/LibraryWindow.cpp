#include "LibraryWindow.h"
#include "ui_LibraryWindow.h"

#include "AddEditTypeForm.h"
#include "AddEditAttribForm.h"
#include "AddEditComponentForm.h"
#include "AddEditLocalityForm.h"
#include "AddEditLocalityForm.h"

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


    this->attrModel = new QSqlTableModel();
    this->attrModel->setTable("slownik_atrybutow");
    this->attrModel->setHeaderData(0,Qt::Horizontal,tr("nazwa"));
    this->attrSortProxy = new QSortFilterProxyModel();
    this->attrSortProxy->setSourceModel(this->attrModel);
    this->attrSortProxy->sort(0);
    this->ui->attrTable->setModel(this->attrSortProxy);
    this->attrModel->select();
    this->ui->attrTable->resizeColumnsToContents();
    this->ui->attrTable->horizontalHeader()->setStretchLastSection(true);


    this->componentModel = new QSqlTableModel();
    this->componentModel->setTable("slownik_podzespolow");
    this->componentSortProxy = new QSortFilterProxyModel();
    this->componentSortProxy->setSourceModel(this->componentModel);
    this->componentSortProxy->sort(0);
    this->ui->componentTable->setModel(this->componentSortProxy);
    this->componentModel->select();
    this->ui->componentTable->resizeColumnsToContents();
    this->ui->componentTable->horizontalHeader()->setStretchLastSection(true);

    this->localityModel = new QSqlTableModel();
    this->localityModel->setTable("slownik_stanowisk");
    this->localitySortProxy = new QSortFilterProxyModel();
    this->localitySortProxy->setSourceModel(this->localityModel);
    this->localitySortProxy->sort(0);
    this->ui->localityTable->setModel(this->localitySortProxy);
    this->localityModel->select();
    this->ui->localityTable->resizeColumnsToContents();
    this->ui->localityTable->horizontalHeader()->setStretchLastSection(true);
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
    if(!this->ui->typeTable->selectionModel()->selectedRows().isEmpty())
    {
        AddEditTypeForm *w = new AddEditTypeForm();
        this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshTypeView()));
        w->editRecord(this->typeSortProxy->mapToSource(this->ui->typeTable->selectionModel()->selectedRows().at(0)).data().toString());
    }

}
void LibraryWindow::refreshTypeView()
{
    this->typeModel->select();
    this->ui->typeTable->resizeColumnsToContents();
    this->ui->typeTable->horizontalHeader()->setStretchLastSection(true);
}

void LibraryWindow::on_deleteType_clicked()
{
    if(!this->ui->typeTable->selectionModel()->selectedRows().isEmpty())
    {
        int result = QMessageBox::question(this,tr("Usunięcie"),tr("Czy usunąć zaznaczony rekord?"),QMessageBox::Ok,QMessageBox::Cancel);
        if(result == QMessageBox::Ok)
        {
            QSqlQuery q;
            q.prepare("delete from slownik_typow where nazwa=:name");
            q.bindValue(":name",this->typeSortProxy->mapToSource(this->ui->typeTable->selectionModel()->selectedRows().at(0)).data().toString() );
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
                this->refreshTypeView();
            }
        }
    }
}






void LibraryWindow::refreshAttribView()
{
    this->attrModel->select();
    this->ui->attrTable->resizeColumnsToContents();
    this->ui->attrTable->horizontalHeader()->setStretchLastSection(true);
}




void LibraryWindow::on_typeTable_doubleClicked(const QModelIndex &index)
{
    this->on_editType_clicked();
}

void LibraryWindow::on_addAttr_clicked()
{
    AddEditAttribForm *w = new AddEditAttribForm();
    this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshAttribView()));
    w->addRecord();
}

void LibraryWindow::on_editAttr_clicked()
{
    if(!this->ui->attrTable->selectionModel()->selectedRows().isEmpty())
    {
        AddEditAttribForm *w = new AddEditAttribForm();
        this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshAttribView()));
        w->editRecord(this->attrSortProxy->mapToSource(this->ui->attrTable->selectionModel()->selectedRows().at(0)).data().toString());
    }
}

void LibraryWindow::on_deleteAttr_clicked()
{
    if(!this->ui->attrTable->selectionModel()->selectedRows().isEmpty())
    {
        int result = QMessageBox::question(this,tr("Usunięcie"),tr("Czy usunąć zaznaczony rekord?"),QMessageBox::Ok,QMessageBox::Cancel);
        if(result == QMessageBox::Ok)
        {
            QSqlQuery q;
            q.prepare("delete from slownik_atrybutow where nazwa_atrybutu=:name");
            q.bindValue(":name",this->attrSortProxy->mapToSource(this->ui->attrTable->selectionModel()->selectedRows().at(0)).data().toString() );
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
                this->refreshAttribView();
            }
        }
    }
}

void LibraryWindow::on_attrTable_doubleClicked(const QModelIndex &index)
{
    this->on_editAttr_clicked();
}

void LibraryWindow::refreshComponentView()
{
    this->componentModel->select();
    this->ui->componentTable->resizeColumnsToContents();
    this->ui->componentTable->horizontalHeader()->setStretchLastSection(true);
}


void LibraryWindow::on_addComponent_clicked()
{
    AddEditComponentForm *w = new AddEditComponentForm();
    this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshComponentView()));
    w->addRecord();
}

void LibraryWindow::on_editComponent_clicked()
{
    if(!this->ui->componentTable->selectionModel()->selectedRows().isEmpty())
    {
        AddEditComponentForm *w = new AddEditComponentForm();
        this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshComponentView()));
        w->editRecord(this->componentSortProxy->mapToSource(this->ui->componentTable->selectionModel()->selectedRows().at(0)).data().toString());
    }
}

void LibraryWindow::on_deleteComponent_clicked()
{
    if(!this->ui->componentTable->selectionModel()->selectedRows().isEmpty())
    {
        int result = QMessageBox::question(this,tr("Usunięcie"),tr("Czy usunąć zaznaczony rekord?"),QMessageBox::Ok,QMessageBox::Cancel);
        if(result == QMessageBox::Ok)
        {
            QSqlQuery q;
            q.prepare("delete from slownik_podzespolow where nazwa=:name");
            q.bindValue(":name",this->componentSortProxy->mapToSource(this->ui->componentTable->selectionModel()->selectedRows().at(0)).data().toString() );
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
                this->refreshComponentView();
            }
        }
    }
}

void LibraryWindow::on_addLocality_clicked()
{
    AddEditLocalityForm *w = new AddEditLocalityForm();
    this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshLocalityView()));
    w->addRecord();
}

void LibraryWindow::refreshLocalityView()
{
    this->localityModel->select();
    this->ui->localityTable->resizeColumnsToContents();
    this->ui->localityTable->horizontalHeader()->setStretchLastSection(true);
}

void LibraryWindow::on_editLocality_clicked()
{
    if(!this->ui->localityTable->selectionModel()->selectedRows().isEmpty())
    {
        AddEditLocalityForm *w = new AddEditLocalityForm();
        this->connect(w,SIGNAL(refreshView()),this,SLOT(refreshLocalityView()));
        w->editRecord(this->localitySortProxy->mapToSource(this->ui->localityTable->selectionModel()->selectedRows().at(0)).data().toString());
    }
}

void LibraryWindow::on_localityTable_doubleClicked(const QModelIndex &index)
{
    this->on_editLocality_clicked();
}

void LibraryWindow::on_deleteLocality_clicked()
{
    if(!this->ui->localityTable->selectionModel()->selectedRows().isEmpty())
    {
        int result = QMessageBox::question(this,tr("Usunięcie"),tr("Czy usunąć zaznaczony rekord?"),QMessageBox::Ok,QMessageBox::Cancel);
        if(result == QMessageBox::Ok)
        {
            QSqlQuery q;
            q.prepare("delete from slownik_stanowisk where identyfikator_stanowiska=:name");
            q.bindValue(":name",this->localitySortProxy->mapToSource(this->ui->localityTable->selectionModel()->selectedRows().at(0)).data().toString() );
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
                this->refreshLocalityView();
            }
        }
    }
}
