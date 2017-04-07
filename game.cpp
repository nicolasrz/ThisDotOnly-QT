#include "game.h"
#include <QDateTime>
#include "time.h"
#include <QMessageBox>
#include <QSize>
#include <QDebug>

Game::Game(QWidget *parent)
    : QWidget(parent)
{

    init();
}

Game::~Game()
{

}

void Game::init()
{
    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    initColorList();
    initShape();
    turn = 0;
    lost = false;
    currentStep = 0;
    initTimer();


    vLayout = new QVBoxLayout(this);
    hInfoGame = new QHBoxLayout();
    labelColorToKill = new QLabel();
    labelTurn = new QLabel("Turn : " + QString::number(turn));
    timeLabel = new QLabel(q.toString("ss"));


    hInfoGame->addWidget(labelColorToKill);
    hInfoGame->addWidget(labelTurn);
    vLayout->addLayout(hInfoGame);
    lastRandomColor = "white";
    colorToKill = "white";
    initGrille();
    addRandomColorInGrill(false);
    newTurn();
}

void Game::initGrille()
{
    for(int i =0; i < 25 ; ++i){
        if(i%5 == 0){
            hLayout = new QHBoxLayout();
        }

        QPointer<QPushButton> button = new QPushButton();
        button->setObjectName(QString::number(i));
        ButtonColor *buttonColor = new ButtonColor(button, "white", i, "circle");
        vButtonColor.append(buttonColor);
        connect(button, &QPushButton::clicked, this, &Game::killThisDot) ;
        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }
}

void Game::addRandomColorInGrill(bool changeShape)
{
    listColorShowed.clear();
    listShapeShowed.clear();

    for(int i =0; i< vButtonColor.size(); ++i){
        QString colorRandom = getRandomColorFrom(listColor);
        vButtonColor[i]->setColor(colorRandom);
        completeListColorShowed(colorRandom);

        if(changeShape){
            QString shapeRandom = getRandomShape(listShape);
            completeListShapeShowed(shapeRandom);
            if(shapeRandom == "square"){
                vButtonColor[i]->getButton()->setStyleSheet("QPushButton#"+QString::number(i)+"{ border-radius:0px; background-color:"+colorRandom+"}");
            }
            vButtonColor[i]->setShape(shapeRandom);
        }else{
            vButtonColor[i]->getButton()->setStyleSheet(changeColorButtonTo(colorRandom));
        }

    }


}

void Game::initTimer()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,&Game::timerUpdate);
    q = QTime::fromString("00:00:05");
    timer->start(1000);
    timerIsCounting = false;
}

QString Game::getRandomColorFrom(QStringList list)
{
    int random = getRandomNumber();
    if(random == list.size()){
        random--;
    }
    return list.at(random);
}

QString Game::getRandomShape(QStringList list)
{
    int random = getRandomNumber(0,1);
    if(random == list.size()){
        random--;
    }
    return list.at(random);
}

int Game::getRandomNumber(){
    int min = 0;
    int max = listColor.size();
    return qrand() % ((max + 1) - min) + min;
}
int Game::getRandomNumber(int min,  int max){
    return qrand() % ((max + 1) - min) + min;
}

QString Game::changeColorButtonTo(QString color)
{
    QString styleSheet = "QPushButton{background-color :"+color+";border:"+color+";}";
    return styleSheet;
}


void Game::killThisDot(){
    QTextStream out(stdout);
    QObject *senderObj = sender(); // This will give Sender object
    int position = senderObj->objectName().toInt();

    switch (currentStep) {
    case 1:
        toWinStep1and2(position);
        break;
    case 2:
        toWinStep1and2(position);
        break;
    case 3:
        toWinStep3(position);
        break;
    case 4:
        toWinStep4(position);
    default:
        break;
    }


}

void Game::initColorList(){
    hashColor.insert("Green","#00FF80");
    hashColor.insert("Blue","#3399FF");
    hashColor.insert("Red","#FF3333");
    hashColor.insert("Pink","#FF66B2");
    hashColor.insert("Orange","#FF9933");
    listColor << hashColor.value("Green") <<hashColor.value("Blue") << hashColor.value("Red") << hashColor.value("Pink") << hashColor.value("Orange");
}

void Game::initShape(){
    listShape << "circle" <<  "square";
}

QString Game::getRandomColorShowed()
{
    return getRandomColorFrom(listColorShowed);
}

int Game::getColorToKillSize(QString color)
{
    int count = 0;
    for(int i = 0; i< vButtonColor.size(); ++i){
        if(vButtonColor[i]->getColor() == color){
            ++count;
        }
    }
    return count;
}

void Game::reset()
{
    for(int i = 0; i< vButtonColor.size(); ++i){
        delete vButtonColor[i];
    }
    delete vLayout;
}

void Game::completeListColorShowed(QString colorRandom)
{
    if(!listColorShowed.contains(colorRandom)){
        listColorShowed.append(colorRandom);
    }
}
void Game::completeListShapeShowed(QString shapeRandom)
{
    if(!listShapeShowed.contains(shapeRandom)){
        listShapeShowed.append(shapeRandom);
    }
}

void Game::lose()
{
    lost = true;
    timerIsCounting = false;

    QMessageBox msgBox;
    msgBox.setText("You loose at turn " + QString::number(turn));
    msgBox.exec();
    timeLabel->setText("");
    turn = 0 ;
    newTurn();
}
void Game::timerUpdate()
{
    if(timerIsCounting){
        q = q.addSecs(-1);
        timeLabel->setText(q.toString("ss"));
        if(q.toString("ss").toInt() == 0){
            lose();
        }
    }
}


void Game::newTurn(){
    turn++;
    timerIsCounting = false;
    colorToKill = lastRandomColor;
    labelTurn->setText("Turn : " + QString::number(turn));

    if(turn <= 4){
        step4();
    }
    else if(turn > 4 &&  turn <= 8){
        step2();
    }else if(turn > 8){
            step3();

    }/*else{
        step3();
    }*/

}


QString Game::colorDifferent(QString last, QString current)
{
    while(current == last){
        current = getRandomColorShowed();
    }
    return current;
}


void Game::step1()
{
    qDebug() << "Step1";
    currentStep = 1;
    addRandomColorInGrill(false);
    colorToKill = colorDifferent(lastRandomColor, colorToKill);
    lastRandomColor = colorToKill;
    colorToKillName = hashColor.key(colorToKill);
    labelColorToKill->setText(colorToKillName);
    qDebug() << colorToKillName;
    qDebug() << colorToKillSize;
    colorToKillSize = getColorToKillSize(colorToKill);

}

void Game::step2()
{
    qDebug() << "Step2";
    currentStep = 2;
    q = QTime::fromString("00:00:05");
    timeLabel->setText(q.toString("ss"));
    hInfoGame->addWidget(timeLabel);
    addRandomColorInGrill(false);
    colorToKill = colorDifferent(lastRandomColor, colorToKill);
    lastRandomColor = colorToKill;
    colorToKillName = hashColor.key(colorToKill);
    labelColorToKill->setText(colorToKillName);
    qDebug() << colorToKillName;
    qDebug() << colorToKillSize;
    colorToKillSize = getColorToKillSize(colorToKill);
    timerIsCounting = true;
}
void Game::toWinStep1and2(int position)
{
    if(vButtonColor[position]->getColor() == colorToKill)
    {
        vButtonColor[position]->getButton()->setStyleSheet(changeColorButtonTo("white"));
        vButtonColor[position]->setColor("white");
        --colorToKillSize;

        if(colorToKillSize == 0){
            lost = false;
            newTurn();
        }
    }else
    {
        lose();
    }
}



void Game::step3()
{
    qDebug() << "Step3";
    currentStep = 3;


    addRandomColorInGrill(false);

    QString firstColor = getRandomColorShowed();
    QString secondColor = colorDifferent(firstColor, firstColor);
    colorAndOr.clear();
    colorAndOr.append(firstColor);
    colorAndOr.append(secondColor);

    andor = getRandomNumber(0,1);
    //AND
    if(andor == 0){
        labelColorToKill->setText(hashColor.key(firstColor)+ " AND " + hashColor.key(secondColor));
        colorToKillSize = getColorToKillSize(firstColor) + getColorToKillSize(secondColor);
        q = QTime::fromString("00:00:10");
    //OR
    }else{
        colorToKillSize = 0;
        nbClick = 0;
        colorChoosen = "white";
        labelColorToKill->setText(hashColor.key(firstColor)+ " OR " + hashColor.key(secondColor));
        q = QTime::fromString("00:00:07");
    }
    timeLabel->setText(q.toString("ss"));
    hInfoGame->addWidget(timeLabel);
    timerIsCounting = true;
}


void Game::toWinStep3(int position)
{
    QString  colorClicked = vButtonColor[position]->getColor();
    //0 alors AND et timer à 10
    if(andor == 0){
        QString firstColor = colorAndOr[0];
        QString secondColor = colorAndOr[1];
        if( colorClicked == firstColor || colorClicked == secondColor){
            vButtonColor[position]->getButton()->setStyleSheet(changeColorButtonTo("white"));
            vButtonColor[position]->setColor("white");
            --colorToKillSize;
            if(colorToKillSize == 0){
                lost = false;
                newTurn();
            }
        }else{
            lose();
        }
        //OR
    }else{
        nbClick++;
        if(nbClick == 1){
            colorChoosen = vButtonColor[position]->getColor();
            colorToKillSize = getColorToKillSize(colorChoosen);
        }
        if(vButtonColor[position]->getColor() == colorChoosen){
            --colorToKillSize;
            vButtonColor[position]->getButton()->setStyleSheet(changeColorButtonTo("white"));
            vButtonColor[position]->setColor("white");

            if(colorToKillSize == 0){
                lost = false;
                newTurn();
            }

        }else{
            this->lose();
        }
    }
}

void Game::step4(){
    qDebug() << "Step4";
    currentStep = 4;
    addRandomColorInGrill(true);

    shapeOr = getRandomShape(listShape);
    //circle
    if(shapeOr == "circle"){

    //square
    }else{

    }
}

void Game::toWinStep4(int position){

}





