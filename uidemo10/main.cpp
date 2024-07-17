#include "uidemo10.h"
#include "appinit.h"
#include <QApplication>
// #include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    a.setFont(QFont("Microsoft Yahei", 9));
    AppInit::Instance()->start();

    UIDemo10 w;
    w.show();

    return a.exec();
}
