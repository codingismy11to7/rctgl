// ----------------------------------------------------------
// Moon.h
// ----------------------------------------------------------

#pragma once
#ifndef __MOON_H__
#define __MOON_H__

#include "Observer.h"

//#define _USE_MATH_DEFINES // required by Visual Studio .NET
#include <math.h>         // to access math.h constant M_PI
                          //
                          // those using gcc should use the
                          // -lm option during compilation

const double M_PI   =	3.14159265358979323846;
const double M_PI_2	=	1.57079632679489661923;


class Moon
{

public:

   Moon();
   ~Moon();

   void computeMoonPosition(Observer *);

   inline double getRightAscension() const
   { return m_rightAscensionTOPO; }

   inline double getDeclination() const
   { return m_declinationTOPO; }

private:

	// get the number of days to December 31 0h 2000
	// h is UT in decimal hours
	// valid for the 20th and 21st centuries
	inline double getDays(int y, int m, int d, double h) const
	{
		long val = - 7 * (y + (m + 9) / 12) / 4 + 275 * m / 9 + d;
		val += y * 367;
		return (double)(val - 730530.0 + h / 24.0);
	}


	// return the angle in the range [0, 2M_PI] depending on
	// the signs of x and y
	inline double getAngle(double y, double x) const
	{
		double a = atan(y / x);
		if (x < 0.0) a += M_PI;
		if (y < 0.0 && x > 0.0) a += (2*M_PI);
		return a;
	}

	// return an angle in the range [0, 2M_PI]
	inline double getRange(double x) const
	{
		double tpi = 2 * M_PI;
		double b = x / tpi;
		double a = tpi * (b - getInteger(b));
		if (a < 0.0) a += tpi;
		return a;
	}

	// return the integer part of a double
	inline int getInteger(double x) const
	{
		int sign = (x < 0.0) ? -1 : 1;
		int val = (int)abs(x);
		return sign * val;
	}

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

   double m_rightAscensionGEO;   // geocentric
   double m_declinationGEO;      //

   double m_rightAscensionTOPO;  // topocentric
   double m_declinationTOPO;     //

};

#endif // __MOON_H__