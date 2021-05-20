#pragma once

#ifndef TABLE_H
#define TABLE_H

#include "database.h"

#include <QStandardItemModel>
#include <QModelIndex>
#include <ui_mainwindow.h>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QMainWindow>

#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Table {
public:
    Table();

    static void create(QStandardItemModel *table);
    static void create(QTableWidget *table, int rowsCount, int columnsCount);
    static void update(QTableWidget *model, Ui::MainWindow *ui);
    static void deleteRow(QTableWidget *table, int row);
    static void searchInTable(Ui::MainWindow *ui);

    static void updateWithData(Ui::MainWindow *ui, vector<vector<string>> newData);

    static void filterByCostAndEndOfTerm(Ui::MainWindow *ui);
    static void filterByASCTitleAndEditTime(Ui::MainWindow *ui);
    static void filterByASCTitleAndCost(Ui::MainWindow *ui);
};

#endif // TABLE_H
