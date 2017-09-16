#include "ambientLine.h"
#include <math.h>
#include <QDebug>
ambientLine::ambientLine()
{

};
ambientLine::ambientLine(int a,int b,int c,int d,bool _orient)
{
x[0]=a;
y[0]=b;
x[1]=c;
y[1]=d;
orient=_orient;


//qDebug()<<ex;
//qDebug()<<yx;
length=sqrt((x[1]-x[0])*(x[1]-x[0])+(y[1]-y[0])*(y[1]-y[0]));
ex=(x[1]-x[0])/length;
ey=(y[1]-y[0])/length;
ox=-ey;
oy=ex;

}
