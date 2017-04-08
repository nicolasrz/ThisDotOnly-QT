#ifndef BUTTONCOLOR_H
#define BUTTONCOLOR_H
#include <QPointer>
#include <QPushButton>
#include "owncustombutton.h"
class OwnButton : public QObject
{
    Q_OBJECT
public:
    OwnButton();
    OwnButton(QPointer<QPushButton> button, int position, QPointer<OwnCustomButton> ownCustombutton);
    ~OwnButton();

    QPointer<QPushButton> getButton();
    void setButton(QPointer<QPushButton> button);

    int getPosition();
    void setPosition(int pos);

    QPointer<OwnCustomButton> getOwnCustomButton();
    void setOwnCustomButton(QPointer<OwnCustomButton> ownCustomButton );


private:
    QPointer<QPushButton> button;
    int position;
    QPointer<OwnCustomButton> ownCustomButton;


};

#endif // BUTTONCOLOR_H
