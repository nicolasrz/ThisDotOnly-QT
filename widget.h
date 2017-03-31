#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPointer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "buttoncolor.h"
#include <QLabel>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QPointer<QVBoxLayout> vLayout;
    QPointer<QHBoxLayout> hLayout;
    QPointer<QHBoxLayout> hInfoGame;
    QVector<ButtonColor*> vButtonColor;
    QString colorToKill;
    QStringList listColor;
    QStringList listColorShowed;
    QPointer<QLabel> labelColorToKill;
    QPointer<QLabel> labelTurn;
    int turn;
    int colorToKillSize;


    QString changeColorButtonTo(QString color);
    QString getRandomColorFrom(QStringList list);
    int getRandomNumber();
    QString getRandomColorShowed();
    int getColorToKillSize();



    void init();
    void initQss();
    void initColorList();
    void newTurn();
    void reset();
    void completeListColorShowed(QString colorRandom);
    void lose();

public slots:
    void killThisDot();

};

#endif // WIDGET_H
