#include "databaseitem.h"

DatabaseItem::DatabaseItem(int ID, string title, string type, string features, string isAvailable, string date) {
    this->ID = ID;
    this->title = title;
    this->type = type;
    this->features = features;
    this->isAvailable = isAvailable;
    this->date = date;
}
