#ifndef PIC_H
#define PIC_H

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
    
private slots:
    void on_pushButton_3_clicked();


    void on_pushButton_clicked();


private:
    Ui::Widget *ui;
private:
    //Form pForm;
};

#endif // PIC_H
