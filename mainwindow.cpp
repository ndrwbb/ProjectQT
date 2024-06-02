#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QString>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QStandardItemModel>
#include "roomfind.h"
#include <QTableWidget>
#include "addbookingdialog.h"

QList<QStringList> MainWindow::bookings;
QList<QStringList> MainWindow::rooms;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadFile();

    displayRoomsDataset(rooms);

    // Setting up headers
    QStringList headers;
    for (int c = 1; c < MainWindow::rooms[0].length(); c++) {
        headers.append(MainWindow::rooms[0][c]);
    }
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Setting up the whole table
    ui->tableWidget->setRowCount(MainWindow::rooms.length() - 1);
    for (int row = 1; row < MainWindow::rooms.length(); row++) {
        for (int col = 1; col < MainWindow::rooms[row].length(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(MainWindow::rooms[row][col]);
            ui->tableWidget->setItem(row - 1, col - 1, item);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayRoomsDataset(const QList<QStringList> &dataset)
{
    // Setting up headers
    ui->comboBoxRoomOptions->show();
    ui->labelSortBy->show();
    QStringList headers;
    for (int c = 0; c < MainWindow::rooms[0].length(); c++) {
        headers.append(MainWindow::rooms[0][c]);
    }
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Setting up the whole table
    ui->tableWidget->setRowCount(dataset.length() - 1);
    for (int row = 1; row < dataset.length(); row++) {
        for (int col = 0; col < dataset[row].length(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(dataset[row][col]);
            ui->tableWidget->setItem(row - 1, col, item);
        }
    }
}

void MainWindow::setupUI()
{
    // Connect the combo box signal
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));
    connect(ui->push_SearchRoom, SIGNAL(clicked()), this, SLOT(on_push_SearchRoom_clicked()));
}

void MainWindow::loadFile() {
    QString bookingPath = ":/new/bookings_set.csv";
    QString roomPath = ":/new/rooms_set.csv";

    QFile bookingFile(bookingPath);
    QFile roomFile(roomPath);

    bookingFile.open(QIODevice::ReadOnly);
    roomFile.open(QIODevice::ReadOnly);

    if (!bookingFile.isOpen()) {
        qDebug() << "Can't open the booking file";
        return;
    }
    if (!roomFile.isOpen()) {
        qDebug() << "Can't open the room file";
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
    if (index == 0) {
        displayRoomsDataset(rooms);
    } else {
        ui->comboBoxRoomOptions->setVisible(false);
        ui->labelSortBy->setVisible(false);
        QStringList headers;
        for (int c = 0; c < MainWindow::bookings[0].length(); c++) {
            headers.append(MainWindow::bookings[0][c]);
        }
        ui->tableWidget->setColumnCount(headers.size());
        ui->tableWidget->setHorizontalHeaderLabels(headers);

        ui->tableWidget->setRowCount(MainWindow::bookings.length() - 1);
        for (int row = 1; row < MainWindow::bookings.length(); row++) {
            for (int col = 0; col < MainWindow::bookings[row].length(); col++) {
                QTableWidgetItem *item = new QTableWidgetItem(MainWindow::bookings[row][col]);
                ui->tableWidget->setItem(row - 1, col, item);
            }
        }
    }
}


void MainWindow::on_push_SearchRoom_clicked()
{
    roomFind *roomFindWindow = new roomFind(this);
    connect(roomFindWindow, &roomFind::filterRooms, this, &MainWindow::applyRoomFilters);
    roomFindWindow->show();
}

void MainWindow::applyRoomFilters(const QDate &checkIn, const QDate &checkOut, int minPrice, int maxPrice, const QStringList &roomTypes, int guestsNumber, bool safe, bool miniBar, bool isMerged)
{
    filterRooms(checkIn, checkOut, minPrice, maxPrice, roomTypes, guestsNumber, safe, miniBar, isMerged);
}

void MainWindow::filterRooms(const QDate &checkIn, const QDate &checkOut, int minPrice, int maxPrice, const QStringList &roomTypes, int guestsNumber, bool safe, bool miniBar, bool isMerged)
{
    QList<QStringList> filteredRooms;
    foreach (const QStringList &room, rooms) {
        if (room == rooms[0]) {
            filteredRooms.append(room);
            continue;
        }

        int priceNight = room[8].toInt();
        bool roomSafe = room[3] == "true";
        bool roomMiniBar = room[4] == "true";
        bool roomIsMerged = room[5] == "true";
        int roomGuestsNumber = room[2].toInt();
        bool roomIsFree = room[6] == "true";
        QString roomType = room[1];

        bool priceMatch = priceNight >= minPrice && priceNight <= maxPrice;
        bool guestsMatch = roomGuestsNumber >= guestsNumber;
        bool typeMatch = roomTypes.contains(roomType);
        bool safeMatch = !safe || (safe && roomSafe);
        bool miniBarMatch = !miniBar || (miniBar && roomMiniBar);
        bool mergedMatch = !isMerged || (isMerged && roomIsMerged);

        if (priceMatch && guestsMatch && typeMatch && safeMatch && miniBarMatch && mergedMatch && roomIsFree) {
            filteredRooms.append(room);
        }
    }

    QStringList headers;
    for (int c = 0; c < MainWindow::rooms[0].length(); c++) {
        headers.append(MainWindow::rooms[0][c]);
    }

    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(filteredRooms.length() - 1);


    for (int row = 1; row < filteredRooms.length(); row++) {
        for (int col = 0; col < filteredRooms[row].length(); col++) {
            QTableWidgetItem *item = new QTableWidgetItem(filteredRooms[row][col]);
            ui->tableWidget->setItem(row - 1, col, item);
        }
    }
}


QList<QStringList> MainWindow::sortRooms(int index)
{
    QList<QStringList> sortedRooms = rooms;
    std::sort(sortedRooms.begin() + 1, sortedRooms.end(), [index](const QStringList &a, const QStringList &b) {
        if (index == 0) {
            // Sort by price ascending
            return a[8].toInt() < b[8].toInt();
        } else if (index == 1) {
            // Sort by price descending
            return a[8].toInt() > b[8].toInt();
        } else if (index == 2) {
            // Sort by square ascending
            return a[7].toFloat() < b[7].toFloat();
        } else if (index == 3) {
            // Sort by square descending
            return a[7].toFloat() > b[7].toFloat();
        }
        return false;
    });

    return sortedRooms;
}

void MainWindow::on_comboBoxRoomOptions_currentIndexChanged(int index)
{
    QList<QStringList> sortedRooms = sortRooms(index);
    displayRoomsDataset(sortedRooms);
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->comboBox->currentIndex() == 0) {
        ui->pushButton->hide();
    }
    else {
         ui->pushButton->show();
        AddBookingDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            QStringList newBooking = dialog.getBookingDetails();

            // Add the new booking to the current table
            int newRow = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(newRow);
            for (int col = 0; col < newBooking.size(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(newBooking[col]);
                ui->tableWidget->setItem(newRow, col, item);
            }

            // Write the new booking to the bookings_set.csv file
            QFile file(":/new/bookings_set.csv");
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&file);
                out << newBooking.join(';') << '\n';
                file.close();
            } else {
                qDebug() << "Unable to open file for writing";
            }

            // Update the bookings list
            MainWindow::bookings.append(newBooking);
        }
    }
}

