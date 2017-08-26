#ifndef WORK_H
#define WORK_H
#include <QDialog>

class work : public QObject
{
    Q_OBJECT
public:
int i;
//    work();
public slots:
    void doWork();
};

#endif // WORK_H
