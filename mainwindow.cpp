#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Table widget
    Table::create(ui->tableWidget, 0, 7);
    Table::update(ui->tableWidget, ui);
    ui->statusbar->showMessage("Last action: database loaded");

    // Add item mini table
    addItemTableModel = new QStandardItemModel(1, 5, this);
    ui->addItemTable->setModel(addItemTableModel);
    ui->addItemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->addItemTable->verticalHeader()->hide();
    Table::create(addItemTableModel);

    // Filters QComboBox fix (make first element non editable)
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->filter_picker->model());
    QModelIndex firstIndex = model->index(0, ui->filter_picker->modelColumn(), ui->filter_picker->rootModelIndex());
    QStandardItem* firstItem = model->itemFromIndex(firstIndex);
    firstItem->setSelectable(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_add_item_button_clicked() {
    QVariant idData = ui->addItemTable->model()->index(0, 0).data();
    QVariant titleData = ui->addItemTable->model()->index(0, 1).data();
    QVariant traffic = ui->addItemTable->model()->index(0, 2).data();
    QVariant endOfTerm = ui->addItemTable->model()->index(0, 3).data();
    QVariant costPerMonth = ui->addItemTable->model()->index(0, 4).data();

    bool isIdValid = !idData.toString().toStdString().empty();
    bool isTitleValid = !titleData.toString().toStdString().empty();
    bool isTrafficValid = !traffic.toString().toStdString().empty();
    bool isEndOfTermValid = !endOfTerm.toString().toStdString().empty();
    bool isCostPerMonthValid = !costPerMonth.toString().toStdString().empty();

    if (!isIdValid) {
        QMessageBox::critical(this, tr("Error!"),
                              tr("Unable to add new item. The \"ID\" field is empty or invalid."), QMessageBox::Yes);
        return;
    }

    if (!isTitleValid) {
        QMessageBox::critical(this, tr("Error!"),
                              tr("Unable to add new item. The \"Title\" field is empty or invalid."), QMessageBox::Yes);
        return;
    }

    if (!isTrafficValid) {
        QMessageBox::critical(this, tr("Error!"),
                              tr("Unable to add new item. The \"Traffic\" field is empty or invalid."), QMessageBox::Yes);
        return;
    }

    if (!isEndOfTermValid) {
        QMessageBox::critical(this, tr("Error!"),
                              tr("Unable to add new item. The \"End of term\" field is empty or invalid."), QMessageBox::Yes);
        return;
    }

    if (!isCostPerMonthValid) {
        QMessageBox::critical(this, tr("Error!"),
                              tr("Unable to add new item. The \"Cost per month\" field is empty or invalid."), QMessageBox::Yes);
        return;
    }

    if (isIdValid && isTitleValid && isTrafficValid && isEndOfTermValid && isCostPerMonthValid) {
        if (Database::find(idData.toInt())) {
            QMessageBox::critical(this, tr("Error!"),
                                  tr(("Unable to add new item. Element with id "+to_string(idData.toInt())+" already exists!").c_str()), QMessageBox::Yes);
            return;
        }

        DatabaseItem *item = new DatabaseItem(
                    idData.toInt(),
                    titleData.toString().toStdString(),
                    traffic.toString().toStdString(),
                    endOfTerm.toString().toStdString(),
                    costPerMonth.toString().toStdString(),
                    Database::getCurrentTime()
        );

        Database::create(item);

        QModelIndex index;

        for (int column = 0; column < ui->addItemTable->model()->columnCount(); column++) {
            index = ui->addItemTable->model()->index(0, column);

            ui->addItemTable->model()->setData(index, "");
        }


        Table::update(ui->tableWidget, ui);
        ui->statusbar->showMessage("Last action: new item successfully added and saved to database");
    }

}

void MainWindow::on_import_btn_clicked() {
    string desktopPath = QString("%1/database.csv").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)).toStdString();

    string fileName = QFileDialog::getOpenFileName(this, tr("Open database"), desktopPath.c_str(), tr("Spreadsheet Files (*.csv)")).toStdString();
    if (fileName.length() > 1) {
        Database::import(fileName);
        Table::update(ui->tableWidget, ui);
        ui->statusbar->showMessage("Last action: database imported successfully");
    }
}

void MainWindow::on_export_btn_clicked() {
    string desktopPath = QString("%1/database.csv").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)).toStdString();

    string fileName = QFileDialog::getSaveFileName(this, tr("Save database"), desktopPath.c_str(), tr("Spreadsheet Files (*.csv)")).toStdString();
    if (fileName.length() > 1) {
        Database::exportBase(fileName);
        ui->statusbar->showMessage("Last action: database exported successfully");
    }
}

void MainWindow::on_clear_filters_btn_clicked() {
    ui->line_edit->clear();
    Table::update(ui->tableWidget, ui);
}

void MainWindow::on_line_edit_returnPressed() {
    Table::searchInTable(ui);
}

void MainWindow::on_search_btn_clicked() {
    Table::searchInTable(ui);
}

void MainWindow::on_filter_picker_currentIndexChanged(int index) {
    if (index == 1) Table::filterByIncreasingCostAndEndOfTermThisYear(ui);
    else if (index == 2) Table::filterByASCTitleAndEditTime(ui);
    else if (index == 3) Table::filterByASCTitleAndCostMoreThanAverage(ui);
}













