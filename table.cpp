#include "table.h"

void Table::create(QStandardItemModel *model) {
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Title");
    model->setHeaderData(2, Qt::Horizontal, "Type");
    model->setHeaderData(3, Qt::Horizontal, "Special info");
    model->setHeaderData(4, Qt::Horizontal, "Availability");
}

void Table::create(QTableWidget *table, int rowsCount, int columnsCount) {
    table->setRowCount(rowsCount);
    table->setColumnCount(columnsCount);

    QStringList labels;
    labels << "ID" << "Title" << "Type" << "Special info" << "Availability" << "Created date" << "Actions";
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
                QAbstractButton::connect(deleteBtn, &QPushButton::clicked, deleteBtn, [table, row]() {
                    Table::deleteRow(table, row);
                });

                // Save
                QAbstractButton::connect(saveBtn, &QPushButton::clicked, saveBtn, [ui, item, row]() {
                    int id = ui->tableWidget->model()->index(row, 0).data().toInt();
                    string title = ui->tableWidget->model()->index(row, 1).data().toString().toStdString();
                    string type = ui->tableWidget->model()->index(row, 2).data().toString().toStdString();
                    string specialInfo = ui->tableWidget->model()->index(row, 3).data().toString().toStdString();
                    string avalability = ui->tableWidget->model()->index(row, 4).data().toString().toStdString();
                    string updated = Database::getCurrentTimt();

                    DatabaseItem *newItem = new DatabaseItem(id, title, type, specialInfo, avalability, updated);
                    Database::updateRow(row, newItem);

                    auto tableModel = ui->tableWidget->model();
                    tableModel->setData(tableModel->index(row, 5), QString::fromStdString(updated));
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
