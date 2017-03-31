#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPointer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QPointer<QVBoxLayout> vLayout;
    QPointer<QHBoxLayout> hLayout;
    QMap<int, QMap<QPointer<QPushButton>, QString>> *map;
    QString colorToKill;
    QStringList listColor;
    QStringList listColorShowed;
    int turn;


    QString changeColorButton(QString color);
    QString getRandomColor(QStringList list);
    int getRandomNumber();
    QString getRandomColorShowed();



    void init();
    void initQss();
    void initColorList();
    void newTurn();
public slots:
    void killThisDot();

};

#endif // WIDGET_H
