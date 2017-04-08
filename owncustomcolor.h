#ifndef OWNCUSTOMCOLOR_H
#define OWNCUSTOMCOLOR_H
#include <QString>
#include <QObject>

class OwnCustomColor : public QObject
{
    Q_OBJECT
public:
    OwnCustomColor();
    OwnCustomColor(QString name, QString hexa);
    ~OwnCustomColor();

    QString getHexa();
    QString getName();



private :
    QString hexa;
    QString name;
};

#endif // OWNCUSTOMCOLOR_H
