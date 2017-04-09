#ifndef INFORMATION_H
#define INFORMATION_H
#include <QWidget>
#include "ownbutton.h"
#include <QPointer>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
class KillThis : public QWidget
{
    Q_OBJECT
public:
    KillThis(QWidget *parent, QPointer<OwnCustomColor> color, QString shape, QString message);
    ~KillThis();

private:
    QPointer<QLabel> labelKill;
    QPointer<QHBoxLayout> hLayout;
    QString message;
    QPointer<OwnCustomColor> color;
    QString shape;

};

#endif // INFORMATION_H
