#include "roomfind.h"
#include "ui_roomfind.h"
#include <QMessageBox>
#include <QCalendarWidget>
#include <QDate>
#include <QChar>
#include <QIntValidator>
#include <QKeyEvent>

roomFind::roomFind(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::roomFind)
{
    ui->setupUi(this);
    QIntValidator *intValidator = new QIntValidator(0, 10000, this); // You can adjust the range as needed
    ui->lineEdit_minPrice->setValidator(intValidator);
    ui->lineEdit_maxPrice->setValidator(intValidator);

    connect(ui->lineEdit_minPrice, &QLineEdit::returnPressed, this, &roomFind::handleReturnPressed);
    connect(ui->lineEdit_maxPrice, &QLineEdit::returnPressed, this, &roomFind::handleReturnPressed);
}

roomFind::~roomFind()
{
    delete ui;
}

void roomFind::on_pushResetFilters_clicked()
{
    ui->checkBoxSingle->setChecked(false);
    ui->checkBoxDouble->setChecked(false);
    ui->checkBoxSuite->setChecked(false);
    ui->checkBoxFamily->setChecked(false);
    ui->checkBoxSafe->setChecked(false);
    ui->checkBoxMiniBar->setChecked(false);
    ui->checkBoxMerged->setChecked(false);

    ui->lineEdit_minPrice->clear();
    ui->lineEdit_maxPrice->clear();
    ui->comboBoxNumGuests->setCurrentIndex(0);

    ui->calendarCheckIn->setCurrentPage(2024, 6);
    ui->calendarCheckOut->setCurrentPage(2024, 6);
}


bool isOnlyDigits(const QString& str) {
    int countDigits = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i].isDigit()) {
            countDigits++;
        }
    }
    if (countDigits == str.length()) {
        return true;
    }
    else {
        return false;
    }
}

void roomFind::on_pushFindRoom_clicked()
{
    // Firstly check if both dates are selected
    if (ui->calendarCheckIn->selectedDate() == ui->calendarCheckOut->selectedDate()) {
        QMessageBox::warning(this, "dWarning", "You cannot choose the the same date for check in and check out. Try again.");
    }
    // Secondly check if the check-in date is not in the pust in respect to the today
    if (ui->calendarCheckIn->selectedDate() < QDate::currentDate()) {
        QMessageBox::warning(this, "pastWarning", "You cannot choose this check in date, because it's already over. Try again.");
    }
    // Check if the person had entered the price limits
    if (ui->lineEdit_minPrice->text() == "" or ui->lineEdit_maxPrice->text() == "") {
        QMessageBox::warning(this, "emptyWarning", "Enter both minimal and maximum limits for price.");
    }
    // Check if minimal price is less than the maximum price
    if (ui->lineEdit_minPrice->text() > ui->lineEdit_maxPrice->text()) {
        QMessageBox::warning(this, "minMaxInEquality", "Error. The minimal price limit is bigger than the maximum price");
    }
    // Check if at least one room type is chosen
    if (!ui->checkBoxSingle->isChecked() and !ui->checkBoxDouble->isChecked() and !ui->checkBoxSuite->isChecked() and !ui->checkBoxFamily->isChecked()) {
        QMessageBox::warning(this, "empty2Warning", "Choose at least one type of room.");
    }

    // The beginning of the comparsion
    QList<QStringList> comparsion = {{}};
}


void roomFind::handleReturnPressed()
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());
    if (lineEdit) {
        QString text = lineEdit->text();
        // Handle the text as needed without clearing it
        qDebug() << "Entered text:" << text;
        // Set focus back to the lineEdit to prevent text from disappearing
        lineEdit->setFocus();
    }
}

void roomFind::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(focusWidget());
        if (lineEdit) {
            // If Enter is pressed while a QLineEdit has focus, handle it
            QString text = lineEdit->text();
            qDebug() << "Entered text:" << text;
            lineEdit->setFocus();
            return; // Do not propagate the event further
        }
    }
    QDialog::keyPressEvent(event); // Call the base class implementation
}


// void roomFind::on_lineEdit_minPrice_returnPressed()
// {
//     QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());
//     if (lineEdit) {
//         QString text = lineEdit->text();
//         // Handle the text as needed without clearing it
//         qDebug() << "Entered text:" << text;
//     }
// }


// void roomFind::on_lineEdit_maxPrice_returnPressed()
// {
//     QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());
//     if (lineEdit) {
//         QString text = lineEdit->text();
//         // Handle the text as needed without clearing it
//         qDebug() << "Entered text:" << text;
//     }
// }

