#include "mythread.h"
#include <QDebug>
#include <QImage>
float array0[11];
char isStop;

myThread::myThread(QObject *parent) :
    QThread(parent)
{
}

void myThread::run()
{
    while(1)
    {
        QImage image(WINDOW_WIDTH,WINDOW_HEIGHT-40,QImage::Format_RGB32); // 画布810x610
        QColor backColor = qRgb(255,255,255);    //画布初始化背景色使用白色
        image.fill(backColor);

        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
        int pointx=30,pointy=580;//坐标轴起点坐标
        int width=750,height=550;//坐标轴宽度,高度
        //绘制坐标轴
        painter.drawRect(5,5,WINDOW_WIDTH-10,WINDOW_HEIGHT-50);//外围的矩形大小800x600,间隙5。
        painter.drawLine(pointx,pointy,width+pointx,pointy);
        painter.drawLine(pointx,pointy-height,pointx,pointy);

        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);

        int i;
        for(i=1;i<=10;i++)
        {
            painter.drawLine(pointx+i*72,pointy,pointx+i*72,pointy+4);  // x轴刻度
            painter.drawText(pointx+i*72,pointy+20,QString::number(i));  // x轴数值
            painter.drawLine(pointx,pointy-i*52,26,pointy-i*52);  // y轴刻度
            painter.drawText(pointx-20,pointy-i*52,QString::number(i*10));  // y轴数值
        }
        painter.drawLine(pointx+width-7,pointy-7,pointx+width,pointy);  // x箭头
        painter.drawLine(pointx+width-7,pointy+7,pointx+width,pointy);

        painter.drawLine(pointx-7,pointy-height+7,pointx,pointy-height);  // y箭头
        painter.drawLine(pointx+7,pointy-height+7,pointx,pointy-height);

        painter.drawText(pointx,pointy+20,QString::number(0));  // 坐标原点

        QPen penText;
        penText.setColor(Qt::red);
        penText.setWidth(2);
        painter.setPen(penText);
        painter.drawText(pointx+width+3,pointy+2,QStringLiteral("x"));
        painter.drawText(pointx-2,pointy-height-5,QStringLiteral("y"));

        QPen penPoint;
        penPoint.setColor(Qt::blue);
        penPoint.setWidth(4);
        painter.setPen(penPoint);

        for(i=0;i<=10;i++)
        {
            painter.drawPoint(pointx+i*72,pointy-array0[i]*52/10);        // 描点
        }

        QPen penLine;
        penLine.setColor(Qt::green);
        penLine.setWidth(2);
        painter.setPen(penLine);

        for(i=0;i<10;i++)
        {
            painter.drawLine(pointx+i*72,pointy-array0[i]*52/10,pointx+(i+1)*72,pointy-array0[i+1]*52/10);  // 画线
        }

        emit updateImage(image);
        sleep(10);
        if(isStop==1)
        {
            break;
        }
    }
}

void myThread::getTemp2(QString xxTemp)
{
    int i;
    static int j;
    QString temp00=xxTemp;
    float temp11=temp00.toFloat();
    if(array0[10]==0)
    {
        array0[j]=temp11;
        j++;
    }
    else
    {
        for(i=0;i<=9;i++)
        {
            array0[i]=array0[i+1];
        }
        array0[10]=temp11;
    }
}
