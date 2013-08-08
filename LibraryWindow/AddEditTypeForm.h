#ifndef ADDEDITTYPEFORM_H
#define ADDEDITTYPEFORM_H

#include <QDialog>

namespace Ui {
class AddEditTypeForm;
}

class AddEditTypeForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddEditTypeForm(QWidget *parent = 0);
    ~AddEditTypeForm();
    void addRecord();
    void editRecord(QString name);
    
private slots:
    void on_closeButton_clicked();

    void on_okButton_clicked();

private:
    Ui::AddEditTypeForm *ui;
    QString name;

signals:
    void refreshView();
};

#endif // ADDEDITTYPEFORM_H
