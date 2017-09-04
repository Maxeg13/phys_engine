#include "dialog.h"
#include <QPainter>
#include <QTimer>
#include <QThread>
//#include "work.h"
#include "myline.h"
#include "node.h"
#include "edge.h"
#include <math.h>
#include "physobject.h"
//#include "vars.h"
int nodes_N=0;
int lines_N=5;
int edges_N=2;
float f;
edge** ed;
QTimer *timer;
//work* WK;
PhysObject* PO;
myLine* ML;
node* _node;
node* nd;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{

    ed=new edge*[edges_N];
    PO=new PhysObject(ed,edges_N,3);
//  edge::size=nodes_N;
    float cs=cos(1.3)*15;
    float sn=sin(1.3)*15;
    nd=new node[3];

    //    nd[0]=node(70,55);
    //    nd[1]=node(85,55);
    //    nd[2]=node(85+cs,55+sn);
    //    nd[3]=node(85,55+2*sn);
    //    nd[4]=node(70,55+2*sn);
    //    nd[5]=node(70-cs,55+sn);

    nd[0]=node(PO,70,55);
    nd[1]=node(PO,85,55);//nd[1].vy=.1;
    nd[2]=node(PO,85,70);
    nd[3]=node(PO,70,70);

    ed[0]=new edge(nd,0,1);
    ed[1]=new edge(nd,1,2);
    ed[2]=new edge(nd,2,3);
    ed[3]=new edge(nd,3,0);
    ed[4]=new edge(nd,0,2);
    ed[5]=new edge(nd,3,1);



    //    ed[0]=new edge(nd,0,1);
    //    ed[1]=new edge(nd,1,2);
    //    ed[2]=new edge(nd,2,0);
    //        ed[3]=new edge(nd,3,4);
    //        ed[4]=new edge(nd,4,5);
    //        ed[5]=new edge(nd,5,0);
    //        ed[6]=new edge(nd,0,2);
    //        ed[7]=new edge(nd,1,3);
    //        ed[8]=new edge(nd,2,4);
    //        ed[9]=new edge(nd,3,5);
    //        ed[10]=new edge(nd,4,0);
    //        ed[11]=new edge(nd,5,1);
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
        _node[i]=node(PO,40+(rand()%70),80+(rand()%90));   //(190,320);
    ML=new myLine[lines_N]();
    ML[0]=myLine(50,199,60,190,0);
    ML[1]=myLine(60,300,284,300,0);
    ML[2]=myLine(277,300,300,280,0);
    ML[3]=myLine(300,280,325,300,0);
    ML[4]=myLine(324,300,410,100,0);
}

void Dialog::drawing()
{
    this->update();
}

void Dialog::mainCircle()
{
    /////////////////////
    //    for(int k=0;k<3;k++)
    //        for (int i=0;i<edges_N;i++)
    //            ed[i]->correctLength();
//    for (int i=0;i<edges_N;i++)
//        ed[i]->spaceKinemat();

    PO->spaceKinemat();

//    for (int i=0;i<lines_N;i++)
//        for (int i1=0;i1<edges_N;i1++)
//            ed[i1]->checkStuck(ML[i]);

    for (int i=0;i<lines_N;i++)
        PO->checkStuck(ML[i]);

    //qDebug()<<"hello";
    for(int j=0;j<nodes_N;j++)
    {
        _node[j].spaceKinemat();
        for (int i=0;i<lines_N;i++)
            _node[j].checkStuck(ML[i]);
    }
}

void Dialog::paintEvent(QPaintEvent* e)
{
    static float t=3;
    //    t+=.06;
    //    if(t>10)t=1;
    for (int i=0;i<t;i++)
        mainCircle();

    QPainter* painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, 1);
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->scale(1.5,1.5);

    //    draw edge
    for(int i=0;i<PO->size;i++)
        painter->drawLine(PO->ed[i]->getX0(),PO->ed[i]->getY0(),PO->ed[i]->getX1(),PO->ed[i]->getY1());

    for(int j=0;j<lines_N;j++)
        painter->drawLine(ML[j].x[0],ML[j].y[0],ML[j].x[1],ML[j].y[1]);

    pen=QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);


    for(int j=0;j<nodes_N;j++)
    {
        pen.setColor(QColor(_node[j].clr[0],_node[j].clr[1],_node[j].clr[2]));
        painter->setPen(pen);
        painter->drawPoint(_node[j].x,_node[j].y);
    }
    delete painter;
}

Dialog::~Dialog()
{

}
