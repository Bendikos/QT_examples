#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    ui->pushButton_2->setEnabled(false);
    // 接受消息
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    connect(udpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(mStateChanged(QAbstractSocket::SocketState)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::readPendingDatagrams()
{
    QByteArray tmpByteArray;
    // 重新定义数组的大小
    tmpByteArray.resize(udpSocket->pendingDatagramSize());
    QHostAddress ipaddr;
    quint16 port;

    while (udpSocket->hasPendingDatagrams()) {
        udpSocket->readDatagram(tmpByteArray.data(), tmpByteArray.size(), &ipaddr, &port);
        // 打印发送者的IP地址、端口和信息
        ui->textBrowser->append("接受来自: " + ipaddr.toString() + ":" + QString::number(port) + tmpByteArray);
    }
}

void Widget::on_pushButton_3_clicked()
{
    // 单播消息
    ui->textBrowser->append("发送: "+ ui->lineEdit->text());
    udpSocket->writeDatagram(ui->lineEdit->text().toUtf8(), QHostAddress("127.0.0.1"), 7755);
    // udpSocket->writeDatagram(ui->lineEdit->text().toUtf8(), QHostAddress("192.168.3.30"), 7756);


}


void Widget::on_pushButton_clicked()
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(false);
    // 绑定端口
    udpSocket->bind(7756);
}


void Widget::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
    // 解除绑定
    udpSocket->abort();
}


void Widget::on_pushButton_4_clicked()
{
    // 广播消息
    ui->textBrowser->append("发送: "+ ui->lineEdit->text());
    // udpSocket->writeDatagram(ui->lineEdit->text().toUtf8(), QHostAddress::Broadcast, 7756);
    // udpSocket->writeDatagram(ui->lineEdit->text().toUtf8(), QHostAddress("192.168.3.30"), 7756);

}

void Widget::mStateChanged(QAbstractSocket::SocketState socketState)
{
    switch(socketState){
    case QAbstractSocket::BoundState:
        ui->textBrowser->append("socket状态: BoundState");
    default:
        break;
    }
}

