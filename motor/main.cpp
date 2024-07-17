#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    a.setFont(QFont("wenquanyi",12));
    return a.exec();
}
