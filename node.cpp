#include "node.h"
#include "physobject.h"
#include <QDebug>
node::node(PhysObject* _PO,int a, int b)
{
    PO=_PO;
    x=a;
    y=b;
    vx=0;
    vy=0;

    crash=0;
    for(int i=0;i<3;i++)
        clr[i]=rand()%10*25;
}
node::node()
{
    vx=0;
    vy=0;

}
void node::spaceKinemat(float ax,float ay)
{

    vx+=ax;
    vy+=ay+0.0048;
    x+=vx*frict;
    y+=vy*frict;
}
void node::checkStuck(ambientLine& ML)
{
    float xh=x-ML.x[0];
    float yh=y-ML.y[0];

    float proj=xh*ML.ex+yh*ML.ey;
    float ortho=xh*ML.ox+yh*ML.oy;


    if((proj>0)&&(proj<ML.length))
    {
        if((!ML.orient)&&(ortho>-2)||(ML.orient)&&(ortho<4))
            // time to bounce
            if(fabs(ortho)<10)
            {
                PO->crashed=1;
                //             qDebug()<<"fuck";
                //            x-=vx;
                //            y-=vy;
                //                x+=-(ortho)*ML.ox;
                //                y+=-(ortho)*ML.oy;
                PO->shift_x=-(ortho+2)*ML.ox;
                PO->shift_y=- (ortho+2)*ML.oy;
                proj=2*(vx*ML.ex+vy*ML.ey);
                ortho=2*(vx*ML.ox+vy*ML.oy);
                PO->shift_vx=ML.ex*proj-ML.ox*ortho;
                PO->shift_vy=ML.ey*proj-ML.oy*ortho;

                vx=((PO->shift_vx>0)?1:(-1))*(sqrt(PO->shift_vx*PO->shift_vx+4)-2);
                vy=((PO->shift_vy>0)?1:(-1))*(sqrt(PO->shift_vy*PO->shift_vy+4)-2);

                for(int i=0;i<PO->nodes_N;i++)
                {
                    if((PO->ed[0]->nd+i)!=this)
                    {
                        PO->ed[0]->nd[i].x+=PO->shift_x;
                        PO->ed[0]->nd[i].y+=PO->shift_y;
                    }
                }
                //            crash=1;
            }
    }
    //    else
    //        qDebug()<<"not_fuck";
}
