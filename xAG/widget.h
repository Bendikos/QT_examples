#ifndef WIDGET_H
#define WIDGET_H
#include "mythread.h"

#include <QWidget>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void getImage(QImage);
    void dealClose();
    void Read_Data();
    void getTemp(QString);

private slots:
    void on_radioButton_clicked(bool checked);
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    myThread *thread;
    QImage image;
    QSerialPort *serialAG;

signals:
    void sendTemp(QString);
};

#endif // WIDGET_H
