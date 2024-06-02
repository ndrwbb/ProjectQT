#ifndef ADDBOOKINGDIALOG_H
#define ADDBOOKINGDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class AddBookingDialog;
}

class AddBookingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookingDialog(QWidget *parent = nullptr);
    ~AddBookingDialog();

    QStringList getBookingDetails() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddBookingDialog *ui;
    QStringList bookingDetails;
};

#endif // ADDBOOKINGDIALOG_H
