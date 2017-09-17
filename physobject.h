#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H
#include "edge.h"

class PhysObject
{
public:
    PhysObject();
    edge** ed;
    float bouncing_common;
    bool crashed;
    float shift_x,shift_vx;
    float shift_y,shift_vy;
    float x,y,vx,vy;
    int edges_N;
    int nodes_N;
    PhysObject(edge **ed, int n1, int n2, float bc);
    void spaceKinemat();
    void checkStuck(ambientLine &ML);
    void shift(float _x, float _y);
    void correctV();
    void getV();
    void getX();
    void shiftV(float _x, float _y);
};

#endif // PHYSOBJECT_H
