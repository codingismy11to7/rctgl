// ----------------------------------------------------------
// sun.cpp
// ----------------------------------------------------------

#include "sun.h"

const double M_PI   =	3.14159265358979323846;
const double M_PI_2 =	1.57079632679489661923;


Sun::Sun()
: m_theta(0.0), m_phi(0.0)
{
}

Sun::~Sun() { }

void Sun::calculatePosition(double time,
                            double meridian,
                            double longitude,
                            double latitude,
                            int day)
{

   // Example input data:
   //
   // June 21, 10:30 Eastern Standard Time
   // Toronto, Ontario, CANADA
   //
   // time = 10.5
   // meridian = 1.3788101

   // longitude = 1.3852096
   // latitude = 0.762127107
   // day = 172
   //
   //
   // See section 4.0.2.1 Sun for further details
   //

   double t, delta;
   double A, B, C, D, E, F;

   A = 4*M_PI*(day - 80) / 373;
   B = 2*M_PI*(day - 8)  / 355;
   C = 2*M_PI*(day - 81) / 368;

   t = time +
     0.170*sin(A) -
     0.129*sin(B) +
     12*(meridian - longitude)/M_PI;

   delta = 0.4093*sin(C);

   D = M_PI*t/12;

   E = sin(latitude)*sin(delta) -
     cos(latitude)*cos(delta)*cos(D);

   F = (-cos(delta)*sin(D))/(cos(latitude)*sin(delta) -
                            sin(latitude)*cos(delta)*cos(D));

   m_theta = M_PI_2 - asin(E);
   m_phi = atan(F);

}
