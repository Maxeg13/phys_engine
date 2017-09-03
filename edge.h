#ifndef EDGE_H
#define EDGE_H
#include "node.h"

class edge
{
public:
    edge();
    edge(int a,int b,int c,int d);
    int ind[2];
    float length;
    float length_const;
    float ex;
    float ey;
    float ox;
    float oy;
    node* nd;
    void getLength();
    void checkStuck();
    void spaceKinemat();

    void correctLength();
    void checkStuck(myLine &ML);
    edge(node *_nd, int, int);
    int getY1();
    int getY0();
    int getX1();
    int getX0();
};

#endif // EDGE_H
