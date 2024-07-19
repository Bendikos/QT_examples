#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "axistag.h"
#include "queue.h"
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void timerSlot();
    void timerSerialSlot();

private:
    Ui::MainWindow *ui;

    QCustomPlot *mPlot;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    AxisTag *mTag1;
    AxisTag *mTag2;
    QTimer mDataTimer;
    QTimer mSerialDataTimer;
    QSerialPort *serial;//接收数据的串口
    bool m_IsOpened=false;

    //接收数据的环形队列
    RingBuffer *ringBuffer;

};

#endif // MAINWINDOW_H
