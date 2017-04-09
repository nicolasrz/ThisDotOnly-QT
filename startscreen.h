#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "killthis.h"
#include <QWidget>
#include <QPointer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "game.h"
class StartScreen : public QWidget
{
        Q_OBJECT
public:
    StartScreen(QWidget *parent = 0);
    ~StartScreen();

    QPointer<QVBoxLayout> vStartLayout;
    QPointer<QPushButton> buttonStartGame;
    QPointer<QPushButton> buttonShowScore;
    QPointer<QPushButton> buttonQuitGame;
    QPointer<Game> game;

public slots:
    void startGame();
    void showScore();
    void quitGame();

};

#endif // STARTSCREEN_H
