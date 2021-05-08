#include "database.h"

int Database::getDataRowsCount() {
    int rows = 0;

    ifstream DATABASE("database.csv");
    string line;

    while (getline(DATABASE, line)) {
        rows++;
    }

    return rows;
}

void Database::create(DatabaseItem *item) {
    fstream DATABASE;
    DATABASE.open("database.csv", ios::out | ios::app);

    DATABASE << item->ID << ","
             << '\"' << item->title << '\"' << ","
             << '\"' << item->type << '\"' << ","
             << '\"' << item->features << '\"' << ","
             << item->isAvailable << '\n';

    DATABASE.close();
}

vector<vector<string>> Database::read() {
    ifstream DATABASE("database.csv");

           vector<string> row;
           int l = 0;
           string line, word, temp;

           vector<vector<string>> data;

           while (DATABASE) {
               l++;
               string s;

               if (!getline(DATABASE, s)) break;

               if (s[0] != '#') {
                   istringstream ss(s);
                   vector<string> record;

                   while (ss) {
                       string line;

                       if (!getline(ss, line, ',')) break;

                       try {
                           record.push_back(line);
                       }
                       catch (const std::invalid_argument e) {
                           qDebug() << "NaN found in file " << " line " << l;
                       }
                   }

                   data.push_back(record);
               }
           }

           if (!DATABASE.eof())
               qDebug() << "Could not read file " << "\n";

           return data;
}

bool Database::find(int id) {
    vector<vector<string>> data = Database::read();

    auto dataIterator = data.begin();
    bool isInDatabaseRow = false;

    while(dataIterator != data.end()) {
        vector<string> row = *dataIterator;

        if (stoi(row[0]) == id) {
            isInDatabaseRow = true;
            break;
        }

        ++dataIterator;
    }

    return isInDatabaseRow;
}