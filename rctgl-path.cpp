#include "rctgl-path.h"

RCTGLPath::RCTGLPath(void)
{

}


bool RCTGLPath::loadOffset(uchar *data)
{	
	pathModifier1 = 0;
	pathModifier2 = 0;
	pathExtras = 0;
	baseHeight = 0;
	pathExtensions = 0;

	//lower 2 bits of byte 0 are path qualifier
	//mask with 00000011
	uchar tmp = (data[0] & 0x03);
	pathModifier1 = tmp;

	//middle 2 bits of upper nibble of bit 1 are support type
	//mask with 01100000 and shift right
	tmp = ((data[1] & 0x60) >> 5);
	pathModifier2 = tmp;

	//base height = byte 3
	baseHeight = data[3];

	//upper nibble of byte 4 is path type
	//mask with 11110000 and shift right
	pathModifier1 |= ((data[4] & 0xF0) >> 2);

	//lower nibble of byte 4 is path slope
	//mask with 00001111
	tmp = (data[4] & 0x0F);

	switch(tmp)
	{
	case 0x00:
		pathModifier2 |= PATH_SLOPE_NONE;
		break;
	case 0x04:
		pathModifier2 |= PATH_SLOPE_WEST;
		break;
	case 0x05:
		pathModifier2 |= PATH_SLOPE_NORTH;
		break;
	case 0x06:
		pathModifier2 |= PATH_SLOPE_EAST;
		break;
	case 0x07:
		pathModifier2 |= PATH_SLOPE_SOUTH;
		break;
	}

	//if bit 3 is set, then the path is a queue entry point
	if(tmp & 0x08)
		pathModifier2 |= PATH_QUEUE_ENTRY;

	//byte 5 has additions to the path
	pathExtras = data[5];

	//byte 6 has path extensions
	pathExtensions = data[6];

	//byte 7 has edge info (extras)
	tmp = data[7];

	//upper 2 bits are for S (11000000)
	if(tmp & 0xC0)
		pathExtras |= MOD_APPLY_SOUTH;
	//next 2 bits are for E (00110000)
	if(tmp & 0x30)
		pathExtras |= MOD_APPLY_EAST;
	//next 2 bits are for N (00001100)
	if(tmp & 0x0C)
		pathExtras |= MOD_APPLY_NORTH;
	//bottom 2 bits are for W (00000011)
	if(tmp & 0x03)
		pathExtras |= MOD_APPLY_WEST;

	return true;
}