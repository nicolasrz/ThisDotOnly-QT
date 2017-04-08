#include "ownbutton.h"
#include <QDebug>
OwnButton::OwnButton()
{
}

OwnButton::OwnButton(QPointer<QPushButton> button, int position, QPointer<OwnCustomButton> ownCustomButton)
{
    this->button = button;
    this->position = position;
    this->ownCustomButton = ownCustomButton;
    this->button->setStyleSheet("QPushButton{background-color :" + this->ownCustomButton->getOwnCustomColor()->getHexa()+ ";}");

}

OwnButton::~OwnButton()
{

}

QPointer<QPushButton> OwnButton::getButton()
{
    return this->button;
}
void OwnButton::setButton(QPointer<QPushButton> button)
{
    this->button = button;
}

int OwnButton::getPosition()
{
    return this->position;
}

void OwnButton::setPosition(int pos)
{
    this->position = pos;
}

QPointer<OwnCustomButton> OwnButton::getOwnCustomButton()
{
    return this->ownCustomButton;
}

void OwnButton::setOwnCustomButton(QPointer<OwnCustomButton> ownCustomButton)
{
    this->ownCustomButton = ownCustomButton;
}






