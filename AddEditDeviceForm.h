#ifndef ADDEDITDEVICE_H
#define ADDEDITDEVICE_H

#include <QDialog>

namespace Ui {
class AddEditDeviceForm;
}

class AddEditDeviceForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddEditDeviceForm(QWidget *parent = 0);
    ~AddEditDeviceForm();
    void addRecord();
    void editRecord(QString name);
    
private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::AddEditDeviceForm *ui;
    QString name;

signals:
    void refreshView();
};

#endif // ADDEDITDEVICE_H
