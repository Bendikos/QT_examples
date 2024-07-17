#include "pic.h"
#include "ui_pic.h"
#include <QMovie>
#include "form.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap pMap(QString(":/1.jpg"));

    ui->label->setFixedWidth(pMap.width());
    ui->label->setFixedHeight(pMap.height());
    ui->label->setPixmap(pMap);
    this->setFixedWidth(pMap.width());
}

Widget::~Widget()
{
    delete ui;

}

void Widget::on_pushButton_3_clicked()
{
    QPixmap pMap(QString(":/2.jpg"));

    ui->label->setFixedWidth(pMap.width());
    ui->label->setFixedHeight(pMap.height());
    ui->label->setPixmap(pMap);
}



void Widget::on_pushButton_clicked()
{
    Form* pForm = new Form();
    pForm->setParent(this);
    pForm->setAttribute(Qt::WA_DeleteOnClose, true);
    pForm->show();
    hide();

}

