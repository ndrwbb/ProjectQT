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

private slots:
    void on_pushFindRoom_clicked();

    void on_pushEraseFilters_clicked();

private:
    Ui::roomFind *ui;
};

#endif // ROOMFIND_H
