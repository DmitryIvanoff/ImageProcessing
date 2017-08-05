#include "noize.h"
//-----Base class:Noize----
 Noize::Noize(QObject *parent): QObject(parent)
{
   qsrand(time(NULL));
}


double Noize::noize()
{
    double r=(qrand()/(RAND_MAX));
    return r;
}

Noize::~Noize()
{

}

//--------------------------------



//-----Derived class:NoizeAWGN----
NoizeAWGN::NoizeAWGN(QObject *parent,double mat, double s):Noize(parent)
{
    used=false;
    sigma=s;
    m=mat;
}

NoizeAWGN::~NoizeAWGN()
{

}


double NoizeAWGN::noize()
{

        if (!used)
        {
            double u;
            double v;
            double s;
            do {
                u=((double)qrand()/(double)RAND_MAX);
                v=((double)qrand()/(double)RAND_MAX);
                int i=(qrand()%2);
                if (i>0)
                {
                  u*=-1;
                }
                i=(qrand()%2);
                if (i>0)
                {
                   v*=-1;
                }
                s = u * u + v * v;
            } while (s > 1.0 || s == 0.0);
             double t=sqrt((-2)*log(s)/s);
             z[0]=u*t;
             z[1]=v*t;
             used=true;
         return m+z[0]*sigma;
        }
        else
        {
            used=false;
            return m+z[1]*sigma;
        }


}
//--------------------------------
//-----Derived class:NoizeAWGN----
NoizeImN::NoizeImN(QObject *parent, double a, double b,double p_a,double p_b):Noize(parent)
{
     z[0]=a;
     z[1]=b;
     p[0]=p_a;
     p[1]=p_b;
}

NoizeImN::~NoizeImN()
{

}

double NoizeImN::noize(double I)
{
    double t=((double)qrand()/(double)RAND_MAX);
    if (t<=(p[0]+p[1]))
    {
        int i=(qrand()%2);
        if (i>0)
        {
           return z[0];
        }
        else
        {
           return z[1];
        }
    }
    else
    {
         return I;
    }
}
