#include "dialog.h"
#include "ui_dialog.h"
#include <QIntValidator>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(ui->lineEdit));

}

Dialog::~Dialog()
{
    delete ui;
}
