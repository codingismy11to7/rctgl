/*******************************************************************
* Contient toutes les fonctions nécessaires pour afficher du texte *
********************************************************************/
/*
   Note : Ce n'est pas moi qui l'ai programmé, je ne sais donc pas commenter le code.
   ------															  
															  19/10/2000 Leyder Dylan
*/
#include "Tga.h" // Pour charger un fichier TGA
#include <tchar.h>

extern float white[4];
extern float gray[4];


// ***********************************************************************
struct Texte_t
{
   Texte_t();
   int Load(char *name);
   int LoadEx(char *name, int row, int col);
   void Draw(int xpos, int ypos, char *s, ...);
   void Region(int x, int y, int w, int h)
    {region = 1; regionX = x; regionY = y - h; regionW = w; regionH = h;}
   void Taille(int sze) {size = sze;}
   void Shadow(void) {shadow = 1;}
   void Gradient(void) {gradient = 1;}
   void Color3f(float r, float g, float b)
    {fgColor[0] = r; fgColor[1] = g; fgColor[2] = b; fgColor[3] = 1.0;}
   void Color4f(float r, float g, float b, float a)
    {fgColor[0] = r; fgColor[1] = g; fgColor[2] = b; fgColor[3] = a;}
   void Color3fv(float *clr)
    {fgColor[0] = clr[0]; fgColor[1] = clr[1]; fgColor[2] = clr[2]; fgColor[3] = 1.0;}
   void Color4fv(float *clr)
    {fgColor[0] = clr[0]; fgColor[1] = clr[1]; fgColor[2] = clr[2]; fgColor[3] = clr[3];}
   void ShadowColor3f(float r, float g, float b)
    {bgColor[0] = r; bgColor[1] = g; bgColor[2] = b; bgColor[3] = 1.0;}
   void ShadowColor4f(float r, float g, float b, float a)
    {bgColor[0] = r; bgColor[1] = g; bgColor[2] = b; bgColor[3] = a;}
   void ShadowColor3fv(float *clr)
    {bgColor[0] = clr[0]; bgColor[1] = clr[1]; bgColor[2] = clr[2]; bgColor[3] = 1.0;}
   void ShadowColor4fv(float *clr)
    {bgColor[0] = clr[0]; bgColor[1] = clr[1]; bgColor[2] = clr[2]; bgColor[3] = clr[3];}
   void GradientColor3f(float r, float g, float b)
    {gdColor[0] = r; gdColor[1] = g; gdColor[2] = b; gdColor[3] = 1.0;}
   void GradientColor4f(float r, float g, float b, float a)
    {gdColor[0] = r; gdColor[1] = g; gdColor[2] = b; gdColor[3] = a;}
   void GradientColor3fv(float *clr)
    {gdColor[0] = clr[0]; gdColor[1] = clr[1]; gdColor[2] = clr[2]; gdColor[3] = 1.0;}
   void GradientColor4fv(float *clr)
    {gdColor[0] = clr[0]; gdColor[1] = clr[1]; gdColor[2] = clr[2]; gdColor[3] = clr[3];}

protected:
   void Reset(void);
   void ColorCopy(float *dest, float *src)
    {dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; dest[3] = src[3];}
   void DrawChar(char c, int x, int y, int size, int shadow);
   void RenderChar(char c, int x, int y, int size);
   void ScissorNormal(int xpos, int ypos, int tabs, int carrage, int size, int len);
   void ScissorTextRegion(void)
    {glScissor(regionX, regionY, regionW, regionH);}
   void ForeColorReset(void) {ColorCopy(fgColor, white);}
   void ShadowColorReset(void) {ColorCopy(bgColor, gray);}
   void GradientColorReset(void) {ColorCopy(gdColor, gray);}
   int SlashParser (char *buffPtr, int *x, int *y);
   void WalkString(char *buffPtr, int xpos, int ypos, int *vPort);
   int SetColorFromToken(char *s);
   int ItalicsMode(char *s);
   int BoldMode(char *s);
   int GetCharHits(char *s, char f);
   void MakeMap(void);
   void SetModes(int state);

   static int fontBlockCol;
   static int fontBlockRow;
   static int fontGetModes; 
   static int fontRestoreModes; 
   static const int fontMaxLen;
   static int fontTabSpace;
   static float fontITOF;
   static int fontItalic;

   float fgColor[4];   /* foreground color, default white */
   float gdColor[4];   /* gradient color, default gray */
   float bgColor[4];   /* background color, default gray */
   int size;           /* size of text, default 12 */
   int shadow;         /* shadow text? default 0 */
   int gradient;       /* gradient? default 0 */
   int italic;         /* italic amount, defaul 0 */
   int bold;           /* bold text? */
   int region;         /* do we have a text region */
   int regionX;        /* lower left x */
   int regionY;        /* lower left y */
   int regionW;        /* text region w */
   int regionH;        /* text region h */
   float tIncX;        /* used for texture coords, x axis amount to move */
   float tIncY;        /* used for texture coords, y axis amount to move */
   int blockRow;       /* characters per row */
   int blockCol;       /* characters per col */
   unsigned int texId; /* texture id */
   
};

static float white[4] = {1.0, 1.0, 1.0, 1.0};
static float gray[4] = {0.5, 0.5, 0.5, 1.0};

int Texte_t::fontBlockCol = 16;
int Texte_t::fontBlockRow = 16;
int Texte_t::fontGetModes = 1; 
int Texte_t::fontRestoreModes = 2; 
const int Texte_t::fontMaxLen = 1024;
int Texte_t::fontTabSpace = 4;
float Texte_t::fontITOF = (float) pow (255, -1);
int Texte_t::fontItalic = 8;

float tPoints[257][2]; 


// ***********************************************************************
Texte_t::Texte_t()
{
   ColorCopy(fgColor, white); 
   ColorCopy(gdColor, gray);
   ColorCopy(gdColor, gray);
   size = 12;
   shadow = 0;
   gradient = 0;
   italic = 0;
   bold = 0;
   region = 0;;         
   regionX = 0;
   regionY = 0;
   regionW = 0;
   regionH = 0;
   tIncX = 0.0f;
   tIncY = 0.0f;
   blockRow = fontBlockRow;
   blockCol = fontBlockCol;
   texId = 0;
}


// ***********************************************************************
void Texte_t::Reset(void)
{
   size = 12;
   shadow = 0;
   region = 0;
   gradient = 0;
   italic = 0;
   bold = 0;
   regionX = 0;
   regionY = 0;
   regionW = 0;
   regionH = 0;
   ForeColorReset();
   ShadowColorReset();
   GradientColorReset();
}


// ***********************************************************************
int Texte_t::Load(char *name)
{
   tga_t image;

   texId = image.GenId();

   blockRow = fontBlockRow;
   blockCol = fontBlockCol;
   
   MakeMap();

   return image.Load(name, texId, tga_t::uploadYes, GL_ALPHA);
}


// ***********************************************************************
int Texte_t::LoadEx (char *name, int row, int col)
{
   /* make sure we have valid dimensions */
   if (row * col != 256)
      return 0;
   
   tga_t image;

   texId = image.GenId();

   blockRow = row;
   blockCol = col;

   MakeMap ();

   return image.Load(name, texId, tga_t::uploadYes, GL_ALPHA);
}


// ***********************************************************************
void Texte_t::DrawChar(char c, int x, int y, int size, int shadow)
{
   if (!gradient && !shadow)
      glColor4fv(fgColor);
   else if (!gradient && shadow)
      glColor4fv(bgColor);
   else if (gradient && !shadow)
      glColor4fv(gdColor);

   glBegin (GL_QUADS);
      glTexCoord2f(tPoints[(int) c][0], tPoints[(int) c][1]);
      glVertex2i(x, y);

      glTexCoord2f(tPoints[(int) c][0] + tIncX, tPoints[(int) c][1]);
      glVertex2i(x + size, y);

      if (!shadow)
         glColor4fv(fgColor);
      else glColor4fv(bgColor);

      glTexCoord2f(tPoints[(int) c][0] + tIncX, tPoints[(int) c][1] + tIncY);
      glVertex2i(x + size + italic, y + size);

      glTexCoord2f(tPoints[(int) c][0], tPoints[(int) c][1] + tIncY);
      glVertex2i(x + italic, y + size);
   glEnd ();
}


// ***********************************************************************
void Texte_t::RenderChar (char c, int x, int y, int size)
{
   if (shadow)
   {
      if (!bold)
         DrawChar(c, x + 1,  y + 1, size, 1);
      else DrawChar(c, x + 2,  y + 1, size, 1);
   }

   DrawChar(c, x, y, size, 0);

   if (bold)
      DrawChar(c, x + 1, y, size, 0);
}


// ***********************************************************************
void Texte_t::ScissorNormal(int xpos, int ypos, int tabs, int carrage, int size, int len)
{
   int sy, ex, ey;
   
   ex = len * size * tabs;

   if (carrage)
   {
      sy = ypos - (size * carrage);
      ey = size * (carrage + 1);
   } 
   else
   {
      sy = ypos;
      ey = size;
   }
   
   glScissor(xpos, sy, ex, ey);
}


// ***********************************************************************
int Texte_t::SlashParser(char *buffPtr, int *x, int *y)
{
   int ret = 0;

   *buffPtr++;

   if (!*buffPtr)
      return ret;

   switch (*buffPtr)
   {
      case 'a':
      case 'c':
         *x -= size;
         return SetColorFromToken(buffPtr);
      break;
      case 'i':
         *x -= size;
         return ItalicsMode(buffPtr);
      break;
      case 'b':
         *x -= size;
         return BoldMode(buffPtr);
      break;
      default:
         *buffPtr--;
         RenderChar(*buffPtr, *x, *y, size);
         return ret;
      break;
   }
}


// ***********************************************************************
void Texte_t::WalkString(char *buffPtr, int xpos, int ypos, int *vPort)
{
   int x = xpos;
   int y = ypos;
   int carrage = 0;
   int tabs = 0;
   int len = strlen(buffPtr);
   int xMax;

   xMax = vPort[0] + vPort[2];

   carrage = GetCharHits(buffPtr, '\n');
   tabs = GetCharHits(buffPtr, '\t');

   if (!tabs)
      tabs = 1;
   else tabs *= fontTabSpace;

   if (region)
   {
      ScissorTextRegion();
      x = regionX;
      y = (regionY + regionH) - size;
   } else ScissorNormal(xpos, ypos, tabs, carrage, size, len);

   /* lets draw! */
   for ( ; *buffPtr; *buffPtr++, x += size)
   {
      if (x > xMax)
         break;
   
      if (region)
      {
         if (x + size > (regionX + regionW))
         {
            y -= size;
            x = regionX;
         }
         if (y < regionY)
            break;
      }

      switch (*buffPtr)
      {
         case '\n':
            y -= size;
            x = xpos - size;
            continue; 
         break;
         
         case '\t':
            x += (size * fontTabSpace);
            continue; 
         break;
      
         case '\\':
            buffPtr += SlashParser(buffPtr, &x, &y);
            if (*buffPtr == '\n' || *buffPtr == '\t')
            {
               buffPtr -= 1;
               continue;
            }
         break;
         default:
            RenderChar(*buffPtr, x, y, size);
         break;
      }
   }
}


// ***********************************************************************
void Texte_t::Draw(int xpos, int ypos, char *s, ...)
{
   va_list	msg;
   char buffer[fontMaxLen] = {'\0'};
   int vPort[4];

   va_start (msg, s);
#ifdef _WIN32
   _vsntprintf (buffer, fontMaxLen - 1, s, msg);	
#else /* linux */
   vsnprintf (buffer, fontMaxLen - 1, s, msg);	
#endif
   va_end (msg);

   /* get current viewport */
   glGetIntegerv(GL_VIEWPORT, vPort);
   /* setup various opengl things that we need */
   SetModes(fontGetModes);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glBindTexture(GL_TEXTURE_2D, texId);

   /* draw the string */
   WalkString(buffer, xpos, ypos, vPort);

   glMatrixMode(GL_PROJECTION);
   glPopMatrix();   
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();

   SetModes (fontRestoreModes);
   Reset ();
}


// ***********************************************************************
int Texte_t::SetColorFromToken (char *s)
{
   int clr[4];
   int ret = 1;

   if (*s == 'c')
   {
      s += 1;
      if (sscanf(s, "(%d %d %d)", &clr[0], &clr[1], &clr[2]) != 3)
         return -1;
      Color3f(clr[0] * fontITOF, clr[1] * fontITOF, clr[2] * fontITOF);
   }
   else if (*s == 'a')
   {
      s += 1;
      if (sscanf(s, "(%d %d %d %d)", &clr[0], &clr[1], &clr[2], &clr[3]) != 4)
         return -1;
      Color4f(clr[0] * fontITOF, clr[1] * fontITOF, clr[2] * fontITOF, clr[3] * fontITOF);
   }

   while (*s != ')' && ret ++)
      s += 1;

   return ret + 1;
}


// ***********************************************************************
int Texte_t::ItalicsMode (char *s)
{
   s += 1;

   if (*s == '+')
      italic = fontItalic;
   else if (*s == '-')
      italic = 0;
   else return -1;

   return 2;
}


// ***********************************************************************
int Texte_t::BoldMode (char *s)
{
   s += 1;

   if (*s == '+')
      bold = 1;
   else if (*s == '-')
      bold = 0;
   else return -1;

   return 2;
}


// ***********************************************************************
int Texte_t::GetCharHits(char *s, char f)
{
   for (int hits = 0; *s; *s++)
      if (*s == f)
         hits ++;

	return hits;
}


// ***********************************************************************
void Texte_t::MakeMap(void)
{
#define vCopy(d,x,y) {d[0] = x; d[1] = y;}
   int i = 0;
   float x, y;

   tIncX = (float)pow (blockCol, -1);
   tIncY = (float)pow (blockRow, -1);


   for (y = 1 - tIncY; y >= 0; y -= tIncY)
      for (x = 0; x <= 1 - tIncX; x += tIncX, i ++)
         vCopy(tPoints[i], x, y);
#undef vCopy
}


// ***********************************************************************
void Texte_t::SetModes(int state)
{
   static int matrixMode;
   static int polyMode[2];
   static int lightingOn;
   static int blendOn;
   static int depthOn;
   static int textureOn;
   static int scissorOn;
   static int blendSrc;
   static int blendDst;

   /* grab the modes that we might need to change */
   if (state == fontGetModes)
   {
      glGetIntegerv(GL_POLYGON_MODE, polyMode);

      if (polyMode[0] != GL_FILL)
         glPolygonMode(GL_FRONT, GL_FILL);
      if (polyMode[1] != GL_FILL)
         glPolygonMode(GL_BACK, GL_FILL);

      textureOn = glIsEnabled(GL_TEXTURE_2D);
         
      if (!textureOn)
         glEnable(GL_TEXTURE_2D);

      depthOn = glIsEnabled(GL_DEPTH_TEST);
   
      if (depthOn)
         glDisable(GL_DEPTH_TEST);

      lightingOn = glIsEnabled(GL_LIGHTING);        

      if (lightingOn) 
         glDisable(GL_LIGHTING);

      scissorOn= glIsEnabled(GL_SCISSOR_TEST);        

      if (!scissorOn) 
         glEnable(GL_SCISSOR_TEST);

      glGetIntegerv(GL_MATRIX_MODE, &matrixMode); 

      /* i don't know if this is correct */
      blendOn= glIsEnabled(GL_BLEND);        
      glGetIntegerv(GL_BLEND_SRC, &blendSrc);
      glGetIntegerv(GL_BLEND_DST, &blendDst);
   
      if (!blendOn)
         glEnable(GL_BLEND);

      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   }
   else if (state == fontRestoreModes)
   {
      /* put everything back where it was before */
      if (polyMode[0] != GL_FILL)
         glPolygonMode(GL_FRONT, polyMode[0]);
      if (polyMode[1] != GL_FILL)
         glPolygonMode(GL_BACK, polyMode[1]);

      //if (lightingOn)
      //   glEnable(GL_LIGHTING);

      /* i don't know if this is correct */
      if (!blendOn)
      {
         glDisable(GL_BLEND);
         glBlendFunc(blendSrc, blendDst);
      }
      else glBlendFunc(blendSrc, blendDst);

      if (depthOn)
         glEnable(GL_DEPTH_TEST);

      if (!textureOn)
         glDisable(GL_TEXTURE_2D);

      if (!scissorOn) 
         glDisable(GL_SCISSOR_TEST);

      glMatrixMode(matrixMode);
   }
}


//**************************
// Fin du fichier "Text.h" *
//**************************
