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
    static float h1, h2;
    h1=vx+ax;
    h2=vy+ay+0.0024*!crashed;
    //    if((h1*h1+h2*h2)<.9)
    {
        vx+=ax;
        vy+=ay+0.0024*!crashed;
        crashed=0;
    }

}

void node::getOrtho()
{
    float r=sqrt(ex*ex+ey*ey);
    ex/=r;
    ey/=r;
    ox=-ey;
    oy=ex;
}

void node::setX()
{
    x+=vx;
    y+=vy;
    ex=x-PO->x;
    ey=y-PO->y;


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
        int layer_width=20;
        if((!ML.orient)&&(ortho>-2)||(ML.orient)&&(ortho<2))// 2 is for point
            // time to bounce
            if(fabs(ortho)<layer_width)
            {
                crashed=1;
                PO->crashed=1;
                PO->shift_x=-(ortho+2)*ML.ox;
                PO->shift_y=- (ortho+2)*ML.oy;

                proj=0.4*(vx*ML.ex+vy*ML.ey);
                ortho=3*(vx*ML.ox+vy*ML.oy);
                static float korrect=0;
                static float sqrt_korrect=sqrt(korrect);
                //                ortho=((ortho>0)?1:(-1))*(sqrt(ortho*ortho+korrect)-sqrt(korrect));
                PO->shift_vx=ML.ex*proj-ML.ox*ortho;
                PO->shift_vy=ML.ey*proj-ML.oy*ortho;

                vx=((PO->shift_vx>0)?1:(-1))*(sqrt(PO->shift_vx*PO->shift_vx+korrect)-sqrt_korrect);
                vy=((PO->shift_vy>0)?1:(-1))*(sqrt(PO->shift_vy*PO->shift_vy+korrect)-sqrt_korrect);


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
