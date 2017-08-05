#ifndef NOIZE_H
#define NOIZE_H
#include <QtCore>
#include <ctime>
//-----Base class:Noize----
 class Noize : public QObject
{
    Q_OBJECT
public:
    explicit Noize(QObject *parent = 0);
    virtual double noize();
     ~Noize();
signals:
private:

public slots:
};
//--------------------------------




 //-----Derived class:NoizeAWGN----
class NoizeAWGN : public Noize
{
    Q_OBJECT
public:

     NoizeAWGN(QObject *parent,double,double);
     ~NoizeAWGN();
    virtual double noize();
signals:
private:
   double sigma;
   double m;
   double z[2];
   bool used=false;
public slots:
};
//--------------------------------


//-----Derived class:ImpulseNoize----
class NoizeImN : public Noize
{
    Q_OBJECT
public:

     NoizeImN(QObject *parent, double, double, double, double);
     ~NoizeImN();
    virtual double noize(double I);
signals:
private:
   double p[2];
   double z[2];
public slots:
};
//--------------------------------
#endif // NOIZE_H
