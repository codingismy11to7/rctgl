#include "rctgl-init.h"

// loads the colors from data in a provided XML file
bool loadRCTColors(void)
{	
	char *filename = "rctColors.dat";

	TiXmlDocument doc(filename);		

	if ( !doc.LoadFile() )
	{
		printf( "Could not load '%s'. Error='%s'\n", filename, doc.ErrorDesc() );
		return false;
	}

	TiXmlNode *child = 0;

	//load the file	
	child = doc.FirstChild();

	while(child->Type() != child->ELEMENT)
	{
		child = doc.IterateChildren(child);

		if(child == NULL)
		{
			printf("Error parsing '%s'\n", filename);
			return false;
		}
	}

	//loop through the data
	TiXmlNode *node = 0;
	TiXmlElement *tmpElement = 0;

	int colorCount = 0;

	for( node = child->FirstChild(); node; node = node->NextSibling() )
	{
		tmpElement = node->ToElement();

		if(strcmp(tmpElement->Value(), "color") == 0)
		{
			RCTColorsR[colorCount] = (float)atof((char *)tmpElement->Attribute("r"));
			RCTColorsG[colorCount] = (float)atof((char *)tmpElement->Attribute("g"));
			RCTColorsB[colorCount] = (float)atof((char *)tmpElement->Attribute("b"));
			colorCount++;
		}
	}

	//we can't continue if we didn't get all of the data
	if(colorCount != RCT_NUM_COLORS)
	{
		printf("Error: Incorrect number of colors read\n");
		return false;
	}
	

	return true;
}

bool calcTrigValues(void)
{
	int i;

	for(i=0; i<360; i++)
	{
		sinTable[i] = (float)sin(i * (3.14f / 180.0f));
		cosTable[i] = (float)cos(i * (3.14f / 180.0f));
		tanTable[i] = (float)tan(i * (3.14f / 180.0f));
	}

	return true;
}

bool initRCTGL(RCTGLPark *thePark)
{
	displayMode = MENU;

	DWORD temp;
	char EXELoc[1024];


	// TIM: The installer I made now puts the install path
	// into HKLM\Software\RCTGL\Path.  Use that instead?

	
	// get current directory so we can restore later
	temp = GetModuleFileName(NULL, EXELoc, 1024);
	printf("program location: %s\n", EXELoc);


	RCTGL_Location = EXELoc;
	RCTGL_Location.resize( RCTGL_Location.rfind( '\\' ) );

	printf("program dir: %s\n", RCTGL_Location.c_str());

	if(!loadRCTColors())
		return false;

	if(!calcTrigValues())
		return false;

	thePark->loadTextures();

	GLfloat fogColor[4]= {0.65f, 0.65f, 0.60f, 1.0f};
	glFogi(GL_FOG_MODE, GL_LINEAR);		// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.45f);				// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);				// Fog Start Depth
	glFogf(GL_FOG_END, 500.0f);				// Fog End Depth
	glEnable(GL_FOG);

	return true;
}