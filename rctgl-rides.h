#ifndef RCTGL_Rides_H
#define RCTGL_Rides_H

#include "rctgl.h"
#include "rctgl-texman.h"
#include "rctgl-rides.h"

#include "rctgl-rgb.h"
#include "rctgl-vertex.h"
#include "rctgl-poly.h"


#include <vector>
#include <map>


namespace RCTRide
{
	enum ColorSchemes {RCTStyle, LLStyle};
}

using namespace RCTRide;

struct RCTGLRide
{
	uchar rideType;
	uchar vehicleType;
	uchar operatingMode;
	ColorSchemes colorScheme;
	uchar primaryColor;
	uchar secondaryColor;
	uchar supportColor;

	uchar primaryColors[4];
	uchar secondaryColors[4];
	uchar supportColors[4];
};


class RCTGLRideSystem
{
public:
	RCTGLRide m_rides[255];
	RCTGLRideSystem();
	bool load(uchar *data);
	void clear();
};

#endif