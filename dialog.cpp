#include "dialog.h"
#include <QPainter>
#include <QTimer>
#include <QThread>
//#include "work.h"
#include "ambientLine.h"
#include "node.h"
#include "edge.h"
#include <math.h>
#include <QDebug>
#include "physobject.h"
//#include "vars.h"

int lines_N=5;

int edges_N=11;
int nodes_N=6;
float f;
edge** ed;
QTimer *timer;
//work* WK;
PhysObject* PO;
ambientLine* ML;
node* nd;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    ML=new ambientLine[lines_N]();
    ML[0]=ambientLine(50,199,60,190,0);
    ML[1]=ambientLine(60,190,120,300,0);
    ML[2]=ambientLine(120,300,300,280,0);
    ML[3]=ambientLine(300,280,325,300,0);
    ML[4]=ambientLine(324,300,410,100,0);

    ed=new edge*[edges_N];
    PO=new PhysObject(ed,edges_N,nodes_N);//

//  edge::size=nodes_N;
    float cs=cos(1.05)*15;
    float sn=sin(1.05)*15;
    nd=new node[nodes_N];

        nd[0]=node(PO,70,55);
        nd[1]=node(PO,85,55);
        nd[2]=node(PO,85+cs,55+sn);
        nd[3]=node(PO,85,55+2*sn);
        nd[4]=node(PO,70,55+2*sn);
        nd[5]=node(PO,70-cs,55+sn);

//    nd[0]=node(PO,170,55);
//    nd[1]=node(PO,200,55);//nd[1].vy=.1;
//    nd[2]=node(PO,200,85);
//    nd[3]=node(PO,170,85);

    ed[0]=new edge(nd,0,1);
    ed[1]=new edge(nd,1,2);
    ed[2]=new edge(nd,2,3);
    ed[3]=new edge(nd,3,4);
    ed[4]=new edge(nd,4,5);
    ed[5]=new edge(nd,5,0);
    ed[6]=new edge(nd,5,3);
    ed[7]=new edge(nd,4,2);
    ed[8]=new edge(nd,3,1);
    ed[9]=new edge(nd,2,0);
    ed[10]=new edge(nd,1,5);

//nd->vx;

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
//        PO->shift(-80,0);
    PO->shift(30,110);


    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawing()));
    timer->start(40);
    this->update();
    //    QThread* thread = new QThread( );
    //    WK=new work();
    //    WK->moveToThread(thread);
    //    connect(thread,SIGNAL(started()),WK,SLOT(doWork()));
    //    thread->start();

}

void Dialog::drawing()
{
    this->update();

}

void Dialog::mainCircle()
{


    PO->spaceKinemat();


    for (int i=0;i<lines_N;i++)
        PO->checkStuck(ML[i]);


}

void Dialog::paintEvent(QPaintEvent* e)
{
    for (int i=0;i<20;i++)
        mainCircle();

    QPainter* painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, 1);
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->scale(1.5,1.5);

    //    draw edge
    for(int i=0;i<PO->edges_N;i++)
        painter->drawLine(PO->ed[i]->getX0(),PO->ed[i]->getY0(),PO->ed[i]->getX1(),PO->ed[i]->getY1());

    for(int j=0;j<lines_N;j++)
        painter->drawLine(ML[j].x[0],ML[j].y[0],ML[j].x[1],ML[j].y[1]);

    delete painter;
}

Dialog::~Dialog()
{

}
