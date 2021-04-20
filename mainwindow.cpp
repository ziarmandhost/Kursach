#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <fstream>
#include <iostream>

#include <databaseitem.h>

using namespace std;

void MainWindow::createTable(QStandardItemModel *model) {
    // Меняем заголовок
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Название");
    model->setHeaderData(2, Qt::Horizontal, "Тип");
    model->setHeaderData(3, Qt::Horizontal, "Особенность");
    model->setHeaderData(4, Qt::Horizontal, "Доступность");
    model->setHeaderData(5, Qt::Horizontal, "Действия");

    // Заполняем таблицу фейковыми значениями
    QModelIndex index;

    for (int row = 0; row < model->rowCount(); row++) {
        for (int column = 0; column < model->columnCount(); column++) {
            index = model->index(row, column);

            model->setData(index, "empty");
        }
    }
}

void MainWindow::createDatabase(DatabaseItem *item) {
    fstream DATABASE;
    DATABASE.open("database.csv", ios::out | ios::app);

    DATABASE << item->ID << ","
             << '\"' << item->title << '\"' << ","
             << '\"' << item->type << '\"' << ","
             << '\"' << item->features << '\"' << ","
             << item->isAvailable << '\n';

    DATABASE.close();
}

bool MainWindow::isValueEmpty (QString qstr) {
    const wchar_t* wideCharacterString = (const wchar_t*) qstr.constData();
    unsigned int offsetOfFirstNonBlank = wcsspn(wideCharacterString, L" ");

    return !*(wideCharacterString+offsetOfFirstNonBlank);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mainTableModel = new QStandardItemModel(5, 6, this);
    ui->tableView->setModel(mainTableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->hide();
    MainWindow::createTable(mainTableModel);



    addItemTableModel = new QStandardItemModel(1, 5, this);
    ui->addItemTable->setModel(addItemTableModel);
    ui->addItemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->addItemTable->verticalHeader()->hide();
    MainWindow::createTable(addItemTableModel);

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

        MainWindow::createDatabase(item);
    }

}
