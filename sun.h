// ----------------------------------------------------------
// sun.h
// ----------------------------------------------------------

#ifndef __SUN_H__
#define __SUN_H__

#include <iostream>
#include <math.h>

#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923

class Sun
{

   public:

     Sun();
     ~Sun();

     void calculatePosition(double, double, double, double,
                            int);

     void setColour(double [4]);
     double getTheta(void);
     double getPhi(void);

   private:

      double theta;   // angle from surface normal
                      // 0 = directly overhead
                      // pi/2 = at horizon

      double phi;     // angle from south direction
                      // 0 = south
                      // pi/2 = west
                      // -pi/2 = east

      double colour[4];

};

inline void Sun::setColour(double c[4])
{

    colour[0] = c[0];
    colour[1] = c[1];
    colour[2] = c[2];
    colour[3] = c[3];

}

inline double Sun::getTheta()
{

    return theta;

}

inline double Sun::getPhi()
{

    return phi;

}

#endif // __SUN_H__