#include "rctgl-texman.h"

void RCTGLTextureManager::loadPathTex(char *filename, int texNum, uchar pathOptions)
{

}

unsigned int RCTGLTextureManager::loadTex(char *filename, uchar texOptions)
{
	enum fileTypes {TGA, PNG};

	//fileTypes fileType;

	//loop through the textures to see if the path exists
	//(if the path exists, then the texture already exists)
	bool foundIt = false;


	//if we're here, then the current texture isn't already loaded
	//so we have to load it into OGL ourselves and return our internal texID
	unsigned int texID;

		
	glGenTextures (1, &texID);
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );	

	corona::Image* image = corona::OpenImage(filename);
	if (!image) {
		DebugLog::writeToLog(string("Error loading image ") + filename);
		return -1;
		// error
	}

	int width = image->getWidth();
	int height = image->getHeight();
	corona::PixelFormat format = image->getFormat();
	image = corona::FlipImage(image, corona::CA_X);
	void* pixels = image->getPixels();

	
	if(texOptions & TEXTURE_CLAMP)
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	
	}
	else
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);


	switch (format) {
		case corona::PF_B8G8R8A8:
			//printf("BGRA \n");
			BGRA2RGBA((uchar *)pixels, width, height);
			//break;
		//	image = corona::CloneImage(image, corona::PF_R8G8B8A8);
		case corona::PF_R8G8B8A8:  // process image data
			//printf("found RGBA %4d %4d\n", width, height);

			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			//glTexImage2D ( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
			//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, (uchar *)pixels);
			break;
		case corona::PF_B8G8R8:
			//printf("BGR \n");
			BGR2RGB((uchar *)pixels, width, height);
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

	return texID;

}

void RCTGLTextureManager::BGRA2RGBA(uchar *pixels, int w, int h)
{
	uchar oldR, oldG, oldB, oldA;

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

void RCTGLTextureManager::BGR2RGB(uchar *pixels, int w, int h)
{
	uchar oldR, oldG, oldB;

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

void RCTGLTextureManager::buildPathTex(uchar *pixels, int w, int h, unsigned int pathOptions)
{

}

int RCTGLTextureManager::addPathTexture(const char *filepath, int texID, unsigned int options)
{
	return 0;
}

unsigned int RCTGLTextureManager::addTexture(const char *filepath, uchar texOptions)
{
	char *tmp = (char *)malloc(256);
	char tempstr[256];

	tmp = strcpy(&tempstr[0], &RCTGL_Location[0]);
	tmp = strcat(tmp, filepath);

	return loadTex(tmp, texOptions);
}
