#ifndef MYLINE_H
#define MYLINE_H


class ambientLine
{
public:


    int x[2],y[2];
    float length;
    bool orient;
    float ex,ey;
    float ox, oy;
    ambientLine();
    ambientLine(int a, int b, int c, int d, bool ori);
};

#endif // MYLINE_H
