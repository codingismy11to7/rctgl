// ----------------------------------------------------------
// Moon.h
// ----------------------------------------------------------

#pragma once
#ifndef __MOON_H__
#define __MOON_H__

#include "Observer.h"

#define _USE_MATH_DEFINES // required by Visual Studio .NET
#include <math.h>         // to access math.h constant M_PI
                          //
                          // those using gcc should use the
                          // -lm option during compilation

#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923



class Moon
{

public:

   Moon(void);
   ~Moon(void);

   void computeMoonPosition(Observer *);
   double getRightAscension();
   double getDeclination();

private:

   double getDays(int, int, int, double);
   double getAngle(double, double);
   double getRange(double);
   int getInteger(double);

   // the right ascension of the Moon is the angular
   // distance eastward along the celestial equator from
   // the vernal equinox to the intersection of the hour
   // circle that passes through the body; expressed in
   // hours and minutes and seconds (hh.mmss)
   //
   // the declination of the Moon is the angular distance
   // to a point on a celestial object measured north or
   // south from the celestial equator; expressed in
   // degrees (ddd.mmss); used with right ascension to
   // specify positions on the celestial sphere
   //
   // EXAMPLE:
   //
   // latitude: 43.67 degrees
   // longitude: -79.39 degrees
   // date: December 12, 2003
   // time: 00:30:00 UT
   //
   // topocentric right ascension = 7.85358
   //                             = 7 hours, 51 minutes,
   //                               12.8872 seconds
   //
   // topocentric declination = 25.2242
   //                         = 25 degrees, 13 minutes,
   //                           27.1306 seconds
   //

   double rightAscensionGEO;   // geocentric
   double declinationGEO;      //

   double rightAscensionTOPO;  // topocentric
   double declinationTOPO;     //

};

inline double Moon::getRightAscension()
{

   return rightAscensionTOPO;

}

inline double Moon::getDeclination()
{

   return declinationTOPO;

}

// get the number of days to December 31 0h 2000
// h is UT in decimal hours
// valid for the 20th and 21st centuries
inline double Moon::getDays(int y, int m, int d, double h)
{

   long val = - 7 * (y + (m + 9) / 12) / 4 + 275 * m / 9 + d;
   val += y * 367;
   return (double)(val - 730530.0 + h / 24.0);

}

// return the angle in the range [0, 2M_PI] depending on
// the signs of x and y
inline double Moon::getAngle(double y, double x)
{

   double a;

   a = atan(y / x);
   if (x < 0.0) a += M_PI;
   if (y < 0.0 && x > 0.0) a += (2*M_PI);
   return a;

}

// return an angle in the range [0, 2M_PI]
inline double Moon::getRange(double x)
{

   double b;
   double a;
   double tpi;

   tpi = 2 * M_PI;
   b = x / tpi;
   a = tpi * (b - getInteger(b));
   if (a < 0.0) a += tpi;
   return a;

}

// return the integer part of a double
inline int Moon::getInteger(double x)
{

   int sign;
   int val;

   sign = (x < 0.0) ? -1 : 1;
   val = (int)abs(x);
   return sign * val;

}

#endif // __MOON_H__