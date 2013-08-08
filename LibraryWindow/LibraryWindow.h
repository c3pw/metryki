#ifndef LIBRARYWINDOW_H
#define LIBRARYWINDOW_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
class LibraryWindow;
}

class LibraryWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit LibraryWindow(QWidget *parent = 0);
    ~LibraryWindow();
    
private slots:
    void on_addType_clicked();

    void on_editType_clicked();
    void refreshTypeView();

    void on_deleteType_clicked();

    void on_typeTable_doubleClicked(const QModelIndex &index);

private:
    Ui::LibraryWindow *ui;

    QSqlTableModel  *typeModel;
    QSortFilterProxyModel *typeSortProxy;
};

#endif // LIBRARYWINDOW_H
