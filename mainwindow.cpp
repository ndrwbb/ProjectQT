#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QString>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QStandardItemModel>
#include "roomfind.h"

QList<QStringList> MainWindow::bookings;
QList<QStringList> MainWindow::rooms;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadFile();
    QStandardItemModel *model = new QStandardItemModel(this);

    // Setting up headers
    for (int c = 1; c < MainWindow::rooms[0].length(); c++)
    {
        QStandardItem *item = new QStandardItem(MainWindow::rooms[0][c]);
        model->setHorizontalHeaderItem(c - 1, item);
    }

    // Setting up the whole table
    for (int row = 1; row < MainWindow::rooms.length(); row++)
    {
        for(int col = 1; col < MainWindow::rooms[row].length(); col++)
        {
            QStandardItem *item = new QStandardItem(MainWindow::rooms[row][col]);
            model->setItem(row-1, col - 1, item);
        }
    }
    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile() {
    QString bookingPath = ":/new/bookings_set.csv";
    QString roomPath = ":/new/rooms_set.csv";

    QFile bookingFile(bookingPath);
    QFile roomFile(roomPath);

    bookingFile.open(QIODevice::ReadOnly);
    roomFile.open(QIODevice::ReadOnly);

    if (!bookingFile.isOpen()) {
        qDebug() << "Can't open the file";
        return;
    }
    if (!roomFile.isOpen()) {
        qDebug() << "Can't open the file";
        return;
    }

    QTextStream inBooking(&bookingFile);
    QTextStream inRoom(&roomFile);

    while (!inBooking.atEnd())
    {
        QString line = inBooking.readLine();
        QStringList tokens = line.split(';');
        MainWindow::bookings.append(tokens);
    }
    bookingFile.close();

    while (!inRoom.atEnd())
    {
        QString line = inRoom.readLine();
        QStringList tokens = line.split(';');
        MainWindow::rooms.append(tokens);
    }
    roomFile.close();
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QStandardItemModel *model = new QStandardItemModel(this);
    if (index == 0) {

        // Setting up headers
        for (int c = 0; c < MainWindow::rooms[0].length(); c++)
        {
            QStandardItem *item = new QStandardItem(MainWindow::rooms[0][c]);
            model->setHorizontalHeaderItem(c, item);
        }

        // Setting up the whole table
        for (int row = 1; row < MainWindow::rooms.length(); row++)
        {
            for(int col = 0; col < MainWindow::rooms[row].length(); col++)
            {
                QStandardItem *item = new QStandardItem(MainWindow::rooms[row][col]);
                model->setItem(row-1, col, item);
            }
        }
    }
    else {
        for (int c = 0; c < MainWindow::bookings[0].length(); c++)
        {
            QStandardItem *item = new QStandardItem(MainWindow::bookings[0][c]);
            model->setHorizontalHeaderItem(c, item);
        }

        // Setting up the whole table
        for (int row = 1; row < MainWindow::bookings.length(); row++)
        {
            for(int col = 0; col < MainWindow::bookings[row].length(); col++)
            {
                QStandardItem *item = new QStandardItem(MainWindow::bookings[row][col]);
                model->setItem(row-1, col, item);
            }
        }
    }
    ui->tableView->setModel(model);
}


void MainWindow::on_push_SearchRoom_clicked()
{
    roomFind *roomFindWindow = new roomFind(this);
    roomFindWindow->show();
}

