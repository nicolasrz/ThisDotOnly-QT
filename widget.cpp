#include "widget.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QLabel>
#include <QFile>

Widget::Widget(QWidget *parent)
{
}
Widget::Widget(int dpiX, int dpiY){

    mainLayout = new QHBoxLayout(this);

    startScreen = new StartScreen();
    game = new Game(dpiX, dpiY);

    stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(startScreen);
    stackedLayout->addWidget(game);


    mainLayout->addLayout(stackedLayout);

    stackedLayout->setCurrentIndex(0);
    this->initQss();



}

Widget::~Widget()
{

}


void Widget::initQss()
{
    QFile file(":/css/css/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    setStyleSheet(styleSheet);
}




