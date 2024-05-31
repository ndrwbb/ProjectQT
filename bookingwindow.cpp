#include "bookingwindow.h"
#include "ui_bookingwindow.h"  // Ensure this line is present

BookingWindow::BookingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookingWindow)
{
    ui->setupUi(this);
}

BookingWindow::~BookingWindow()
{
    delete ui;
}
