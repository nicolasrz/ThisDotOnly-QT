#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "startscreen.h"
#include "game.h"
#include <QStackedLayout>
#include <QHBoxLayout>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    int heightScreen;
    int widthScreen;

    QPointer<QStackedLayout> stackedLayout;
    QPointer<QHBoxLayout> mainLayout ;
    QPointer<StartScreen> startScreen;
    QPointer<Game> game;

    void initQss();



};

#endif // WIDGET_H
