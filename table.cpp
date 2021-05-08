#include "table.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>

void Table::create(QStandardItemModel *model) {
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Title");
    model->setHeaderData(2, Qt::Horizontal, "Type");
    model->setHeaderData(3, Qt::Horizontal, "Special info");
    model->setHeaderData(4, Qt::Horizontal, "Availability");
    model->setHeaderData(5, Qt::Horizontal, "Actions");
}

void Table::create(QTableWidget *table, int rowsCount, int columnsCount) {
    table->setRowCount(rowsCount);
    table->setColumnCount(columnsCount);

    QStringList labels;
    labels << "ID" << "Title" << "Type" << "Special info" << "Availability" << "Actions";
    table->setHorizontalHeaderLabels(labels);

    // Table params
    table->setShowGrid(true);
    table->setSortingEnabled(true);
    table->setCornerButtonEnabled(true);
    table->setAlternatingRowColors(true);

    table->horizontalHeader()->setVisible(true);
    table->horizontalHeader()->setDefaultSectionSize(150);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Cell
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void Table::update(QTableWidget *table) {
    int rowsCount = Database::getDataRowsCount();
    table->setRowCount(rowsCount);

    vector<vector<string>> data = Database::read();

    for (int row = 0; row < table->rowCount(); row++) {
        QTableWidgetItem *item;
        for (int column = 0; column < table->columnCount(); column++) {
            item = new QTableWidgetItem();

            if (column == 5) {
                QPushButton *deleteBtn = new QPushButton("Delete");

                QAbstractButton::connect(deleteBtn, &QPushButton::clicked, deleteBtn, [table, row]() {
                    Table::deleteRow(table, row);
                });

                QHBoxLayout *layout = new QHBoxLayout();
                layout->addWidget(deleteBtn);

                QWidget *widget = new QWidget();
                widget->setFixedWidth(70);
                widget->setLayout(layout);

                table->setCellWidget(row, 5, widget);
            }
            else item->setText(QString::fromStdString(data[row][column]));

            table->setItem(row, column, item);
        }

        table->setRowHeight(row, 40);
    }
}

void Table::deleteRow(QTableWidget *table, int row) {
    Database::deleteRow(row);
    table->removeRow(row);
}
