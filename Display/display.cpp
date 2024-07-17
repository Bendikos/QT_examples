#include "display.h"
#include "ui_display.h"

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
    ui->label_BackGround->setStyleSheet("background-color:black");
    km = new Form_KM(this);
    km->setGeometry(0,0,400,255);
    km->show();

    connect(&testTimer,SIGNAL(timeout()),this,SLOT(change_Speed()));
    testTimer.start(10);
}

Display::~Display()
{
    testTimer.stop();
    delete ui;
}
static float temp = 0.0;
void Display::change_Speed()
{
    temp = temp + 0.5;
    km->change_Speed(temp);
}
