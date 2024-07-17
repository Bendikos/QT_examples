#include "frmlunarcalendarwidget.h"
#include <QApplication>
// #include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));


    frmLunarCalendarWidget w;
    w.show();


    return a.exec();
}
