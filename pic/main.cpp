#include <QApplication>
#include "pic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w ;

    w.show();
    
    a.exec();

    return 0;
}
