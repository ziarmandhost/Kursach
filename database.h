#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>

#include <QDebug>
#include <QFile>

using namespace std;

class Database {
public:
    Database();

    static int getDataRowsCount();
    static void create(DatabaseItem *item);
    static vector<vector<string>> read();
    static bool find(int id);
    static void updateRow(int rowId, DatabaseItem *item);
    static void deleteRow(int row);

    static void import(string path);
    static void exportBase(string path);

    static string getCurrentTimt();
};

#endif // DATABASE_H
