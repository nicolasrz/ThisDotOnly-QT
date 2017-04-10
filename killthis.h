#ifndef INFORMATION_H
#define INFORMATION_H
#include <QWidget>
#include "ownbutton.h"
#include <QPointer>
#include <QLabel>
#include <QString>
#include <QGridLayout>
#include <QVBoxLayout>
class KillThis : public QWidget
{
    Q_OBJECT
public:
    KillThis(QWidget *parent, QPointer<OwnCustomColor> color, QString shape, QString message);
    ~KillThis();

private:
    QPointer<QLabel> labelKill;
    QPointer<QGridLayout> gridLayout;
    QPointer<QVBoxLayout> vLayout;
    QString message;
    QPointer<OwnCustomColor> color;
    QString shape;
public slots:
    void iUnderstand();

};

#endif // INFORMATION_H
