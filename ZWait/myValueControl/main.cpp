#include <QtWidgets>
#include "frmmain.h"

#include <QScreen>
//#include <QDesktopWidget>
//#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //支持中文编码


    //窗体居中显示
    QScreen *screen = QGuiApplication::primaryScreen();
    int width=screen->geometry().width();
    int height=screen->geometry().height();

    frmMain w;
    //设置窗口没有最大化按钮
    w.setWindowFlags(Qt::WindowMinimizeButtonHint);
    w.move((width-w.width())/2,(height-w.height())/2);
    w.setFixedSize(w.width(),w.height());
    w.show();
    //应用样式
    QApplication::setStyle(QStyleFactory::create("Plastique"));
    QApplication::setPalette(QApplication::style()->standardPalette());

    return a.exec();
}
