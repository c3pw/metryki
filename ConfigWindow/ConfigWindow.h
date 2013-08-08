#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigWindow();
    ~ConfigWindow();
    
private slots:
    void on_closeButton_clicked();

    void on_saveButton_clicked();

    void on_databaseButton_clicked();

    void on_logoButton_clicked();

    void on_mapGraphicButton_clicked();

    void on_mapMetaButton_clicked();

private:
    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
