#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>



class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
//    paintEvent(QPaintEvent*);
private:
protected:
     void paintEvent(QPaintEvent *e);
public slots:
     void drawing();

};

#endif // DIALOG_H
