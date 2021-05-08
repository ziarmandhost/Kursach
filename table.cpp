#include "table.h"

#include <QHBoxLayout>
#include <QPushButton>

void Table::create(QStandardItemModel *model) {
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Title");
    model->setHeaderData(2, Qt::Horizontal, "Type");
    model->setHeaderData(3, Qt::Horizontal, "Special info");
    model->setHeaderData(4, Qt::Horizontal, "Availability");
    model->setHeaderData(5, Qt::Horizontal, "Actions");
}

bool isStringContainNumber(string &line) {
    string NUMBERS = "0123456789";

    for (int x = 0; x < (int)(line.size()); x++) {
        for (int y = 0; y < (int)(NUMBERS.size()); y++) {
            if (NUMBERS[y] == line[x])
                return true;
        }
    }

    return false;
}

void Table::update(QStandardItemModel *model, Ui::MainWindow* ui) {
    int rowsCount = Database::getDataRowsCount();
    model->setRowCount(rowsCount);

    vector<vector<string>> data = Database::read();

    QModelIndex index;
    qDebug() << "DEBUG INFO " << data.size();

    for (int row = 0; row < model->rowCount(); row++) {
        for (int column = 0; column < model->columnCount(); column++) {
            index = model->index(row, column);

            if (column == 4) {
                if (isStringContainNumber(data[row][4]) && stoi(data[row][4]) == 1) model->setData(index, QString::fromStdString("+"));
                else if (isStringContainNumber(data[row][4]) && stoi(data[row][4]) == 0) model->setData(index, QString::fromStdString("-"));
                else model->setData(index, QString::fromStdString(data[row][4]));
            }
            else if (column == 5) {
//                QHBoxLayout *l = new QHBoxLayout();
//                l->addWidget((new QPushButton("I`m in cell")));

//                QWidget *widget = new QWidget();
//                widget->setLayout(l);

//                ui->tableView->setCellWidget(row, 5, widget);
            }
            else model->setData(index, QString::fromStdString(data[row][column]));
        }
    }
}
