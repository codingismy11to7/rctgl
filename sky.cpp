// ----------------------------------------------------------
// sky.cpp
// ----------------------------------------------------------

#include "sky.h"

Sky::Sky()
{

   thetaS = 0.0;
   phiS = 0.0;
   sun[0] = 0.0;
   sun[1] = 0.0;
   sun[2] = 1.0;
   T = 1.0;

}

Sky::~Sky() { }

void Sky::computeColour(SkyElement *e)
{

   double a;
   double theta, gamma, chi;

   double YZenith;
   double xZenith;
   double yZenith;
   double A, B, C, D, E;
   double Y, x, y, z;
   double d;

   a = e->v[0]*sun[0] + e->v[1]*sun[1] + e->v[2]*sun[2];
   gamma = acos(a);
   theta = e->theta;

   // CIE Y
   //

   chi = (4/9 - T/120)*(M_PI - 2*thetaS);
   YZenith = (4.0453*T - 4.9710)*tan(chi) - 0.2155*T + 2.4192;
   if (YZenith < 0.0) YZenith = -YZenith;

   A = YDC[0][0]*T + YDC[0][1];
   B = YDC[1][0]*T + YDC[1][1];
   C = YDC[2][0]*T + YDC[2][1];
   D = YDC[3][0]*T + YDC[3][1];
   E = YDC[4][0]*T + YDC[4][1];

   d = computeDistribution(A, B, C, D, E, theta, gamma);
   Y = YZenith * d;

  // x
  //

   xZenith = computeChromaticity(xZC);
   A = xDC[0][0]*T + xDC[0][1];
   B = xDC[1][0]*T + xDC[1][1];
   C = xDC[2][0]*T + xDC[2][1];
   D = xDC[3][0]*T + xDC[3][1];
   E = xDC[4][0]*T + xDC[4][1];

   d = computeDistribution(A, B, C, D, E, theta, gamma);
   x = xZenith * d;

  // y
  //

   yZenith = computeChromaticity(yZC);
   A = yDC[0][0]*T + yDC[0][1];
   B = yDC[1][0]*T + yDC[1][1];
   C = yDC[2][0]*T + yDC[2][1];
   D = yDC[3][0]*T + yDC[3][1];
   E = yDC[4][0]*T + yDC[4][1];

   d = computeDistribution(A, B, C, D, E, theta, gamma);
   y = yZenith * d;

   z = 1.0 - x - y;

   e->X = (x/y)*Y;
   e->Y = Y;
   e->Z = (z/y)*Y;

}

double Sky::computeDistribution(double A, double B,
                                double C, double D,
                                double E,
                                double theta,
                                double gamma)
{

   double e0, e1, e2;
   double f0, f1, f2;

   e0 = B / cos(theta);
   e1 = D * gamma;
   e2 = cos(gamma);
   e2 *= e2;
   f1 = (1 + A*pow(M_E, e0)) * (1 + C*pow(M_E, e1) + E*e2);

   e0 = B;
   e1 = D * thetaS;
   e2 = cos(thetaS);
   e2 *= e2;
   f2 = (1 + A*pow(M_E, e0)) * (1 + C*pow(M_E, e1) + E*e2);

   f0 = f1 / f2;
   return f0;

}

double Sky::computeChromaticity(double m[][4])
{

   double a;
   double T2;
   double t2, t3;

   T2 = T*T;

   t2 = thetaS*thetaS;
   t3 = thetaS*thetaS*thetaS;

   a =
     (T2*m[0][0] + T*m[1][0] + m[2][0])*t3 +
     (T2*m[0][1] + T*m[1][1] + m[2][1])*t2 +
     (T2*m[0][2] + T*m[1][2] + m[2][2])*thetaS +
     (T2*m[0][3] + T*m[1][3] + m[2][3]);

   return a;

}