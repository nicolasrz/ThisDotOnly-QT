#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include "buttoncolor.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPointer>
#include <QTimer>
#include <QTime>
class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    ~Game();

    QPointer<QVBoxLayout> vLayout;
    QPointer<QHBoxLayout> hLayout;
    QPointer<QHBoxLayout> hInfoGame;
    QVector<ButtonColor*> vButtonColor;
    QString colorToKill;
    QStringList listColor;
    QStringList listColorShowed;
    QPointer<QLabel> labelColorToKill;
    QPointer<QLabel> labelTurn;
    QPointer <QTimer> timer;
    QTime q;
    QPointer <QLabel> timeLabel;
    int turn;
    int colorToKillSize;
    bool lost;
    bool timerIsCounting;

    QString changeColorButtonTo(QString color);
    QString getRandomColorFrom(QStringList list);
    int getRandomNumber();
    QString getRandomColorShowed();
    int getColorToKillSize();

    void init();

    void initColorList();
    void newTurn();
    void reset();
    void completeListColorShowed(QString colorRandom);
    void lose();
    void caseTurn();
    void firstStep();
public slots:
    void killThisDot();
    void timerUpdate();
};

#endif // GAME_H
