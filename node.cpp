#include "node.h"
#include <QDebug>
node::node(int a, int b)
{
    x=a;
    y=b;
    vx=0;
    vy=0;
    ax=0;
    ay=0;
}
node::node()
{
    vx=0;
    vy=0;
    ax=0;
    ay=0;
};
void node::spaceKinemat()
{
    ay=.004;
    vx+=ax;
    vy+=ay;
    x+=vx*frict;
    y+=vy*frict;
}
node::checkStuck(myLine& ML)
{
    float xh=x-ML.x[0];
    float yh=y-ML.y[0];

    float proj=xh*ML.ex+yh*ML.ey;
    float ortho=xh*ML.ox+yh*ML.oy;


    if((proj>0)&&(proj<ML.length))
    {
        if((!ML.orient)&&(ortho>0)||(ML.orient)&&(ortho<0))
           // time to bounce
        {
//             qDebug()<<"fuck";
            x-=vx;
            y-=vy;
            proj=vx*ML.ex+vy*ML.ey;
            ortho=vx*ML.ox+vy*ML.oy;
            vx=ML.ex*proj-ML.ox*ortho;
            vy=ML.ey*proj-ML.oy*ortho;
        }
    }
//    else
//        qDebug()<<"not_fuck";
}
