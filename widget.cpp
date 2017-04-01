#include "widget.h"

#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QLabel>
#include <QFile>

Widget::Widget(QWidget *parent)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    this->heightScreen = screenGeometry.height();
    this->widthScreen = screenGeometry.width();
//    this->setMinimumHeight(this->heightScreen);
//    this->setMinimumWidth(this->widthScreen);



    startScreen = new StartScreen();
    game = new Game();

    stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(startScreen);
    stackedLayout->addWidget(game);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(stackedLayout);

    stackedLayout->setCurrentIndex(0);
    qDebug() << "widget";
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




