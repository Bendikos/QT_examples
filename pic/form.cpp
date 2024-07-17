#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    pWid = NULL;
}

Form::~Form()
{
    delete ui;
    qDebug("Form deleted");

}

void Form::setParent(QWidget *parent)
{
    pWid = parent;
}

void Form::closeEvent(QCloseEvent * event)
{
    if(pWid)
    {
        pWid->showNormal();
        qDebug("event close");
    }
}
