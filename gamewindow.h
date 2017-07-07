#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QKeyEvent>
#include <QTimer>
#include <QPaintEvent>



class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);



private:

    int rows, cols;
    int cellH,cellW;
    int X,Y;
    int speed,interval;
    int len;



    int direction;

    QVector<QPoint> body;

    QPoint food;

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    enum{
        left =0,
        right,
        up,
        down
    };


signals:

public slots:
    void calc();
};

#endif // GAMEWINDOW_H
