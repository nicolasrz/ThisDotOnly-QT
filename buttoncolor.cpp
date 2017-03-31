#include "buttoncolor.h"
#include <QDebug>
ButtonColor::ButtonColor()
{

}

ButtonColor::ButtonColor(QPointer<QPushButton> button, QString color, int pos)
{
    this->button = button;
    this->color = color;
    this->position = pos;
}

ButtonColor::~ButtonColor()
{

}

QPointer<QPushButton> ButtonColor::getButton()
{
    qDebug() << "test";
    return this->button;
}
void ButtonColor::setButton(QPointer<QPushButton> button)
{
    this->button = button;
}

QString ButtonColor::getColor()
{
    return this->color;
}

void ButtonColor::setColor(QString color)
{
    this->color = color;
}

int ButtonColor::getPosition()
{
    return this->position;
}

void ButtonColor::setPOsition(int pos)
{
    this->position = pos;
}




