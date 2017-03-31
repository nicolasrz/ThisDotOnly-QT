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
    for(QMap<int, QMap<QPointer<QPushButton>, QString> >::Iterator it = map->begin(); it != map->end();++it){
        connect(it.value()., &QPushButton::clicked, this, &Widget::killThisDot) ;
    }

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
    this->newTurn();

}

void Widget::initQss()
{
    QFile file(":/css/css/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    file.close();
    setStyleSheet(styleSheet);
}

QString Widget::getRandomColor(QStringList list)
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

QString Widget::changeColorButton(QString color)
{
    QString styleSheet = "QPushButton{background-color :"+color+";border:"+color+";}";
    return styleSheet;
}

void Widget::killThisDot(){
    QTextStream out(stdout);
    QObject *senderObj = sender(); // This will give Sender object
    QString senderObjName = senderObj->objectName();
//    QPointer<QPushButton> button = map->value(senderObjName.toInt());
//    button->
//    if(colorButton == this->colorToKill)
//    {
//        ->setStyleSheet(this->changeColorButton("white"));
//    }else{
//        QMessageBox msgBox;
//        msgBox.setText("Lose !");
//        msgBox.exec();
//    }
}

void Widget::newTurn(){
    this->initColorList();
    map = new QMap<int, QMap<QPointer<QPushButton>, QString>>();
    this->turn = 0;
    vLayout = new QVBoxLayout(this);

    for(int i =0; i < 25 ; ++i){
        if(i%5 == 0){
            hLayout = new QHBoxLayout();
        }
        QPointer<QPushButton> button = new QPushButton();
        button->setObjectName(QString::number(i));
        QString colorRandom = this->getRandomColor(this->listColor);
        button->setStyleSheet(this->changeColorButton(colorRandom));
        if(!this->listColorShowed.contains(colorRandom)){
            this->listColorShowed.append(colorRandom);
        }
        QMap<QPointer<QPushButton>,QString> buttonColor;
        buttonColor.insert(button,colorRandom);
        map->insert(i, buttonColor);
        hLayout->addWidget(button);
        vLayout->addLayout(hLayout);
    }

    this->colorToKill = this->getRandomColorShowed();
    qDebug() << "Kill the dot with the color :" + this->colorToKill;
}

void Widget::initColorList(){
    //listColor = new QStringList();
    this->listColor << "red" << "blue" << "black" << "yellow" << "grey";
}

QString Widget::getRandomColorShowed()
{

    return this->getRandomColor(this->listColorShowed);

}
