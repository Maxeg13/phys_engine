#ifndef NODE_H
#define NODE_H
#include "ambientLine.h"
class PhysObject;

class node
{
public:
    PhysObject* PO;
    float frict=1;
    float x, y;
    float vx, vy;
//    float ax, ay;
    float clr[3];
    bool crash;
    node();
    node(PhysObject*,int ,int );
    void spaceKinemat(float ,float);
//    checkWall(ambientLine ML);
    void checkStuck(ambientLine &ML);
};

#endif // NODE_H
