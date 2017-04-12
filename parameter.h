#ifndef PARAMETER_H
#define PARAMETER_H
#include <QHash>
#include <QStringList>
#include <QVector>
#include <QPointer>
#include "owncustomcolor.h"
#include <QDesktopWidget>


class Parameter : public QObject
{
    Q_OBJECT
public:
    Parameter();
    ~Parameter();

    QHash<QString,QString> getHashColor();
    QStringList getListShape();
    QPointer<OwnCustomColor> getRandomOwnCustomColor();
    int getRandomNumber(int min, int max);
    int getDpiX();
    int getDpiY();

private:
    QStringList listShape;
    QVector<QPointer<OwnCustomColor>> listOwnColor;
    int dpiX;
    int dpiY;






};

#endif // PARAMETER_H
