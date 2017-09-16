#ifndef NODE_H
#define NODE_H
#include "ambientLine.h"
class PhysObject;

class node
{
public:
    bool crashed;
    PhysObject* PO;
    static int size;
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
    void setV(float ax, float ay);
    void setX();
};

#endif // NODE_H
