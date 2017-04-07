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
    QString colorToKillName;
    QString lastRandomColor;
    QStringList listColor;
    QStringList listColorShowed;
    QPointer<QLabel> labelColorToKill;
    QPointer<QLabel> labelTurn;
    QPointer <QTimer> timer;
    QTime q;
    QPointer <QLabel> timeLabel;
    QHash<QString, QString> hashColor;
    QStringList colorAndOr;
    QString colorChoosen;
    QStringList listShape;
    QStringList listShapeShowed;
    int nbClick;
    int andor;
    int shapeOr;
    int currentStep;
    int turn;
    int colorToKillSize;
    bool lost;
    bool timerIsCounting;


    QString changeColorButtonTo(QString color);
    QString changeShapeButtonTo(QString shape);
    QString getRandomColorFrom(QStringList list);
    QString getRandomColorShowed();

    int getRandomNumber();
    int getRandomNumber(int min, int max);
    QString getRandomShape(QStringList listShape);
    int getColorToKillSize(QString color);
    void init();
    void initColorList();
    void newTurn();
    void reset();
    void completeListColorShowed(QString colorRandom);
    void completeListShapeShowed(QString shapeRandom);
    void lose();
    void initTimer();  
    void initGrille();
    void initShape();
    void addRandomColorInGrill(bool changeShape);
    void step1();
    void step2();
    void step3();
    void step4();

    QString colorDifferent(QString last, QString current);


    void toWinStep1and2(int position);
    void toWinStep3(int position);
    void toWinStep4(int position);

public slots:
    void killThisDot();
    void timerUpdate();
};

#endif // GAME_H
