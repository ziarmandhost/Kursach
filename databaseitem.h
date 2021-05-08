#pragma once

#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include <string>

using namespace std;

class DatabaseItem {
public:
    DatabaseItem(int ID, string title, string type, string features, string isAvailable, string date);

public:
        int ID;
        string title;
        string type;
        string features;
        string isAvailable;
        string date;
};

#endif // DATABASEITEM_H
