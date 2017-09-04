#include "physobject.h"
#include <QDebug>
//#include "edge.h"
PhysObject::PhysObject()
{

}

PhysObject::PhysObject(edge **_ed, int n1, int n2)
{
    shift_y=0;
    shift_x=0;
    shift_vy=0;
    shift_vx=0;

    ed=_ed;
    size=n1;
    nodes_N=n2;
//    qDebug()<<nodes_N;
}

void PhysObject::spaceKinemat()
{
    for (int i=0;i<size;i++)
        ed[i]->spaceKinemat();

//    for (int i=0;i<size;i++)
//        ed[i]->correctLength();
//    for (int i=0;i<size;i++)
//        ed[i]->correctLength();
}

void PhysObject::checkStuck(myLine& ML)
{
    for (int i=0;i<size;i++)
    {
        ed[i]->checkStuck(ML);
    }
    for (int i=0;i<nodes_N;i++)
    {
        ed[0]->nd[i].x+=shift_x;
        ed[0]->nd[i].y+=shift_y;
//        ed[0]->nd[i].vx+=shift_vx;
//        ed[0]->nd[i].vy+=shift_vy;
    }
    shift_x=0;
    shift_y=0;
    shift_vx=0;
    shift_vy=0;
}
