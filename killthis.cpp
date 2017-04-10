#include "killthis.h"
#include <QDebug>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
KillThis::KillThis(QWidget *parent, QPointer<OwnCustomColor> color, QString shape, QString message)
{

    vLayout = new QVBoxLayout(this);
    this->setStyleSheet("KillThis{background-color:white;}");
    labelKill = new QLabel(message);
    QPointer<QPushButton> button = new QPushButton();
    button->setStyleSheet("QPushButton{"
                          "background-color : " + color->getHexa()+";"
                          "border-style: solid;"
                          "border-width:1px;"
                          "border-radius:25px;"
                          "max-width:50px;"
                          "max-height:50px;"
                          "min-width:50px;"
                          "min-height:50px;}");
    gridLayout = new QGridLayout();
    gridLayout->addWidget(button,0,1);

    vLayout->addWidget(labelKill);
    vLayout->addLayout(gridLayout);
    connect(button, &QPushButton::clicked, this, &KillThis::iUnderstand) ;
    setWindowFlags( Qt::CustomizeWindowHint );
    this->adjustSize();
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    this->show();
}

KillThis::~KillThis()
{

}

void KillThis::iUnderstand()
{
    this->close();
}
