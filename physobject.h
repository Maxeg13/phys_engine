#ifndef PHYSOBJECT_H
#define PHYSOBJECT_H
#include "edge.h"

class PhysObject
{
public:
    PhysObject();
    edge** ed;
    bool crashed;
    float shift_x,shift_vx;
    float shift_y,shift_vy;
    int size;
    int nodes_N;
    PhysObject(edge **ed, int n1, int n2);
    void spaceKinemat();
    void checkStuck(ambientLine &ML);
};

#endif // PHYSOBJECT_H
