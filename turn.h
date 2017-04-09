#ifndef TURN_H
#define TURN_H
#include <QLabel>
#include <QObject>
#include <QString>
#include "ownbutton.h"
#include <QTimer>
#include <QVector>
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

    int getDotToKillSize();
    void setDotToKillSize(int size);

    int getTouchedDot();
    void touchedDotIncrement();

    bool getTimerIsCounting();
    void setTimerCounting(bool state);

    QVector<QPointer<OwnButton>> getMultiButtonToKill();
    void addInMultiButtonToKill(QPointer<OwnButton> ownButtonToKill);
    void clearMultiButtonToKill();
    QString getColorAndOr();
    void setColorAndOr(QString state);



private:
    int count;
    int touchedDot;
    QPointer<OwnButton> ownButtonToKill;
    QString timeLabel;
    bool win;
    int dotToKillSize;
    QVector<QPointer<OwnButton>> multiButtonToKill;
    QString colorAndOr;


};

#endif // TURN_H
