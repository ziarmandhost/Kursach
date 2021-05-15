#include "databaseitem.h"

DatabaseItem::DatabaseItem(int ID, string title, string type, string features, string isAvailable, string date) {
    this->ID = ID;
    this->title = title;
    this->traffic = type;
    this->endOfTerm = features;
    this->costPerMonth = isAvailable;
    this->date = date;
}
