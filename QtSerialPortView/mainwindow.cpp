#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort;

    //缓存队列,初始256个字节
    ringBuffer =new RingBuffer(256);

    mPlot=ui->customPlot;

    mPlot->yAxis->setTickLabels(false);
    connect(mPlot->yAxis2, SIGNAL(rangeChanged(QCPRange)), mPlot->yAxis, SLOT(setRange(QCPRange)));
    mPlot->yAxis2->setVisible(true);
    mPlot->axisRect()->addAxis(QCPAxis::atRight);
    mPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30);
    mPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30);

    //添加两条曲线
    //mGraph1用于显示串口缓存队列的数据
    mGraph1 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 0));
    //mGraph2显示模拟的正弦信号
    mGraph2 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 1));
    mGraph1->setPen(QPen(QColor(250, 120, 0)));
    mGraph2->setPen(QPen(QColor(0, 180, 60)));

    mPlot->xAxis->setRange(-0.5,1.2);
    //添加坐标轴上的显示标签
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    mTag2 = new AxisTag(mGraph2->valueAxis());
    mTag2->setPen(mGraph2->pen());

    //定时器刷新显示，相当于主线程用于显示数据
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(60);

    //定时接收串口数据，相当于另一个线程读取串口数据
    connect(&mSerialDataTimer, SIGNAL(timeout()), this, SLOT(timerSerialSlot()));
    //mSerialDataTimer.start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(m_IsOpened)
    {
        m_IsOpened=false;
        mSerialDataTimer.stop();
        serial->close();
        ui->pushButton->setText("open");
        ui->pushButton->setStyleSheet("background-color: rgb(255, 0, 0);");
    }
    else
    {
        //设置串口 并打开
        serial->setPortName(ui->cbxName->currentText());
        serial->setBaudRate(ui->cbxBrate->currentText().toInt());
        serial->open(QIODevice::ReadWrite);
        mSerialDataTimer.start(20);
        ui->pushButton->setText("close");
        ui->pushButton->setStyleSheet("background-color: rgb(0, 255, 0);");
        m_IsOpened=true;
    }
}

//定时时间一到刷新显示
void MainWindow::timerSlot()
{
    double data=0;//默认0吧
    if(!ringBuffer->isEmpty())
    {
        //这里简化了协议解析，直接读取第二个数据值,也没有做校验
        ringBuffer->pop();
        data=ringBuffer->pop()/200.0; //为了两个曲线范围一致，进行了缩小
        ringBuffer->pop();
    }

    mGraph1->addData(mGraph2->dataCount(),data);
    mGraph2->addData(mGraph2->dataCount(), qSin(mGraph1->dataCount()/50.0)+qSin(mGraph1->dataCount()/50.0/0.3843)*0.25);

    mPlot->xAxis->rescale();
    //mGraph1->rescaleValueAxis(false, true);
    mGraph2->rescaleValueAxis(false, true);
    mPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);

    double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
    double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
    mTag1->updatePosition(graph1Value);
    mTag2->updatePosition(graph2Value);
    mTag1->setText(QString::number(graph1Value, 'f', 2));
    mTag2->setText(QString::number(graph2Value, 'f', 2));

    mPlot->replot();
}

//相当于线程不停的读取串口数据放入缓存
void MainWindow::timerSerialSlot()
{
    //缓冲区有空间就往里面写数据
    if(!ringBuffer->isFull())
    {
        QByteArray buf;
        buf=serial->readAll();
        if(buf.size()==0) return;
        for(int i=0;i<buf.size();i++)
        {
            ringBuffer->push(buf[i]);//全部入队
            qDebug()<<buf[i];
        }

    }
}
