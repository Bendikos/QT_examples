#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    this->setWindowTitle("服务端");
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(mNewConnection()));
    ui->pushButton_2->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mNewConnection()
{
    QTcpSocket* tmpTcpSocket = tcpServer->nextPendingConnection();
    ui->textBrowser->append("客户端的ip地址: " + tmpTcpSocket->peerAddress().toString());
    ui->textBrowser->append("客户端的端口: " + QString::number(tmpTcpSocket->peerPort()));

    connect(tmpTcpSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    connect(tmpTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(mstateChanged(QAbstractSocket::SocketState)));
}

void Widget::receiveMessage()
{
    QTcpSocket *tmpTcpSocket = qobject_cast<QTcpSocket *>(sender());
    if (tmpTcpSocket) {
        ui->textBrowser->append("客户端:" + tmpTcpSocket->readAll());
    }
}

void Widget::mstateChanged(QAbstractSocket::SocketState state)
{
    QTcpSocket *tmpTcpSocket = qobject_cast<QTcpSocket *>(sender());

    switch(state)
    {
    case QAbstractSocket::UnconnectedState:
        ui->textBrowser->append("(服务端:)客户端断开连接");
        tmpTcpSocket->deleteLater();
        break;
    case QAbstractSocket::ConnectingState:
        ui->textBrowser->append("(服务端:)客户端正在连接");
        break;
    default:
        break;
    }
}

void Widget::on_pushButton_3_clicked()
{
    QList<QTcpSocket *> socketList = tcpServer->findChildren<QTcpSocket *>();
    qDebug() << "tcpSocket 数量: " << socketList.count();
    if (socketList.count() == 0) {
        ui->textBrowser->append("当前没有客户端, 请先与客户端连接!");
        return;
    }

    foreach(QTcpSocket *tmpTcpSocket, socketList) {
        if (tmpTcpSocket->state() == QAbstractSocket::ConnectedState) {
            tmpTcpSocket->write(ui->lineEdit->text().toUtf8());
        }
    }
    ui->textBrowser->append("服务端->客户端 " + ui->lineEdit->text());
}

void Widget::on_pushButton_clicked()
{
    if (tcpServer->listen(QHostAddress("192.168.3.30"), 8080)) {
        ui->textBrowser->append("服务端:监听的IP地址和端口: 192.168.3.30 8080");
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
    } else {
        ui->textBrowser->append("服务端:监听失败");
    }
}

void Widget::on_pushButton_2_clicked()
{
    tcpServer->close();

    QList<QTcpSocket *> socketList = tcpServer->findChildren<QTcpSocket *>();
    foreach(QTcpSocket *tmpTcpSocket, socketList) {
        tmpTcpSocket->disconnectFromHost();
        tmpTcpSocket->close();
    }

    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->textBrowser->append("(服务端:)已停止监听");
}
