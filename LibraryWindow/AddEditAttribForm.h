#ifndef ADDEDITATTRIBFORM_H
#define ADDEDITATTRIBFORM_H

#include <QDialog>

namespace Ui {
class AddEditAttribForm;
}

class AddEditAttribForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddEditAttribForm(QWidget *parent = 0);
    void addRecord();
    void editRecord(QString name);
    ~AddEditAttribForm();
    
private:
    Ui::AddEditAttribForm *ui;
    QString name;
signals:
    void refreshView();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // ADDEDITATTRIBFORM_H
