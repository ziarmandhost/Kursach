#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void createTable(Ui::MainWindow *ui, QStandardItemModel *model);

private:
    Ui::MainWindow *ui;

    QStandardItemModel *mainTableModel;
    QStandardItemModel *addItemTableModel;
};
#endif // MAINWINDOW_H
