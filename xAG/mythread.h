#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QPainter>
#include <QByteArray>
#include <QFileDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QQueue>
#include <QMutex>
extern char isStop;
#define WINDOW_WIDTH 810
#define WINDOW_HEIGHT 650

class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = 0);
    void run();
    void getTemp2(QString);


signals:
    void updateImage(QImage);

public slots:

};

#endif // MYTHREAD_H
