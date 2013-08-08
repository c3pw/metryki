#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>

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

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
