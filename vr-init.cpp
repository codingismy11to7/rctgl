#include "vr3d.h"
#include "tgaload.h"
#include "tga2.h"

#include "corona.h"

#include "NeHeGL.h"
#include "skyDome.h"


/* global variables */
float RCTColorsR[32];
float RCTColorsG[32];
float RCTColorsB[32];



int InclineDegrees;

int framecount;

int detailLevel;

int fogLevel;

long NumPolys;

int lastmousex, lastmousey;

float FrameRate;

int FrameCount;

int TOrientation;
int TOrientationOrig;

float xWaterOffset;
float zWaterOffset;

float XV, YV, ZV;
float XR, YR, ZR;

extern RenderModes DisplayMode;

extern GL_Window			window;

extern AudioStructType AudioSpecifiers[256];

extern float ambientRData[17], ambientGData[17], ambientBData[17];
extern GLuint starfieldDisplayListA;	//the small stars
extern GLuint starfieldDisplayListB;	//the bigger stars
extern bbVertex sphereCoords[17][19];

extern skyDome *mySkyDome;

#define PATH_NORTH	1	//00000001
#define PATH_NE		2	//00000010
#define PATH_EAST	4	//00000100
#define PATH_SE		8	//00001000
#define PATH_SOUTH	16	//00010000
#define PATH_SW		32	//00100000
#define PATH_WEST	64	//01000000
#define PATH_NW		128	//10000000

void buildPathTex(unsigned char *pixels, int w, int h, unsigned int options)
{
	//white is invisible (100% alpha)
	//the tile starts out as all black (0% alpha)
	//options specifies the areas we want to make invisible

	//crop width = 1/8 of total width
	int cropWidth = w/8;

	long offset = 3;

	for(int j=0; j<h; j++)
	{
		for(int i=0 ;i<w; i++)
		{
			if((options & PATH_NW) && (i<cropWidth) && (j<cropWidth))
				*(pixels + offset) = 0xFF;
			else if((options & PATH_NE) && (i>(w-cropWidth)) && (j<cropWidth))
				*(pixels + offset) = 0xFF;
			else if((options & PATH_SE) && (i>(w-cropWidth)) && (j>(h-cropWidth)))
				*(pixels + offset) = 0xFF;
			else if((options & PATH_SW) && (i<cropWidth) && (j>(h-cropWidth)))
				*(pixels + offset) = 0xFF;

			else if((options & PATH_NORTH) && (i>=cropWidth) && (i<=(w-cropWidth)) && (j<cropWidth))
				*(pixels + offset) = 0xFF;
			else if((options & PATH_SOUTH) && (i>=cropWidth) && (i<=(w-cropWidth)) && (j>(h-cropWidth)))
				*(pixels + offset) = 0xFF;
			else if((options & PATH_EAST) && (i>(w-cropWidth)) && (j>=cropWidth) && (j<=(h-cropWidth)))
				*(pixels + offset) = 0xFF;
			else if((options & PATH_WEST) && (i<cropWidth) && (j>=cropWidth) && (j<=(h-cropWidth)))
				*(pixels + offset) = 0xFF;

			offset += 4;
		}
	}
}

void BGRA2RGBA(unsigned char *pixels, int w, int h)
{
	unsigned char oldR, oldG, oldB, oldA;

	for(int i=0; i<(w*h*4); i+=4)
	{
		//read the old vals
		oldB = *(pixels + i);
		oldG = *(pixels + i + 1);
		oldR = *(pixels + i + 2);
		oldA = *(pixels + i + 3);

		//set the new vals
		*(pixels + i) = oldR;
		*(pixels + i + 2) = oldB;
	}
}

void BGR2RGB(unsigned char *pixels, int w, int h)
{
	unsigned char oldR, oldG, oldB;

	for(int i=0; i<(w*h*3); i+=3)
	{
		//read the old vals
		oldB = *(pixels + i);
		oldG = *(pixels + i + 1);
		oldR = *(pixels + i + 2);

		//set the new vals
		*(pixels + i) = oldR;
		*(pixels + i + 2) = oldB;
	}
}


int addPathTexture(const char *filepath, int texID, unsigned int options)
{
	enum fileTypes {TGA, PNG};

	fileTypes fileType;

	//loop through the textures to see if the path exists
	//(if the path exists, then the texture already exists)
	bool foundIt = false;


	//if we're here, then the current texture isn't already loaded
	//so we have to load it into OGL ourselves and return our internal texID

		
	glGenTextures (1, &texture_id[texID]);
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );	

	corona::Image* image = corona::OpenImage(filepath);
	if (!image) {
		printf("can't load file %s\n", filepath);
		return -1;
		// error
	}

	int width = image->getWidth();
	int height = image->getHeight();
	corona::PixelFormat format = image->getFormat();
	image = corona::FlipImage(image, corona::CA_X);
	void* pixels = image->getPixels();

	

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glGenTextures(1, &texture_id[texID]);
	glBindTexture(GL_TEXTURE_2D, texture_id[texID]);


	buildPathTex((unsigned char *)pixels, width, height, options);


	switch (format) {
		case corona::PF_B8G8R8A8:
			//printf("BGRA \n");
			BGRA2RGBA((unsigned char *)pixels, width, height);
			//break;
		//	image = corona::CloneImage(image, corona::PF_R8G8B8A8);
		case corona::PF_R8G8B8A8:  // process image data
			//printf("found RGBA %4d %4d\n", width, height);

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			//glTexImage2D ( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
			//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)pixels);
			break;
		case corona::PF_B8G8R8:
			//printf("BGR \n");
			BGR2RGB((unsigned char *)pixels, width, height);
			//break;
		//	image = corona::CloneImage(image, corona::PF_R8G8B8);
		case corona::PF_R8G8B8:    // process image data

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			//printf("found RGB %4d %4d\n", width, height);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			break;

		case corona::PF_I8:
			//printf("I8\n");
			break;
		default:  // can't handle the format?
			printf("unsupported image format\n");
			break;
	}

	delete image;

	//printf("loaded texture %d - %s\n", (*ppTex)->GLTexID, (*ppTex)->filename);

	return 0;
}


unsigned int addTextureNoArray(const char *filepath)
{
	enum fileTypes {TGA, PNG};

	fileTypes fileType;

	//loop through the textures to see if the path exists
	//(if the path exists, then the texture already exists)
	bool foundIt = false;


	//if we're here, then the current texture isn't already loaded
	//so we have to load it into OGL ourselves and return our internal texID

	unsigned int texID;

		
	glGenTextures (1, &texID);
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );	

	corona::Image* image = corona::OpenImage(filepath);
	if (!image) {
		printf("can't load file %s\n", filepath);
		return -1;
		// error
	}

	int width = image->getWidth();
	int height = image->getHeight();
	corona::PixelFormat format = image->getFormat();
	image = corona::FlipImage(image, corona::CA_X);
	void* pixels = image->getPixels();

	

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);


	switch (format) {
		case corona::PF_B8G8R8A8:
			//printf("BGRA \n");
			BGRA2RGBA((unsigned char *)pixels, width, height);
			//break;
		//	image = corona::CloneImage(image, corona::PF_R8G8B8A8);
		case corona::PF_R8G8B8A8:  // process image data
			//printf("found RGBA %4d %4d\n", width, height);

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			//glTexImage2D ( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
			//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)pixels);
			break;
		case corona::PF_B8G8R8:
			//printf("BGR \n");
			BGR2RGB((unsigned char *)pixels, width, height);
			//break;
		//	image = corona::CloneImage(image, corona::PF_R8G8B8);
		case corona::PF_R8G8B8:    // process image data

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			//printf("found RGB %4d %4d\n", width, height);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			break;

		case corona::PF_I8:
			//printf("I8\n");
			break;
		default:  // can't handle the format?
			printf("unsupported image format\n");
			break;
	}

	delete image;

	//printf("loaded texture %d - %s\n", (*ppTex)->GLTexID, (*ppTex)->filename);

	return texID;
}



int addTexture(const char *filepath, int texID)
{
	texture_id[texID] = addTextureNoArray(filepath);

	return 0;
}




int addTextureClamp(const char *filepath, int texID)
{
	enum fileTypes {TGA, PNG};

	fileTypes fileType;

	//loop through the textures to see if the path exists
	//(if the path exists, then the texture already exists)
	bool foundIt = false;


	//if we're here, then the current texture isn't already loaded
	//so we have to load it into OGL ourselves and return our internal texID

		
	glGenTextures (1, &texture_id[texID]);
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );	

	corona::Image* image = corona::OpenImage(filepath);
	if (!image) {
		printf("can't load file %s\n", filepath);
		return -1;
		// error
	}

	int width = image->getWidth();
	int height = image->getHeight();
	corona::PixelFormat format = image->getFormat();
	image = corona::FlipImage(image, corona::CA_X);
	void* pixels = image->getPixels();

	

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glGenTextures(1, &texture_id[texID]);
	glBindTexture(GL_TEXTURE_2D, texture_id[texID]);


	switch (format) {
		case corona::PF_B8G8R8A8:
			//printf("BGRA \n");
			BGRA2RGBA((unsigned char *)pixels, width, height);
			//break;
		//	image = corona::CloneImage(image, corona::PF_R8G8B8A8);
		case corona::PF_R8G8B8A8:  // process image data
			//printf("found RGBA %4d %4d\n", width, height);

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			//glTexImage2D ( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
			//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)pixels);
			break;
		case corona::PF_B8G8R8:
			//printf("BGR \n");
			BGR2RGB((unsigned char *)pixels, width, height);
			//break;
		//	image = corona::CloneImage(image, corona::PF_R8G8B8);
		case corona::PF_R8G8B8:    // process image data

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			//printf("found RGB %4d %4d\n", width, height);
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			break;

		case corona::PF_I8:
			//printf("I8\n");
			break;
		default:  // can't handle the format?
			printf("unsupported image format\n");
			break;
	}

	delete image;

	//printf("loaded texture %d - %s\n", (*ppTex)->GLTexID, (*ppTex)->filename);

	return 0;
}


/* -- init_lightsource() --
 * sets up the lighting system
 */
GLvoid init_lightsource ( GLvoid )
{
	/*
	GLfloat light_ambient0[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position0[] = { 100.0, 100.0, 100.0, 0.0 };
  
	// declare the blue light at <2,2,2>
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,1.0);
	glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,0.0);
	glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,0.0);
  

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);  

	
	// enable the lighting model and the lights at <2,2,2> and <-2,-2,2>
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	*/

	
	GLfloat specular [] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat ambient [] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shininess [] = { 1000.0f };
	GLfloat position [] = { -372.0f, -134.0f, -1000.0f, 0.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_SHININESS, shininess);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	

	/*
	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]= { -372.0, -134.0, -1000.0, 0.0 };

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);
	*/
}


/* -- Timer() --
 * wates for a specific period, in milliseconds
 */
GLvoid Timer( int value )
{
/*
   if( value ) glutPostRedisplay();
   glutTimerFunc(40,Timer,value);
*/
}




void loadPathTexWithPath(char *filename, int texNum, unsigned int options)
{
	char *tmp = (char *)malloc(256);
	char tempstr[256];

	tmp = strcpy(&tempstr[0], RCTGL_Location);

	int doh = addPathTexture(strcat(tempstr, filename), texNum, options);

	//printf ("loaded texture %s (%d)\n", filename, doh);
}


void loadTexWithPath(char *filename, int texNum)
{
	char *tmp = (char *)malloc(256);
	char tempstr[256];

	tmp = strcpy(&tempstr[0], RCTGL_Location);

	int doh = addTexture(strcat(tempstr, filename), texNum);

	//printf ("loaded texture %s (%d)\n", filename, doh);
}


unsigned int loadTexWithPathNoArray(char *filename)
{
	char *tmp = (char *)malloc(256);
	char tempstr[256];

	tmp = strcpy(&tempstr[0], RCTGL_Location);

	return addTextureNoArray(strcat(tempstr, filename));

	//printf ("loaded texture %s (%d)\n", filename, doh);
}


void loadTexWithPathClamp(char *filename, int texNum)
{
	char *tmp = (char *)malloc(256);
	char tempstr[256];

	tmp = strcpy(&tempstr[0], RCTGL_Location);

	int doh = addTextureClamp(strcat(tempstr, filename), texNum);

	//printf ("loaded texture %s (%d)\n", filename, doh);
}



void init ( GLvoid )     // Create Some Everyday Functions
{
	int i;
	float tempval;

		//XV = YV = ZV = 20.0f;
	XV = ZV = 0.0f;
	YV = -10.0f;
	XR = YR = ZR = 0.0f;

	//YV = -20.0f;

	XR = 180.0f;

	xWaterOffset = 0.0f;
	zWaterOffset = 0.0f;

	TOrientation = 0;
	TOrientationOrig = TOrientation;

	//initialize FPS counter
	FrameCount=0;
	FrameRate=0.0f;

	lastmousex=0;
	lastmousey=0;

	NumPolys = 0;

	framecount = 0;

	detailLevel = M_MEDIUM_DETAIL;

	fogLevel = M_FOG_HAZE;

	//set up a temporary track to test with
	
	/*
	TrackLength = 5;
	TrackSetup[0].TrackType = 0x00;
	TrackSetup[0].x = 0.0f;
	TrackSetup[0].y = 0.0f;
	TrackSetup[0].z = 0.0f;
	TrackSetup[1].TrackType = 0x00;
	TrackSetup[1].x = UNITWIDTH;
	TrackSetup[1].y = UNITWIDTH;
	TrackSetup[1].z = UNITWIDTH;
	TrackSetup[2].TrackType = 0x00;
	TrackSetup[2].x = 2.0f * UNITWIDTH;
	TrackSetup[2].y = 2.0f * UNITWIDTH;
	TrackSetup[2].z = 2.0f * UNITWIDTH;
	TrackSetup[3].TrackType = 0x00;
	TrackSetup[3].x = 3.0f * UNITWIDTH;
	TrackSetup[3].y = 3.0f * UNITWIDTH;
	TrackSetup[3].z = 3.0f * UNITWIDTH;
	TrackSetup[4].TrackType = 0x00;
	TrackSetup[4].x = 4.0f * UNITWIDTH;
	TrackSetup[4].y = 4.0f * UNITWIDTH;
	TrackSetup[4].z = 4.0f * UNITWIDTH;
	*/
		
	
	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);
	

	//InitTextures();

	//init_lightsource();

	//calculate degrees in incline/decline
	tempval = UNITHEIGHT / UNITWIDTH;

	InclineDegrees = atan (tempval) * 180.0f / M_PI;

	printf("inclines are %d degrees steep\n", InclineDegrees);

	//CreateLandscape();
	

	// populate RCTColors arrays
	RCTColorsR[0] = 0.16f;
	RCTColorsG[0] = 0.25f;
	RCTColorsB[0] = 0.26f;

	RCTColorsR[1] = 0.42f;
	RCTColorsG[1] = 0.51f;
	RCTColorsB[1] = 0.52f;

	RCTColorsR[2] = 0.71f;
	RCTColorsG[2] = 0.76f;
	RCTColorsB[2] = 0.76f;

	RCTColorsR[3] = 0.45f;
	RCTColorsG[3] = 0.49f;
	RCTColorsB[3] = 0.68f;

	RCTColorsR[4] = 0.52f;
	RCTColorsG[4] = 0.32f;
	RCTColorsB[4] = 0.74f;

	RCTColorsR[5] = 0.03f;
	RCTColorsG[5] = 0.25f;
	RCTColorsB[5] = 0.75f;

	RCTColorsR[6] = 0.26f;
	RCTColorsG[6] = 0.53f;
	RCTColorsB[6] = 0.91f;

	RCTColorsR[7] = 0.16f;
	RCTColorsG[7] = 0.57f;
	RCTColorsB[7] = 0.55f;

	RCTColorsR[8] = 0.09f;
	RCTColorsG[8] = 0.47f;
	RCTColorsB[8] = 0.00f;

	RCTColorsR[9] = 0.29f;
	RCTColorsG[9] = 0.53f;
	RCTColorsB[9] = 0.35f;

	RCTColorsR[10] = 0.39f;
	RCTColorsG[10] = 0.56f;
	RCTColorsB[10] = 0.22f;

	RCTColorsR[11] = 0.26f;
	RCTColorsG[11] = 0.68f;
	RCTColorsB[11] = 0.13f;

	RCTColorsR[12] = 0.52f;
	RCTColorsG[12] = 0.62f;
	RCTColorsB[12] = 0.35f;

	RCTColorsR[13] = 0.52f;
	RCTColorsG[13] = 0.54f;
	RCTColorsB[13] = 0.22f;

	RCTColorsR[14] = 0.84f;
	RCTColorsG[14] = 0.65f;
	RCTColorsB[14] = 0.06f;

	RCTColorsR[15] = 0.55f;
	RCTColorsG[15] = 0.32f;
	RCTColorsB[15] = 0.00f;

	RCTColorsR[16] = 1.00f;
	RCTColorsG[16] = 0.43f;
	RCTColorsB[16] = 0.06f;

	RCTColorsR[17] = 0.71f;
	RCTColorsG[17] = 0.27f;
	RCTColorsB[17] = 0.00f;

	RCTColorsR[18] = 0.71f;
	RCTColorsG[18] = 0.51f;
	RCTColorsB[18] = 0.26f;

	RCTColorsR[19] = 0.48f;
	RCTColorsG[19] = 0.33f;
	RCTColorsB[19] = 0.09f;

	RCTColorsR[20] = 0.48f;
	RCTColorsG[20] = 0.40f;
	RCTColorsB[20] = 0.29f;

	RCTColorsR[21] = 0.81f;
	RCTColorsG[21] = 0.51f;
	RCTColorsB[21] = 0.39f;

	RCTColorsR[22] = 0.65f;
	RCTColorsG[22] = 0.22f;
	RCTColorsB[22] = 0.22f;

	RCTColorsR[23] = 0.55f;
	RCTColorsG[23] = 0.00f;
	RCTColorsB[23] = 0.00f;

	RCTColorsR[24] = 0.91f;
	RCTColorsG[24] = 0.02f;
	RCTColorsB[24] = 0.00f;

	RCTColorsR[25] = 0.87f;
	RCTColorsG[25] = 0.22f;
	RCTColorsB[25] = 0.55f;

	RCTColorsR[26] = 0.94f;
	RCTColorsG[26] = 0.62f;
	RCTColorsB[26] = 0.62f;

	RCTColorsR[27] = 0.58f;
	RCTColorsG[27] = 0.02f;
	RCTColorsB[27] = 0.29f;

	RCTColorsR[28] = 0.22f;
	RCTColorsG[28] = 0.26f;
	RCTColorsB[28] = 0.45f;

	RCTColorsR[29] = 0.52f;
	RCTColorsG[29] = 0.81f;
	RCTColorsB[29] = 0.81f;

	RCTColorsR[30] = 1.00f;
	RCTColorsG[30] = 0.91f;
	RCTColorsB[30] = 0.16f;

	RCTColorsR[31] = 0.55f;
	RCTColorsG[31] = 0.83f;
	RCTColorsB[31] = 0.97f;

//	CFileDialog MyDlg(FALSE,"gam","*.gam",OFN_OVERWRITEPROMPT |	OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,NULL,NULL);
//	if(MyDlg.DoModal()==IDOK)
//  {
//		printf("yeah\n");
//  }

	
	
}

void InitSkydome(void)
{

}

void InitSurfaceTextures(void)
{
	// non-loopy landscapes textures
	loadTexWithPath("\\surfaces\\grass4b.tga", TEXTURE_GRASS1);
	loadTexWithPath("\\surfaces\\sand1.tga", TEXTURE_SAND1);
	loadTexWithPath("\\surfaces\\gravel1.tga", TEXTURE_GRAVEL1);
	loadTexWithPath("\\surfaces\\jungle1.tga", TEXTURE_JUNGLE1);
	loadTexWithPath("\\surfaces\\roofing1.tga", TEXTURE_ROOFING1);
	loadTexWithPath("\\surfaces\\mars1.tga", TEXTURE_MARS1);
	loadTexWithPath("\\surfaces\\checker1.tga", TEXTURE_CHECKER1);
	loadTexWithPath("\\surfaces\\dirt1.tga", TEXTURE_DIRT1);

	// loopy landscapes textures
	loadTexWithPath("\\surfaces\\green1.tga", TEXTURE_GREEN1);
	loadTexWithPath("\\surfaces\\purple1.tga", TEXTURE_PURPLE1);
	loadTexWithPath("\\surfaces\\yellow1.tga", TEXTURE_YELLOW1);
	loadTexWithPath("\\surfaces\\red1.tga", TEXTURE_RED1);
	loadTexWithPath("\\surfaces\\grey1.tga", TEXTURE_GREYROOF1);
	loadTexWithPath("\\surfaces\\iron1.tga", TEXTURE_IRONROOF1);
	loadTexWithPath("\\surfaces\\log1.tga", TEXTURE_LOGROOF1);
	loadTexWithPath("\\surfaces\\icetop1.tga", TEXTURE_ICETOP1);
	loadTexWithPath("\\surfaces\\water1.tga", TEXTURE_WATER1);
}

void InitEdgeTextures()
{	
	// standard wall textures
	loadTexWithPath("\\edges\\wood1.tga", TEXTURE_WOODWALL1);
	loadTexWithPath("\\edges\\dirtwall.tga", TEXTURE_DIRTWALL1);
	loadTexWithPath("\\edges\\bricks.tga", TEXTURE_BRICKWALL1);
	loadTexWithPath("\\edges\\rustwall.tga", TEXTURE_IRONWALL1);
	loadTexWithPath("\\edges\\darkwall.tga", TEXTURE_BLACKWALL1);
	loadTexWithPath("\\edges\\greywall.tga", TEXTURE_GREYWALL1);
	loadTexWithPath("\\edges\\yelwall.tga", TEXTURE_YELLOWWALL1);
	loadTexWithPath("\\edges\\redwall.tga", TEXTURE_REDWALL1);


	//LL wall textures
	loadTexWithPath("\\edges\\icewall.tga", TEXTURE_ICEWALL1);
	loadTexWithPath("\\edges\\purwall.tga", TEXTURE_PURPLEWALL1);
	loadTexWithPath("\\edges\\grnwall.tga", TEXTURE_GREENWALL1);
	loadTexWithPath("\\edges\\brstwall.tga", TEXTURE_BROWNSTONEWALL1);
	loadTexWithPath("\\edges\\grstwall.tga", TEXTURE_GRAYSTONEWALL1);
	loadTexWithPath("\\edges\\skyawall.tga", TEXTURE_SKYSCRAPERAWALL1);
	loadTexWithPath("\\edges\\skybwall.tga", TEXTURE_SKYSCRAPERBWALL1);
}

void InitSkyTextures(void)
{
	loadTexWithPath("\\skies\\original\\front.tga", TEXTURE_SKYFRONT);
	loadTexWithPath("\\skies\\original\\right.tga", TEXTURE_SKYRIGHT);
	loadTexWithPath("\\skies\\original\\back.tga", TEXTURE_SKYBACK);
	loadTexWithPath("\\skies\\original\\left.tga", TEXTURE_SKYLEFT);
	loadTexWithPath("\\skies\\original\\up.tga", TEXTURE_SKYUP);
	loadTexWithPath("\\skies\\original\\down.tga", TEXTURE_SKYDOWN);

	unsigned int skyTex;
	skyTex = loadTexWithPathNoArray("\\clearsky2d.png"); //, TEXTURE_SKYDOME);
	mySkyDome->setSkyTexture(skyTex);
	skyTex = loadTexWithPathNoArray("\\clouds.tga"); //, TEXTURE_SKYDOME);
	mySkyDome->setCloudTexture(skyTex);
}
	

void InitTreeTextures(void)
{
	/*
	 * Load whole-tile trees
	 */
	loadTexWithPath("\\trees\\00-1.tga", TEXTURE_TREE_00_1);
	loadTexWithPath("\\trees\\01-1.tga", TEXTURE_TREE_01_1);
	loadTexWithPath("\\trees\\02-1.tga", TEXTURE_TREE_02_1);
	loadTexWithPath("\\trees\\03-1.tga", TEXTURE_TREE_03_1);
	loadTexWithPath("\\trees\\04-1.tga", TEXTURE_TREE_04_1);
	loadTexWithPath("\\trees\\05-1.tga", TEXTURE_TREE_05_1);
	loadTexWithPath("\\trees\\06-1.tga", TEXTURE_TREE_06_1);
	loadTexWithPath("\\trees\\07-1.tga", TEXTURE_TREE_07_1);
	loadTexWithPath("\\trees\\0F-1.tga", TEXTURE_TREE_0F_1);

	loadTexWithPath("\\trees\\11-1.tga", TEXTURE_TREE_11_1);
	loadTexWithPath("\\trees\\12-1.tga", TEXTURE_TREE_12_1);
	loadTexWithPath("\\trees\\13-1.tga", TEXTURE_TREE_13_1);
	loadTexWithPath("\\trees\\14-1.tga", TEXTURE_TREE_14_1);
	loadTexWithPath("\\trees\\16-1.tga", TEXTURE_TREE_16_1);
	loadTexWithPath("\\trees\\18-1.tga", TEXTURE_TREE_18_1);
	loadTexWithPath("\\trees\\19-1.tga", TEXTURE_TREE_19_1);
	loadTexWithPath("\\trees\\1A-1.tga", TEXTURE_TREE_1A_1);
	loadTexWithPath("\\trees\\1B-1.tga", TEXTURE_TREE_1B_1);
	loadTexWithPath("\\trees\\1D-1.tga", TEXTURE_TREE_1D_1);
	loadTexWithPath("\\trees\\1E-1.tga", TEXTURE_TREE_1E_1);
	loadTexWithPath("\\trees\\1F-1.tga", TEXTURE_TREE_1F_1);

	loadTexWithPath("\\trees\\20-1.tga", TEXTURE_TREE_20_1);
	loadTexWithPath("\\trees\\21-1.tga", TEXTURE_TREE_21_1);
	loadTexWithPath("\\trees\\22-1.tga", TEXTURE_TREE_22_1);
	//loadTexWithPath("\\trees\\23-1.tga", TEXTURE_TREE_23);
	loadTexWithPath("\\trees\\24-1.tga", TEXTURE_TREE_24_1);
	loadTexWithPath("\\trees\\25-1.tga", TEXTURE_TREE_25_1);
	loadTexWithPath("\\trees\\26-1.tga", TEXTURE_TREE_26_1);
	loadTexWithPath("\\trees\\27-1.tga", TEXTURE_TREE_27_1);
	loadTexWithPath("\\trees\\28-1.tga", TEXTURE_TREE_28_1);
	loadTexWithPath("\\trees\\29-1.tga", TEXTURE_TREE_29_1);
	loadTexWithPath("\\trees\\2A-1.tga", TEXTURE_TREE_2A_1);

	loadTexWithPath("\\trees\\34-1.tga", TEXTURE_TREE_34_1);
	loadTexWithPath("\\trees\\36-1.tga", TEXTURE_TREE_36_1);
	loadTexWithPath("\\trees\\37-1.tga", TEXTURE_TREE_37_1);

	loadTexWithPath("\\trees\\66-1.tga", TEXTURE_TREE_66_1);

	loadTexWithPath("\\trees\\77-1.tga", TEXTURE_TREE_77_1);

	loadTexWithPath("\\trees\\80-1.tga", TEXTURE_TREE_80_1);
	loadTexWithPath("\\trees\\81-1.tga", TEXTURE_TREE_81_1);
	loadTexWithPath("\\trees\\82-1.tga", TEXTURE_TREE_82_1);
	loadTexWithPath("\\trees\\83-1.tga", TEXTURE_TREE_83_1);
	loadTexWithPath("\\trees\\84-1.tga", TEXTURE_TREE_84_1);

	loadTexWithPath("\\trees\\jungle2.tga", TEXTURE_TREE_97_1);
	loadTexWithPath("\\trees\\jungle1.tga", TEXTURE_TREE_98_1);
	loadTexWithPath("\\trees\\jungle5.tga", TEXTURE_TREE_9E_1);
	loadTexWithPath("\\trees\\jungle4.tga", TEXTURE_TREE_9F_1);
	loadTexWithPath("\\trees\\jungle3.tga", TEXTURE_TREE_A3_1);

	loadTexWithPath("\\trees\\AC.tga", TEXTURE_TREE_AC);
	loadTexWithPath("\\trees\\AD.tga", TEXTURE_TREE_AD);
	loadTexWithPath("\\trees\\AE.tga", TEXTURE_TREE_AE);
	loadTexWithPath("\\trees\\AF.tga", TEXTURE_TREE_AF);
	loadTexWithPath("\\trees\\B0.tga", TEXTURE_TREE_B0);
	loadTexWithPath("\\trees\\B0.tga", TEXTURE_TREE_B1);
	loadTexWithPath("\\trees\\B0.tga", TEXTURE_TREE_B2);

	loadTexWithPath("\\trees\\41.tga", TEXTURE_TREE_41);
	loadTexWithPath("\\trees\\42.tga", TEXTURE_TREE_42);
	loadTexWithPath("\\trees\\43.tga", TEXTURE_TREE_43);
	loadTexWithPath("\\trees\\44.tga", TEXTURE_TREE_44);
	loadTexWithPath("\\trees\\45.tga", TEXTURE_TREE_45);
	loadTexWithPath("\\trees\\46.tga", TEXTURE_TREE_46);
	loadTexWithPath("\\trees\\47.tga", TEXTURE_TREE_47);
	loadTexWithPath("\\trees\\48.tga", TEXTURE_TREE_48);
	loadTexWithPath("\\trees\\49.tga", TEXTURE_TREE_49);
	loadTexWithPath("\\trees\\4A.tga", TEXTURE_TREE_4A);
	loadTexWithPath("\\trees\\4B.tga", TEXTURE_TREE_4B);
	loadTexWithPath("\\trees\\4C.tga", TEXTURE_TREE_4C);
	loadTexWithPath("\\trees\\4D.tga", TEXTURE_TREE_4D);
}

void InitPathTextures(void)
{
	/*
	queue textures
	*/
	loadTexWithPath("\\paths\\00-00.tga", TEXTURE_PATH_00_00);
	loadTexWithPath("\\paths\\00-05.tga", TEXTURE_PATH_00_05);
	loadTexWithPath("\\paths\\00-07.tga", TEXTURE_PATH_00_07);

	loadTexWithPath("\\paths\\01-00.tga", TEXTURE_PATH_01_00);
	loadTexWithPath("\\paths\\01-05.tga", TEXTURE_PATH_01_05);
	loadTexWithPath("\\paths\\01-07.tga", TEXTURE_PATH_01_07);

	loadTexWithPath("\\paths\\02-00.tga", TEXTURE_PATH_02_00);
	loadTexWithPath("\\paths\\02-05.tga", TEXTURE_PATH_02_05);
	loadTexWithPath("\\paths\\02-07.tga", TEXTURE_PATH_02_07);
	
	loadTexWithPath("\\paths\\03-00.tga", TEXTURE_PATH_03_00);
	loadTexWithPath("\\paths\\03-05.tga", TEXTURE_PATH_03_05);
	loadTexWithPath("\\paths\\03-07.tga", TEXTURE_PATH_03_07);

	/*
	normal textures
	*/

	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_0B, 0);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\04-base.tga", TEXTURE_PATH_04_27, PATH_NE | PATH_SW | PATH_SE);
	
	loadTexWithPath("\\paths\\05-00.tga", TEXTURE_PATH_05_00);
	loadTexWithPath("\\paths\\05-01.tga", TEXTURE_PATH_05_01);
	loadTexWithPath("\\paths\\05-05.tga", TEXTURE_PATH_05_05);
	loadTexWithPath("\\paths\\05-07.tga", TEXTURE_PATH_05_07);
	loadTexWithPath("\\paths\\05-0B.tga", TEXTURE_PATH_05_0B);
	loadTexWithPath("\\paths\\05-0C.tga", TEXTURE_PATH_05_0C);
	loadTexWithPath("\\paths\\05-10.tga", TEXTURE_PATH_05_10);
	loadTexWithPath("\\paths\\05-14.tga", TEXTURE_PATH_05_14);
	loadTexWithPath("\\paths\\05-15.tga", TEXTURE_PATH_05_15);
	loadTexWithPath("\\paths\\05-19.tga", TEXTURE_PATH_05_19);
	loadTexWithPath("\\paths\\05-1D.tga", TEXTURE_PATH_05_1D);
	loadTexWithPath("\\paths\\05-21.tga", TEXTURE_PATH_05_21);
	loadTexWithPath("\\paths\\05-23.tga", TEXTURE_PATH_05_23);
	loadTexWithPath("\\paths\\05-27.tga", TEXTURE_PATH_05_27);

	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_0B, 0);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\06-base.tga", TEXTURE_PATH_06_27, PATH_NE | PATH_SW | PATH_SE);	

	loadTexWithPath("\\paths\\07-00.tga", TEXTURE_PATH_07_00);
	loadTexWithPath("\\paths\\07-01.tga", TEXTURE_PATH_07_01);
	loadTexWithPath("\\paths\\07-05.tga", TEXTURE_PATH_07_05);
	loadTexWithPath("\\paths\\07-07.tga", TEXTURE_PATH_07_07);
	loadTexWithPath("\\paths\\07-0B.tga", TEXTURE_PATH_07_0B);
	loadTexWithPath("\\paths\\07-0C.tga", TEXTURE_PATH_07_0C);
	loadTexWithPath("\\paths\\07-10.tga", TEXTURE_PATH_07_10);
	loadTexWithPath("\\paths\\07-14.tga", TEXTURE_PATH_07_14);
	loadTexWithPath("\\paths\\07-15.tga", TEXTURE_PATH_07_15);
	loadTexWithPath("\\paths\\07-19.tga", TEXTURE_PATH_07_19);
	loadTexWithPath("\\paths\\07-1D.tga", TEXTURE_PATH_07_1D);
	loadTexWithPath("\\paths\\07-21.tga", TEXTURE_PATH_07_21);
	loadTexWithPath("\\paths\\07-23.tga", TEXTURE_PATH_07_23);
	loadTexWithPath("\\paths\\07-27.tga", TEXTURE_PATH_07_27);

	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_0B, 0);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\08-base.tga", TEXTURE_PATH_08_27, PATH_NE | PATH_SW | PATH_SE);
	

	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_0B, 0);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\09-base.tga", TEXTURE_PATH_09_27, PATH_NE | PATH_SW | PATH_SE);	

	
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_0B, 0);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\0A-base.tga", TEXTURE_PATH_0A_27, PATH_NE | PATH_SW | PATH_SE);	
	

	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_0B, 0);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\0B-base.tga", TEXTURE_PATH_0B_27, PATH_NE | PATH_SW | PATH_SE);
	

	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_0B, 0);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\0C-base.tga", TEXTURE_PATH_0C_27, PATH_NE | PATH_SW | PATH_SE);	
	


	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_0B, 0);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\0D-base.tga", TEXTURE_PATH_0D_27, PATH_NE | PATH_SW | PATH_SE);


	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_00, PATH_NE | PATH_EAST | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_01,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_05,	PATH_NE | PATH_EAST | PATH_SE | PATH_SW | PATH_WEST | PATH_NW);	
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_07,	PATH_NE | PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_0B, 0);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_0C,	PATH_NW | PATH_WEST | PATH_SW);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_10,	PATH_NE | PATH_NW | PATH_SE | PATH_SW | PATH_NORTH);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_14,	PATH_NE | PATH_NW | PATH_SE | PATH_SW);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_15,	PATH_NW | PATH_SW);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_19, PATH_SE | PATH_SOUTH | PATH_SW | PATH_WEST | PATH_NW);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_1D, PATH_NE);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_21, PATH_SE | PATH_NW);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_23, PATH_NE | PATH_SW | PATH_SE | PATH_SOUTH);
	loadPathTexWithPath("\\paths\\0E-base.tga", TEXTURE_PATH_0E_27, PATH_NE | PATH_SW | PATH_SE);
	
}

void InitWallTextures(void)
{
	loadTexWithPath("\\walls\\00.tga", TEXTURE_WALL_00);
	loadTexWithPath("\\walls\\01.tga", TEXTURE_WALL_01);
	loadTexWithPath("\\walls\\02.tga", TEXTURE_WALL_02);
	loadTexWithPath("\\walls\\03.tga", TEXTURE_WALL_03);
	loadTexWithPath("\\walls\\04.tga", TEXTURE_WALL_04);
	loadTexWithPath("\\walls\\05.tga", TEXTURE_WALL_05);
	loadTexWithPath("\\walls\\06.tga", TEXTURE_WALL_06);
	loadTexWithPath("\\walls\\07.tga", TEXTURE_WALL_07);
	loadTexWithPath("\\walls\\08.tga", TEXTURE_WALL_08);
	loadTexWithPath("\\walls\\09.tga", TEXTURE_WALL_09);
	loadTexWithPath("\\walls\\11.tga", TEXTURE_WALL_11);
	loadTexWithPath("\\walls\\12.tga", TEXTURE_WALL_12);
	loadTexWithPath("\\walls\\14.tga", TEXTURE_WALL_14);
	loadTexWithPath("\\walls\\1A.tga", TEXTURE_WALL_1A);
	loadTexWithPath("\\walls\\20.tga", TEXTURE_WALL_20);
	loadTexWithPath("\\walls\\21.tga", TEXTURE_WALL_21);
	loadTexWithPath("\\walls\\22.tga", TEXTURE_WALL_22);
	loadTexWithPath("\\walls\\23.tga", TEXTURE_WALL_23);
	loadTexWithPath("\\walls\\24.tga", TEXTURE_WALL_24);
	loadTexWithPath("\\walls\\26.tga", TEXTURE_WALL_26);
	loadTexWithPath("\\walls\\27.tga", TEXTURE_WALL_27);
	loadTexWithPath("\\walls\\28.tga", TEXTURE_WALL_28);
	loadTexWithPath("\\walls\\2B.tga", TEXTURE_WALL_2B);

	loadTexWithPath("\\walls\\30.tga", TEXTURE_WALL_30);
	loadTexWithPath("\\walls\\31.tga", TEXTURE_WALL_31);
	loadTexWithPath("\\walls\\33.tga", TEXTURE_WALL_33);
	loadTexWithPath("\\walls\\34.tga", TEXTURE_WALL_34);
	loadTexWithPath("\\walls\\35.tga", TEXTURE_WALL_35);
	loadTexWithPath("\\walls\\36.tga", TEXTURE_WALL_36);
	loadTexWithPath("\\walls\\37.tga", TEXTURE_WALL_37);
	loadTexWithPath("\\walls\\38.tga", TEXTURE_WALL_38);
	loadTexWithPath("\\walls\\3B.tga", TEXTURE_WALL_3B);
}

void InitRideTextures(void)
{
	loadTexWithPath("\\rides\\loglift.tga", TEXTURE_RIDE_LOGLIFT);

	loadTexWithPath("\\rides\\00-00.tga", TEXTURE_RIDE_00_00);
	loadTexWithPath("\\rides\\00-01.tga", TEXTURE_RIDE_00_01);

	loadTexWithPath("\\rides\\04-00.tga", TEXTURE_RIDE_04_00);
	loadTexWithPath("\\rides\\04-01.tga", TEXTURE_RIDE_04_01);

	loadTexWithPath("\\rides\\05-00.tga", TEXTURE_RIDE_05_00);

	loadTexWithPath("\\rides\\06-00.tga", TEXTURE_RIDE_06_00);
	loadTexWithPath("\\rides\\06-01.tga", TEXTURE_RIDE_06_01);
	loadTexWithPath("\\rides\\06-02.tga", TEXTURE_RIDE_06_02);

	loadTexWithPath("\\rides\\09-00.tga", TEXTURE_RIDE_09_00);

	loadTexWithPath("\\rides\\0B-00.tga", TEXTURE_RIDE_0B_00);

	loadTexWithPath("\\rides\\0C-00.tga", TEXTURE_RIDE_0C_00);

	loadTexWithPath("\\rides\\0F-00.tga", TEXTURE_RIDE_0F_00);
	loadTexWithPath("\\rides\\0F-01.tga", TEXTURE_RIDE_0F_01);

	loadTexWithPath("\\rides\\11-00.tga", TEXTURE_RIDE_11_00);
	loadTexWithPath("\\rides\\11-01.tga", TEXTURE_RIDE_11_01);

	loadTexWithPath("\\rides\\12-00.tga", TEXTURE_RIDE_12_00);

	loadTexWithPath("\\rides\\32-00.tga", TEXTURE_RIDE_32_00);

	loadTexWithPath("\\rides\\36-00.tga", TEXTURE_RIDE_36_00);
	loadTexWithPath("\\rides\\36-01.tga", TEXTURE_RIDE_36_01);

	loadTexWithPath("\\rides\\3B-00.tga", TEXTURE_RIDE_3B_00);

	loadTexWithPath("\\edges\\rent1.tga", TEXTURE_RIDE_ENT1);
	loadTexWithPath("\\edges\\rent2.tga", TEXTURE_RIDE_ENT2);
	loadTexWithPath("\\edges\\rentrf.tga", TEXTURE_RIDE_ENT3);
}


/* do lighting stuff here */
void normalize(float * vect)	//scales a vector a length of 1
{
	float length;
	int a;

	length=sqrt(					//A^2 + B^2 + C^2 = length^2
				pow(vect[0],2.0f)+	
				pow(vect[1],2.0f)+
				pow(vect[2],2.0f)
				);

	for (a=0;a<3;++a)				//divides vector by its length to normalise
	{
		vect[a]/=length;
	}
}

void crossProduct(float *c,float a[3], float b[3])		//finds the cross product of two vectors
{															
	c[0]=a[1]*b[2] - b[1]*a[2];
	c[1]=a[2]*b[0] - b[2]*a[0];
	c[2]=a[0]*b[1] - b[0]*a[1];
}


void getFaceNormal(float *norm,float pointa[3],float pointb[3],float pointc[3])
{
	float vect[2][3];
	int a,b;
	float point[3][3];

	for (a=0;a<3;++a)
	{
		point[0][a]=pointa[a];						//copies points into point[][]
		point[1][a]=pointb[a]; 
		point[2][a]=pointc[a];
	}

	for (a=0;a<2;++a)									//calculates vectors from point[0] to point[1]
	{														//and point[0] to point[2]
		for (b=0;b<3;++b)
		{
			vect[a][b]=point[2-a][b]-point[0][b];			
		}
	}

	crossProduct(norm,vect[0],vect[1]);			//calculates vector at 90° to to 2 vectors
	normalize(norm);									//makes the vector length 1
}



void loadExtendedInfo(char *filename)
{
	FILE *inp;

	int i, j;

	char inpString[128];

	/*
	for(i=0; i<128; i++)
		for(j=0; j<128; j++)
			thePark.cdTrack[i][j] = -1;
	*/


	inp = fopen(filename, "r");

	if(inp == NULL)
		perror("fopen\n");

	while(!feof(inp))
	{
		fgets(&inpString[0], 128, inp);		

		inpString[strlen(&inpString[0]) - 1] = '\0';

		if(strcmp("[AudioDescriptor]", &inpString[0]) == 0)
			inp = loadAudioDescriptor(inp);
	}

	fclose(inp);

	//DisplayMode = InGame;

	//SetMenu(window.hWnd, NULL);
}