#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QStringList getPortNameList();//获取所有可用的串口列表
    enum model{ASCII,HEX};
    QString StringtoHex(QString buf);
    QString HextoString(QString buf);

private slots:
    void readMycom();
    void autoScroll();
    void on_OpenpushButton_clicked();

    void on_ClearpushButton_clicked();

    void on_ClosepushButton_clicked();

    void on_SendpushButton_clicked();

    void on_Clear1pushButton_clicked();

    void on_RecvAsciiradioButton_toggled(bool checked);

    void on_SendAsciiradioButton_toggled(bool checked);

private:
    Ui::Widget *ui;
    QSerialPort* m_serialPort; //串口类
    QStringList m_serialPortName;
    QByteArray QBAtemp;
    QString Qstrtemp;
    model sendmodel;
    model recvmodel;
};
#endif // WIDGET_H
