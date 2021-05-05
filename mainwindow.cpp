#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseitem.h"

#include "Database.cpp"

#include <QMessageBox>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool MainWindow::isValueEmpty (QString qstr) {
    const wchar_t* wideCharacterString = (const wchar_t*) qstr.constData();
    unsigned int offsetOfFirstNonBlank = wcsspn(wideCharacterString, L" ");

    return !*(wideCharacterString+offsetOfFirstNonBlank);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mainTableModel = new QStandardItemModel(0, 5, this);
    ui->tableView->setModel(mainTableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->hide();
    Database::createTable(mainTableModel);
    Database::updateTable(mainTableModel);



    addItemTableModel = new QStandardItemModel(1, 5, this);
    ui->addItemTable->setModel(addItemTableModel);
    ui->addItemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->addItemTable->verticalHeader()->hide();
    Database::createTable(addItemTableModel);

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

    bool isIdValid = !MainWindow::isValueEmpty(idData.toString());
    bool isTitleValid = !MainWindow::isValueEmpty(titleData.toString());
    bool isTypeValid = !MainWindow::isValueEmpty(typeData.toString());
    bool isFeaturesValid = !MainWindow::isValueEmpty(featuresData.toString());

    if (!isIdValid)
        QMessageBox::question(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"ID\" пустое или некорректное."), QMessageBox::Yes);

    if (!isTitleValid)
        QMessageBox::question(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"Название\" пустое или некорректное."), QMessageBox::Yes);

    if (!isTypeValid)
        QMessageBox::question(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"Тип\" пустое или некорректное."), QMessageBox::Yes);

    if (!isFeaturesValid)
        QMessageBox::question(this, tr("Ошибка!"),
                              tr("Невозможно добавить новый элемент. Поле \"Особенность\" пустое или некорректное."), QMessageBox::Yes);

    if (isIdValid && isTitleValid && isTypeValid && isFeaturesValid) {
        DatabaseItem *item = new DatabaseItem(
                    idData.toInt(),
                    titleData.toString().toStdString(),
                    typeData.toString().toStdString(),
                    featuresData.toString().toStdString(),
                    isAvailable.toBool());

        Database::createDatabase(item);

        QModelIndex index;

        for (int column = 0; column < ui->addItemTable->model()->columnCount(); column++) {
            index = ui->addItemTable->model()->index(0, column);

            ui->addItemTable->model()->setData(index, "");
        }


        Database::updateTable(mainTableModel);
    }

}
