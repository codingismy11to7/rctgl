// ----------------------------------------------------------
// Observer.cpp
// ----------------------------------------------------------

//#include "stdafx.h"
#include "Observer.h"

Observer::Observer(double lat, double lon,
                   int yr, int mth,
                   int dy, int hr,
                   int min, int sec)
				   : latitude(lat), longitude(lon), year(yr), month(mth),
				   day(dy), hour(hr), minute(min), second(sec)
{
}
