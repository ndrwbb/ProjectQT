#include "addbookingdialog.h"
#include "ui_addbookingdialog.h"

AddBookingDialog::AddBookingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookingDialog)
{
    ui->setupUi(this);
}

AddBookingDialog::~AddBookingDialog()
{
    delete ui;
}

QStringList AddBookingDialog::getBookingDetails() const
{
    return bookingDetails;
}

void AddBookingDialog::on_buttonBox_accepted()
{
    bookingDetails.append(ui->lineEditBookingID->text());
    bookingDetails.append(ui->lineEditRoomID->text());
    bookingDetails.append(ui->lineEditFirstName->text());
    bookingDetails.append(ui->lineEditLastName->text());
    bookingDetails.append(ui->lineEditPhone->text());
    bookingDetails.append(ui->calendarCheckIn->selectedDate().toString("dd.MM.yyyy"));
    bookingDetails.append(ui->calendarCheckOut->selectedDate().toString("dd.MM.yyyy"));
}
