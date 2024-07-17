#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFile>
#include"comm.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    seriaport=new QSerialPort();
    seriaport->setPortName("COM3");//待打开的串口号
    seriaport->setBaudRate(115200,QSerialPort::AllDirections);
    seriaport->setDataBits(QSerialPort::Data8);
    seriaport->setParity(QSerialPort::NoParity);//校验位
    seriaport->setStopBits(QSerialPort::OneStop);//停止位
    seriaport->setFlowControl(QSerialPort::NoFlowControl);//流控制

    open=false;
     changeTemp=true;
    connect(seriaport,&QSerialPort::readyRead,this,&MainWindow::readbuffer);
//ui->dial->setSingleStep(0.5);
    ui->dial->setMaximum(999);
    struct data dd;
    QFile qFile("data");
    if(!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"erro";
        return ;
    }
     qFile.read((char*)&dd,sizeof(dd));
     ui->lcdNumber_4->display((float)dd.setTemp/10);
     ui->lcdNumber_3->display((float)dd.setHum/10);
     ui->checkBox->setChecked(true);
    qFile.close();

    messageBox=false;

}

MainWindow::~MainWindow()
{
    seriaport->close();
    delete ui;
}

void MainWindow::readbuffer()
{
    QByteArray dataArray;
    QMessageBox message(QMessageBox::NoIcon, "警告", "温湿度超限！！",QMessageBox::Ok);
     struct da1{
         short a;
         short b;
         char c;
       }__attribute__((packed));

    dataArray=seriaport->readAll();
    if (!dataArray.isEmpty()) {
       const da1 *da=(const da1 *)(dataArray.data());     
//         qDebug()<<da->a;
//         qDebug()<<da->b;
//         qDebug()<<da->c;
         ui->lcdNumber->display(da->a);
         ui->lcdNumber_2->display(da->b);
         //if(ui->lcdNumber_3->)


         struct data dd;
         QFile qFile("data");
         if(!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
         {
             qDebug()<<"erro";
            return ;
         }
         qFile.read((char*)&dd,sizeof(dd));
         if(da->a>((float)dd.setTemp/10)||da->b>((float)dd.setHum/10))
         {

            if(messageBox==false)
              {
                messageBox=true;
                ui->checkBox->setChecked(false);
                message.exec();
              }
            qDebug()<<"  "<<message.isActiveWindow();
         }

         qFile.close();


    }
}

void MainWindow::on_pushButton_clicked()
{
    if(open==false){
        ui->pushButton->setText("关闭");
        seriaport->open(QIODevice::ReadWrite);//打开串口
        open=true;
    }else{
        ui->pushButton->setText("打开");
        seriaport->close();
        open=false;
    }

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
   open=false;
   seriaport->close();
   ui->pushButton->setText("打开");
   //qDebug()<<arg1;
   switch(arg1.toInt())
   {
        case 1:
        seriaport->setPortName("COM1");//待打开的串口号
        break;
        case 2:
        seriaport->setPortName("COM2");//待打开的串口号
        break;
        case 3:
        seriaport->setPortName("COM3");//待打开的串口号
        break;
        case 4:
        seriaport->setPortName("COM4");//待打开的串口号
        break;
        case 5:
        seriaport->setPortName("COM5");//待打开的串口号
        break;
        case 6:
        seriaport->setPortName("COM6");//待打开的串口号
        break;
        case 7:
        seriaport->setPortName("COM7");//待打开的串口号
        break;
        case 8:
        seriaport->setPortName("COM8");//待打开的串口号
        break;
        case 9:
        seriaport->setPortName("COM9");//待打开的串口号
        break;
        case 10:
        seriaport->setPortName("COM10");//待打开的串口号
        break;
        case 11:
        seriaport->setPortName("COM11");//待打开的串口号
        break;
        default:
        seriaport->setPortName("COM1");//待打开的串口号
        break;
   }
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked==true)
    {
        changeTemp=true;
    }else{
         changeTemp=false;
    }
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if(checked==true)
    {
         changeTemp=false;
    }else{
       changeTemp=true;
    }
}



void MainWindow::on_dial_valueChanged(int value)
{

    qDebug()<<value;
    struct data dd;
    memset(&dd,0,sizeof(dd));
    if(changeTemp==true)
    {
        setTemp=(value);
        ui->lcdNumber_3->display((float)setTemp/10);
    }
    else
    {
        setHum=(value);
        ui->lcdNumber_4->display((float)setHum/10);
    }

    dd.setHum=ui->lcdNumber_3->value()*10;
    dd.setTemp=ui->lcdNumber_4->value()*10;
    QFile qFile("data");
    if(!qFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"erro";
       return ;
    }
    qFile.write((char *)&dd,sizeof(dd));
    qFile.close();
    qDebug()<<"close";

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
         messageBox=false;
}
