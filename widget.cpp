#include "widget.h"
#include <QSize>
#include <QDebug>
#include <QPushButton>
#include <QDateTime>
#include "time.h"
#include <QFile>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->init();
    this->initQss();

}

Widget::~Widget()
{

}

void Widget::init()
{
    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    this->initColorList();
    this->turn = 0;


    vLayout = new QVBoxLayout(this);
    hInfoGame = new QHBoxLayout();
    labelColorToKill = new QLabel();
    labelTurn = new QLabel("Turn : " + QString::number(this->turn));


    hInfoGame->addWidget(labelColorToKill);
    hInfoGame->addWidget(labelTurn);
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
        connect(button, &QPushButton::clicked, this, &Widget::killThisDot) ;
        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }
    this->colorToKill = this->getRandomColorShowed();
    this->colorToKillSize = this->getColorToKillSize();
    labelColorToKill->setText("Kill this dot only ! -> " + this->colorToKill);
    qDebug() << this->colorToKill;
    qDebug() << this->colorToKillSize;


}

void Widget::initQss()
{
    QFile file(":/css/css/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    setStyleSheet(styleSheet);
}

QString Widget::getRandomColorFrom(QStringList list)
{
    int random = this->getRandomNumber();
    if(random == list.size()){
        random--;
    }
    return list.at(random);
}

int Widget::getRandomNumber(){
    int min = 0;
    int max = this->listColor.size();
    return qrand() % ((max + 1) - min) + min;
}

QString Widget::changeColorButtonTo(QString color)
{
    QString styleSheet = "QPushButton{background-color :"+color+";border:"+color+";}";
    return styleSheet;
}

void Widget::killThisDot(){
    QTextStream out(stdout);
    QObject *senderObj = sender(); // This will give Sender object
    int position = senderObj->objectName().toInt();

    if(vButtonColor[position]->getColor() == this->colorToKill)
    {
        vButtonColor[position]->getButton()->setStyleSheet(this->changeColorButtonTo("white"));
        --this->colorToKillSize;

        if(this->colorToKillSize == 0){
            qDebug() << "next" ;
            this->newTurn();
        }
    }else
    {
        this->lose();
    }
}


void Widget::initColorList(){
    this->listColor << "red" << "blue" << "black" << "yellow" << "grey";
}

QString Widget::getRandomColorShowed()
{
    return this->getRandomColorFrom(this->listColorShowed);
}

int Widget::getColorToKillSize()
{
    int count = 0;
    for(int i = 0; i< vButtonColor.size(); ++i){
        if(vButtonColor[i]->getColor() == this->colorToKill){
            ++count;
        }
    }
    return count;
}


void Widget::newTurn(){
    //this->listColorShowed.clear();
    this->turn++;
    labelTurn->setText("Turn : " + QString::number(this->turn));
    QString colorRandom = this->getRandomColorFrom(this->listColor);
    for(int i =0; i< vButtonColor.size(); ++i){
        QString colorRandom = this->getRandomColorFrom(this->listColor);
        vButtonColor[i]->setColor(colorRandom);
        vButtonColor[i]->getButton()->setStyleSheet(this->changeColorButtonTo(colorRandom));
    }
    this->colorToKill = this->getRandomColorShowed();
    this->colorToKillSize = this->getColorToKillSize();
    labelColorToKill->setText("Kill this dot only ! -> " + this->colorToKill);
    qDebug() << this->colorToKill;
    qDebug() << this->colorToKillSize;
    qDebug() << "Kill the dot with the color :" + this->colorToKill;
}

void Widget::reset()
{
    for(int i = 0; i< vButtonColor.size(); ++i){
        delete vButtonColor[i];
    }
    delete vLayout;
}

void Widget::completeListColorShowed(QString colorRandom)
{
    if(!this->listColorShowed.contains(colorRandom)){
        this->listColorShowed.append(colorRandom);
    }
}

void Widget::lose()
{
    QMessageBox msgBox;
    msgBox.setText("You loose ! You success to the turn " + QString::number(this->turn));
    msgBox.exec();
}
