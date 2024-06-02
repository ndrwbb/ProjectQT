#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QTableView>
#include <QPushButton>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QList<QStringList> rooms;
    static QList<QStringList> bookings;

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_push_SearchRoom_clicked();

    void applyRoomFilters(const QDate &checkIn, const QDate &checkOut, int minPrice, int maxPrice, const QStringList &roomTypes, int guestsNumber, bool safe, bool miniBar, bool isMerged);

    void on_comboBoxRoomOptions_currentIndexChanged(int index);

    QList<QStringList> sortRooms(int index);

    void on_pushButton_clicked();

private:
    void loadFile();

    void setupUI();

    void displayRoomsDataset(const QList<QStringList> &dataset);

    void filterRooms(const QDate &checkIn, const QDate &checkOut, int minPrice, int maxPrice, const QStringList &roomTypes, int guestsNumber, bool safe, bool miniBar, bool isMerged);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
