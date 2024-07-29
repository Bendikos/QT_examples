#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>
#include <QTextStream>
#include <dialog.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    // 构造函数
    explicit MainWindow(QWidget *parent = nullptr);

    // 设备当前的波特率倍数
    int BaudRateMultiple = 0;

    // 设备当前的波特率
    quint32 deviceBaudRate = 0;

    // 设备接收的原始数据
    QByteArray receiveData ;

    // 上位机要发送的数据
    QByteArray dataToSend;

    // 上位机发送指令的校验和
    quint16 checkSumTemp;





    QByteArray dataPacket[50];  // 各部分数据

    uint32_t i; // 接收到包的索引

    int FingerprintID = 0; // 指纹库id索引


    // 模块地址
    QByteArray AS608_Address = QByteArray::fromHex("FFFF FFFF");


    // 包头

    const QByteArray packet_head = QByteArray::fromHex("EF01");

    //包长度3
    const QByteArray packet_length3 = QByteArray::fromHex("0003");

    //包长度4
    const QByteArray packet_length4 = QByteArray::fromHex("0004");

    //包长度5
    const QByteArray packet_length5 = QByteArray::fromHex("0005");

    //包长度6
    const QByteArray packet_length6 = QByteArray::fromHex("0006");

    //包长度7
    const QByteArray packet_length7 = QByteArray::fromHex("0007");









    // 命令包 包标识
    const QByteArray cmdPacketIdentifier = QByteArray::fromHex("01");

    // 数据包 包标识
    const QByteArray dataPacketIdentifier = QByteArray::fromHex("02");

    // 结束包 包标识
    const QByteArray endPacketIdentifier = QByteArray::fromHex("08");

    // 应答包 包标识
    const QByteArray responsePacketIdentifier = QByteArray::fromHex("07");





    // 校验和
    QByteArray checkSum;
    // 析构函数
    ~MainWindow() override;












    enum Command {

        // 录入图像
        PS_GetImage = 0X01,

        // 生成特性
        PS_GenChar,

        // 精确比对两枚指纹特征
        PS_Match,

        // 搜索指纹
        PS_Search,

        // 合并特征（生成模板）
        PS_RegModel,

        // 储存模板
        PS_StoreChar,

        // 读出模板
        PS_LoadChar,

        // 上传特征或模板
        PS_UpChar,

        // 下载特征或模板
        PS_DownChar,

        // 上传图像
        PS_UpImage,

        // 下载图像
        PS_DownImage,

        // 删除模板
        PS_DeletChar,

        // 清空指纹库
        PS_Empty,

        // 写系统寄存器
        PS_WriteReg,

        // 读系统基本参数
        PS_ReadSysPara,

        // 自动注册模板
        PS_Enroll,

        // 自动验证指纹
        PS_Identify,

        // 设置口令, 慎用!
        PS_SetPwd,

        // 验证口令
        PS_VfyPwd,

        // 采样随机数
        PS_GetRandomCode,

        // 设置芯片地址
        PS_SetChipAddr,

        // 读 flash 信息页
        PS_ReadINFpage,

        // 端口控制
        PS_Port_Control,

        // 写记事本
        PS_WriteNotepad,

        // 读记事本
        PS_ReadNotepad,

        // 烧写片内 FLASH
        PS_BurnCode,

        // 高速搜索
        PS_HighSpeedSearch,

        // 生成细化指纹图像
        PS_GenBinImage,

        // 读有效模板个数
        PS_ValidTempleteNum,

    };
    Q_ENUM(Command)


private:
    Ui::MainWindow *ui;               // UI 控件的指针
    QFile logFile;                    // 日志文件
    QTextStream logStream;            // 日志流
    QSerialPort *serialPort;          // 串口对象

    QTimer *timer;               // 开始测试波特率的定时器
    QTimer *timer2;              // 拼接一帧数据的定时器
    QTimer *timer3;              // 系统初始化的定时器


    QDialog *myDialog;  // 声明一个QDialog指针


    void writeLog(const QString &message);// 写入日志的函数

    void setWidgetVisible(bool state);// 设置按钮是否可见

    void setFingerprintCapacity();      // 设置指纹库容量

    void setSysPara();      // 设置系统参数

    void timeUpdate();      // 处理接收到的数据

    void slotReadData();    // 拼接接收到的数据

    void addFingerprint();    // 录入指纹

    void addFingerprintContinuously();    // 连续录入指纹

    void identifyFingerprint();    // 验证指纹

    void MatchFingerprint();    // 对比选中的指纹

    void deleteFingerprint();    // 删除选中的指纹

    void EmptyFingerprint();    // 清空指纹库


    uint16_t receiveResponsePacket14(); // 处理14长度的应答包





public slots:
    void handleTimeout();  //超时处理函数

public slots:
    // 关于对话框
    void about();

    // 打开或关闭串口
    void openSerial(bool checked);

    // 设置设备波特率
    void setDeviceBaudRate();

    // 设置设备安全等级
    void setDeviceSecurityLevel();

    // 设置设备数据包大小
    void setDevicePacketSize();

    // 发送命令包函数
    void sendCommandPacket(uint8_t cmdCode);
    // void sendCommandPacket(uint8_t cmdCode, uint8_t bufferID);

    // 发送数据包函数
    void sendDataPacket(QByteArray &data);

    // 发送或者接收结束包
    void sendOrReceiveEndPacket(QByteArray &data);

    // 接收应答包
    void receiveResponsePacket(QByteArray &data);
};

#endif // MAINWINDOW_H
