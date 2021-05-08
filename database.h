#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include "databaseitem.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <QDebug>

using namespace std;

class Database {
public:
    Database();

    static int getDataRowsCount();
    static void create(DatabaseItem *item);
    static vector<vector<string>> read();
    static bool find(int id);
};

#endif // DATABASE_H
