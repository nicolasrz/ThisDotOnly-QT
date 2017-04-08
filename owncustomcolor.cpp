#include "owncustomcolor.h"

OwnCustomColor::OwnCustomColor()
{

}

OwnCustomColor::OwnCustomColor(QString name, QString hexa)
{
    this->name = name;
    this->hexa = hexa;
}

OwnCustomColor::~OwnCustomColor()
{

}

QString OwnCustomColor::getHexa()
{
    return this->hexa;
}

QString OwnCustomColor::getName()
{
    return this->name;
}

