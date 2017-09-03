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
edge::edge(node *_nd)
{
    nd=_nd;
    getLength();
    length_const=length;
//    qDebug()<<n[0].ax;
//     qDebug()<<n[1].ax;

}

void edge::getLength()
{
    length=sqrt((nd[0].x-nd[1].x)*(nd[0].x-nd[1].x)+(nd[0].y-nd[1].y)*(nd[0].y-nd[1].y));
    ex=(nd[0].x-nd[1].x)/length;
    ey=(nd[0].y-nd[1].y)/length;
    ox=-ey;
    oy=ex;
}

void edge::correctLength()
{
    getLength();
    nd[0].vx+=0.5*(length_const-length)*ex;
    nd[0].vy+=0.5*(length_const-length)*ey;
    nd[1].vx-=0.5*(length_const-length)*ex;
    nd[1].vy-=0.5*(length_const-length)*ey;
}

void edge::checkStuck(myLine& ML)
{
    nd[0].checkStuck(ML);
    nd[1].checkStuck(ML);
}

void edge::spaceKinemat()
{
    nd[0].spaceKinemat();
    nd[1].spaceKinemat();
    correctLength();

}



