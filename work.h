#ifndef WORK_H
#define WORK_H
#include "myline.h"
#include <QDialog>
#include "node.h"

class work : public QObject
{
    Q_OBJECT
public:
    node _node;
    myLine ML;
    work();
public slots:
    void doWork();
};

#endif // WORK_H
