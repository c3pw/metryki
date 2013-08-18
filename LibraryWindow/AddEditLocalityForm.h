#ifndef ADDEDITLOCALITYFORM_H
#define ADDEDITLOCALITYFORM_H

#include <QDialog>

namespace Ui {
class AddEditLocalityForm;
}

class AddEditLocalityForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddEditLocalityForm(QWidget *parent = 0);
    ~AddEditLocalityForm();
    void addRecord();
    void editRecord(QString name);
    
private:
    Ui::AddEditLocalityForm *ui;
    QString name;
signals:
    void refreshView();
private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();
};

#endif // ADDEDITLOCALITYFORM_H
