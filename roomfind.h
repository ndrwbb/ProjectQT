#ifndef ROOMFIND_H
#define ROOMFIND_H

#include <QDialog>

namespace Ui {
class roomFind;
}

class roomFind : public QDialog
{
    Q_OBJECT

public:
    explicit roomFind(QWidget *parent = nullptr);
    ~roomFind();

signals:
    void filterRooms(const QDate &checkIn, const QDate &checkOut, int minPrice, int maxPrice, const QStringList &roomTypes, int guestsNumber, bool safe, bool miniBar, bool isMerged);


private slots:
    void on_pushResetFilters_clicked();

    void on_pushFindRoom_clicked();

    void handleReturnPressed();

    // void on_lineEdit_minPrice_returnPressed();

    // void on_lineEdit_maxPrice_returnPressed();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::roomFind *ui;

};

#endif // ROOMFIND_H
