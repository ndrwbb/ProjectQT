#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QTableView>
#include <QPushButton>

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

private:
    void loadFile();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
