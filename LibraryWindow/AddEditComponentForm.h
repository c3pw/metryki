#ifndef ADDEDITCOMPONENTFORM_H
#define ADDEDITCOMPONENTFORM_H

#include <QDialog>

namespace Ui {
class AddEditComponentForm;
}

class AddEditComponentForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddEditComponentForm(QWidget *parent = 0);
    ~AddEditComponentForm();
    void addRecord();
    void editRecord(QString name);
signals:
    void refreshView();
private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::AddEditComponentForm *ui;
    QString name;
};

#endif // ADDEDITCOMPONENTFORM_H
