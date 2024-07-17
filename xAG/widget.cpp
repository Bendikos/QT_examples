#include "widget.h"
#include "ui_widget.h"

char flag;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    thread=new myThread(this);
    //resize(WINDOW_WIDTH,WINDOW_HEIGHT);  // 窗口大小810x650
    setFixedSize(WINDOW_WIDTH+160,WINDOW_HEIGHT-40);

    thread->start();

    connect(thread,&myThread::updateImage,this,&Widget::getImage);
    connect(this,&Widget::destroyed,this,&Widget::dealClose);

    QStringList list;
    list<<"115200"<<"4800"<<"9600";
    ui->comboBox2->addItems(list);

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())  // 查找可用的串口
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(serial.portName());
            serial.close();
        }
     }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);
}

void Widget::getImage(QImage temp)
{
    image=temp;
    update();
}

void Widget::dealClose()
{
    isStop=1;
    thread->quit();
    thread->wait();
}

void Widget::Read_Data()
{
    QByteArray array = serialAG->readAll(); // 获取对方发送的内容
    QString temp1;
    temp1=QString(array);
    emit sendTemp(temp1);
}

void Widget::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        serialAG=new QSerialPort(this);
        serialAG->setPortName(ui->comboBox->currentText());
        serialAG->open(QIODevice::ReadWrite);
        serialAG->setBaudRate(ui->comboBox2->currentText().toInt());
        serialAG->setDataBits(QSerialPort::Data8);
        serialAG->setStopBits(QSerialPort::OneStop);
        serialAG->setParity(QSerialPort::NoParity);
        serialAG->setFlowControl(QSerialPort::NoFlowControl);
        ui->comboBox2->setEnabled(0);
        ui->radioButton->setText("关闭串口");

        connect(serialAG, &QSerialPort::readyRead, this, &Widget::Read_Data);
        connect(this,&Widget::sendTemp,this,&Widget::getTemp);
        connect(this,&Widget::sendTemp,thread,&myThread::getTemp2);
    }
    else
    {
        serialAG->clear();
        serialAG->close();
        serialAG->deleteLater();

        ui->radioButton->setText("打开串口");
        ui->comboBox2->setEnabled(1);
    }
}

void Widget::getTemp(QString xxTemp)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");
    QString temp2=xxTemp;
    QString path="../xag.txt";
    if(path.isEmpty()==0)
    {
        QFile file(path);
        bool isOk=file.open(QIODevice::WriteOnly|QIODevice::Append);
        if(isOk==1)
        {
            if(flag==1)
            {
                flag=0;
                file.resize(0);  // 清空 xAG.txt
            }
            file.write(current_date.toUtf8()+" Temp="+temp2.toUtf8()+"\r\n");
         }
         file.close();
     }
}

void Widget::on_pushButton_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, "warning", "Are you sure clear xag.txt?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        flag=1;
    }
}
