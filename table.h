#pragma once

#ifndef TABLE_H
#define TABLE_H

#include "database.h"

#include <QStandardItemModel>
#include <QModelIndex>
#include <ui_mainwindow.h>

#include <string>
#include <vector>

using namespace std;

class Table {
public:
    Table();

    static void create(QStandardItemModel *table);
    static void create(QTableWidget *table, int rowsCount, int columnsCount);
    static void update(QTableWidget *model);
    static void deleteRow(QTableWidget *table, int row);
};

#endif // TABLE_H
