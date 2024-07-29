#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QTimer>

#define TIMER_TIMEOUT   (40)
#define TIMER_TIMEOUT2   (5)


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , logFile(QDir(QApplication::applicationDirPath() + "/logs").filePath(QDateTime::currentDateTime().toString("MMddhhmmss") + ".txt"))
    , serialPort(new QSerialPort(this))
{
    ui->setupUi(this);
    myDialog = new Dialog(this);

    // 确保日志文件夹存在
    QDir logsDir(QApplication::applicationDirPath() + "/logs");
    if (!logsDir.exists() && !logsDir.mkpath(".")) {
        qDebug() << "Failed to create logs directory.";
    }

    // 打开日志文件并初始化 QTextStream
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        logStream.setDevice(&logFile);
        writeLog("[START] Logs by AS608-Upper-Monitor. https://github.com/19e2k67/AS608-Upper-Monitor");
    } else {
        qDebug() << "Failed to open log file.";
    }

    // 扫描本机的串口，并添加到下拉框里
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        ui->comboBox->addItem(info.portName());
        writeLog("[searchPort] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " " + info.portName());
    }
    // 设置某些按钮不可见
    MainWindow::setWidgetVisible(false);

    // 连接信号和槽
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openSerial);


    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::addFingerprint);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::addFingerprintContinuously);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::identifyFingerprint);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::MatchFingerprint);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::deleteFingerprint);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::EmptyFingerprint);



    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::setDeviceBaudRate);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::setDevicePacketSize);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::setDeviceSecurityLevel);




    connect(serialPort, &QIODevice::readyRead, this, &MainWindow::slotReadData);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    timer = new QTimer(this);
    timer2 = new QTimer(this);
    timer3 = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::handleTimeout);
    connect(timer2, &QTimer::timeout, this, &MainWindow::timeUpdate);
    connect(timer3, &QTimer::timeout, this, &MainWindow::setSysPara);


}

MainWindow::~MainWindow()
{
    if (logFile.isOpen()) {
        logFile.close();
    }
    delete ui;
    delete serialPort;

}
void MainWindow::handleTimeout()
{
    if(BaudRateMultiple <= 96 && deviceBaudRate == 0){

        BaudRateMultiple++;
        serialPort->setBaudRate(9600 * BaudRateMultiple);

        writeLog("[connectDevice] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " BaudRate: " + QString::number(9600 * BaudRateMultiple));
        sendCommandPacket(MainWindow::PS_ValidTempleteNum);
        timer->start(TIMER_TIMEOUT);
        return;
    } else if(BaudRateMultiple <= 96 && deviceBaudRate != 0){
        timer->stop();
        writeLog("[connectDevice] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " Connected Device BaudRate: " + QString::number(9600 * BaudRateMultiple));

    }
    else{
        timer->stop();
        writeLog("[connectDevice] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " Connected Device failure");

    }


    // else{
    //     timer->stop();
    //     writeLog("[connectDevice] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " Connected Device BaudRate: " + QString::number(9600 * BaudRateMultiple));

    // }


}

void MainWindow::writeLog(const QString &message)
{
    if (logFile.isOpen()) {
        logStream << QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") << " " << message << "\n";
        logStream.flush();  // 确保数据被立即写入文件
    } else {
        qDebug() << "Log file is not open.";
    }
}

void MainWindow::setWidgetVisible(bool state)
{


    ui->comboBox_2->setVisible(state);
    ui->comboBox_3->setVisible(state);
    ui->comboBox_4->setVisible(state);
    ui->label_12->setVisible(state);
    ui->label_13->setVisible(state);
    ui->label_14->setVisible(state);
    ui->label_15->setVisible(state);
    ui->label_16->setVisible(state);
    ui->label_17->setVisible(state);
    ui->label_18->setVisible(state);
    ui->label_20->setVisible(state);
    ui->label_22->setVisible(state);
    ui->label_24->setVisible(state);





    ui->pushButton_2->setVisible(state);
    ui->pushButton_3->setVisible(state);
    ui->pushButton_4->setVisible(state);
    ui->pushButton_5->setVisible(state);
    ui->pushButton_6->setVisible(state);
    ui->pushButton_7->setVisible(state);
    ui->pushButton_8->setVisible(state);
    ui->pushButton_9->setVisible(state);
    ui->pushButton_10->setVisible(state);
    ui->listWidget->setVisible(state);


}

void MainWindow::setFingerprintCapacity()
{






}

void MainWindow::setSysPara()
{

    if(dataPacket[1].length() <= 22)
        return;
    timer3->stop();
    // writeLog("[setSysPara] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss"));

    ui->comboBox_2->setCurrentText(QString::number(dataPacket[1].at(24)*9600));

    ui->comboBox_3->setCurrentIndex(dataPacket[1].at(22));

    ui->comboBox_4->setCurrentIndex(dataPacket[1].at(16) - 1);

    ui->label_13->setText(QString::number(dataPacket[1].at(13)*16*16 + dataPacket[1].at(14)));

    ui->label_24->setText(ui->comboBox_4->itemText(dataPacket[1].at(16) - 1));

    ui->label_15->setText("0X" + dataPacket[1].mid(17, 4).toHex().toUpper());



    switch (dataPacket[1].at(11)*16*16 + dataPacket[1].at(12)) {
    case  0x00:
        ui->label_16->setText( "fpc1011c");
        break;
    case  0x02:
        ui->label_16->setText( "祥群 c500");
        break;
    case  0x03:
        ui->label_16->setText( "祥群 s500 条状");
        break;
    case  0x07:
        ui->label_16->setText( "深圳芯微条状");
        break;
    case  0x09:
        ui->label_16->setText( "用户自定义传感器 ");
        break;

    default :
        ui->label_16->setText( "未知 ");
        break;
    }



    if(i == 16){

        ui->label_17->setText(dataPacket[1].mid(37, 4) + dataPacket[2].mid(9, 4));
        ui->label_18->setText(dataPacket[2].mid(13, 8));
        ui->label_20->setText(dataPacket[2].mid(21, 8));
        ui->label_22->setText(dataPacket[2].mid(29, 8));
    }else{
        ui->label_17->setText(dataPacket[1].mid(37, 8));
        ui->label_18->setText(dataPacket[1].mid(45, 8));
        ui->label_20->setText(dataPacket[1].mid(53, 8));
        ui->label_22->setText(dataPacket[1].mid(61, 8));
    }
    ui->label_12->setText(QString::number(dataPacket[1].at(23)*16*16 + dataPacket[1].at(24)*9600));
    ui->label_14->setText(ui->comboBox_3->itemText(dataPacket[1].at(22)));

    MainWindow::setWidgetVisible(true);

}

void MainWindow::timeUpdate()
{

    timer2->stop();
    if (!receiveData.isEmpty()) {

        qDebug() << "receiveData.length() " << receiveData.length();

        uint16_t dataPacketLengh;
        i = 0;

        if(receiveData.length()>=7 && receiveData.mid(6 , 1) == responsePacketIdentifier){

            dataPacketLengh = receiveData.at(7)*16*16 + receiveData.at(8);
            dataPacket[i] = receiveData.mid(0, dataPacketLengh + 9);

            receiveData.remove(0, dataPacketLengh + 9);
        }
        i++;
        while(receiveData.length()>=7 && receiveData.mid(6 , 1) == dataPacketIdentifier){
            dataPacketLengh = receiveData.at(7)*16*16 + receiveData.at(8);
            dataPacket[i] = receiveData.mid(0, dataPacketLengh + 9);
            receiveData.remove(0, dataPacketLengh + 9);
            i++;
        }
        if(receiveData.length()>=7 && receiveData.mid(6 , 1) == endPacketIdentifier){

            dataPacketLengh = receiveData.at(7)*16*16 + receiveData.at(8);
            dataPacket[i] = receiveData.mid(0, dataPacketLengh + 9);
            receiveData.remove(0, dataPacketLengh + 9);

        }
        qDebug() << "i " << i;

    }
    receiveData.clear();
}

void MainWindow::slotReadData()
{


    timer2->start(TIMER_TIMEOUT2);//启动定时器，接收 TIMER_TIMEOUT2 毫秒数据（根据情况设定）
    receiveData.append(serialPort->readAll());

    if(deviceBaudRate == 0 && receiveData.length() >= 12){
        deviceBaudRate = 9600 * BaudRateMultiple;
        sendCommandPacket(MainWindow::PS_ReadINFpage);
        timer3->start(30);
        receiveData.clear();
        return;
    }


}

void MainWindow::addFingerprint()
{






    myDialog->exec();

}

void MainWindow::addFingerprintContinuously()
{

}

void MainWindow::identifyFingerprint()
{

}

void MainWindow::MatchFingerprint()
{

}

void MainWindow::deleteFingerprint()
{


}

void MainWindow::EmptyFingerprint()
{
    sendCommandPacket(MainWindow::PS_Empty);
}

uint16_t MainWindow::receiveResponsePacket14()
{
    return receiveData.at(10)*16*16 + receiveData.at(11);
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About AS608-Upper-Monitor"),
                       tr("<h2>AS608-Upper-Monitor</h2>"
                          "<p><a href='https://github.com/19e2k67/AS608-Upper-Monitor'>GitHub 项目页面</a></p>"
                          "这是一个基于QT的开源项目"));
}
void MainWindow::openSerial(bool checked)
{
    if (checked) {
        // 开启串口
        writeLog("[openPort] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " port opening");
        serialPort->setPortName(ui->comboBox->currentText());
        serialPort->setStopBits(QSerialPort::TwoStop);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);

        if (!serialPort->open(QIODevice::ReadWrite)) {
            QMessageBox::warning(this, "错误", "串口打开失败，可能被占用了");
            writeLog("[openPort] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " port open error");
            ui->pushButton->setChecked(false);  // 关闭按钮
            return;
        }
        ui->pushButton->setText("关闭设备");
        timer->start(TIMER_TIMEOUT);

    } else {
        MainWindow::setWidgetVisible(false);
        serialPort->close(); // 关闭串口
        ui->pushButton->setText("打开设备");
        deviceBaudRate = 0;
        BaudRateMultiple = 0;
        timer->stop();
        timer2->stop();
        timer3->stop();

        receiveData.clear();
        dataToSend.clear();
        checkSum.clear();

        for(; i > 0; i--){
            dataPacket[i].clear();
        }

        writeLog("[openPort] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " port state closed");
    }
}

void MainWindow::setDeviceBaudRate()
{

    checkSumTemp = cmdPacketIdentifier.at(0) +packet_length5.at(0) +packet_length5.at(1) + PS_WriteReg + 0x04 + ui->comboBox_2->currentText().toInt()/9600;
    checkSum = QByteArray::fromHex(QString::number(checkSumTemp, 16).rightJustified(4, '0').toUtf8());


    dataToSend.append(packet_head);
    dataToSend.append(AS608_Address);
    dataToSend.append(cmdPacketIdentifier);
    dataToSend.append(packet_length5);
    dataToSend.append(PS_WriteReg);
    dataToSend.append(0x04);
    dataToSend.append(ui->comboBox_2->currentText().toInt()/9600);
    dataToSend.append(checkSum);
    serialPort->write(dataToSend);
    checkSum.clear();
    dataToSend.clear();

}
void MainWindow::setDeviceSecurityLevel()
{

    checkSumTemp = cmdPacketIdentifier.at(0) +packet_length5.at(0) +packet_length5.at(1) + PS_WriteReg + 0x05 + ui->comboBox_4->currentText().toInt();
    checkSum = QByteArray::fromHex(QString::number(checkSumTemp, 16).rightJustified(4, '0').toUtf8());


    dataToSend.append(packet_head);
    dataToSend.append(AS608_Address);
    dataToSend.append(cmdPacketIdentifier);
    dataToSend.append(packet_length5);
    dataToSend.append(PS_WriteReg);
    dataToSend.append(0x05);
    dataToSend.append(ui->comboBox_4->currentText().toInt());
    dataToSend.append(checkSum);
    serialPort->write(dataToSend);
    checkSum.clear();
    dataToSend.clear();

}
void MainWindow::setDevicePacketSize()
{

    checkSumTemp = cmdPacketIdentifier.at(0) +packet_length5.at(0) +packet_length5.at(1) + PS_WriteReg + 0x06 + ui->comboBox_3->currentIndex();
    checkSum = QByteArray::fromHex(QString::number(checkSumTemp, 16).rightJustified(4, '0').toUtf8());


    dataToSend.append(packet_head);
    dataToSend.append(AS608_Address);
    dataToSend.append(cmdPacketIdentifier);
    dataToSend.append(packet_length5);
    dataToSend.append(PS_WriteReg);
    dataToSend.append(0x06);
    dataToSend.append(ui->comboBox_3->currentIndex());
    dataToSend.append(checkSum);
    serialPort->write(dataToSend);
    checkSum.clear();
    dataToSend.clear();


}




void MainWindow::sendCommandPacket(uint8_t cmdCode) {

    checkSumTemp = cmdPacketIdentifier.at(0) +packet_length3.at(0) +packet_length3.at(1) + cmdCode;

    checkSum = QByteArray::fromHex(QString::number(checkSumTemp, 16).rightJustified(4, '0').toUtf8());

    // 拼接数据
    dataToSend.append(packet_head);
    dataToSend.append(AS608_Address);
    dataToSend.append(cmdPacketIdentifier);
    dataToSend.append(packet_length3);
    dataToSend.append(cmdCode);
    dataToSend.append(checkSum);

    writeLog("[send] " + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss") + " sendCmdId:" + QString::number(cmdCode));

    // 发送完整的数据包
    serialPort->write(dataToSend);

    dataToSend.clear();

}


void MainWindow::sendDataPacket(QByteArray &data)
{
    Q_UNUSED(data)
}

void MainWindow::sendOrReceiveEndPacket(QByteArray &data)
{
    Q_UNUSED(data)
}

void MainWindow::receiveResponsePacket(QByteArray &data)
{
    Q_UNUSED(data)
}


