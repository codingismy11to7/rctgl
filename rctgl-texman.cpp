#include "rctgl-texman.h"

using namespace RCTTextureManager;

unsigned int RCTGLTextureManager::loadPathTex(const string &filename, uchar pathOptions)
{
	return 0;
}

unsigned int RCTGLTextureManager::loadTex(const string &filename, uchar texOptions)
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

	corona::Image* image = corona::OpenImage(filename.c_str());
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

	if(texOptions)
		buildPathTex((uchar *)pixels, width, height, texOptions);

	
	/*
	if(texOptions & TEXTURE_CLAMP)
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);	
	}
	else
	*/
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

			//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
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
			//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
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
			if((pathOptions & PATH_NW) && (i<cropWidth) && (j<cropWidth))
				*(pixels + offset) = 0xFF;
			else if((pathOptions & PATH_NE) && (i>(w-cropWidth)) && (j<cropWidth))
				*(pixels + offset) = 0xFF;
			else if((pathOptions & PATH_SE) && (i>(w-cropWidth)) && (j>(h-cropWidth)))
				*(pixels + offset) = 0xFF;
			else if((pathOptions & PATH_SW) && (i<cropWidth) && (j>(h-cropWidth)))
				*(pixels + offset) = 0xFF;

			else if((pathOptions & PATH_NORTH) && (i>=cropWidth) && (i<=(w-cropWidth)) && (j<cropWidth))
				*(pixels + offset) = 0xFF;
			else if((pathOptions & PATH_SOUTH) && (i>=cropWidth) && (i<=(w-cropWidth)) && (j>(h-cropWidth)))
				*(pixels + offset) = 0xFF;
			else if((pathOptions & PATH_EAST) && (i>(w-cropWidth)) && (j>=cropWidth) && (j<=(h-cropWidth)))
				*(pixels + offset) = 0xFF;
			else if((pathOptions & PATH_WEST) && (i<cropWidth) && (j>=cropWidth) && (j<=(h-cropWidth)))
				*(pixels + offset) = 0xFF;

			offset += 4;
		}
	}
}


unsigned int RCTGLTextureManager::addPathTexture(const string &filepath, unsigned int options)
{
	return loadPathTex((RCTGL_Location + filepath).c_str(), options);
}

unsigned int RCTGLTextureManager::addTexture(const string &filepath, uchar texOptions)
{
	return loadTex((RCTGL_Location + filepath).c_str(), texOptions);
}
