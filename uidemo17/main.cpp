#include "uidemo17.h"
#include "appinit.h"
#include "qicon.h"
// #include "qtextcodec.h"
#include "qapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));
    a.setWindowIcon(QIcon(":/main.ico"));


    AppInit::Instance()->start();

    UIDemo17 w;
    w.show();

    return a.exec();
}
