// ----------------------------------------------------------
// sky.h
// ----------------------------------------------------------

#ifndef __SKY_H__
#define __SKY_H__

#include <iostream>
#include <map>
#include <math.h>
using namespace std;

#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923

#define M_E     0.911e-27       /* mass of electron */


typedef struct {

   double X, Y, Z;   // CIE XYZ colour values
   double theta;     // angle from zenith
   double v[3];      // normalised direction vector from
                     // viewer at 'p' to sky element

} SkyElement;


// the following coefficient matrices are derived from
//
// Preetham, A.J., Peter Shirley and Brian Smits
// A Practical Analytic Model for Daylight
// Department of Computer Science, University of Utah,
// 1999
//


static double YDC[5][2] = {
   {0.1787, -1.4630},
   {-0.3554, 0.4275},
   {-0.0227, 5.3251},
   {0.1206, -2.5771},
   {-0.0670, 0.3703}
};

static double xDC[5][2] = {
   {-0.0193, -0.2592},
   {-0.0665, 0.0008},
   {-0.0004, 0.2125},
   {-0.0641, -0.8989},
   {-0.0033, 0.0452}
};

static double yDC[5][2] = {
   {-0.0167, -0.2608},
   {-0.0950, 0.0092},
   {-0.0079, 0.2102},
   {-0.0441, -1.6537},
   {-0.0109, 0.0529}
};

static double xZC[3][4] = {
   {0.00166, -0.00375, 0.00209, 0},
   {-0.02903, 0.06377, -0.03203, 0.00394},
   {0.11693, -0.21196, 0.06052, 0.25886}
};

static double yZC[3][4] = {
   {0.00275, -0.00610, 0.00317, 0},
   {-0.04214, 0.08970, -0.04153, 0.00516},
   {0.15346, -0.26756, 0.06670, 0.26688}
};

// CIE XYZ to RGB conversion matrix assuming
// D65 white point
//

static double CM[3][3] = {
   {3.240479, -1.537150, -0.498535},
   {-0.969256, 1.875992, 0.041556},
   {0.055648, -0.204043, 1.057311}
};

class Sky
{

   public:

      Sky();
      ~Sky();

      void setTurbidity(double);
      void setSVector(double, double);
      void computeColour(SkyElement *);
      map<int, SkyElement> getSkyElements(void);

   private:

      double computeDistribution(double, double, double,
                                 double, double, double,
                                 double);

      void XYZtoRGB(double, double, double,
                    double *, double *, double *);

      double computeChromaticity(double [][4]);
      double thetaS;
      double phiS;

      double sun[3];   // normalised direction vector from
                       // viewer at 'p' to the Sun

      double T;   // Turbidity T is the ratio of the
                  // thickness of haze atmosphere (haze and
                  // air) to the atmosphere (air) alone.
                  //
                  // Pure air has a turbidity of one.  Hazy,
                  // foggy and/or polluted atmospheres have
                  // turbidities in the range from two to ten.

      map<int, SkyElement> skyElement;

};

inline void Sky::setTurbidity(double t)
{

   T = (t < 1.0) ? 1.0 : t;

}

inline void Sky::setSVector(double theta, double phi)
{

   sun[0] = cos(phi)*sin(theta);
   sun[1] = sin(phi)*sin(theta);
   sun[2] = cos(theta);

   thetaS = theta;
   phiS = phi;

}

inline void Sky::XYZtoRGB(double X, double Y, double Z,
			  double *r, double *g,
			  double *b)
{

   *r = CM[0][0]*X + CM[0][1]*Y + CM[0][2]*Z;
   *g = CM[1][0]*X + CM[1][1]*Y + CM[1][2]*Z;
   *b = CM[2][0]*X + CM[2][1]*Y + CM[2][2]*Z;

}

#endif // __SKY_H__