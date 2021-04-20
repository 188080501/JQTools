#include "mousedropper.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QScreen>
#include <QCursor>
const QSize winSize(100,100);       //窗口尺寸
const int grabInterval=50;          //刷新频率
const int magnificationTimes=10;    //放大倍数
const double split=0.7;             //分割
const int sizeOfMouseIcon=20;       //鼠标图标大小

MouseDropper::MouseDropper(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer=new QTimer;
    setFixedSize(winSize);
    setMouseTracking(true);
    timer->setInterval(grabInterval);
    connect(timer,&QTimer::timeout,[this,parent](){
        QPoint show=QCursor::pos()+QPoint(sizeOfMouseIcon,-(winSize.height()+sizeOfMouseIcon));
        if(show.y()<0)
            show.setY(show.y()+winSize.height()+sizeOfMouseIcon);
        if(show.x()+winSize.width()>parent->width())
            show.setX(show.x()-(winSize.height()+sizeOfMouseIcon));
        move(show);
        update();
    });
    timer->start();
}

QColor MouseDropper::getColor() const
{
    return color;
}

void MouseDropper::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap grab=QGuiApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId()).copy(QCursor::pos().x()-winSize.width()/magnificationTimes/2,QCursor::pos().y()-winSize.height()*split/magnificationTimes/2,winSize.width()/magnificationTimes,winSize.height()*split/magnificationTimes);
    painter.drawPixmap(0,0,winSize.width(),winSize.height()*split,grab);

    QPixmap pixmap = grab.copy(winSize.width()/magnificationTimes/2,winSize.height()*split/magnificationTimes/2,1,1);//截图1个像素
    color = pixmap.toImage().pixel(0,0);
    if(color.red()>100&&color.blue()>100&&color.green()>100)    //调节方框颜色，使得更容易区分
         painter.setPen(QColor(0,0,0));
    else
        painter.setPen(QColor(255,255,255));
    painter.fillRect(0,winSize.height()*split,winSize.width()-1,winSize.height()*(1-split),QColor(100,100,100));
    painter.drawRect(0,0,rect().width()-1,rect().height()-1);
    painter.fillRect(4,74,22,22,color);
    painter.drawLine(50,30,50,40);
    painter.drawLine(45,35,55,35);
    painter.setPen(QColor(255,255,255));
    painter.drawText(32,82,"RGB");
    painter.drawText(32,95,QString().sprintf("%d,%d,%d",(color.red()-1)*255/254,(color.green()-1)*255/254,(color.blue()-1)*255/254));       //根据透明度算法复原原色素值

}
