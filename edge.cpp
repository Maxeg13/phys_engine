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

void edge::getLength()
{
    length=sqrt((nd[ind[0]].x-nd[ind[1]].x)*(nd[ind[0]].x-nd[ind[1]].x)+(nd[ind[0]].y-nd[ind[1]].y)*(nd[ind[0]].y-nd[ind[1]].y));
    ex=(nd[ind[0]].x-nd[ind[1]].x)/length;
    ey=(nd[ind[0]].y-nd[ind[1]].y)/length;
    ox=-ey;
    oy=ex;
}

void edge::correctLength()
{
    getLength();
    float k=.5;
    nd[ind[0]].vx+=k*(length_const-length)*ex;
    nd[ind[0]].vy+=k*(length_const-length)*ey;
    nd[ind[1]].vx-=k*(length_const-length)*ex;
    nd[ind[1]].vy-=k*(length_const-length)*ey;
}

void edge::checkStuck(myLine& ML)
{
    nd[ind[0]].checkStuck(ML);
    nd[ind[1]].checkStuck(ML);
}

void edge::spaceKinemat()
{
       correctLength();
    nd[ind[0]].spaceKinemat();
    nd[ind[1]].spaceKinemat();
    correctLength();

}



