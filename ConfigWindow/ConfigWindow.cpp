#include "ConfigWindow.h"
#include "ui_ConfigWindow.h"

#include <QSettings>
#include <QFileDialog>

ConfigWindow::ConfigWindow() :
    QDialog(),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    QSettings s;
    this->ui->databaseLineEdit->setText(s.value("database/path").toString());
    this->ui->headerEdit->setPlainText(s.value("header/html").toString());
    this->ui->logoLineEdit->setText(s.value("header/path").toString());
    this->ui->mapGrapgicEdit->setText(s.value("map/graphPath").toString());
    this->ui->mapMetaEdit->setText(s.value("map/metaPath").toString());

}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::on_closeButton_clicked()
{
    this->close();
}

void ConfigWindow::on_saveButton_clicked()
{
    QSettings s;
    s.setValue("database/path",this->ui->databaseLineEdit->text());
    s.setValue("header/html",this->ui->headerEdit->toPlainText());
    s.setValue("header/path",this->ui->logoLineEdit->text());
    s.setValue("map/graphPath",this->ui->mapGrapgicEdit->text());
    s.setValue("map/metaPath",this->ui->mapMetaEdit->text());
    this->close();
}

void ConfigWindow::on_databaseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Wybierz plik bazy danych"), "", tr("SQLITE Database (*.sqlite)"));
    if(!fileName.isEmpty() && !fileName.isNull())
    {
        this->ui->databaseLineEdit->setText(fileName);
    }
}

void ConfigWindow::on_logoButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Wybierz plik graficzny"), "", tr("SQLITE Database (*.png *.jpeg *.jpg *.gif *.bmp)"));
    if(!fileName.isEmpty() && !fileName.isNull())
    {
        this->ui->logoLineEdit->setText(fileName);
    }
}

void ConfigWindow::on_mapGraphicButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Wybierz plik graficzny"), "", tr("SQLITE Database (*.png *.jpeg *.jpg *.gif *.bmp)"));
    if(!fileName.isEmpty() && !fileName.isNull())
    {
        this->ui->mapGrapgicEdit->setText(fileName);
    }
}

void ConfigWindow::on_mapMetaButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Wybierz plik metadanych"), "", tr("SQLITE Database (*.xml)"));
    if(!fileName.isEmpty() && !fileName.isNull())
    {
        this->ui->mapMetaEdit->setText(fileName);
    }
}
