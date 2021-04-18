#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::createTable(Ui::MainWindow *ui, QStandardItemModel *model) {
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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 5 - рядков, 6 столбцов,
    // this - что-бы не удалять элемент отдельно,
    // когда уничтожится главное окно, то и model тоже
    mainTableModel = new QStandardItemModel(5, 6, this);

    ui->tableView->setModel(mainTableModel);
    // Колонки одинакового размера
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Спрятать хэдэр слева
    ui->tableView->verticalHeader()->hide();
    MainWindow::createTable(ui, mainTableModel);



    addItemTableModel = new QStandardItemModel(1, 6, this);
    ui->addItemTable->setModel(addItemTableModel);
    ui->addItemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->addItemTable->verticalHeader()->hide();
    MainWindow::createTable(ui, addItemTableModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

