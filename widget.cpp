#include "widget.h"
#include <QSize>
#include <QDebug>
#include <QPushButton>
#include <QDateTime>
#include "time.h"
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->init();
    this->initQss();
    this->newTurn();
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
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


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
    qDebug() << "clicked";
    QTextStream out(stdout);
    QObject *senderObj = sender(); // This will give Sender object
    QString senderObjName = senderObj->objectName();

//    if(colorButton == this->colorToKill)
//    {
//        ->setStyleSheet(this->changeColorButtonTo("white"));
//    }else{
//        QMessageBox msgBox;
//        msgBox.setText("Lose !");
//        msgBox.exec();
//    }
}


void Widget::initColorList(){
    this->listColor << "red" << "blue" << "black" << "yellow" << "grey";
}

QString Widget::getRandomColorShowed()
{
    return this->getRandomColorFrom(this->listColorShowed);
}


void Widget::newTurn(){
    this->initColorList();

    for(int i=0; i < vButtonColor.size(); ++i){
        connect(vButtonColor[i]->getButton(), &QPushButton::clicked, this, &Widget::killThisDot) ;
    }
    this->turn = 0;
    vLayout = new QVBoxLayout(this);

    for(int i =0; i < 25 ; ++i){
        if(i%5 == 0){
            hLayout = new QHBoxLayout();
        }

        QPointer<QPushButton> button = new QPushButton();
        QString colorRandom = this->getRandomColorFrom(this->listColor);

        button->setObjectName(QString::number(i));
        button->setStyleSheet(this->changeColorButtonTo(colorRandom));

        if(!this->listColorShowed.contains(colorRandom)){
            this->listColorShowed.append(colorRandom);
        }

        ButtonColor *buttonColor = new ButtonColor(button, colorRandom, i);
        vButtonColor.append(buttonColor);

        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }

    this->colorToKill = this->getRandomColorShowed();
    qDebug() << "Kill the dot with the color :" + this->colorToKill;
}
