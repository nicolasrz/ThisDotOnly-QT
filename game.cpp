#include "game.h"
#include <QDateTime>
#include "time.h"

#include <QMessageBox>
#include <QSize>
#include <QDebug>

Game::Game(QWidget *parent)
    : QWidget(parent)
{

    this->init();
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
    this->initColorList();
    this->turn = 1;
    this->lost = false;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,&Game::timerUpdate);
    q = QTime::fromString("00:00:00");
    timer->start(1000);
    this->timerIsCounting = false;


    vLayout = new QVBoxLayout(this);
    hInfoGame = new QHBoxLayout();
    labelColorToKill = new QLabel();
    labelTurn = new QLabel("Turn : " + QString::number(this->turn));
    timeLabel = new QLabel(q.toString("hh:mm:ss"));


    hInfoGame->addWidget(labelColorToKill);
    hInfoGame->addWidget(labelTurn);
    hInfoGame->addWidget(timeLabel);


    vLayout->addLayout(hInfoGame);


    for(int i =0; i < 25 ; ++i){
        if(i%5 == 0){
            hLayout = new QHBoxLayout();
        }

        QPointer<QPushButton> button = new QPushButton();
        QString colorRandom = this->getRandomColorFrom(this->listColor);

        button->setObjectName(QString::number(i));
        button->setStyleSheet(this->changeColorButtonTo(colorRandom));

        this->completeListColorShowed(colorRandom);

        ButtonColor *buttonColor = new ButtonColor(button, colorRandom, i);
        vButtonColor.append(buttonColor);
        connect(button, &QPushButton::clicked, this, &Game::killThisDot) ;
        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }
    this->colorToKill = this->getRandomColorShowed();
    this->colorToKillSize = this->getColorToKillSize();
    labelColorToKill->setText("Kill this dot only ! -> " + this->colorToKill);
    qDebug() << this->colorToKill;
    qDebug() << this->colorToKillSize;


}



QString Game::getRandomColorFrom(QStringList list)
{
    int random = this->getRandomNumber();
    if(random == list.size()){
        random--;
    }
    return list.at(random);
}

int Game::getRandomNumber(){
    int min = 0;
    int max = this->listColor.size();
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

    if(vButtonColor[position]->getColor() == this->colorToKill)
    {
        vButtonColor[position]->getButton()->setStyleSheet(this->changeColorButtonTo("white"));
        --this->colorToKillSize;

        if(this->colorToKillSize == 0){
            qDebug() << "next" ;
            this->lost = false;
            this->newTurn();
        }
    }else
    {
        this->lose();
    }
}

void Game::initColorList(){
    this->listColor << "red" << "blue" << "black" << "yellow" << "grey";
}

QString Game::getRandomColorShowed()
{
    return this->getRandomColorFrom(this->listColorShowed);
}

int Game::getColorToKillSize()
{
    int count = 0;
    for(int i = 0; i< vButtonColor.size(); ++i){
        if(vButtonColor[i]->getColor() == this->colorToKill){
            ++count;
        }
    }
    return count;
}


void Game::newTurn(){
    //this->listColorShowed.clear();
    this->turn++;
    labelTurn->setText("Turn : " + QString::number(this->turn));
    this->doSpecialTurn();
    qDebug() << this->colorToKill;
    qDebug() << this->colorToKillSize;
    qDebug() << "Kill the dot with the color :" + this->colorToKill;
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
    if(!this->listColorShowed.contains(colorRandom)){
        this->listColorShowed.append(colorRandom);
    }
}

void Game::lose()
{
    this->lost = true;

    QMessageBox msgBox;
    msgBox.setText("You loose at turn " + QString::number(this->turn));
    msgBox.exec();
    this->turn = 0 ;
    this->newTurn();
}

void Game::doSpecialTurn(){
    if(this->turn <= 2){
        this->easyTurn();
    }
    else if(this->turn > 2){
        this->easyTurn();
    }else{
        this->easyTurn();
    }
    labelColorToKill->setText("Kill this dot only ! -> " + this->colorToKill);
}

void Game::easyTurn()
{
    qDebug() << "easyTurn";
    QString colorRandom = this->getRandomColorFrom(this->listColor);
    for(int i =0; i< vButtonColor.size(); ++i){
        QString colorRandom = this->getRandomColorFrom(this->listColor);
        vButtonColor[i]->setColor(colorRandom);
        vButtonColor[i]->getButton()->setStyleSheet(this->changeColorButtonTo(colorRandom));
    }
    this->colorToKill = this->getRandomColorShowed();
    this->colorToKillSize = this->getColorToKillSize();

}

void Game::timeTurn(int secondes)
{
    qDebug() << "timeTurn";
    this->easyTurn();
    secondes = secondes * 1000;

}

void Game::timerUpdate()
{
    q = q.addSecs(1);
    timeLabel->setText(q.toString("hh:mm:ss"));
    qDebug() << q.toString("hh:mm:ss");
}
