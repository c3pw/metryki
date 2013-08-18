#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_4_clicked();

    void on_commandLinkButton_2_clicked();

    void on_commandLinkButton_clicked();

    void on_addDeviceButton_clicked();

    void refreshDeviceView();

    void on_editDeviceButton_clicked();

    void on_deleteDeviceButton_clicked();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);

    QSqlQueryModel *deviceModel;
    QSortFilterProxyModel *deviceSortProxy;
};

#endif // MAINWINDOW_H
