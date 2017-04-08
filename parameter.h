#ifndef PARAMETER_H
#define PARAMETER_H
#include <QHash>
#include <QStringList>
#include <QVector>
#include <QPointer>
#include "owncustomcolor.h"
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
private:
    QStringList listShape;
    QVector<QPointer<OwnCustomColor>> listOwnColor;





};

#endif // PARAMETER_H
