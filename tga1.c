#include "tga1.h"

GLenum texFormat;

extern GLuint texture_id[];

int checkSize (int x)
{
    if (x == 2	 || x == 4 || 
        x == 8	 || x == 16 || 
        x == 32  || x == 64 ||
        x == 128 || x == 256 || x == 512)
        return 1;
    else
		return 0;
}


unsigned char* getRGBA (FILE *s, int size)
{
    unsigned char *rgba;
    unsigned char temp;
    int bread;
    int i;

    rgba = (unsigned char *)malloc (size * 4); 

    if (rgba == NULL)
        return 0;

    bread = fread (rgba, sizeof (unsigned char), size * 4, s); 

    /* TGA is stored in BGRA, make it RGBA */
    if (bread != size * 4)
    {
        free (rgba);
        return 0;
    }

    for (i = 0; i < size * 4; i += 4 )
    {
        temp = rgba[i];
        rgba[i] = rgba[i + 2];
        rgba[i + 2] = temp;
    }

    texFormat = GL_RGBA;
    return rgba;
}
/*
=============
getRGB

Reads in RGB data for a 24bit image. 
=============
*/
unsigned char* getRGB (FILE *s, int size)
{
    unsigned char *rgb;
    unsigned char temp;
    int bread;
    int i;

    rgb = (unsigned char *)malloc (size * 3); 

    if (rgb == NULL)
        return 0;

    bread = fread (rgb, sizeof (unsigned char), size * 3, s);

    if (bread != size * 3)
    {
        free (rgb);
        return 0;
    }

    /* TGA is stored in BGR, make it RGB */
    for (i = 0; i < size * 3; i += 3)
    {
        temp = rgb[i];
        rgb[i] = rgb[i + 2];
        rgb[i + 2] = temp;
    }

    texFormat = GL_RGB;

    return rgb;
}
/*
=============
getGray

Gets the grayscale image data.  Used as an alpha channel.
=============
*/
unsigned char* getGray (FILE *s, int size)
{
    unsigned char *grayData;
    int bread;

    grayData = (unsigned char *)malloc (size);

    if (grayData == NULL)
        return 0;

    bread = fread (grayData, sizeof (unsigned char), size, s);

    if (bread != size)
    {
        free (grayData);
        return 0;
    }

    //texFormat = GL_ALPHA;
   texFormat = GL_LUMINANCE;

    return grayData;
}



unsigned char* getData (FILE *s, int sz, int iBits)
{
    if (iBits == 32)
        return getRGBA (s, sz);
    else if (iBits == 24)
        return getRGB (s, sz);	
    else if (iBits == 8)
        return getGray (s, sz);
    return NULL;
}



int LoadTGAFromFile(char *fname, int texID)
{   unsigned char type[4];
    unsigned char info[7];
    unsigned char *imageData = NULL;
    int imageWidth, imageHeight;
    int imageBits, size;
    FILE *s;

    if (!(s = fopen (fname, "r+bt")))
	{
		printf("TGA file not found\n");
        return 0;
	}

    fread (&type, sizeof (char), 3, s); // read in colormap info and image type, byte 0 ignored
    fseek (s, 12, SEEK_SET);			// seek past the header and useless info
    fread (&info, sizeof (char), 6, s);

    if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
	{
		printf("bad image type\n");
        return 0;
	}

    imageWidth = info[0] + info[1] * 256; 
    imageHeight = info[2] + info[3] * 256;
    imageBits =	info[4]; 

    size = imageWidth * imageHeight; 

    /* make sure dimension is a power of 2 */
    if (!checkSize (imageWidth) || !checkSize (imageHeight))
	{
		printf("dimensions are not a power of 2\n");
        return 0;
	}

    /* make sure we are loading a supported type */
    if (imageBits != 32 && imageBits != 24 && imageBits != 8)
	{
		printf("unsupported color depth\n");
		return 0;
	}
     

    imageData = getData (s, size, imageBits);

    /* no image data */
    if (imageData == NULL)
	{
		printf("no image data\n");
		return 0;
	}

    glGenTextures(1,&texture_id[texID]);
	
	glBindTexture (GL_TEXTURE_2D, texture_id[texID]);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, imageData); 

    /*
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexImage2D (GL_TEXTURE_2D, 0, texFormat, imageWidth, imageHeight, 0, texFormat, GL_UNSIGNED_BYTE, imageData);
	*/

    /* release data, its been uploaded */
    free (imageData);

    fclose (s);
	
	return 0;


}
