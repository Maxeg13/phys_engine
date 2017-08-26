#include "dialog.h"
#include <QPainter>
#include <QTimer>
#include <QThread>
#include "work.h"
#include "myline.h"
//#include "vars.h"
QTimer *timer;
work* WK;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawing()));
    timer->start(40);
    this->update();
    QThread* thread = new QThread( );
    WK=new work();
    WK->moveToThread(thread);
    connect(thread,SIGNAL(started()),WK,SLOT(doWork()));
    thread->start();


}

void Dialog::drawing()
{
    this->update();
}

void Dialog::paintEvent(QPaintEvent* e)
{

    QPainter* painter=new QPainter(this);
    painter->drawLine(WK->ML.x[0],WK->ML.y[0],WK->ML.x[1],WK->ML.y[1]);
    delete painter;
}

Dialog::~Dialog()
{

}
