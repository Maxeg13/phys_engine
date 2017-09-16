#include "edge.h"
#include <math.h>
#include <QDebug>
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
    return(nd[ind[0]].x);
}

int edge::getX1()
{
    return(nd[ind[1]].x);
}

int edge::getY0()
{
    return(nd[ind[0]].y);
}

int edge::getY1()
{
    return(nd[ind[1]].y);
}

edge::edge(node *_nd, int a, int b)
{

    ind[0]=a;
    ind[1]=b;
    nd=_nd;
    getLength();
    length_const=length;

    //    qDebug()<<n[0].ax;
    //     qDebug()<<n[1].ax;

}

void edge::getOrths()
{
    ex=(nd[ind[0]].x-nd[ind[1]].x)/length;
    ey=(nd[ind[0]].y-nd[ind[1]].y)/length;
    ox=-ey;
    oy=ex;
}

void edge::getLength()
{
    length=sqrt((nd[ind[0]].x-nd[ind[1]].x)*(nd[ind[0]].x-nd[ind[1]].x)+
            (nd[ind[0]].y-nd[ind[1]].y)*(nd[ind[0]].y-nd[ind[1]].y));
    ex=(nd[ind[0]].x-nd[ind[1]].x)/length;
    ey=(nd[ind[0]].y-nd[ind[1]].y)/length;
    ox=-ey;
    oy=ex;
}

void edge::correctLength()
{
    getLength();
    float k=.5;
    nd[ind[0]].x+=k*(length_const-length)*ex;
    nd[ind[0]].y+=k*(length_const-length)*ey;
    nd[ind[1]].x-=k*(length_const-length)*ex;
    nd[ind[1]].y-=k*(length_const-length)*ey;
}

void edge::setV()
{
    getOrths();

    ov0=nd[ind[0]].vx*ox+nd[ind[0]].vy*oy;
    ov1=nd[ind[1]].vx*ox+nd[ind[1]].vy*oy;

    float ev0=nd[ind[0]].vx*ex+nd[ind[0]].vy*ey;
    float ev1=nd[ind[1]].vx*ex+nd[ind[1]].vy*ey;

    float  evd=.5*(ev0-ev1);

    nd[ind[0]].vx=(ev0-evd)*ex+(ov0)*ox;
    nd[ind[0]].vy=(ev0-evd)*ey+(ov0)*oy;
    nd[ind[1]].vx=(ev1+evd)*ex+(ov1)*ox;
    nd[ind[1]].vy=(ev1+evd)*ey+(ov1)*oy;

    correctLength();

}



void edge::preSpaceKinemat()
{

    ov0=nd[ind[0]].vx*ox+nd[ind[0]].vy*oy;
    ov1=nd[ind[1]].vx*ox+nd[ind[1]].vy*oy;
    ovd=(ov1-ov0)/2;
}

void edge::spaceKinemat()
{

    getOrths();

    ov0=nd[ind[0]].vx*ox+nd[ind[0]].vy*oy;
    ov1=nd[ind[1]].vx*ox+nd[ind[1]].vy*oy;
    float ovs=(ov1+ov0)/2;
    float ev0=nd[ind[0]].vx*ex+nd[ind[0]].vy*ey;
    float ev1=nd[ind[1]].vx*ex+nd[ind[1]].vy*ey;


    nd[ind[0]].vx=ev0*ex+(ovs-ovd)*ox;
    nd[ind[0]].vy=ev0*ey+(ovs-ovd)*oy;
    nd[ind[1]].vx=ev1*ex+(ovs+ovd)*ox;
    nd[ind[1]].vy=ev1*ey+(ovs+ovd)*oy;

    correctLength();

}



