#ifndef NODE_H
#define NODE_H
#include "myline.h"
class PhysObject;

class node
{
public:
    PhysObject* PO;
    float frict=1;
    float x, y;
    float vx, vy;
    float ax, ay;
    float clr[3];
    bool crash;
    node();
    node(PhysObject*,int ,int );
    void spaceKinemat();
//    checkWall(myLine ML);
    checkStuck(myLine &ML);
};

#endif // NODE_H
