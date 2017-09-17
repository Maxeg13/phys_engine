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
#include <QMouseEvent>
#include <QPointF>
//#include "vars.h"

int lines_N=5;
QPointF MouseP[2];
//hexa
//int edges_N=11;
//int nodes_N=6;

//hexapond
int edges_N=7;
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
    ML[0]=ambientLine(30,195,60,190,0);
    ML[1]=ambientLine(60,190,120,300,0);
    ML[2]=ambientLine(120,300,300,280,0);
    ML[3]=ambientLine(300,280,325,300,0);
    ML[4]=ambientLine(324,300,410,100,0);

    ed=new edge*[edges_N];
    PO=new PhysObject(ed,edges_N,nodes_N,.05);//box
//    PO=new PhysObject(ed,edges_N,nodes_N,.55);//hexa

    int hexa_s=17;
    float cs=cos(1.05)*hexa_s;
    float sn=sin(1.05)*hexa_s;
    nd=new node[nodes_N];

    //hexa
//            nd[0]=node(PO,70,55);
//            nd[1]=node(PO,70+hexa_s,55);
//            nd[2]=node(PO,70+hexa_s+cs,55+sn);
//            nd[3]=node(PO,70+hexa_s,55+2*sn);
//            nd[4]=node(PO,70,55+2*sn);
//            nd[5]=node(PO,70-cs,55+sn);

//            ed[0]=new edge(nd,0,1);
//            ed[1]=new edge(nd,1,2);
//            ed[2]=new edge(nd,2,3);
//            ed[3]=new edge(nd,3,4);
//            ed[4]=new edge(nd,4,5);
//            ed[5]=new edge(nd,5,0);
//            ed[6]=new edge(nd,5,3);
//            ed[7]=new edge(nd,4,2);
//            ed[8]=new edge(nd,3,1);
//            ed[9]=new edge(nd,2,0);
//            ed[10]=new edge(nd,1,5);
//        PO->shift(300,0);

    //hexapond
    nd[0]=node(PO,170,55);
    nd[1]=node(PO,210,55);//nd[1].vy=.1;
    nd[2]=node(PO,210,85);
    nd[3]=node(PO,170,85);
    nd[4]=node(PO,170,115,1);
    nd[5]=node(PO,210,115,1);

    ed[0]=new edge(nd,0,1);
    ed[1]=new edge(nd,1,2);
    ed[2]=new edge(nd,2,3);
    ed[3]=new edge(nd,3,0);
    ed[4]=new edge(nd,0,2);
    ed[5]=new edge(nd,2,5);
    ed[6]=new edge(nd,3,4);




    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(drawing()));
    timer->start(40);
    this->update();
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

void Dialog::mousePressEvent(QMouseEvent *e)
{

    MouseP[0]=(e->pos());
    QPointF V;
    V=MouseP[0]-QPointF(PO->ed[0]->nd[0].x, PO->ed[0]->nd[0].y);
    qDebug()<<V;
    PO->shift(V.x(),V.y());

}

void Dialog::mouseMoveEvent(QMouseEvent *e)
{
    MouseP[1]=MouseP[0];
    MouseP[0]=(e->pos());
    QPointF S, V;
    V=(MouseP[0]-MouseP[1])/200;
    S=MouseP[0]-QPointF(PO->ed[0]->nd[0].x, PO->ed[0]->nd[0].y);
//    qDebug()<<V;
    PO->shift(S.x(),S.y());
    PO->shiftV(V.x(),V.y());

}

Dialog::~Dialog()
{

}
