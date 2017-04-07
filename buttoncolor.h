#ifndef BUTTONCOLOR_H
#define BUTTONCOLOR_H
#include <QPointer>
#include <QPushButton>

class ButtonColor
{
public:
    ButtonColor();
    ButtonColor(QPointer<QPushButton> button, QString color, int position, QString shape);
    ~ButtonColor();

    QPointer<QPushButton> getButton();
    void setButton(QPointer<QPushButton> button);

    QString getColor();
    void setColor(QString color);

    int getPosition();
    void setPosition(int pos);

    QString getShape();
    void setShape(QString shape);

private:
    QPointer<QPushButton> button;
    QString color;
    int position;
    QString shape;


};

#endif // BUTTONCOLOR_H
