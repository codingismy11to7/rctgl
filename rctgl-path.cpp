#include "rctgl-path.h"

using namespace RCTPath;  //import path constants

RCTGLPath::RCTGLPath(void)
{

}


bool RCTGLPath::loadOffset(uchar *data)
{	
	m_pathModifier1 = 0;
	m_pathModifier2 = 0;
	m_pathExtras = 0;
	m_baseHeight = 0;
	m_pathExtensions = 0;

	//lower 2 bits of byte 0 are path qualifier
	//mask with 00000011
	uchar tmp = (data[0] & 0x03);
	m_pathModifier1 = tmp;

	//middle 2 bits of upper nibble of bit 1 are support type
	//mask with 01100000 and shift right
	tmp = ((data[1] & 0x60) >> 5);
	m_pathModifier2 = tmp;

	//base height = byte 3
	m_baseHeight = data[3];

	//upper nibble of byte 4 is path type
	//mask with 11110000 and shift right
	m_pathModifier1 |= ((data[4] & 0xF0) >> 2);

	//lower nibble of byte 4 is path slope
	//mask with 00001111
	tmp = (data[4] & 0x0F);

	switch(tmp)
	{
	case 0x00:
		m_pathModifier2 |= PATH_SLOPE_NONE;
		break;
	case 0x04:
		m_pathModifier2 |= PATH_SLOPE_WEST;
		break;
	case 0x05:
		m_pathModifier2 |= PATH_SLOPE_NORTH;
		break;
	case 0x06:
		m_pathModifier2 |= PATH_SLOPE_EAST;
		break;
	case 0x07:
		m_pathModifier2 |= PATH_SLOPE_SOUTH;
		break;
	}

	//if bit 3 is set, then the path is a queue entry point
	if(tmp & 0x08)
		m_pathModifier2 |= PATH_QUEUE_ENTRY;

	//byte 5 has additions to the path
	m_pathExtras = data[5];

	//byte 6 has path extensions
	m_pathExtensions = data[6];

	//byte 7 has edge info (extras)
	tmp = data[7];

	//upper 2 bits are for S (11000000)
	if(tmp & 0xC0)
		m_pathExtras |= MOD_APPLY_SOUTH;
	//next 2 bits are for E (00110000)
	if(tmp & 0x30)
		m_pathExtras |= MOD_APPLY_EAST;
	//next 2 bits are for N (00001100)
	if(tmp & 0x0C)
		m_pathExtras |= MOD_APPLY_NORTH;
	//bottom 2 bits are for W (00000011)
	if(tmp & 0x03)
		m_pathExtras |= MOD_APPLY_WEST;

	return true;
}