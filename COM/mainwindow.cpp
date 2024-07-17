#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer=new QTimer(this);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(SetTime()));

    QDate dateNow=QDate::currentDate();
    ui->label_date->setText(QString("日期:%1").arg(dateNow.toString("yyyy年MM月dd日 dddd")));
    ui->label_serialPortStaut->setText("串口状态：关闭");

    ReadTimer=new QTimer(this);
    ReadTimer->setInterval(200);//设置时间间隔
    connect(ReadTimer,SIGNAL(timeout()),this,SLOT(ReadCom()));

    ui->pushButton_send->setEnabled(false);
    ui->checkBox_resieveHex->setCheckState(Qt::Checked);
    ui->checkBox_sendHex->setCheckState(Qt::Checked);

    QStringList portList;//串口号
    QStringList baudList;//波特率
    QStringList parityList;//校验位
    QStringList dataBitsList;//数据位
    QStringList stopBitsList;//停止位

    portList<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"
            <<"COM7"<<"COM8"<<"COM9"<<"COM10";
    ui->comboBox_portName->addItems(portList);
    ui->comboBox_portName->setCurrentIndex(0);

    baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
            <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
            <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
            <<"76800"<<"115200"<<"128000"<<"256000";
    ui->comboBox_baudRate->addItems(baudList);
    ui->comboBox_baudRate->setCurrentIndex(12);

    parityList<<"无"<<"奇"<<"偶";
    ui->comboBox_parity->addItems(parityList);
    ui->comboBox_parity->setCurrentIndex(0);

    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->comboBox_dataBits->addItems(dataBitsList);
    ui->comboBox_dataBits->setCurrentIndex(3);

    stopBitsList<<"1"<<"1.5"<<"2";
    ui->comboBox_stopBits->addItems(stopBitsList);
    ui->comboBox_stopBits->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    serial->close();
    delete ui;
}

void MainWindow::SetTime()
{
    QTime timeNow=QTime::currentTime();
    ui->label_time->setText(QString("时间：%1").arg(timeNow.toString()));
}

void MainWindow::on_pushButton_send_clicked()
{
    if (!serial->isOpen())
    {
        return;
    }
    this->WriteCom();

}

void MainWindow::on_pushButton_serialPortOprate_clicked()
{
    if (ui->pushButton_serialPortOprate->text()=="打开串口")
    {
        QString portName=ui->comboBox_portName->currentText();

        serial = new QSerialPort(portName);

        if (serial->open(QIODevice::ReadWrite))
        {
            serial->flush(); //清空缓冲区
            serial->setBaudRate((QSerialPort::BaudRate)ui->comboBox_baudRate->currentText().toInt()); //设置波特率
            serial->setDataBits((QSerialPort::DataBits)ui->comboBox_dataBits->currentText().toInt()); //设置数据位
            serial->setParity((QSerialPort::Parity)ui->comboBox_parity->currentIndex()); //设置校验位
            serial->setStopBits((QSerialPort::StopBits)ui->comboBox_stopBits->currentIndex()); //设置停止位
            serial->setFlowControl(QSerialPort::NoFlowControl);

            ui->pushButton_serialPortOprate->setText("关闭串口");//here
            ui->label_serialPortStaut->setText("串口状态：打开");
            this->ReadTimer->start();
            ui->pushButton_send->setEnabled(true);


        }
    }
    else
    {
        serial->close();
        ui->pushButton_serialPortOprate->setText("打开串口");
        ui->label_serialPortStaut->setText("串口状态：关闭");
        this->ReadTimer->stop();
        ui->pushButton_send->setDisabled(true);
    }
}

void MainWindow::ReadCom()
{
    if (serial->bytesAvailable()<=0){return;}
    QByteArray buffer=serial->readAll();
        if (IsHexReceive)
        {
            QString hexData=buffer.toHex();
            ui->textEdit->append(QString("接收:%1 时间:%2")
                                   .arg(hexData)
                                   .arg(QTime::currentTime().toString("HH:mm:ss")));
        }
        else
        {
            QString normalData=QString(buffer);
            ui->textEdit->append(QString("接收:%1 时间:%2")
                                   .arg(normalData)
                                   .arg(QTime::currentTime().toString("HH:mm:ss")));

        }
}

void MainWindow::WriteCom()
{
    QString str=ui->lineEdit->text();
    qDebug() << str;
    if (!serial->isOpen()) { return; }//串口没有打开

    QByteArray outData=str.toLatin1();//QString 转 QByteArray

    if (IsHexSend)//转化为16进制发送
    {
        outData = outData.toHex();

        serial->write(outData);
    }
    else
    {
        serial->write(outData);
    }
    qDebug() << outData;

}

void MainWindow::on_pushButton_clearRecieveData_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_pushButton_clearSendData_clicked()
{
    ui->lineEdit->clear();
}

void MainWindow::on_checkBox_resieveHex_stateChanged(int argHex)
{
    IsHexReceive=(argHex==0?false:true);
}

void MainWindow::on_checkBox_sendHex_stateChanged(int argHex)
{
    IsHexSend=(argHex==0?false:true);
}
