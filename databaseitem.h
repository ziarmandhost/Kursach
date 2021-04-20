#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include <QString>
#include <string>
using namespace std;

class DatabaseItem {
    public:
        DatabaseItem(int ID, string title, string type, string features, bool isAvailable);

        int ID;
        string title;
        string type;
        string features;
        bool isAvailable;
};

#endif // DATABASEITEM_H
