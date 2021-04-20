#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <databaseitem.h>
#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTable(QStandardItemModel *model);

    void createDatabase(DatabaseItem *item);

    bool isValueEmpty (QString qstr);
private slots:
    void on_add_item_button_clicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *mainTableModel;
    QStandardItemModel *addItemTableModel;
};
#endif // MAINWINDOW_H
