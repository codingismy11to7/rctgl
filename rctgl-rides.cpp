#include "rctgl-rides.h"

RCTGLRideSystem::RCTGLRideSystem()
{
}

bool RCTGLRideSystem::load(uchar *data)
{
	for(uchar i=0; i<255; i++)
	{
		m_rides[i].rideType = data[0];
		m_rides[i].vehicleType = data[1];

		//for non CF/LL parks
		m_rides[i].primaryColor = data[0x1E];
		m_rides[i].secondaryColor = data[0x1F];
		m_rides[i].supportColor = data[0x20];

		//for CF/LL parks
		m_rides[i].primaryColors[0] = data[0x16C];
		m_rides[i].primaryColors[1] = data[0x16D];
		m_rides[i].primaryColors[2] = data[0x16E];
		m_rides[i].primaryColors[3] = data[0x16F];

		m_rides[i].secondaryColors[0] = data[0x170];
		m_rides[i].secondaryColors[1] = data[0x171];
		m_rides[i].secondaryColors[2] = data[0x172];
		m_rides[i].secondaryColors[3] = data[0x173];

		m_rides[i].supportColors[0] = data[0x174];
		m_rides[i].supportColors[1] = data[0x175];
		m_rides[i].supportColors[2] = data[0x176];
		m_rides[i].supportColors[3] = data[0x177];

		data += 0x260;	//each ride element contains 608 bytes
	}

	return true;
}

void RCTGLRideSystem::clear()
{

}