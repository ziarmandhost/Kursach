#include "table.h"

void Table::create(QStandardItemModel *model) {
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Title");
    model->setHeaderData(2, Qt::Horizontal, "Traffic");
    model->setHeaderData(3, Qt::Horizontal, "End of term");
    model->setHeaderData(4, Qt::Horizontal, "Cost per month");
}

void Table::create(QTableWidget *table, int rowsCount, int columnsCount) {
    table->setRowCount(rowsCount);
    table->setColumnCount(columnsCount);

    QStringList labels;
    labels << "ID" << "Title" << "Traffic" << "End of term" << "Cost per month" << "Edited date" << "Actions";
    table->setHorizontalHeaderLabels(labels);

    // Table params
    table->setShowGrid(true);
    table->setSortingEnabled(true);
    table->setCornerButtonEnabled(true);
    table->setAlternatingRowColors(true);

    table->horizontalHeader()->setVisible(true);
    table->horizontalHeader()->setDefaultSectionSize(100);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Cell
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Table::update(QTableWidget *table, Ui::MainWindow *ui) {
    int rowsCount = Database::getDataRowsCount();
    table->setRowCount(rowsCount);

    vector<vector<string>> data = Database::read();

    for (int row = 0; row < table->rowCount(); row++) {
        QTableWidgetItem *item;
        for (int column = 0; column < table->columnCount(); column++) {
            item = new QTableWidgetItem();

            if (column == 6) {
                QPushButton *saveBtn = new QPushButton("Save");
                QPushButton *deleteBtn = new QPushButton("Delete");

                QHBoxLayout *layout = new QHBoxLayout();
                layout->addWidget(saveBtn);
                layout->addWidget(deleteBtn);

                QWidget *widget = new QWidget();
                widget->setLayout(layout);

                table->setCellWidget(row, 6, widget);

                // Delete
                QAbstractButton::connect(deleteBtn, &QPushButton::clicked, deleteBtn, [ui, table, row]() {
                    Table::deleteRow(table, row);
                    ui->statusbar->showMessage("Last action: row sucessfully deleted from database");
                });

                // Save
                QAbstractButton::connect(saveBtn, &QPushButton::clicked, saveBtn, [ui, row]() {
                    int id = ui->tableWidget->model()->index(row, 0).data().toInt();
                    string title = ui->tableWidget->model()->index(row, 1).data().toString().toStdString();
                    string type = ui->tableWidget->model()->index(row, 2).data().toString().toStdString();
                    string specialInfo = ui->tableWidget->model()->index(row, 3).data().toString().toStdString();
                    string avalability = ui->tableWidget->model()->index(row, 4).data().toString().toStdString();
                    string updated = Database::getCurrentTime();

                    DatabaseItem *newItem = new DatabaseItem(id, title, type, specialInfo, avalability, updated);
                    Database::updateRow(row, newItem);

                    auto tableModel = ui->tableWidget->model();
                    tableModel->setData(tableModel->index(row, 5), QString::fromStdString(updated));

                    ui->statusbar->showMessage("Last action: row sucessfully saved to database");
                });
            }
            else {
                string cell = data[row][column];
                if (cell[0] == '\"' && cell[cell.length() - 1] == '\"')
                    cell = cell.substr(1, cell.size() - 2);

                item->setText(QString::fromStdString(cell));
            }

            table->setItem(row, column, item);
        }

        table->setRowHeight(row, 40);
    }
}

void Table::deleteRow(QTableWidget *table, int row) {
    Database::deleteRow(row);
    table->removeRow(row);
}

void Table::updateWithData(Ui::MainWindow *ui, vector<vector<string>> newData) {
    int rowsCount = newData.size();
    ui->tableWidget->setRowCount(rowsCount);

    for (int row = 0; row < rowsCount; row++) {
        QTableWidgetItem *item;
        for (int column = 0; column < (int)newData[row].size(); column++) {
            item = new QTableWidgetItem();

            if (column == 6) {
                QPushButton *saveBtn = new QPushButton("Save");
                QPushButton *deleteBtn = new QPushButton("Delete");

                QHBoxLayout *layout = new QHBoxLayout();
                layout->addWidget(saveBtn);
                layout->addWidget(deleteBtn);

                QWidget *widget = new QWidget();
                widget->setLayout(layout);

                ui->tableWidget->setCellWidget(row, 6, widget);

                // Delete
                QAbstractButton::connect(deleteBtn, &QPushButton::clicked, deleteBtn, [ui, row]() {
                    Table::deleteRow(ui->tableWidget, row);
                    ui->statusbar->showMessage("Last action: row sucessfully deleted from database");
                });

                // Save
                QAbstractButton::connect(saveBtn, &QPushButton::clicked, saveBtn, [ui, row]() {
                    int id = ui->tableWidget->model()->index(row, 0).data().toInt();
                    string title = ui->tableWidget->model()->index(row, 1).data().toString().toStdString();
                    string type = ui->tableWidget->model()->index(row, 2).data().toString().toStdString();
                    string specialInfo = ui->tableWidget->model()->index(row, 3).data().toString().toStdString();
                    string avalability = ui->tableWidget->model()->index(row, 4).data().toString().toStdString();
                    string updated = Database::getCurrentTime();

                    DatabaseItem *newItem = new DatabaseItem(id, title, type, specialInfo, avalability, updated);
                    Database::updateRow(row, newItem);

                    auto tableModel = ui->tableWidget->model();
                    tableModel->setData(tableModel->index(row, 5), QString::fromStdString(updated));

                    ui->statusbar->showMessage("Last action: row sucessfully saved to database");
                });
            }
            else {
                string cell = newData[row][column];
                if (cell[0] == '\"' && cell[cell.length() - 1] == '\"')
                    cell = cell.substr(1, cell.size() - 2);

                item->setText(QString::fromStdString(cell));
            }

            ui->tableWidget->setItem(row, column, item);
        }

        ui->tableWidget->setRowHeight(row, 40);
    }
}

void Table::searchInTable(Ui::MainWindow *ui) {
    QString searchValue = ui->line_edit->text();
    vector<vector<string>> resultTable;

    if (searchValue.length() > 1) {
        vector<vector<string>> data = Database::read();

        for (int i = 0; i < (int)data.size(); i++) {
            string titleInData = QString(data[i][1].c_str()).toLower().toStdString();
            string needle = searchValue.toLower().toStdString();

            if (titleInData.find(needle) != string::npos) {
                resultTable.push_back(data[i]);
            }
        }
    }

    if (resultTable.size() > 0) Table::updateWithData(ui, resultTable);
    else Table::update(ui->tableWidget, ui);
}

void Table::filterByCostAndEndOfTerm(Ui::MainWindow *ui) {
    vector<vector<string>> data = Database::read();

    for (int i = 1; i < (int)data.size(); i++) {
        vector<string> prev = data[i - 1];
        vector<string> that = data[i];

        if (stoi(that[4]) < stoi(prev[4])) {
            iter_swap(data.begin() + i, data.begin() + i - 1);
        }
    }

    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    int currentYear = timePtr->tm_year + 1900;

    vector<vector<string>> newData;
    for (int i = 0; i < (int)data.size(); i++) {
        QStringList date = QString::fromStdString(data[i][3]).split(".");

        if (stoi(date.at(2).toStdString()) == currentYear) newData.push_back(data[i]);
    }

    Table::updateWithData(ui, newData);
}

void Table::filterByASCTitleAndEditTime(Ui::MainWindow *ui) {
    vector<vector<string>> data = Database::read();

    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    int currentYear = timePtr->tm_year + 1900;
    int currentMonth = timePtr->tm_mon + 1;

    vector<vector<string>> newData;
    for (int i = 0; i < (int)data.size(); i++) {
        QStringList date = QString::fromStdString(data[i][5]).split(" ");
        int year = date.at(0).split("-").at(2).toInt();
        int month = date.at(0).split("-").at(1).toInt();

        if (year == currentYear && currentMonth - 3 <= month && month <= currentMonth) newData.push_back(data[i]);
    }

    for (int i = 1; i < (int)newData.size(); i++) {
        vector<string> prev = newData[i - 1];
        vector<string> that = newData[i];

        if (that[1] < prev[1]) {
            iter_swap(newData.begin() + i, newData.begin() + i - 1);
        }
    }

    Table::updateWithData(ui, newData);
}

void Table::filterByASCTitleAndCost(Ui::MainWindow *ui) {
    vector<vector<string>> data = Database::read();
    vector<vector<string>> newData;

    int sum = 0;
    double average = 0;

    for (int i = 0; i < (int)data.size(); i++) sum += stoi(data[i][4]);

    average = (double)sum / (double)data.size();

    for (int i = 0; i < (int)data.size(); i++)
        if (stoi(data[i][4]) >= average) newData.push_back(data[i]);

    for (int i = 1; i < (int)newData.size(); i++) {
        vector<string> prev = newData[i - 1];
        vector<string> that = newData[i];

        if (that[1] < prev[1]) {
            iter_swap(newData.begin() + i, newData.begin() + i - 1);
        }
    }

    Table::updateWithData(ui, newData);
}

















