// ----------------------------------------------------------
// sun.h
// ----------------------------------------------------------

#ifndef __SUN_H__
#define __SUN_H__

#include <iostream>
#include <math.h>

class Sun
{

   public:

     Sun();
     ~Sun();

     void calculatePosition(double, double, double, double,
                            int);

	 inline void setColor(double c[4])
	 {
		 m_color[0] = c[0];
		 m_color[1] = c[1];
		 m_color[2] = c[2];
		 m_color[3] = c[3];
	 }

     inline double getTheta() const
	 { return m_theta; }

     inline double getPhi() const
	 { return m_phi; }

   private:

      double m_theta;   // angle from surface normal
                      // 0 = directly overhead
                      // pi/2 = at horizon

      double m_phi;     // angle from south direction
                      // 0 = south
                      // pi/2 = west
                      // -pi/2 = east

      double m_color[4];

};

#endif // __SUN_H__