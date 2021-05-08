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

    static void create(QStandardItemModel *model);
    static void update(QStandardItemModel *model, Ui::MainWindow* ui);
};

#endif // TABLE_H
