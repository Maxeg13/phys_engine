#ifndef WORK_H
#define WORK_H
#include "myline.h"
#include <QDialog>

class work : public QObject
{
    Q_OBJECT
public:
    myLine ML;
int i;
    work();
public slots:
    void doWork();
};

#endif // WORK_H
