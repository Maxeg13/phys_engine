#include "dialog.h"
#include <QPainter>
#include <QTimer>
#include <QThread>
//#include "work.h"
#include "myline.h"
#include "node.h"
//#include "vars.h"
int nodes_N=140;
float f;
QTimer *timer;
//work* WK;
myLine* ML;
node* _node;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawing()));
    timer->start(40);
    this->update();
    //    QThread* thread = new QThread( );
    //    WK=new work();
    //    WK->moveToThread(thread);
    //    connect(thread,SIGNAL(started()),WK,SLOT(doWork()));
    //    thread->start();
    _node=new node[nodes_N]();
    for (int i=0;i<nodes_N;i++)
        _node[i]=node(190+(rand()%10)*20/10.,320+(rand()%10)*20/10.);   //(190,320);
    ML=new myLine[2]();
    ML[0]=myLine(20,290,252,400,0);
    ML[1]=myLine(250,400,400,180,0);
}

void Dialog::drawing()
{
    this->update();
}

void Dialog::mainCircle()
{



    //qDebug()<<"hello";
    for(int j=0;j<nodes_N;j++)
    {
        _node[j].spaceKinemat();
        for (int i=0;i<2;i++)
            _node[j].checkStuck(ML[i]);
    }
}

void Dialog::paintEvent(QPaintEvent* e)
{

    QPainter* painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, 1);
    QPen pen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    for (int i=0;i<10;i++)
        mainCircle();

    for(int j=0;j<2;j++)
        painter->drawLine(ML[j].x[0],ML[j].y[0],ML[j].x[1],ML[j].y[1]);
    for(int j=0;j<nodes_N;j++)
        painter->drawPoint(_node[j].x,_node[j].y);

    delete painter;
}

Dialog::~Dialog()
{

}
