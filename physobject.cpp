#include "physobject.h"
#include <QDebug>
//#include "edge.h"
PhysObject::PhysObject()
{

}


PhysObject::PhysObject(edge **_ed, int n1, int n2, float bc)
{
    bouncing_common=bc;
    crashed=0;
    shift_y=0;
    shift_x=0;
    shift_vy=0;
    shift_vx=0;

    ed=_ed;
    edges_N=n1;
    nodes_N=n2;
    //    qDebug()<<nodes_N;
}
void PhysObject::getX()
{
    x=0;
    y=0;
    for (int i=0;i<nodes_N;i++)
    {
        x+=ed[0]->nd[i].x;
        y+=ed[0]->nd[i].y;
    }
    x/=nodes_N;
    y/=nodes_N;
}

void PhysObject::getV()
{
    vx=0;
    vy=0;
    for (int i=0;i<nodes_N;i++)
    {
        vx+=ed[0]->nd[i].vx;
        vy+=ed[0]->nd[i].vy;
    }
    vx/=nodes_N;
    vy/=nodes_N;
}

void PhysObject::correctV()
{

    getV();
    float v=sqrt(vx*vx+vy*vy);
    //    if((v)>0.01)
    {


        for(int i=0;i<nodes_N;i++)
        {
            ed[0]->nd[i].getOrtho();
            float ov, ev, nev, nov;
            ov=ed[0]->nd[i].ox*vx+ed[0]->nd[i].oy*vy;
            ev=ed[0]->nd[i].ex*vx+ed[0]->nd[i].ey*vy;
            nev=ed[0]->nd[i].ex*ed[0]->nd[i].vx+ed[0]->nd[i].ey*ed[0]->nd[i].vy;
            nov=ed[0]->nd[i].ox*ed[0]->nd[i].vx+ed[0]->nd[i].oy*ed[0]->nd[i].vy;

            ed[0]->nd[i].vx=ed[0]->nd[i].ox*(nov)+ed[0]->nd[i].ex*(ev);
            ed[0]->nd[i].vy=ed[0]->nd[i].oy*nov+ed[0]->nd[i].ey*ev;
            //            ex=vx/v;
            //            ey=vy/v;
            //            ox=-ey;
            //            oy=ex;

            //            float ov,ev;
            //            ov=ed[0]->nd[i].vx*ox+ed[0]->nd[i].vy*oy;
            //            ev=ed[0]->nd[i].vx*ex+ed[0]->nd[i].vy*ey;

            //            ev-=0.03*(ev-v);
            //            ed[0]->nd[i].vx=ex*ev+ox*ov;
            //            ed[0]->nd[i].vy=ey*ev+oy*ov;

        }
    }
}

void PhysObject::shift(float _x, float _y)
{
    for(int i=0;i<nodes_N;i++)
    {
        ed[0]->nd[i].x+=_x;
        ed[0]->nd[i].y+=_y;
    }
}

void PhysObject::shiftV(float _x, float _y)
{
    for(int i=0;i<nodes_N;i++)
    {
        ed[0]->nd[i].vx+=_x;
        ed[0]->nd[i].vy+=_y;
    }
}

void PhysObject::spaceKinemat()
{

    for (int i=0;i<nodes_N;i++)
        ed[0]->nd[i].setV(0,0);

    int relible_N=4;
    for(int j=0;j<relible_N;j++)
    {
        for(int i=0;i<edges_N;i++)
            ed[i]->setV();

        int cnt_lim=400;
        static int cnt=0;
        cnt++;
        if((cnt%(cnt_lim))==0)
            correctV();

        for(int i=0;i<edges_N;i++)
            ed[i]->correctLength();
    }

    for (int i=0;i<nodes_N;i++)
        ed[0]->nd[i].setX();

}

void PhysObject::checkStuck(ambientLine& ML)
{
    for (int i=0;i<nodes_N;i++)
    {
        ed[0]->nd[i].checkStuck(ML);
    }
    for (int i=0;i<nodes_N;i++)
    {
        //        ed[0]->nd[i].x+=shift_x;
        //        ed[0]->nd[i].y+=shift_y;
        //                ed[0]->nd[i].vx+=shift_vx;
        //                ed[0]->nd[i].vy+=shift_vy;
    }
    shift_x=0;
    shift_y=0;
    //    shift_vx=0;
    //    shift_vy=0;
}
