#ifndef BUTTONCOLOR_H
#define BUTTONCOLOR_H
#include <QPointer>
#include <QPushButton>

class ButtonColor
{
public:
    ButtonColor();
    ButtonColor(QPointer<QPushButton> button, QString color, int position);
    ~ButtonColor();

    QPointer<QPushButton> getButton();
    void setButton(QPointer<QPushButton> button);

    QString getColor();
    void setColor(QString color);

    int getPosition();
    void setPOsition(int pos);

private:
    QPointer<QPushButton> button;
    QString color;
    int position;


};

#endif // BUTTONCOLOR_H
