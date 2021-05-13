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

    // Add item mini table
    addItemTableModel = new QStandardItemModel(1, 5, this);
    ui->addItemTable->setModel(addItemTableModel);
    ui->addItemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->addItemTable->verticalHeader()->hide();
    Table::create(addItemTableModel);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_add_item_button_clicked() {
    QVariant idData = ui->addItemTable->model()->index(0, 0).data();
    QVariant titleData = ui->addItemTable->model()->index(0, 1).data();
    QVariant typeData = ui->addItemTable->model()->index(0, 2).data();
    QVariant featuresData = ui->addItemTable->model()->index(0, 3).data();
    QVariant isAvailable = ui->addItemTable->model()->index(0, 4).data();

    bool isIdValid = !idData.toString().toStdString().empty();
    bool isTitleValid = !titleData.toString().toStdString().empty();
    bool isTypeValid = !typeData.toString().toStdString().empty();
    bool isFeaturesValid = !featuresData.toString().toStdString().empty();

    if (!isIdValid) {
        QMessageBox::critical(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"ID\" пустое или некорректное."), QMessageBox::Yes);
        return;
    }

    if (!isTitleValid) {
        QMessageBox::critical(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"Название\" пустое или некорректное."), QMessageBox::Yes);
        return;
    }

    if (!isTypeValid) {
        QMessageBox::critical(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"Тип\" пустое или некорректное."), QMessageBox::Yes);
        return;
    }

    if (!isFeaturesValid) {
        QMessageBox::critical(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"Особенность\" пустое или некорректное."), QMessageBox::Yes);
        return;
    }

    if (isIdValid && isTitleValid && isTypeValid && isFeaturesValid) {
        if (Database::find(idData.toInt())) {
            QMessageBox::critical(this, tr("Ошибка!"),
                                  tr(("Невозможно добавить новый элемент. Элемент с id "+to_string(idData.toInt())+" уже существует!").c_str()), QMessageBox::Yes);
            return;
        }

        DatabaseItem *item = new DatabaseItem(
                    idData.toInt(),
                    titleData.toString().toStdString(),
                    typeData.toString().toStdString(),
                    featuresData.toString().toStdString(),
                    isAvailable.toString().toStdString(),
                    Database::getCurrentTimt()
        );

        Database::create(item);

        QModelIndex index;

        for (int column = 0; column < ui->addItemTable->model()->columnCount(); column++) {
            index = ui->addItemTable->model()->index(0, column);

            ui->addItemTable->model()->setData(index, "");
        }


        Table::update(ui->tableWidget, ui);
    }

}

void MainWindow::on_search_btn_clicked() {
    qDebug() << "Search";
}

void MainWindow::on_import_btn_clicked() {
    string desktopPath = QString("%1/autoexec.cfg").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)).toStdString();

    string fileName = QFileDialog::getOpenFileName(this, tr("Open table"), desktopPath.c_str(), tr("Spreadsheet Files (*.csv)")).toStdString();
    if (fileName.length() > 1) Database::import(fileName);

    Table::update(ui->tableWidget, ui);
}

void MainWindow::on_export_btn_clicked() {
    qDebug() << "Export";
}
