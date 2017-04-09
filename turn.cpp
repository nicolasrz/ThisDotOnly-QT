#include "turn.h"
#include <QDebug>
#include <QMessageBox>


Turn::Turn()
{
    this->count = 0;
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
    this->count++;
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

int Turn::getDotToKillSize()
{
    return this->dotToKillSize;
}

void Turn::setDotToKillSize(int size)
{
    this->dotToKillSize = size;
}

QVector<QPointer<OwnButton> > Turn::getMultiButtonToKill()
{
    return this->multiButtonToKill;
}

void Turn::addInMultiButtonToKill(QPointer<OwnButton> ownButtonToKill)
{
    this->multiButtonToKill.append(ownButtonToKill);
}

void Turn::clearMultiButtonToKill()
{
    this->multiButtonToKill.clear();
}


QString Turn::getColorAndOr()
{
    return this->colorAndOr;
}

void Turn::setColorAndOr(QString state)
{
    this->colorAndOr = state;
}

