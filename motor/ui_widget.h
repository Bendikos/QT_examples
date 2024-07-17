/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Thu May 16 16:17:50 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGroupBox *status;
    QLabel *status_statu_lable;
    QLabel *status_speed_lable;
    QLabel *status_status;
    QLabel *status_speed;
    QLabel *Status_speed_lable2;
    QLabel *status_true_speed;
    QPushButton *status_motor_turn_R;
    QPushButton *status_motor_turn_L;
    QGroupBox *control;
    QPushButton *control_button_on;
    QPushButton *control_botton_off;
    QSlider *control_speed_slider;
    QLabel *label_2;
    QLabel *control_motor_image;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(261, 206);
        status = new QGroupBox(Widget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(0, 0, 131, 151));
        status_statu_lable = new QLabel(status);
        status_statu_lable->setObjectName(QString::fromUtf8("status_statu_lable"));
        status_statu_lable->setGeometry(QRect(0, 30, 61, 20));
        status_speed_lable = new QLabel(status);
        status_speed_lable->setObjectName(QString::fromUtf8("status_speed_lable"));
        status_speed_lable->setGeometry(QRect(0, 60, 61, 21));
        status_status = new QLabel(status);
        status_status->setObjectName(QString::fromUtf8("status_status"));
        status_status->setGeometry(QRect(73, 30, 41, 21));
        status_speed = new QLabel(status);
        status_speed->setObjectName(QString::fromUtf8("status_speed"));
        status_speed->setGeometry(QRect(73, 60, 41, 21));
        Status_speed_lable2 = new QLabel(status);
        Status_speed_lable2->setObjectName(QString::fromUtf8("Status_speed_lable2"));
        Status_speed_lable2->setGeometry(QRect(0, 90, 61, 21));
        status_true_speed = new QLabel(status);
        status_true_speed->setObjectName(QString::fromUtf8("status_true_speed"));
        status_true_speed->setGeometry(QRect(73, 90, 41, 21));
        status_motor_turn_R = new QPushButton(status);
        status_motor_turn_R->setObjectName(QString::fromUtf8("status_motor_turn_R"));
        status_motor_turn_R->setGeometry(QRect(0, 110, 51, 23));
        status_motor_turn_L = new QPushButton(status);
        status_motor_turn_L->setObjectName(QString::fromUtf8("status_motor_turn_L"));
        status_motor_turn_L->setGeometry(QRect(64, 110, 51, 23));
        control = new QGroupBox(Widget);
        control->setObjectName(QString::fromUtf8("control"));
        control->setGeometry(QRect(120, 0, 131, 151));
        control_button_on = new QPushButton(control);
        control_button_on->setObjectName(QString::fromUtf8("control_button_on"));
        control_button_on->setGeometry(QRect(10, 30, 41, 23));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/on.png"), QSize(), QIcon::Normal, QIcon::Off);
        control_button_on->setIcon(icon);
        control_botton_off = new QPushButton(control);
        control_botton_off->setObjectName(QString::fromUtf8("control_botton_off"));
        control_botton_off->setGeometry(QRect(10, 60, 41, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/off.png"), QSize(), QIcon::Normal, QIcon::Off);
        control_botton_off->setIcon(icon1);
        control_speed_slider = new QSlider(control);
        control_speed_slider->setObjectName(QString::fromUtf8("control_speed_slider"));
        control_speed_slider->setGeometry(QRect(10, 90, 101, 19));
        control_speed_slider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(control);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 110, 121, 20));
        control_motor_image = new QLabel(control);
        control_motor_image->setObjectName(QString::fromUtf8("control_motor_image"));
        control_motor_image->setGeometry(QRect(60, 30, 51, 51));
        control_motor_image->setPixmap(QPixmap(QString::fromUtf8(":/images/motor.png")));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QStringLiteral("Widget"));

        status->setTitle(QString());

        status_statu_lable->setText(QString::fromUtf8("\346\216\247\345\210\266\347\212\266\346\200\201\357\274\232"));
        status_speed_lable->setText(QString::fromUtf8("\346\216\247\345\210\266\351\200\237\345\272\246\357\274\232"));
        status_status->setText(QString::fromUtf8("NULL"));
        status_speed->setText(QString::fromUtf8("NULL"));
        Status_speed_lable2->setText(QString::fromUtf8("\345\256\236\351\231\205\350\275\254\351\200\237\357\274\232"));
        status_true_speed->setText(QString::fromUtf8("NULL"));
        status_motor_turn_R->setText(QString::fromUtf8("\346\255\243"));
        status_motor_turn_L->setText(QString::fromUtf8("\345\217\215"));

        control->setTitle(QString());
        control_button_on->setText(QString::fromUtf8("\345\274\200"));
        control_botton_off->setText(QString::fromUtf8("\345\205\263"));
        label_2->setText(QString::fromUtf8("0  1  2  3  4  5(00)               "));
        control_motor_image->setText(QString());
    } // retranslateUi


};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
