#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include "table.h"

#include <QMessageBox>
#include <QDebug>
#include <QMainWindow>
#include <QTableWidget>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_item_button_clicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *addItemTableModel;

};
#endif // MAINWINDOW_H
