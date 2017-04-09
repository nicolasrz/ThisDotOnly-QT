#ifndef TURN_H
#define TURN_H
#include <QLabel>
#include <QObject>
#include <QString>
#include "ownbutton.h"

class Turn : public QObject
{
    Q_OBJECT
public:
    Turn();
    ~Turn();

    int getCount();
    void countIncrement();

    QPointer<OwnButton> getOwnButtonToKill();
    void setButtonToKill(QPointer<OwnButton> ownButtonToKill);

    QString getTimeLabel();
    void setTimeLabel(QString time);

    bool hasWin();
    void setWin(bool state);

    int getStep();
    void stepIncrement();

    int getDotToKillSize();
    void setDotToKillSize(int size);

    int getTouchedDot();
    void touchedDotIncrement();
    void resetTouchedDot();

private:
    int count;
    int touchedDot;
    QPointer<OwnButton> ownButtonToKill;
    QString timeLabel;
    bool win;
    int step;
    int dotToKillSize;
};

#endif // TURN_H
