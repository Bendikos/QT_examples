#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initSerialPort();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTimer *timer;
    QTimer *ReadTimer; //定时读取串口数据
    QTimer *SendTimer; //定时发送串口数据
    bool IsHexSend = false;//是否16进制数据发送
    bool IsHexReceive = false;//是否16进制数据接收

private slots:
    void SetTime(); //更新时间
    void ReadCom(); //读取串口数据
    void WriteCom(); //写串口数据
    void on_pushButton_send_clicked();
    void on_pushButton_serialPortOprate_clicked();
    void on_pushButton_clearRecieveData_clicked();
    void on_pushButton_clearSendData_clicked();
    void on_checkBox_resieveHex_stateChanged(int arg1);
    void on_checkBox_sendHex_stateChanged(int arg1);
};

#endif // MAINWINDOW_H
