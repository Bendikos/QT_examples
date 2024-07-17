#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtDebug>
#include <QMutex>
#include <QThread>
#include <math.h>

#include <stdlib.h>
#include <unistd.h>
//#include <sys/ioctl.h>
#include <fcntl.h>
#include <math.h>
namespace Ui
{
     class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
    int fd_motor;
protected:
    void changeEvent(QEvent *e);

public:
    Ui::Widget *ui;
    QMutex mutex;
    void Insmod_moudles();
    void Show_motor();
    void GetStatus();
    void Delay(int);


private slots:

    void on_status_motor_turn_L_clicked();
    void on_status_motor_turn_R_clicked();
    void on_control_speed_slider_valueChanged(int value);
    void on_control_botton_off_clicked();
    void on_control_button_on_clicked();


};

#endif // WIDGET_H
