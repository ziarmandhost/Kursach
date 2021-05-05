#include "databaseitem.h"

#include <QStandardItemModel>
#include <fstream>
#include <sstream>

class Database {
public:
    static void createTable(QStandardItemModel *model) {
        // Меняем заголовок
        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "Title");
        model->setHeaderData(2, Qt::Horizontal, "Type");
        model->setHeaderData(3, Qt::Horizontal, "Special info");
        model->setHeaderData(4, Qt::Horizontal, "Availability");
    }

    static int getDataRowsCountFromDatabase() {
        int rows = 0;

        ifstream DATABASE("database.csv");
        string line;

        while (getline(DATABASE, line)) {
            rows++;
        }

        return rows;
    }

    static vector<vector<string>> readDataFromDatabase() {
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


    static void updateTable(QStandardItemModel *model) {
        int rowsCount = Database::getDataRowsCountFromDatabase();
        model->setRowCount(rowsCount);

        vector<vector<string>> data = Database::readDataFromDatabase();

        QModelIndex index;
        qDebug() << "DEBUG INFO " << data.size();

        for (int row = 0; row < model->rowCount(); row++) {
            for (int column = 0; column < model->columnCount(); column++) {
                index = model->index(row, column);

                qDebug() << "ROW : " << row << " COLUMN : " << column << "\n";
                model->setData(index, QString::fromStdString(data[row][column]));
            }
        }
    }

    static void createDatabase(DatabaseItem *item) {
        fstream DATABASE;
        DATABASE.open("database.csv", ios::out | ios::app);

        DATABASE << item->ID << ","
                 << '\"' << item->title << '\"' << ","
                 << '\"' << item->type << '\"' << ","
                 << '\"' << item->features << '\"' << ","
                 << item->isAvailable << '\n';

        DATABASE.close();
    }
};
