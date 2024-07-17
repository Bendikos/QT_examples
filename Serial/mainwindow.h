#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
   void readbuffer();

   void on_pushButton_clicked();

   void on_comboBox_currentIndexChanged(const QString &arg1);

   void on_radioButton_clicked(bool checked);

   void on_radioButton_2_clicked(bool checked);

   //void on_dial_actionTriggered(int action);

   void on_dial_valueChanged(int value);

   void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QSerialPort *seriaport;
    bool open;
    bool changeTemp;
    float setHum;
    float setTemp;
    bool messageBox;
};

#endif // MAINWINDOW_H
