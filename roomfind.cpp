#include "roomfind.h"
#include "ui_roomfind.h"

roomFind::roomFind(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::roomFind)
{
    ui->setupUi(this);
}

roomFind::~roomFind()
{
    delete ui;
}

void roomFind::on_pushFindRoom_clicked()
{

}


void roomFind::on_pushEraseFilters_clicked()
{
    // ui->lineEdit->clear(); // пример того как очистить

}

