#include "widget.h"
#include "ui_widget.h"
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#define DCM_IOCTRL_SETPWM (0x10)
#define DCM_TCNTB0 (16384)

#define MODULES_DRIVER "/root/modules_driver.sh"
int Motor_is_Running = 0;//电机是否在转
int Motor_turn = 1;//正反转

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


    ui->control_speed_slider->setMinimum(0);
    ui->control_speed_slider->setMaximum(500);

    Insmod_moudles();//加载模块硬件驱动脚本程序

}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Widget:: Insmod_moudles()
{
    QProcess *process = new QProcess;
    QStringList str;
    str << "";
    process->start(MODULES_DRIVER,str);
    process->waitForStarted();


    fd_motor = open("/dev/magic_dc_motor0", 0);
    if (fd_motor < 0)
    {
        printf("Can't open /dev/irda\n");
    }
}
void Widget::on_control_button_on_clicked()//启动电机
{

    Motor_is_Running=1;
    QProcess *process = new QProcess;
    process->start("/root/motor/dcm_test");//编译好的可运行的Qt程序
    process->waitForStarted();

    Show_motor();

}
void Widget::on_control_botton_off_clicked()
{
  Motor_is_Running = 0;
  QProcess *process = new QProcess;
  process->start("/root/motor/motor_stop.sh");//????
  process->waitForStarted();

}
void Widget::on_status_motor_turn_R_clicked()
{
      Motor_turn = 1;
      ui->status_status->setText("R");
}
void Widget::on_status_motor_turn_L_clicked()
{
    ui->status_status->setText("L");
    Motor_turn = 0;
}

void Widget::on_control_speed_slider_valueChanged(int value)
{
    if(Motor_is_Running==1)
    {
         int pos = ui->control_speed_slider->value();
         ui->status_speed->setText(QString::number(abs(pos)));//输出控制速度
    }

}

void Widget::Show_motor()
{

    int setpwm = 0;
    int factor = DCM_TCNTB0/1024;
    int pos = ui->control_speed_slider->value();

        if (Motor_is_Running)//开状态输出初始化
        {
            if(Motor_turn == 1)//正转
               {
                    setpwm = pos;
               }
            else
               {
                    setpwm = -pos;

               }
               ui->status_true_speed->setText(QString::number(setpwm));//输出实际转速
               connect(ui->control_speed_slider, SIGNAL(valueChanged(int)),
                  this, SLOT(on_control_speed_slider_valueChanged(int value)));

           /* for (;;)
            {
                   //ioctl(dcm_fd, DCM_IOCTRL_SETPWM, (setpwm * factor));
                    Delay(500);
            }
            */
        }
        else//关状态输出初始化
        {
            ui->status_status->setText("Null");
            ui->status_speed->setText("Null");
            ui->status_true_speed->setText("Null");
        }
}


void Widget:: Delay(int t)
{
     int i;
     for(;t>0;t--)
     for(i=0;i<400;i++);

 }


