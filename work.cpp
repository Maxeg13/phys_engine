#include "work.h"
//#include"vars.h"
#include "QDebug"

work::work():ML(0,300,250,400,0),_node(0,40)
{

}
void work::doWork()
{float f;
    while(1)
    {
        f+=0.007;
_node.x=f;
//qDebug()<<"hello";
_node.checkStuck(ML);
    }
}
