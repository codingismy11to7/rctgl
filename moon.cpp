// ----------------------------------------------------------
// Moon.cpp
//
// based on prior work by Keith Burnett and Paul Schlyter
// (c) 1998
// ----------------------------------------------------------

#include "Moon.h"

Moon::Moon() { }
Moon::~Moon() { }

void Moon::computeMoonPosition(Observer *o)
{

   double degs = 180.0 / M_PI;
   double rads = M_PI / 180.0;

   // get time and date
   double h = o->hour;
   h = h + o->minute / 60.0;

   double d = getDays(o->year, o->month,
                      o->day, h);

   // Moon elements
   // longitude of the Moon's node
   double Nm = getRange((125.1228 - 0.0529538083 * d) *
                        rads);

   double im = 5.1454 * rads;

   // argument for the perihelion of the Moon
   double wm = getRange((318.0634 + 0.1643573223 * d) *
                        rads);

   // Earth radii
   double am = 60.2666;
   double ecm = 0.0549;

   // mean anomoly of the Moon
   double Mm = getRange((115.3654 + 13.0649929509 * d) *
                        rads);

   // Sun elements
   double Ns = 0.0;
   double isun = 0.0;

   // argument for the perihelion of the Sun
   double ws = getRange((282.9404 + 0.0000470935 * d) *
                        rads);

   // one Astronomical Unit
   double asun = 1.0;
   double ecs = 0.016709 - 0.000000001151 * d;

   // mean anomoly of the Sun
   double Ms = getRange((356.047 + 0.9856002585 * d) *
                        rads);

   // position of the Moon
   double Em = Mm + ecm * sin(Mm) * (1.0 + ecm * cos(Mm));
   double xv = am * (cos(Em) - ecm);
   double yv = am * (sqrt(1.0 - ecm * ecm) * sin(Em));
   double vm = getAngle(yv, xv);
   double rm = sqrt(xv * xv + yv * yv);

   double xh = rm * (cos(Nm) * cos(vm + wm) - sin(Nm) *
               sin(vm + wm) * cos(im));

   double yh = rm * (sin(Nm) * cos(vm + wm) + cos(Nm) *
               sin(vm + wm) * cos(im));

   double zh = rm * (sin(vm + wm) * sin(im));

   // the geocentric longitude and latitutde of the Moon
   double lon = getAngle(yh, xh);
   double lat = getAngle(zh, sqrt(xh * xh + yh * yh));

   // perturbations in radians
   // mean longitude of the Sun
   double Ls = Ms + ws;

   // mean longitude of the Moon
   double Lm = Mm + wm + Nm;

   // mean elongation of the Moon
   double dm = Lm - Ls;

   // argument of the latitude for the Moon
   double F = Lm - Nm;

   // add the following terms to the longitude
   // note amplitudes are in degrees, convert at end
   double dlon;

   // evection
   dlon = -1.274 * sin(Mm - 2.0 * dm);

   // variation
   dlon = dlon + 0.658 * sin(2.0 * dm);

   // yearly equation
   dlon = dlon - 0.186 * sin(Ms);
   dlon = dlon - 0.059 * sin(2.0 * Mm - 2.0 * dm);
   dlon = dlon - 0.057 * sin(Mm - 2.0 * dm + Ms);
   dlon = dlon + 0.053 * sin(Mm + 2.0 * dm);
   dlon = dlon + 0.046 * sin(2.0 * dm - Ms);
   dlon = dlon + 0.041 * sin(Mm - Ms);

   // parallactic equation
   dlon = dlon - 0.035 * sin(dm);
   dlon = dlon - 0.031 * sin(Mm + Ms);
   dlon = dlon - 0.015 * sin(2.0 * F - 2.0 * dm);
   dlon = dlon + 0.011 * sin(Mm - 4.0 * dm);
   lon = dlon * rads + lon;

   // latitude terms
   double dlat;

   dlat = -0.173 * sin(F - 2 * dm);
   dlat = dlat - 0.055 * sin(Mm - F - 2.0 * dm);
   dlat = dlat - 0.046 * sin(Mm + F - 2.0 * dm);
   dlat = dlat + 0.033 * sin(F + 2.0 * dm);
   dlat = dlat + 0.017 * sin(2.0 * Mm + F);
   lat = dlat * rads + lat;

   // distance terms Earth radii
   rm = rm - 0.58 * cos(Mm - 2.0 * dm);
   rm = rm - 0.46 * cos(2.0 * dm);

   // find the cartesian coordinates
   // of the geocentric lunar position
   double xg = rm * cos(lon) * cos(lat);
   double yg = rm * sin(lon) * cos(lat);
   double zg = rm * sin(lat);

   // rotate to equatorial coords
   // obliquity of ecliptic of date
   double ecl = (23.4393 - 0.0000003563 * d) * rads;
   double xe = xg;
   double ye = yg * cos(ecl) - zg * sin(ecl);
   double ze = yg * sin(ecl) + zg * cos(ecl);

   // geocentric right ascension and declination
   double ra = getAngle(ye, xe);
   double dec = atan(ze / sqrt(xe * xe + ye * ye));
   m_rightAscensionGEO = ra * degs / 15.0;
   m_declinationGEO = dec * degs;

   // topocentric right ascension and declination
   double lst = 100.46 + 0.985647352 * d + h * 15.0 +
                o->longitude;

   lst = getRange(lst * rads);

   double glat = o->latitude * rads;
   double glong = o->longitude * rads;

   double xtop = xe - cos(glat) * cos(lst);
   double ytop = ye - cos(glat) * sin(lst);
   double ztop = ze - sin(glat);
   double ratop = getAngle(ytop, xtop);
   double dectop = atan(ztop / sqrt(xtop * xtop +
                        ytop * ytop));

    m_rightAscensionTOPO = ratop * degs / 15.0;
    m_declinationTOPO = dectop * degs;

}