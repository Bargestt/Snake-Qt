#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    resize(400,400);

    rows = 20, cols = 20;
    cellH = this->height()/rows;
    cellW = this->width()/cols;


    body.append(QPoint(rows/2,cols/2));

    food = { cols*qrand()/RAND_MAX ,rows*qrand()/RAND_MAX};

    len = 1;

    speed = 5;

    QTimer *calctime = new QTimer(this);
    interval = 1000/speed;
    calctime->setInterval(interval);

    connect(calctime,SIGNAL(timeout()),this,SLOT(calc()));
    calctime->start();

    grabKeyboard();
}



void GameWindow::paintEvent(QPaintEvent */*event*/)
{
    QPainter p(this);

    p.fillRect(this->rect(),QColor(77,77,77));


    foreach (QPoint block, body) {
        p.fillRect(block.x()*cellW,block.y()*cellH,cellW-1,cellH-1,QColor(33,153,33));
    }
    p.fillRect(food.x()*cellW,food.y()*cellH,19,19,QColor(155,0,155));
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_A:
        if(direction != right || len <=1)
            direction = left;
        break;
    case Qt::Key_W:
        if(direction != down || len <=1)
            direction = up;
        break;
    case Qt::Key_D:
        if(direction != left || len <=1)
            direction = right;
        break;
    case Qt::Key_S:
        if(direction != up || len <=1)
            direction = down;
        break;
    }
}

void GameWindow::calc()
{
    for(int i=body.length()-1; i>0 ;i--)
    {

        body[i].setX(body.at(i-1).x());
        body[i].setY(body.at(i-1).y());
    }

    switch (direction) {
    case left:
        body.first().rx()--;
        break;
    case up:
        body.first().ry()--;
        break;
    case right:
        body.first().rx()++;
        break;
    case down:
        body.first().ry()++;
        break;
    }
    if(body.first().x()> 19)body.first().rx() =0;
    if(body.first().x()< 00)body.first().rx() =19;
    if(body.first().y()> 19)body.first().ry() =0;
    if(body.first().y()< 00)body.first().ry() =19;


    for(int i=1;i<body.length();i++)
    {
        if(body[i].x() == body.first().x() &&  body[i].y() == body.first().y() && i !=0)
        {
            len =1;
            body.clear();
            body.append(QPoint(rows/2,cols/2));
            update();
            return;
        }
    }
    if(body.first().x() == food.x() && body.first().y() == food.y())
    {

        len++;
        body.append(QPoint(food));
        food = { cols*qrand()/RAND_MAX ,rows*qrand()/RAND_MAX};
    }

    update();

}
