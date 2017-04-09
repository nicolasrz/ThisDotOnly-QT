#include "killthis.h"
#include <QDebug>
#include <QGuiApplication>
KillThis::KillThis(QWidget *parent, QPointer<OwnCustomColor> color, QString shape, QString message)
{
    hLayout = new QHBoxLayout(this);
    this->setStyleSheet("KillThis{background-color:white;}");

    QPointer<QPushButton> button = new QPushButton();
    button->setStyleSheet("QPushButton{background-color : " + color->getHexa()+";}");
    qDebug() <<  parent->x();
    qDebug() <<  parent->y();
    qDebug() <<  parent->width();
    qDebug() <<  parent->height();
    hLayout->addWidget(button);


    move( 0,0 );

    this->show();
}

KillThis::~KillThis()
{

}
