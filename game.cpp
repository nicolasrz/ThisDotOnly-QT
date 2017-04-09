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

    hInfoGame->addWidget(labelKill);
    hInfoGame->addWidget(labelButtonToKill);

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
    changeButtonInGrille();
    turn->stepIncrement();
    turn->countIncrement();
    int currentTurn = turn->getCount();
    switch (currentTurn) {
    case 1:
        step1();
        break;
    default:
        break;
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
    QPointer<OwnButton> ownButtonToKill = getRandomOwnButtonShowed();
    turn->setButtonToKill(ownButtonToKill);
    turn->setDotToKillSize(getNumberOfDotToKill(turn->getOwnButtonToKill()));
    labelButtonToKill->setText(ownButtonToKill->getOwnCustomButton()->getOwnCustomColor()->getName());
}

void Game::toWinStep1(int position)
{
    if(buttonAddedInGrille[position]->getOwnCustomButton()->getOwnCustomColor()->getHexa() ==
            turn->getOwnButtonToKill()->getOwnCustomButton()->getOwnCustomColor()->getHexa()){
        turn->touchedDotIncrement();
        removeOwnButtonFromGrille(buttonAddedInGrille[position]);
        if(turn->getDotToKillSize() == turn->getTouchedDot() ){
            qDebug() << "win";
            newTurn();
        }
    }else{
        turn->setWin(false);
        newTurn();
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
        toWinStep1(position);
        break;
    default:
        break;
    }
}






