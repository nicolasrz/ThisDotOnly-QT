#include "widget.h"
#include <QApplication>

Widget * widget;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int dpiX = a.desktop()->logicalDpiX();
    int dpiY = a.desktop()->logicalDpiY();

    widget = new Widget(dpiX, dpiY);

    widget->show();

    return a.exec();
}
