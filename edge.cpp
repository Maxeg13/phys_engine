#include "edge.h"
#include <math.h>
#include <QDebug>

//i cant read that
float h, h1;
edge::edge()
{

}
//edge::edge(int a, int b, int c, int d)
//{
//    nd[0].x=a;
//    nd[0].y=b;
//    nd[1].x=c;
//    nd[1].y=d;
//    getLength();
//    length_const=length;
//}

int edge::getX0()
{
    return(nd1->x);
}

int edge::getX1()
{
    return(nd2->x);
}

int edge::getY0()
{
    return(nd1->y);
}

int edge::getY1()
{
    return(nd2->y);
}

edge::edge(node *_nd, int a, int b)
{
    nd1=(_nd+a);
    nd2=(_nd+b);
    ind[0]=a;
    ind[1]=b;
//    nd=_nd;
    getLength();
    length_const=length;

//        qDebug()<<nd1->y;
    //     qDebug()<<n[1].ax;

}

void edge::getOrths()
{
    ex=(nd1->x-nd2->x)/length;
    ey=(nd1->y-nd2->y)/length;
    ox=-ey;
    oy=ex;
}

void edge::getLength()
{
    length=sqrt((nd1->x-nd2->x)*(nd1->x-nd2->x)+
            (nd1->y-nd2->y)*(nd1->y-nd2->y));
    ex=(nd1->x-nd2->x)/length;
    ey=(nd1->y-nd2->y)/length;
    ox=-ey;
    oy=ex;
}

void edge::correctLength()
{
    getLength();
    float k=.5;
    nd1->x+=k*(length_const-length)*ex;
    nd1->y+=k*(length_const-length)*ey;
    nd2->x-=k*(length_const-length)*ex;
    nd2->y-=k*(length_const-length)*ey;
}

void edge::setV()
{
    getOrths();

    ov0=nd1->vx*ox+nd1->vy*oy;
    ov1=nd2->vx*ox+nd2->vy*oy;

    float ev0=nd1->vx*ex+nd1->vy*ey;
    float ev1=nd2->vx*ex+nd2->vy*ey;

    float  evd=.5*(ev0-ev1);

    nd1->vx=(ev0-evd)*ex+(ov0)*ox;
    nd1->vy=(ev0-evd)*ey+(ov0)*oy;
    nd2->vx=(ev1+evd)*ex+(ov1)*ox;
    nd2->vy=(ev1+evd)*ey+(ov1)*oy;

    correctLength();

}



void edge::preSpaceKinemat()
{

    ov0=nd1->vx*ox+nd1->vy*oy;
    ov1=nd2->vx*ox+nd2->vy*oy;
    ovd=(ov1-ov0)/2;
}

void edge::spaceKinemat()
{

    getOrths();

    ov0=nd1->vx*ox+nd1->vy*oy;
    ov1=nd2->vx*ox+nd2->vy*oy;
    float ovs=(ov1+ov0)/2;
    float ev0=nd1->vx*ex+nd1->vy*ey;
    float ev1=nd2->vx*ex+nd2->vy*ey;


    nd1->vx=ev0*ex+(ovs-ovd)*ox;
    nd1->vy=ev0*ey+(ovs-ovd)*oy;
    nd2->vx=ev1*ex+(ovs+ovd)*ox;
    nd2->vy=ev1*ey+(ovs+ovd)*oy;

    correctLength();

}



