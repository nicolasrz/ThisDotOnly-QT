#include "parameter.h"
#include <QTime>
#include <QDebug>
Parameter::Parameter()
{
    //INIT RANDOM
    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());


    QPointer<OwnCustomColor> green = new OwnCustomColor("Green","#00FF80");
    QPointer<OwnCustomColor> blue = new OwnCustomColor("Blue","#3399FF");
    QPointer<OwnCustomColor> red = new OwnCustomColor("Red","#FF3333");
    QPointer<OwnCustomColor> pink = new OwnCustomColor("Pink","#FF66B2");
    QPointer<OwnCustomColor> orange = new OwnCustomColor("Orange","#FF9933");


    this->listOwnColor.append(green);
    this->listOwnColor.append(blue);
    this->listOwnColor.append(red);
    this->listOwnColor.append(pink);
    this->listOwnColor.append(orange);

    this->listShape << "circle" << "square";

}

Parameter::~Parameter()
{

}



QStringList Parameter::getListShape()
{
    return this->listShape;
}




QPointer<OwnCustomColor> Parameter::getRandomOwnCustomColor(){
    int index = getRandomNumber(0, this->listOwnColor.size()-1);
    return this->listOwnColor.at(index);

}

int Parameter::getRandomNumber(int min, int max){
    return qrand() % ((max + 1) - min) + min;
}
