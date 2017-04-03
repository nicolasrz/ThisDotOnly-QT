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
    initTimer();


    vLayout = new QVBoxLayout(this);
    hInfoGame = new QHBoxLayout();
    labelColorToKill = new QLabel();
    labelTurn = new QLabel("Turn : " + QString::number(this->turn));
    timeLabel = new QLabel(q.toString("ss"));


    hInfoGame->addWidget(labelColorToKill);
    hInfoGame->addWidget(labelTurn);
    vLayout->addLayout(hInfoGame);
    initGrille();
    addRandomColorInGrill();
}

void Game::initGrille()
{
    for(int i =0; i < 25 ; ++i){
        if(i%5 == 0){
            hLayout = new QHBoxLayout();
        }

        QPointer<QPushButton> button = new QPushButton();
        button->setObjectName(QString::number(i));
        ButtonColor *buttonColor = new ButtonColor(button, "white", i);
        vButtonColor.append(buttonColor);
        connect(button, &QPushButton::clicked, this, &Game::killThisDot) ;
        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }
}

void Game::addRandomColorInGrill()
{
    for(int i =0; i< vButtonColor.size(); ++i){
        QString colorRandom = this->getRandomColorFrom(this->listColor);
        vButtonColor[i]->setColor(colorRandom);
        vButtonColor[i]->getButton()->setStyleSheet(this->changeColorButtonTo(colorRandom));
        this->completeListColorShowed(colorRandom);
    }
    this->colorToKill = this->getRandomColorShowed();
    this->colorToKillName = hashColor.key(this->colorToKill);
    this->colorToKillSize = this->getColorToKillSize();
    this->labelColorToKill->setText(this->colorToKillName);
    qDebug() << this->colorToKill;
    qDebug() << this->colorToKillName;
    qDebug() << this->colorToKillSize;
}

void Game::initTimer()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,&Game::timerUpdate);
    q = QTime::fromString("00:00:05");
    timer->start(1000);
    this->timerIsCounting = false;
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
    hashColor.insert("Green","#00FF80");
    hashColor.insert("Blue","#3399FF");
    hashColor.insert("Red","#FF3333");
    hashColor.insert("Pink","#FF66B2");
    hashColor.insert("Orange","#FF9933");
    this->listColor << hashColor.value("Green") <<hashColor.value("Blue") << hashColor.value("Red") << hashColor.value("Pink") << hashColor.value("Orange");
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
    this->timerIsCounting = false;

    QMessageBox msgBox;
    msgBox.setText("You loose at turn " + QString::number(this->turn));
    msgBox.exec();
    timeLabel->setText("");
    this->turn = 0 ;
    this->newTurn();
}
void Game::timerUpdate()
{
    if(this->timerIsCounting){
        q = q.addSecs(-1);
        timeLabel->setText(q.toString("ss"));
        if(q.toString("ss").toInt() == 0){
            this->lose();
        }
    }
}


void Game::newTurn(){
    this->turn++;
    this->timerIsCounting = false;
    labelTurn->setText("Turn : " + QString::number(this->turn));
    this->caseTurn();
    qDebug() << this->colorToKill;
    qDebug() << this->colorToKillSize;
    qDebug() << "Kill the dot with the color :" + this->colorToKill;
}
void Game::caseTurn(){
    if(this->turn <= 2){
        this->firstStep();
    }
    else if(this->turn > 2){
        this->secondStep();
    }else{
        this->firstStep();
    }
    labelColorToKill->setText(this->colorToKillName);

}

void Game::firstStep()
{
    this->addRandomColorInGrill();
}

void Game::secondStep()
{
    this->timerIsCounting = true;
    q = QTime::fromString("00:00:05");
    timeLabel->setText(q.toString("ss"));
    hInfoGame->addWidget(timeLabel);
    this->addRandomColorInGrill();
}


