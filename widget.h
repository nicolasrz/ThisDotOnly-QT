#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPointer>
#include <QGridLayout>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QPointer<QGridLayout> gridLayout;

};

#endif // WIDGET_H
