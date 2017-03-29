#include "widget.h"
#include <QSize>
#include <QDebug>
#include <QPushButton>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    QPushButton * button = new QPushButton("1");
    QPushButton * button2 = new QPushButton("2");
    gridLayout->addWidget(button,0,0);
    gridLayout->addWidget(button2,0,1);

}

Widget::~Widget()
{

}
