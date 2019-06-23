#include "physobject.h"
#include <QDebug>
//#include "edge.h"
PhysObject::PhysObject()
{

}


PhysObject::PhysObject(edge **_ed,  int edgesN, node** _nd, int nodesN, float bc)
{
    bouncing_common=bc;
    crashed=0;
    shift_y=0;
    shift_x=0;
    shift_vy=0;
    shift_vx=0;

    nd=_nd;
//    nd[1]->x;
    ed=_ed;

    edges_N=edgesN;
    nodes_N=nodesN;
    qDebug()<<nodes_N;
    qDebug()<<nd[0]->x;
    qDebug()<<(*nd)[1].x;
}
void PhysObject::getX()
{
    x=0;
    y=0;
    for (int i=0;i<nodes_N;i++)
    {
        x+=(*nd)[i].x;
        y+=(*nd)[i].y;
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
        vx+=(*nd)[i].vx;
        vy+=(*nd)[i].vy;
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
            (*nd)[i].getOrtho();
            float ov, ev, nev, nov;
            ov=(*nd)[i].ox*vx+(*nd)[i].oy*vy;
            ev=(*nd)[i].ex*vx+(*nd)[i].ey*vy;
            nev=(*nd)[i].ex*(*nd)[i].vx+(*nd)[i].ey*(*nd)[i].vy;
            nov=(*nd)[i].ox*(*nd)[i].vx+(*nd)[i].oy*(*nd)[i].vy;

            (*nd)[i].vx=(*nd)[i].ox*(nov)+(*nd)[i].ex*(ev);
            (*nd)[i].vy=(*nd)[i].oy*nov+(*nd)[i].ey*ev;
            //            ex=vx/v;
            //            ey=vy/v;
            //            ox=-ey;
            //            oy=ex;

            //            float ov,ev;
            //            ov=(*nd)[i].vx*ox+(*nd)[i].vy*oy;
            //            ev=(*nd)[i].vx*ex+(*nd)[i].vy*ey;

            //            ev-=0.03*(ev-v);
            //            (*nd)[i].vx=ex*ev+ox*ov;
            //            (*nd)[i].vy=ey*ev+oy*ov;

        }
    }
}

void PhysObject::shift(float _x, float _y)
{
    for(int i=0;i<nodes_N;i++)
    {
        (*nd)[i].x+=_x;
        (*nd)[i].y+=_y;
    }
}

void PhysObject::shiftV(float _x, float _y)
{
    for(int i=0;i<nodes_N;i++)
    {
        (*nd)[i].vx+=_x;
        (*nd)[i].vy+=_y;
    }
}

void PhysObject::spaceKinemat()
{

    for (int i=0;i<nodes_N;i++)
        (*nd)[i].setV(0,0);//bad way

    int relible_N=4;
    for(int j=0;j<relible_N;j++)
    {
        for(int i=0;i<edges_N;i++)
            ed[i]->setV();//comment what are you doing!

        int cnt_lim=400;
        static int cnt=0;
        cnt++;
        if((cnt%(cnt_lim))==0)
            correctV();

        for(int i=0;i<edges_N;i++)
            ed[i]->correctLength();
    }

    for (int i=0;i<nodes_N;i++)
        (*nd)[i].setX();

}

void PhysObject::checkStuck(ambientLine& ML)
{
    for (int i=0;i<nodes_N;i++)
    {
        (*nd)[i].checkStuck(ML);
    }
    for (int i=0;i<nodes_N;i++)
    {
        //        (*nd)[i].x+=shift_x;
        //        (*nd)[i].y+=shift_y;
        //                (*nd)[i].vx+=shift_vx;
        //                (*nd)[i].vy+=shift_vy;
    }
    shift_x=0;
    shift_y=0;
    //    shift_vx=0;
    //    shift_vy=0;
}
