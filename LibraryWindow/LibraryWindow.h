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

    void refreshAttribView();

    void refreshComponentView();

    void on_deleteType_clicked();

    void on_typeTable_doubleClicked(const QModelIndex &index);

    void on_addAttr_clicked();

    void on_editAttr_clicked();

    void on_deleteAttr_clicked();

    void on_attrTable_doubleClicked(const QModelIndex &index);

    void on_addComponent_clicked();

    void on_editComponent_clicked();

    void on_deleteComponent_clicked();

private:
    Ui::LibraryWindow *ui;

    QSqlTableModel  *typeModel;
    QSortFilterProxyModel *typeSortProxy;

    QSqlTableModel  *attrModel;
    QSortFilterProxyModel *attrSortProxy;

    QSqlTableModel  *componentModel;
    QSortFilterProxyModel *componentSortProxy;
};

#endif // LIBRARYWINDOW_H
