#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void setParent(QWidget *parent);
    void closeEvent(QCloseEvent * event);




private:
    Ui::Form *ui;
    QWidget* pWid;
};

#endif // FORM_H
