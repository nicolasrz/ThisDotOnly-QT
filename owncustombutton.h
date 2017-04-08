#ifndef OWNCOLOR_H
#define OWNCOLOR_H
#include <QString>
#include <QObject>
#include "owncustomcolor.h"
#include <QPointer>
class OwnCustomButton : public QObject
{
    Q_OBJECT
public:
    OwnCustomButton();
    OwnCustomButton(QPointer<OwnCustomColor> customColor, QString shape);
    ~OwnCustomButton();

    void setShape(QString shape);
    QString getShape();
    QPointer<OwnCustomColor> getOwnCustomColor();
    void setOwnCustomColor(QPointer<OwnCustomColor> customColor);

private:
    QPointer<OwnCustomColor> customColor;
    QString shape;
};

#endif // OWNCOLOR_H
