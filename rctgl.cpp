/****************************************************/
/*  Basic Win32 Template                            */
/****************************************************/

/* 
  Cpw link options:

  #define CPW_EXTERN        - link to the static lib
  #define CPWDLL_EXTERN     - link to the release dll's stub
  #define CPWDLLDBG_EXTERN  - link to the debug dll's stub
  #define CPWEXTDLL_EXTERN  - link to the release dll with cpw addons 
*/

#define CPWDLL_EXTERN

#include "basictemplate/cpw.h"
#include "guicon.h"
#include "vr-menu.h"
#include "vr-displaymodes.h"
#include "vr3d.h"

BOOL Initialize (void);

/* handy window characteristics holder */

static CpwWindowInfo windowInfo = { 0,100,100,640,480 }; /* id,posx,posy,w,h */

void keyboardCallback( pCpw cpw, uint_32 windowid, uint_32 asciicode, uint_32 keystate, uint_32 cursorxpos, uint_32 cursorypos );
void systemKeyboardCallback( pCpw cpw, uint_32 windowid, uint_32 asciicode, uint_32 keystate, uint_32 cursorxpos, uint_32 cursorypos );
void mouseClickCallback(pCpw cpw, uint_32 windowid, uint_32 button, uint_32 buttonstate, uint_32 cursorxpos, uint_32 cursorypos);
void mouseDragCallback(pCpw cpw, uint_32 windowid, uint_32 button, int_32 cursorxpos, int_32 cursorypos);
void mouseMoveCallback(pCpw cpw, uint_32 windowid, uint_32 cursorxpos, uint_32 cursorypos);


CpwFontFace menuFont;
menuClass *gameMenu;

displayModes displayMode = INIT;

void printCpwError(void)
{
	int_32 errorcode;

	if(errorcode != cpw_error_noerror)
	{
		printf("Error: ");

		switch(errorcode)
		{
		case cpw_error_unknown:					/* unknown error (cpw_fonts) */
			printf("Unknown error (cpw_fonts)\n");
			break;
		case cpw_error_outofmemory:				/* out of memory */
			printf("out of memory\n");
			break;
		case cpw_error_invalidparameter:		/* invalid parameter */
			printf("invalid parameter\n");
			break;
		case cpw_error_invalidfont:				/* invalid font file */
			printf("invalid font file\n");
			break;
		case cpw_error_initfailed:				/* initialization failed */
			printf("initialization failed\n");
			break;
		case cpw_error_createwindowfailed:		/* failed to create the window */
			printf("create window failed\n");
			break;
		case cpw_error_visualformatunsupported:	/* draw surface format is not supported */
			printf("draw surface format is not supported\n");
			break;
		case cpw_error_visualformatinvalid:		/* failed to set draw surface visual format */
			printf("failed to set draw surface visual format\n");
			break;
		case cpw_error_createcontextfailed:		/* failed to create a gl rendering context */
			printf("failed to create gl rendering context\n");
			break;
		case cpw_error_setcurrentcontextfailed:	/* failed to set gl rendering context current */
			printf("failed to set gl rendering context\n");
			break;
		case cpw_error_failedtosetvideo:		/* video resolution format not supported */
			printf("video resolution format not supported\n");
			break;
		case cpw_error_failedtogetvideo:		/* could not enumerate video modes */
			printf("could not enumerate video modes\n");
			break;
		case cpw_error_novalidcontext:			/* call occured before a valid window exists */
			printf("call occured before valid window existed\n");
			break;
		case cpw_error_invalidmenuid:			/* invalid menu id specified */
			printf("invalid menu id\n");
			break;
		case cpw_error_maxentriesreached:		/* max menu entries reached */
			printf("max menu entries reached\n");
			break;
		case cpw_error_invalidwindowid:			/* invalid window id specified */
			printf("invalid window id specified\n");
			break;
		case cpw_error_unabletoassignmenu:		/* assign menu to window failed */
			printf("unable to assign menu to window\n");
			break;
		case cpw_error_menunotassigned:			/* the menu was not assigned to the window */
			printf("menu was not assigned to window\n");
			break;
		case cpw_error_invalidentryid:			/* invalid menu entry id */
			printf("invalid menu id\n");
			break;
		case cpw_error_invalidjoystickid:		/* invalid joystick id specified */
			printf("invalid joystick id\n");
			break;
		case cpw_error_failedtoload:			/* failed to load the image file */
			printf("failed to load image\n");
			break;
		case cpw_error_invalidformat:			/* invalid image file format */
			printf("invalid image file format\n");
			break;
		default:
			printf("unknown error\n");
			break;

		}
	}
}



/****************************************************/
/*  OpenGL 2D Matrix Setup                          */
/****************************************************/

void set2DMatrix( void ) 
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, windowInfo.width, 0, windowInfo.height );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

/****************************************************/
/*  OpenGL 3D Matrix Setup                          */
/****************************************************/

void set3DMatrix( void ) 
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60, (float)windowInfo.width / (float)windowInfo.height, 1, 5000 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

/****************************************************/
/*  Draw Window One                                 */
/****************************************************/
void displayInit(pCpw cpw);
void displayParkLoad(pCpw cpw);
void displayGame(pCpw cpw);


void drawWindowOne( pCpw cpw ) 
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    set3DMatrix();

	//enum displayModes {NOTHING, MENU, GAME, INIT, LOADPARK};
	
	switch(displayMode)
	{
	case NOTHING:
		break;
	case MENU:
		set2DMatrix();
		gameMenu->drawMenu(cpw);
		break;
	case PAUSED:
	case MAP:
	case GAME:
		displayGame(cpw);
		break;
	case INIT:
		set2DMatrix();
		displayInit(cpw);
		break;
	case LOADPARK:
		set2DMatrix();
		displayParkLoad(cpw);
		break;
	}
	

	/*
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();

		glColor3f(1.0f, 1.0f, 1.0f);

		glRotated(YR,1.0f,0.0f,0.0f);				// Rotate The Triangle On The Y axis
		glRotated(XR,0.0f,1.0f,0.0f);
		glTranslated(0.0f, -100.0f, 0.0f);
		glTranslated(-XV,-YV,-ZV);
		


		mySkyDome->draw();



	glPopMatrix();
	*/
}

/****************************************************/
/*  Window Draw Event callback                      */
/****************************************************/


void draw( pCpw cpw, uint_32 winid )
{
    drawWindowOne( cpw );
    cpwSwapWindowBuffers( cpw, winid );
}

void idleProcessor(pCpw cpw)
{
	draw(cpw, windowInfo.id);
}

/****************************************************/
/*  Window Create / Destroy Event callback          */
/****************************************************/

void window( pCpw cpw, uint_32 winid, bool flag )
{
    /* creation event */

    if ( flag == true ) {

        glShadeModel( GL_SMOOTH );
        glDepthFunc( GL_LEQUAL );
        glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
        glEnable( GL_LINE_SMOOTH );
        glEnable( GL_POLYGON_SMOOTH );
        glClearColor( 0.0, 0.0, 0.0, 1.0 );
        return;
    }

    /* window close event */

    if ( flag == false ) {
        cpwDestroyWindow( cpw, winid );
        return;
    }
}

/****************************************************/
/*  Window Resize Event callback                    */
/****************************************************/

void reshape( pCpw cpw, uint_32 winid, uint_32 width, uint_32 height )
{
    if ( height == 0 ) { height = 1; }
    if ( width == 0 )  { width = 1; }

    windowInfo.width = width;
    windowInfo.height = height;

    
	set3DMatrix();

    glViewport( 0, 0, width, height );
	
	/*
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective (45.0f, (GLfloat)(width)/(GLfloat)(height),			// Calculate The Aspect Ratio Of The Window
					1.0f, 5000.0f);		
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();
	*/
}


void dumpVideoModes( pCpw cpw ) 
    {
        CpwVideoList list;
        int_32 count;

        if ( !cpwListVideoModes( cpw, &list ) ) return;

        count = list.size;

        while ( count >= 0 ) {

        if ( list.list[count]->active == true )

            printf( "- %dx%d, %d bits\n", list.list[count]->width,
                                        list.list[count]->height,
                                        list.list[count]->depth );
        else

            printf( "%dx%d, %d bits\n", list.list[count]->width,
                                        list.list[count]->height,
                                        list.list[count]->depth );
            count--;
        }

        cpwFreeVideoList( cpw, &list );

        return;
    }




/****************************************************/
/*  Main                                            */
/****************************************************/

#ifdef _WINDOWS
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
#elif _CONSOLE
int main(int argc, char* argv[])
#endif
{
	RedirectIOToConsole();

    pCpw cpw = null;

    /****************************************************/
    /*  Init                                            */
    /****************************************************/

    cpwInitContext( &cpw );
	

    /****************************************************/
    /*  Creaing Windows                                 */
    /****************************************************/
    
    windowInfo.id = 
    cpwCreateWindowEx(cpw, "RCTGL Milestone 6", windowInfo.x, windowInfo.y, 
                             windowInfo.width, windowInfo.height );

	cpwFontMode( cpw, CPW_FONTOPT_PIXELMAP_GLFORMAT, GL_RGB );	
	//menuFont = cpwLoadFont( cpw, "HIROSHT.TTF", CPW_FONTLOC_HOST, "", "" ); //cpwLoadFont(cpw, "air_mitalic.ttf", CPW_FONTLOC_RELATIVE, "/", NULL);
	//menuFont = cpwLoadFont( cpw, "jadem___.ttf", CPW_FONTLOC_HOST, "", "" ); //cpwLoadFont(cpw, "air_mitalic.ttf", CPW_FONTLOC_RELATIVE, "/", NULL);
	//menuFont = cpwLoadFont( cpw, "polaroid.ttf", CPW_FONTLOC_HOST, "", "" ); //cpwLoadFont(cpw, "air_mitalic.ttf", CPW_FONTLOC_RELATIVE, "/", NULL);
	menuFont = cpwLoadFont( cpw, "serpntb.ttf", CPW_FONTLOC_HOST, "", "" );
	printCpwError();

	gameMenu = new menuClass(menuFont);

	cpwSetCursor(cpw, CursorNone, windowInfo.id);

	dumpVideoModes(cpw);

	Initialize();


    /****************************************************/
    /*  Event Callbacks                                 */
    /****************************************************/

    cpwCreateCallback(cpw, window);
    cpwDisplayCallback(cpw, draw);
    cpwReshapeCallback(cpw, reshape);
	cpwKeyboardCallback(cpw, keyboardCallback);
	cpwSystemKeyboardCallback(cpw, systemKeyboardCallback);
	cpwMouseClickCallback(cpw, mouseClickCallback);
	cpwMouseDragCallback(cpw, mouseDragCallback);
	cpwMouseMoveCallback(cpw, mouseMoveCallback);
	cpwIdleCallback(cpw, idleProcessor);
	//cpwInitDisplayMode(cpw, CPW_SURFACE_RGBA | CPW_SURFACE_DOUBLE | CPW_SURFACE_DEPTH | CPW_SURFACE_COLOR16 | CPW_SURFACE_DEPTH8 );
	cpwInitDisplayMode(cpw, CPW_SURFACE_RGBA | CPW_SURFACE_SINGLE | CPW_SURFACE_DEPTH | CPW_SURFACE_COLOR8 | CPW_SURFACE_DEPTH8 );

	

    /****************************************************/
    /*  MainLoop                                        */
    /****************************************************/

    cpwMainLoop( cpw );

    /****************************************************/
    /*  Exit and Free                                   */
    /****************************************************/

    cpwFreeContext( &cpw );

    return 0;
}

