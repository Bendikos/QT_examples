#include <QtWidgets>

#include "bronzedialog.h"
#include "bronzestyle.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle(new BronzeStyle);
    BronzeDialog dialog;
    dialog.layout()->setSpacing(7);
    dialog.layout()->setContentsMargins(7, 7, 7, 7);  // 设置所有四个方向的边距为 10 像素

    dialog.show();
    return app.exec();
}
