#ifndef NODE_H
#define NODE_H
#include "ambientLine.h"
class PhysObject;

class node
{
public:
    bool limb;
    bool crashed;
    PhysObject** PO;
    static int size;
    float frict=1;
    float x, y;
    float ex, ey, ox, oy;
    float vx, vy;
//    float ax, ay;
    float clr[3];
    bool crash;
    node();
    node(PhysObject**, int , int );
    node(PhysObject**, int , int , bool c);
    void spaceKinemat(float ,float);
//    checkWall(ambientLine ML);
    void checkStuck(ambientLine &ML);
    void setV(float ax, float ay);
    void setX();
    void getOrtho();
};

#endif // NODE_H
