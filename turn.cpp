#include "turn.h"
#include <QDebug>
#include <QMessageBox>


Turn::Turn()
{
    this->count = 0;
    this->step = 0;
    this->touchedDot = 0;
}

Turn::~Turn()
{

}

int Turn::getCount()
{
    return this->count;
}

void Turn::countIncrement()
{
    ++this->count;
}

QPointer<OwnButton> Turn::getOwnButtonToKill()
{
    return this->ownButtonToKill;
}

void Turn::setButtonToKill(QPointer<OwnButton> ownButtonToKill)
{
    this->ownButtonToKill = ownButtonToKill;
}

QString Turn::getTimeLabel()
{
    return this->timeLabel;
}

void Turn::setTimeLabel(QString time)
{
    this->timeLabel = time;
}

void Turn::setWin(bool state)
{
    this->win = state;
    if(this->win){
        qDebug() << "win";
    }else{
        QMessageBox msgBox;
        msgBox.setText("You loose at turn " + QString::number(this->count));
        msgBox.exec();
    }
}

bool Turn::hasWin()
{
    return this->win;
}

void Turn::stepIncrement()
{
    ++this->step;
}

int Turn::getDotToKillSize()
{
    return this->dotToKillSize;
}

void Turn::setDotToKillSize(int size)
{
    this->dotToKillSize = size;
}

int Turn::getTouchedDot()
{
    return this->touchedDot;
}

void Turn::touchedDotIncrement()
{
    ++this->touchedDot;
}

int Turn::getStep()
{
    return this->step;
}
