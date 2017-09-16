#include "node.h"
#include "physobject.h"
#include <QDebug>
node::node(PhysObject* _PO,int a, int b)
{
    crashed=0;
    PO=_PO;
    x=a;
    y=b;
    vx=0;
    vy=0;
//size=5;
    crash=0;
    for(int i=0;i<3;i++)
        clr[i]=rand()%10*25;
}
node::node()
{
    vx=0;
    vy=0;
}

void node::setV(float ax,float ay)
{
    vx+=ax*crashed;
    vy+=ay*crashed+0.0048;
    crashed=0;
}

void node::setX()
{
    x+=vx;
    y+=vy;
}

void node::spaceKinemat(float ax,float ay)
{
    setV(ax,ay);

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
        int layer_width=10;
        if((!ML.orient)&&(ortho>-2)||(ML.orient)&&(ortho<2))// 2 is for point
            // time to bounce
            if(fabs(ortho)<layer_width)
            {
                crashed=1;
                PO->crashed=1;
                PO->shift_x=-(ortho+2)*ML.ox;
                PO->shift_y=- (ortho+2)*ML.oy;

                proj=0.8*(vx*ML.ex+vy*ML.ey);
                ortho=0.8*(vx*ML.ox+vy*ML.oy);
                float korrect=20;
//                ortho=((ortho>0)?1:(-1))*(sqrt(ortho*ortho+korrect)-sqrt(korrect));
                PO->shift_vx=ML.ex*proj-ML.ox*ortho;
                PO->shift_vy=ML.ey*proj-ML.oy*ortho;


//            qDebug()<<"crash "<<hhh;
                vx=((PO->shift_vx>0)?1:(-1))*(sqrt(PO->shift_vx*PO->shift_vx+korrect)-sqrt(korrect));
                vy=((PO->shift_vy>0)?1:(-1))*(sqrt(PO->shift_vy*PO->shift_vy+korrect)-sqrt(korrect));
//                vx=PO->shift_vx;
//                vy=PO->shift_vy;

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

}
