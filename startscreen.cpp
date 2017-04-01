#include "startscreen.h"
#include <QDebug>
#include "widget.h"


extern Widget *widget;

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
{
    vStartLayout  = new QVBoxLayout(this);
    buttonStartGame = new QPushButton("Start Game");
    buttonShowScore = new QPushButton("Show Score");
    buttonQuitGame = new QPushButton("Quit Game");

    vStartLayout->addWidget(buttonStartGame);
    vStartLayout->addWidget(buttonShowScore);
    vStartLayout->addWidget(buttonQuitGame);


    connect(buttonStartGame, &QPushButton::clicked, this, &StartScreen::startGame) ;
    connect(buttonShowScore, &QPushButton::clicked, this, &StartScreen::showScore) ;
    connect(buttonQuitGame, &QPushButton::clicked, this, &StartScreen::quitGame) ;
    qDebug() << "startscreen";

}

StartScreen::~StartScreen()
{


}


void StartScreen::startGame()
{
    widget->stackedLayout->setCurrentIndex(1);
}

void StartScreen::showScore()
{

}

void StartScreen::quitGame()
{
    exit(0);
}


