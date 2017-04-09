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
    //INIT TIME
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,&Game::timerUpdate);
    timer->start(1000);
    timerCounting = false;

    //First Turn
    newTurn();
}

Game::~Game()
{

}


void Game::init()
{
    //INIT GAME
    parameter = new Parameter();
    turn = new Turn();
    buttonToKill = new OwnButton();


    // INIT LAYOUT
    vLayout = new QVBoxLayout(this);
    hInfoGame = new QHBoxLayout();
    labelKill = new QLabel("Kill : ");
    labelButtonToKill = new QLabel();
    labelTurn = new QLabel("Turn : ");
    labelTurnCount = new QLabel();
    labelTime = new QLabel();

    hInfoGame->addWidget(labelKill);
    hInfoGame->addWidget(labelButtonToKill);
    hInfoGame->addWidget(labelTurn);
    hInfoGame->addWidget(labelTurnCount);
    hInfoGame->addWidget(labelTime);

    vLayout->addLayout(hInfoGame);

    initGrille();

}

void Game::initGrille()
{
    for(int i =0; i < 25 ; ++i){
        if(i%5 == 0){
            hLayout = new QHBoxLayout();
        }
        QPointer<QPushButton> button = new QPushButton();
        button->setObjectName(QString::number(i));
        QPointer<OwnCustomColor> randomOwnCustomColor = parameter->getRandomOwnCustomColor();
        QPointer<OwnCustomButton> customButton = new OwnCustomButton(randomOwnCustomColor, "circle");
        QPointer<OwnButton> ownButton = new OwnButton(button, i ,customButton);

        connect(ownButton->getButton(), &QPushButton::clicked, this, &Game::touchDot) ;
        buttonAddedInGrille.append(ownButton);
        hLayout->addWidget(ownButton->getButton());
        vLayout->addLayout(hLayout);
    }
}

void Game::newTurn()
{
    if(turn->hasWin() == false){
        delete turn;
        turn = new Turn();
    }
    touchedDotCount = 0;
    changeButtonInGrille();
    turn->stepIncrement();
    turn->countIncrement();
    int currentTurn = turn->getCount();
    labelTurnCount->setText(QString::number(currentTurn));
    if(currentTurn < 3){
        step3();
    }else if(currentTurn > 3 && currentTurn <= 5){
        step3();
    }else{
        step3();
    }
}


QPointer<OwnButton> Game::getRandomOwnButtonShowed()
{
    int i = parameter->getRandomNumber(0, buttonAddedInGrille.size()-1);
    return buttonAddedInGrille[i];
}

void Game::changeButtonInGrille()
{
    for(int i=0; i < buttonAddedInGrille.size(); ++i){
        QPointer<OwnCustomColor> randomOwnCustomColor = parameter->getRandomOwnCustomColor();
        buttonAddedInGrille[i]->getOwnCustomButton()->setOwnCustomColor(randomOwnCustomColor);
        buttonAddedInGrille[i]->getButton()->setStyleSheet("QPushButton{background-color:"+buttonAddedInGrille[i]->getOwnCustomButton()->getOwnCustomColor()->getHexa()+"}");
        buttonAddedInGrille[i]->getButton()->setEnabled(true);
    }
}

void Game::removeOwnButtonFromGrille(QPointer<OwnButton> ownButtonToRemove)
{
    int pos = ownButtonToRemove->getPosition();
    buttonAddedInGrille[pos]->getButton()->setStyleSheet("QPushButton{background-color:white}");
}


int Game::getNumberOfDotToKill(QPointer<OwnButton> ownButtonToKill)
{
    int count = 0;
    for(int i = 0; i< buttonAddedInGrille.size(); ++i){
        if(buttonAddedInGrille[i]->getOwnCustomButton()->getOwnCustomColor()->getHexa()
                == ownButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getHexa()){
            ++count;
        }
    }
    return count;
}

void Game::step1(){
    qDebug() << "Step 1";
    QPointer<OwnButton> ownButtonToKill = getRandomOwnButtonShowed();
    turn->setButtonToKill(ownButtonToKill);
    turn->setDotToKillSize(getNumberOfDotToKill(turn->getOwnButtonToKill()));
    labelButtonToKill->setText(ownButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getName());
}

void Game::toWinStep1(int position)
{
    if(buttonAddedInGrille[position]->getOwnCustomButton()->getOwnCustomColor()->getHexa() ==
            turn->getOwnButtonToKill()->getOwnCustomButton()->getOwnCustomColor()->getHexa()){
        buttonAddedInGrille[position]->getButton()->setDisabled(true);
        removeOwnButtonFromGrille(buttonAddedInGrille[position]);
        touchedDotCountIncrement();
        if(turn->getDotToKillSize() == getTouchedDotCount() ){
            turn->setWin(true);
            newTurn();
        }
    }else{
        qTime = QTime::fromString("00:00:00");
        labelTime->setText(qTime.toString(""));
        timerCounting = false;
        turn->setWin(false);
        newTurn();
    }

}

void Game::step2()
{
    qDebug() << "Step 2";
    QPointer<OwnButton> ownButtonToKill = getRandomOwnButtonShowed();
    turn->setButtonToKill(ownButtonToKill);
    turn->setDotToKillSize(getNumberOfDotToKill(turn->getOwnButtonToKill()));

    labelButtonToKill->setText(ownButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getName());
    qTime = QTime::fromString("00:00:10");
    labelTime->setText(qTime.toString("ss"));
    timerCounting = true;
}

void Game::toWinStep2(int position){
    toWinStep1(position);
}

void Game::step3()
{
    qDebug() << "Step3";
    turn->clearMultiButtonToKill();
    QPointer<OwnButton> firstButtonToKill =  getRandomOwnButtonShowed();
    QPointer<OwnButton> secondButtonToKill =  getRandomOwnButtonShowed();
    while(firstButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getHexa() ==
          secondButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getHexa()){
            secondButtonToKill =  getRandomOwnButtonShowed();
    }
    turn->addInMultiButtonToKill(firstButtonToKill);
    turn->addInMultiButtonToKill(secondButtonToKill);

    //int andOr = parameter->getRandomNumber(0, 1);
    int andOr = 1;
    if(andOr == 0){
        turn->setColorAndOr("or");
        labelButtonToKill->setText(firstButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getName() +" OR " +
                                   secondButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getName());
    }else{
        turn->setColorAndOr("and");
        labelButtonToKill->setText(firstButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getName() +" AND " +
                                   secondButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getName());

        turn->setDotToKillSize(getNumberOfDotToKill(firstButtonToKill) +
                               getNumberOfDotToKill(secondButtonToKill));
    }

    timerCounting = false;

}

void Game::toWinStep3(int position)
{
    if("and" == "and"){
    //if(turn->getColorAndOr() == "and"){
        touchedDotCountIncrement();

        if(buttonAddedInGrille[position]->getOwnCustomButton()->getOwnCustomColor()->getHexa() ==
                turn->getMultiButtonToKill()[0]->getOwnCustomButton()->getOwnCustomColor()->getHexa()
                ||
                buttonAddedInGrille[position]->getOwnCustomButton()->getOwnCustomColor()->getHexa() ==
                turn->getMultiButtonToKill()[1]->getOwnCustomButton()->getOwnCustomColor()->getHexa()
                ){
            removeOwnButtonFromGrille(buttonAddedInGrille[position]);
            if(turn->getDotToKillSize() == getTouchedDotCount()){
                turn->setWin(true);
                newTurn();
            }

        }else{
            turn->setWin(false);
            newTurn();
        }
    }
}

void Game::touchDot()
{
    QTextStream out(stdout);
    QObject *senderObj = sender(); // This will give Sender object
    int position = senderObj->objectName().toInt();
    int step = turn->getStep();
    switch (step) {
    case 1:
        toWinStep3(position);
        break;
//    case 2:
//        toWinStep2(position);
//        break;
    default:
        toWinStep3(position);
        break;
    }
}

void Game::touchedDotCountIncrement(){
    touchedDotCount++;
}
int Game::getTouchedDotCount(){
    return touchedDotCount;
}

void Game::timerUpdate()
{
    if(timerCounting){
        qTime = qTime.addSecs(-1);
        labelTime->setText(qTime.toString("ss"));
        if(qTime.toString("ss").toInt() == 0){
            qTime = QTime::fromString("00:00:00");
            labelTime->setText(qTime.toString(""));
            timerCounting = false;
            turn->setWin(false);
            newTurn();
        }
    }
}




