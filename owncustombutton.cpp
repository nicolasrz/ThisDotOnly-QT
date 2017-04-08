#include "owncustombutton.h"

OwnCustomButton::OwnCustomButton()
{

}

OwnCustomButton::OwnCustomButton(QPointer<OwnCustomColor> customColor, QString shape)
{
    this->customColor = customColor;
    this->shape = shape;
}

OwnCustomButton::~OwnCustomButton()
{

}


void OwnCustomButton::setShape(QString shape)
{
    this->shape = shape;
}

QString OwnCustomButton::getShape()
{
    return this->shape;
}

QPointer<OwnCustomColor> OwnCustomButton::getOwnCustomColor(){
    return this->customColor;
}

void OwnCustomButton::setOwnCustomColor(QPointer<OwnCustomColor> customColor){
    this->customColor = customColor;
}
