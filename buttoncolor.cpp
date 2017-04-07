#include "buttoncolor.h"
#include <QDebug>
ButtonColor::ButtonColor()
{

}

ButtonColor::ButtonColor(QPointer<QPushButton> button, QString color, int pos, QString shape)
{
    this->button = button;
    this->color = color;
    this->position = pos;
    this->shape = shape;

}

ButtonColor::~ButtonColor()
{

}

QPointer<QPushButton> ButtonColor::getButton()
{
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

void ButtonColor::setPosition(int pos)
{
    this->position = pos;
}


QString ButtonColor::getShape()
{
    return this->shape;
}

void ButtonColor::setShape(QString shape)
{
    this->shape = shape;
}




