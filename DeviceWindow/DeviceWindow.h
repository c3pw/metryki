#ifndef DEVICEWINDOW_H
#define DEVICEWINDOW_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

namespace Ui {
class DeviceWindow;
}

class DeviceWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit DeviceWindow(QWidget *parent = 0);
    ~DeviceWindow();
    void showDevice(QString name);
    
private slots:
    void on_closeButton_clicked();

private:
    Ui::DeviceWindow *ui;
    QString name;

    QSqlQueryModel  *attrModel;
    QSortFilterProxyModel *attrSortProxy;
};

#endif // DEVICEWINDOW_H
