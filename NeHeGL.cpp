/***********************************************
*                                              *
*    Jeff Molofee's Revised OpenGL Basecode    *
*  Huge Thanks To Maxwell Sayles & Peter Puck  *
*            http://nehe.gamedev.net           *
*                     2001                     *
*                                              *
***********************************************/

#include <windowsx.h>
#include <windows.h>
#include <stdio.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>
#include "resource.h"														// Header File For The GLu32 Library
#include "guicon.h"
#include "NeHeGL.h"														// Header File For The NeHeGL Basecode
#include "vr3d.h"
#include <dinput.h>


#define WM_TOGGLEFULLSCREEN (WM_USER+5)									// Application Define Message For Toggling



RenderModes DisplayMode;


//char RCTGL_InFile[256];


extern bool UncompressedFile;
extern bool LoadedLandscape;
extern bool LoadedRides;
extern bool LoadedTrees;
extern bool LoadedElements;
extern bool LoadedPaths;
extern bool LoadedWalls;

extern RenderModes DisplayMode;

bool lMousePressed = FALSE, rMousePressed = FALSE;

extern int lastmousex, lastmousey;

HMENU hMenu;


static BOOL g_isProgramLooping;											// Window Creation Loop, For FullScreen/Windowed Toggle																		// Between Fullscreen / Windowed Mode
static BOOL g_createFullScreen;											// If TRUE, Then Create Fullscreen
GL_Window			window;											    // Window Structure


BOOL CALLBACK ScreenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

LPDIRECTINPUT8 lpdi;
LPDIRECTINPUTDEVICE8 m_keyboard;
LPDIRECTINPUTDEVICE8 g_pMouse;
HANDLE g_hMouseEvent;
bool g_bActive;


FMUSIC_MODULE *mod;

void TerminateApplication (GL_Window* window)							// Terminate The Application
{
	PostMessage (window->hWnd, WM_QUIT, 0, 0);							// Send A WM_QUIT Message
	g_isProgramLooping = FALSE;											// Stop Looping Of The Program
}

void ToggleFullscreen (GL_Window* window)								// Toggle Fullscreen/Windowed
{
	PostMessage (window->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);				// Send A WM_TOGGLEFULLSCREEN Message
}

void ReshapeGL (int width, int height)									// Reshape The Window When It's Moved Or Resized
{
	glViewport (0, 0, (GLsizei)(width), (GLsizei)(height));				// Reset The Current Viewport
	glMatrixMode (GL_PROJECTION);										// Select The Projection Matrix
	glLoadIdentity ();													// Reset The Projection Matrix
	gluPerspective (45.0f, (GLfloat)(width)/(GLfloat)(height),			// Calculate The Aspect Ratio Of The Window
					1.0f, 5000.0f);		
	glMatrixMode (GL_MODELVIEW);										// Select The Modelview Matrix
	glLoadIdentity ();													// Reset The Modelview Matrix
}

BOOL ChangeScreenResolution (int width, int height, int bitsPerPixel)	// Change The Screen Resolution
{
	DEVMODE dmScreenSettings;											// Device Mode
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));					// Make Sure Memory Is Cleared
	dmScreenSettings.dmSize				= sizeof (DEVMODE);				// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth		= width;						// Select Screen Width
	dmScreenSettings.dmPelsHeight		= height;						// Select Screen Height
	dmScreenSettings.dmBitsPerPel		= bitsPerPixel;					// Select Bits Per Pixel
	dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		return FALSE;													// Display Change Failed, Return False
	}
	return TRUE;														// Display Change Was Successful, Return True
}

BOOL CreateWindowGL (GL_Window* window)									// This Code Creates Our OpenGL Window
{
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;							// Define Our Window Style
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;						// Define The Window's Extended Style

	PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
	{
		sizeof (PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																// Version Number
		PFD_DRAW_TO_WINDOW |											// Format Must Support Window
		PFD_SUPPORT_OPENGL |											// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,												// Must Support Double Buffering
		PFD_TYPE_RGBA,													// Request An RGBA Format
		window->init.bitsPerPixel,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		0,																// No Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		16,																// 16Bit Z-Buffer (Depth Buffer)  
		0,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	RECT windowRect = {0, 0, window->init.width, window->init.height};	// Define Our Window Coordinates

	GLuint PixelFormat;													// Will Hold The Selected Pixel Format

	if (window->init.isFullScreen == TRUE)								// Fullscreen Requested, Try Changing Video Modes
	{
		if (ChangeScreenResolution (window->init.width, window->init.height, window->init.bitsPerPixel) == FALSE)
		{
			// Fullscreen Mode Failed.  Run In Windowed Mode Instead
			MessageBox (HWND_DESKTOP, "Mode Switch Failed.\nRunning In Windowed Mode.", "Error", MB_OK | MB_ICONEXCLAMATION);
			window->init.isFullScreen = FALSE;							// Set isFullscreen To False (Windowed Mode)
		}
		else															// Otherwise (If Fullscreen Mode Was Successful)
		{
			//ShowCursor (FALSE);											// Turn Off The Cursor
			windowStyle = WS_POPUP;										// Set The WindowStyle To WS_POPUP (Popup Window)
			//windowExtendedStyle |= WS_EX_TOPMOST;						// Set The Extended Window Style To WS_EX_TOPMOST
		}																// (Top Window Covering Everything Else)
	}
	else																// If Fullscreen Was Not Selected
	{
		// Adjust Window, Account For Window Borders
		AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);
	}

	// Create The OpenGL Window
	window->hWnd = CreateWindowEx (windowExtendedStyle,					// Extended Style
								   window->init.application->className,	// Class Name
								   window->init.title,					// Window Title
								   windowStyle,							// Window Style
								   0, 0,								// Window X,Y Position
								   windowRect.right - windowRect.left,	// Window Width
								   windowRect.bottom - windowRect.top,	// Window Height
								   HWND_DESKTOP,						// Desktop Is Window's Parent
								   0,									// No Menu
								   window->init.application->hInstance, // Pass The Window Instance
								   window);

	if (window->hWnd == 0)												// Was Window Creation A Success?
	{
		return FALSE;													// If Not Return False
	}

	window->hDC = GetDC (window->hWnd);									// Grab A Device Context For This Window
	if (window->hDC == 0)												// Did We Get A Device Context?
	{
		// Failed
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	PixelFormat = ChoosePixelFormat (window->hDC, &pfd);				// Find A Compatible Pixel Format
	if (PixelFormat == 0)												// Did We Find A Compatible Format?
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	if (SetPixelFormat (window->hDC, PixelFormat, &pfd) == FALSE)		// Try To Set The Pixel Format
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	window->hRC = wglCreateContext (window->hDC);						// Try To Get A Rendering Context
	if (window->hRC == 0)												// Did We Get A Rendering Context?
	{
		// Failed
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent (window->hDC, window->hRC) == FALSE)
	{
		// Failed
		wglDeleteContext (window->hRC);									// Delete The Rendering Context
		window->hRC = 0;												// Zero The Rendering Context
		ReleaseDC (window->hWnd, window->hDC);							// Release Our Device Context
		window->hDC = 0;												// Zero The Device Context
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
		return FALSE;													// Return False
	}

	ShowWindow (window->hWnd, SW_NORMAL);								// Make The Window Visible
	window->isVisible = TRUE;											// Set isVisible To True

	ReshapeGL (window->init.width, window->init.height);				// Reshape Our GL Window

	ZeroMemory (window->keys, sizeof (Keys));							// Clear All Keys

	window->lastTickCount = GetTickCount ();							// Get Tick Count

	return TRUE;														// Window Creating Was A Success
																		// Initialization Will Be Done In WM_CREATE
}

BOOL DestroyWindowGL (GL_Window* window)								// Destroy The OpenGL Window & Release Resources
{
	if (window->hWnd != 0)												// Does The Window Have A Handle?
	{	
		if (window->hDC != 0)											// Does The Window Have A Device Context?
		{
			wglMakeCurrent (window->hDC, 0);							// Set The Current Active Rendering Context To Zero
			if (window->hRC != 0)										// Does The Window Have A Rendering Context?
			{
				wglDeleteContext (window->hRC);							// Release The Rendering Context
				window->hRC = 0;										// Zero The Rendering Context

			}
			ReleaseDC (window->hWnd, window->hDC);						// Release The Device Context
			window->hDC = 0;											// Zero The Device Context
		}
		DestroyWindow (window->hWnd);									// Destroy The Window
		window->hWnd = 0;												// Zero The Window Handle
	}

	if (window->init.isFullScreen)										// Is Window In Fullscreen Mode
	{
		ChangeDisplaySettings (NULL,0);									// Switch Back To Desktop Resolution
		ShowCursor (TRUE);												// Show The Cursor
	}	
	return TRUE;														// Return True
}

/*
void CenterWindow(HWND hwnd)
{
	RECT rectWnd;
	RECT rectParent;
	HWND hwndParent;
	int nX, nY;
	int nParentWidth, nParentHeight, nWndWidth, nWndHeight;

	// Get a handle for the parent window
	hwndParent = GetParent(hwnd);
	if(hwndParent == NULL)
		hwndParent = GetDesktopWindow();

	// Get the bounding rectangles for the windows
	GetWindowRect(hwndParent, &rectParent);
	GetWindowRect(hwnd, &rectWnd);

	// Compute the new location of the window
	nParentWidth = rectParent.right-rectParent.left;
	nParentHeight = rectParent.bottom-rectParent.top;
	nWndWidth = rectWnd.right-rectWnd.left;
	nWndHeight = rectWnd.bottom-rectWnd.top;
	nX = max(0, rectParent.left + 40);
	nY = max(0, rectParent.top + 40);

	// Move the window to its new location
	SetWindowPos(
		hwnd,
		HWND_TOP,
		nX, nY,
		0, 0,
		SWP_NOSIZE);
}

UINT APIENTRY GetFileNameProc(
	HWND hwndDlg,
	UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
	UINT nRetVal;

	nRetVal = FALSE;

	switch(uMsg)
	{
		case WM_INITDIALOG:
		// Center the window
		CenterWindow(GetParent(hwndDlg));
		nRetVal = TRUE;
		break;
	} return nRetVal;
}



void processFileOpenRequest(void)
{
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	// open the registry to get the location of RCT save files
	HKEY hKey;
	char szStoragePath[256];
	char *tmp;
	DWORD dwBufLen;

	RegOpenKeyEx( HKEY_LOCAL_MACHINE,
	   "SOFTWARE\\Fish Technology Group\\RollerCoaster Tycoon Setup",
	   0, KEY_QUERY_VALUE, &hKey );
	RegQueryValueEx( hKey, "Path", NULL, NULL,
	   (LPBYTE) szStoragePath, &dwBufLen);
	RegCloseKey( hKey );

	tmp = strcat(&szStoragePath[0], "\\Saved Games");

	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = NULL; //hWnd;
	ofn.lpstrFilter = "RCT Saved Games (*.sv4)\0*.sv4\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFile = &RCTGL_InFile[0];
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ENABLEHOOK;
	ofn.lpstrDefExt = "txt";
	ofn.lpstrInitialDir = tmp;
	ofn.lpfnHook = GetFileNameProc;

	ShowCursor (TRUE);

	if(GetOpenFileName(&ofn))
	{
		//initialize all the flags to zero
		UncompressedFile = FALSE;
		LoadedLandscape = FALSE;
		LoadedRides = FALSE;
		LoadedTrees	= FALSE;
		LoadedPaths = FALSE;
		LoadedElements = FALSE;
		LoadedWalls = FALSE;

		//set the mode to SV4 Load
		DisplayMode = SV4Progress;
	}

	ShowCursor (FALSE);

}
*/


// Process Window Message Callbacks
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Get The Window Context
	GL_Window* window = (GL_Window*)(GetWindowLong (hWnd, GWL_USERDATA));

//	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	int movewindow = 0;

	float AngleDelta = 2.0f;

	GLfloat fogColor[4]= {0.65f, 0.65f, 0.60f, 1.0f};

	int doh;
	char tempstr[256];
	char *tmp;

	tmp = (char *)malloc(256);


	switch (uMsg)														// Evaluate Window Message
	{
		case WM_RBUTTONDOWN:
			rMousePressed = TRUE;
			break;

		case WM_RBUTTONUP:
			rMousePressed = FALSE;
			break;

		case WM_LBUTTONDOWN:
			lMousePressed = TRUE;
			break;

		case WM_LBUTTONUP:
			lMousePressed  = FALSE;
			break;

		case WM_MOUSEMOVE:

			if (rMousePressed == FALSE)
			{
				/*
				if(GET_X_LPARAM(lParam)  > (lastmousex + movewindow))
					XR += AngleDelta;
				else if(GET_X_LPARAM(lParam)  < (lastmousex - movewindow))
					XR -= AngleDelta;

				if(GET_Y_LPARAM(lParam)  > (lastmousey + movewindow))
					YR += AngleDelta;
				else if(GET_Y_LPARAM(lParam)  < (lastmousey - movewindow))
					YR -= AngleDelta;

				lastmousex = GET_X_LPARAM(lParam);
				lastmousey = GET_Y_LPARAM(lParam);

				if(XR < 0.0f)
					XR += 360.0f;
				else if(XR > 360.0f)
					XR -= 360.0f;

				if(YR < 0.0f)
					YR += 360.0f;
				else if(XR > 360.0f)
					YR -= 360.0f;
						break;
						*/
			}

		case WM_SYSCOMMAND:												// Intercept System Commands
		{
			switch (wParam)												// Check System Calls
			{
				case SC_SCREENSAVE:										// Screensaver Trying To Start?
				case SC_MONITORPOWER:									// Monitor Trying To Enter Powersave?
				return 0;												// Prevent From Happening
			}
			break;														// Exit
		}
		return 0;														// Return

		case WM_CREATE:													// Window Creation
		{
		
			//make the window
			CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);			// Store Window Structure Pointer
			window = (GL_Window*)(creation->lpCreateParams);
			SetWindowLong (hWnd, GWL_USERDATA, (LONG)(window));

			//make the menu
			HMENU hSubMenu, hDetailPopupMenu, hFogPopupMenu, hEnvPopupMenu;
//			HICON hIcon, hIconSm;

			hMenu = CreateMenu();

			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, MENU_FILE_OPEN, "&Open Park");
			AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, MENU_LOAD_EXTENDED, "&Load Extended Info");
			AppendMenu(hSubMenu, MF_STRING, MENU_FILE_EXIT, "&Exit");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING | MF_GRAYED, MENU_CONFIG_RESOLUTION, "&Resolution");


			hDetailPopupMenu = CreatePopupMenu();
			hFogPopupMenu = CreatePopupMenu();
			hEnvPopupMenu = CreatePopupMenu();

			AppendMenu(hDetailPopupMenu, MF_STRING, MENU_DETAIL_LOW, "&Low");
			AppendMenu(hDetailPopupMenu, MF_STRING, MENU_DETAIL_MEDIUM, "&Medium");
			AppendMenu(hDetailPopupMenu, MF_STRING | MF_CHECKED, MENU_DETAIL_HIGH, "&High");
			AppendMenu(hDetailPopupMenu, MF_STRING, MENU_DETAIL_ALL, "&All");

			AppendMenu(hSubMenu, MF_STRING | MF_POPUP, (UINT)hDetailPopupMenu, "&Detail Level");

			AppendMenu(hFogPopupMenu, MF_STRING, MENU_FOG_SMOG, "&Heavy Smog");
			AppendMenu(hFogPopupMenu, MF_STRING | MF_CHECKED, MENU_FOG_HAZE, "&Haze");
			AppendMenu(hFogPopupMenu, MF_STRING, MENU_FOG_NONE, "&Off");
			
			AppendMenu(hSubMenu, MF_STRING | MF_POPUP, (UINT)hFogPopupMenu, "&Fog");

			AppendMenu(hEnvPopupMenu, MF_STRING | MF_CHECKED, MENU_ENV_ORIGINAL, "&Original");
			AppendMenu(hEnvPopupMenu, MF_STRING, MENU_ENV_SUNNY, "&Perfect Day");
			AppendMenu(hEnvPopupMenu, MF_STRING, MENU_ENV_CLOUDY, "&Evening Clouds");
			AppendMenu(hEnvPopupMenu, MF_STRING, MENU_ENV_STORMY, "A S&torm Approaches");
			AppendMenu(hEnvPopupMenu, MF_STRING, MENU_ENV_OCEAN, "Ocean &Waters");
			
			AppendMenu(hSubMenu, MF_STRING | MF_POPUP, (UINT)hEnvPopupMenu, "&Atmospheres");

			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Setup");

			SetMenu(hWnd, hMenu);
		}
		return 0;// Return

		

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			/*
			case MENU_FILE_OPEN:

				processFileOpenRequest();

				break;
			

			case MENU_LOAD_EXTENDED:
				DWORD temp;

				char EXELoc[256];

				// get current directory so we can restore later
				temp = GetModuleFileName(NULL, &EXELoc[0], 256);

				printf("program location: %s\n", &EXELoc[0]);

				int len;
				
				len = strlen(&EXELoc[0]);

				EXELoc[len - 10] = '\0';

				OPENFILENAME ofn;

				ZeroMemory(&ofn, sizeof(ofn));

				// open the registry to get the location of RCT save files
				HKEY hKey;
				char szStoragePath[256];
				char *tmp;
				DWORD dwBufLen;

				tmp = strcat(&EXELoc[0], "\\Extended");

				ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
				ofn.hwndOwner = NULL; //hWnd;
				ofn.lpstrFilter = "RCTGL Extended Information (*.ext)\0*.ext\0All Files (*.*)\0*.*\0";
				ofn.lpstrFile = &szFileName[0];
				ofn.nMaxFile = MAX_PATH;
				//ofn.lpstrFile = &RCTGL_InFile[0];
				ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ENABLEHOOK;
				ofn.lpstrDefExt = "txt";
				ofn.lpstrInitialDir = tmp;
				ofn.lpfnHook = GetFileNameProc;

				ShowCursor (TRUE);

				if(GetOpenFileName(&ofn))
				{					
					loadExtendedInfo(&szFileName[0]);
				}

				ShowCursor (FALSE);


				break;
				*/

			case MENU_FILE_EXIT:
				TerminateApplication(window);
				break;

			case MENU_CONFIG_RESOLUTION:
				//DialogBox(hInstance , MAKEINTRESOURCE(IDD_SCREENDLG), 
                //     HWND_DESKTOP, (DLGPROC)ScreenDlgProc);
				DialogBox(GetModuleHandle(NULL) , MAKEINTRESOURCE(IDD_SCREENDLG), 
                     HWND_DESKTOP, (DLGPROC)ScreenDlgProc);
				break;

			case MENU_DETAIL_LOW:
				//uncheck all menu items
				CheckMenuItem(hMenu, MENU_DETAIL_LOW, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_MEDIUM, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_HIGH, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_ALL, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_DETAIL_LOW, MF_CHECKED);

				detailLevel = M_LOW_DETAIL;
				rMousePressed = FALSE;
				break;

			case MENU_DETAIL_MEDIUM:
				//uncheck all menu items
				CheckMenuItem(hMenu, MENU_DETAIL_LOW, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_MEDIUM, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_HIGH, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_ALL, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_DETAIL_MEDIUM, MF_CHECKED);

				detailLevel = M_MEDIUM_DETAIL;
				rMousePressed = FALSE;
				break;

			
			case MENU_DETAIL_HIGH:
				//uncheck all menu items
				CheckMenuItem(hMenu, MENU_DETAIL_LOW, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_MEDIUM, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_HIGH, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_ALL, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_DETAIL_HIGH, MF_CHECKED);

				detailLevel = M_HIGH_DETAIL;
				rMousePressed = FALSE;
				break;

			case MENU_DETAIL_ALL:
				//uncheck all menu items
				CheckMenuItem(hMenu, MENU_DETAIL_LOW, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_MEDIUM, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_HIGH, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_DETAIL_ALL, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_DETAIL_ALL, MF_CHECKED);

				detailLevel = -1;
				rMousePressed = FALSE;
				break;

			case MENU_FOG_SMOG:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_FOG_SMOG, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_FOG_HAZE, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_FOG_NONE, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_FOG_SMOG, MF_CHECKED);

				fogLevel = M_FOG_SMOG;
				rMousePressed = FALSE;

				glFogi(GL_FOG_MODE, GL_LINEAR);		// Fog Mode
				glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
				glFogf(GL_FOG_DENSITY, 0.65f);				// How Dense Will The Fog Be
				glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
				glFogf(GL_FOG_START, 15.0f);				// Fog Start Depth
				glFogf(GL_FOG_END, 200.0f);				// Fog End Depth

				break;

			case MENU_FOG_HAZE:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_FOG_SMOG, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_FOG_HAZE, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_FOG_NONE, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_FOG_HAZE, MF_CHECKED);

				fogLevel = M_FOG_HAZE;
				rMousePressed = FALSE;

				glFogi(GL_FOG_MODE, GL_LINEAR);		// Fog Mode
				glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
				glFogf(GL_FOG_DENSITY, 0.25f);				// How Dense Will The Fog Be
				glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
				glFogf(GL_FOG_START, 30.0f);				// Fog Start Depth
				glFogf(GL_FOG_END, 300.0f);				// Fog End Depth

				break;

			case MENU_FOG_NONE:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_FOG_SMOG, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_FOG_HAZE, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_FOG_NONE, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_FOG_NONE, MF_CHECKED);

				fogLevel = M_FOG_NONE;
				rMousePressed = FALSE;

				glDisable(GL_FOG);
				break;

			case MENU_ENV_ORIGINAL:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_ENV_ORIGINAL, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_SUNNY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_CLOUDY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_STORMY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_OCEAN, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_ENV_ORIGINAL, MF_CHECKED);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\original\\front.tga"), TEXTURE_SKYFRONT);
				printf("Loading sky-top texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\original\\right.tga"), TEXTURE_SKYRIGHT);
				printf("Loading sky-right texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\original\\back.tga"), TEXTURE_SKYBACK);
				printf("Loading sky-bottom texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\original\\left.tga"), TEXTURE_SKYLEFT);
				printf("Loading sky-left texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\original\\up.tga"), TEXTURE_SKYUP);
				printf("Loading sky-up texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\original\\down.tga"), TEXTURE_SKYDOWN);
				printf("Loading sky-down texture (%d)\n", doh);

				initAtmosphere(MENU_ENV_ORIGINAL);

				rMousePressed = FALSE;
				break;
				
			case MENU_ENV_CLOUDY:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_ENV_ORIGINAL, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_SUNNY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_CLOUDY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_STORMY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_OCEAN, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_ENV_CLOUDY, MF_CHECKED);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\cloudy1\\front.tga"), TEXTURE_SKYFRONT);
				printf("Loading sky-top texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\cloudy1\\right.tga"), TEXTURE_SKYRIGHT);
				printf("Loading sky-right texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\cloudy1\\back.tga"), TEXTURE_SKYBACK);
				printf("Loading sky-bottom texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\cloudy1\\left.tga"), TEXTURE_SKYLEFT);
				printf("Loading sky-left texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\cloudy1\\up.tga"), TEXTURE_SKYUP);
				printf("Loading sky-up texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\cloudy1\\down.tga"), TEXTURE_SKYDOWN);
				printf("Loading sky-down texture (%d)\n", doh);

				initAtmosphere(MENU_ENV_CLOUDY);


				rMousePressed = FALSE;
				break;

			case MENU_ENV_SUNNY:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_ENV_ORIGINAL, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_SUNNY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_CLOUDY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_STORMY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_OCEAN, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_ENV_SUNNY, MF_CHECKED);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\sunny1\\front.tga"), TEXTURE_SKYFRONT);
				printf("Loading sky-top texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\sunny1\\right.tga"), TEXTURE_SKYRIGHT);
				printf("Loading sky-right texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\sunny1\\back.tga"), TEXTURE_SKYBACK);
				printf("Loading sky-bottom texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\sunny1\\left.tga"), TEXTURE_SKYLEFT);
				printf("Loading sky-left texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\sunny1\\up.tga"), TEXTURE_SKYUP);
				printf("Loading sky-up texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\sunny1\\down.tga"), TEXTURE_SKYDOWN);
				printf("Loading sky-down texture (%d)\n", doh);

				initAtmosphere(MENU_ENV_SUNNY);

				rMousePressed = FALSE;
				break;				

			case MENU_ENV_STORMY:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_ENV_ORIGINAL, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_SUNNY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_CLOUDY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_STORMY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_OCEAN, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_ENV_STORMY, MF_CHECKED);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\stormy1\\front.tga"), TEXTURE_SKYFRONT);
				printf("Loading sky-top texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\stormy1\\right.tga"), TEXTURE_SKYRIGHT);
				printf("Loading sky-right texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\stormy1\\back.tga"), TEXTURE_SKYBACK);
				printf("Loading sky-bottom texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\stormy1\\left.tga"), TEXTURE_SKYLEFT);
				printf("Loading sky-left texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\stormy1\\up.tga"), TEXTURE_SKYUP);
				printf("Loading sky-up texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\stormy1\\down.tga"), TEXTURE_SKYDOWN);
				printf("Loading sky-down texture (%d)\n", doh);

				initAtmosphere(MENU_ENV_STORMY);

				rMousePressed = FALSE;
				break;				
			case MENU_ENV_OCEAN:
				//uncheck all fog items
				CheckMenuItem(hMenu, MENU_ENV_ORIGINAL, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_SUNNY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_CLOUDY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_STORMY, MF_UNCHECKED);
				CheckMenuItem(hMenu, MENU_ENV_OCEAN, MF_UNCHECKED);

				//check the one we want
				CheckMenuItem(hMenu, MENU_ENV_OCEAN, MF_CHECKED);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\ocean1\\front.tga"), TEXTURE_SKYFRONT);
				printf("Loading sky-top texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\ocean1\\right.tga"), TEXTURE_SKYRIGHT);
				printf("Loading sky-right texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\ocean1\\back.tga"), TEXTURE_SKYBACK);
				printf("Loading sky-bottom texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\ocean1\\left.tga"), TEXTURE_SKYLEFT);
				printf("Loading sky-left texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\ocean1\\up.tga"), TEXTURE_SKYUP);
				printf("Loading sky-up texture (%d)\n", doh);

				tmp = strcpy(&tempstr[0], RCTGL_Location);
				doh=LoadTGAFromFile(strcat(tempstr, "\\skies\\ocean1\\down.tga"), TEXTURE_SKYDOWN);
				printf("Loading sky-down texture (%d)\n", doh);

				initAtmosphere(MENU_ENV_OCEAN);

				rMousePressed = FALSE;
				break;				



				
				
			}
		}
		return 0;



		case WM_CLOSE:					// Closing The Window
			
			TerminateApplication(window);								// Terminate The Application
		return 0;														// Return

		case WM_SIZE:													// Size Action Has Taken Place
			switch (wParam)												// Evaluate Size Action
			{
				case SIZE_MINIMIZED:									// Was Window Minimized?
					window->isVisible = FALSE;							// Set isVisible To False
				return 0;												// Return

				case SIZE_MAXIMIZED:									// Was Window Maximized?
					window->isVisible = TRUE;							// Set isVisible To True
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return

				case SIZE_RESTORED:										// Was Window Restored?
					window->isVisible = TRUE;							// Set isVisible To True
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));		// Reshape Window - LoWord=Width, HiWord=Height
				return 0;												// Return
			}
		break;															// Break

		case WM_KEYDOWN:												// Update Keyboard Buffers For Keys Pressed
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				//printf("hit key %d\n", wParam);
				window->keys->keyDown [wParam] = TRUE;					// Set The Selected Key (wParam) To True
				return 0;												// Return
			}
		break;															// Break

		case WM_KEYUP:													// Update Keyboard Buffers For Keys Released
			if ((wParam >= 0) && (wParam <= 255))						// Is Key (wParam) In A Valid Range?
			{
				window->keys->keyDown [wParam] = FALSE;					// Set The Selected Key (wParam) To False
				return 0;												// Return
			}
		break;															// Break

		case WM_TOGGLEFULLSCREEN:										// Toggle FullScreen Mode On/Off
			g_createFullScreen = (g_createFullScreen == TRUE) ? FALSE : TRUE;
			PostMessage (hWnd, WM_QUIT, 0, 0);
		break;															// Break
	}

	return DefWindowProc (hWnd, uMsg, wParam, lParam);					// Pass Unhandled Messages To DefWindowProc
}

BOOL RegisterWindowClass (Application* application)						// Register A Window Class For This Application.
{																		// TRUE If Successful
	// Register A Window Class
	WNDCLASSEX windowClass;												// Window Class
	ZeroMemory (&windowClass, sizeof (WNDCLASSEX));						// Make Sure Memory Is Cleared
	windowClass.cbSize			= sizeof (WNDCLASSEX);					// Size Of The windowClass Structure
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
	windowClass.lpfnWndProc		= (WNDPROC)(WindowProc);				// WindowProc Handles Messages
	windowClass.hInstance		= application->hInstance;				// Set The Instance
	windowClass.hbrBackground	= (HBRUSH)(COLOR_APPWORKSPACE);			// Class Background Brush Color
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	windowClass.lpszClassName	= application->className;				// Sets The Applications Classname
	//windowClass.lpszMenuName	= "MAINMENU2";
	if (RegisterClassEx (&windowClass) == 0)							// Did Registering The Class Fail?
	{
		// NOTE: Failure, Should Never Happen
		MessageBox (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;													// Return False (Failure)
	}
	return TRUE;														// Return True (Success)
}

BOOL CALLBACK ScreenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    switch (message) 
    { 
        case WM_COMMAND: 
            switch (LOWORD(wParam)) 
            {

			  case IDOK: 
//				  bool dumb;

                    if(!IsDlgButtonChecked(hwndDlg, IDC_FULLSCREEN))
		              window.init.isFullScreen = FALSE;								// If Not, Run In Windowed Mode 
					
					if(IsDlgButtonChecked(hwndDlg, IDC_16BPP))
					  window.init.bitsPerPixel	= 16;									// Bits Per Pixel 				
					else
					  window.init.bitsPerPixel	= 32;									// Bits Per Pixel
					
					if(IsDlgButtonChecked(hwndDlg, IDC_640_480))
					{
                     window.init.width			= 640;									// Window Width
	                 window.init.height			= 480;									// Window Height
					}
					else
					{
					 if(IsDlgButtonChecked(hwndDlg, IDC_800_600))
					 {
	                  window.init.width			= 800;									// Window Width
	                  window.init.height		= 600;									// Window Height
					 }
					 else
					 {
	                  window.init.width			= 1024;									// Window Width
	                  window.init.height		= 768;									// Window Height
					 }
					}
					EndDialog(hwndDlg, wParam);
					
					DestroyWindow(window.hWnd);

					//DestroyWindowGL(&window);
					
					CreateWindowGL(&window);

                    return TRUE; 
            }
	     switch (HIWORD(wParam))
		 {
		  case BN_CLICKED:
               CheckDlgButton(hwndDlg, lParam, BST_CHECKED);
   		       break;

		 } break;

		case WM_INITDIALOG:
            {
			 CheckDlgButton(hwndDlg,IDC_FULLSCREEN, BST_CHECKED);
			 CheckRadioButton(hwndDlg,IDC_640_480, IDC_1024_768, IDC_640_480);
			 CheckRadioButton(hwndDlg,IDC_16BPP, IDC_32BPP, IDC_16BPP);
			}
    } 
    return FALSE; 
} 


void InitDInput(void)
{
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&lpdi, NULL)))
	{
		printf("error calling DirectInput8Create()\naborting\n");
		exit(0);
	}
	
	if (FAILED(lpdi->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL)))
	{
		printf("error calling CreateDevice(keyboard)\naborting\n");
		exit(0);
	}
	
	if (FAILED(m_keyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		printf("error calling SetDataFormat(keyboard)\naborting\n");
		exit(0);
	}	
	
	if (FAILED(m_keyboard->SetCooperativeLevel(window.hWnd, DISCL_BACKGROUND |
		DISCL_NONEXCLUSIVE)))
	{
		printf("error calling SetCooperativeLevel(keyboard)\naborting\n");
		exit(0);
	}	
	
	if (FAILED(m_keyboard->Acquire()))
	{
		printf("error calling Acquire(keyboard)\naborting\n");
		exit(0);
	}

	// === initialize the mouse
	if(FAILED(lpdi->CreateDevice(GUID_SysMouse, &g_pMouse, NULL)))
	{
		printf("error calling CreateDevice(mouse)()\naborting\n");
		exit(0);
	}

	if(FAILED(g_pMouse->SetDataFormat(&c_dfDIMouse)))
	{
		printf("error calling CreateDevice(mouse)()\naborting\n");
		exit(0);
	}

	if(FAILED(g_pMouse->SetCooperativeLevel(window.hWnd,
               DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		printf("error calling SetCooperativeLevel(mouse)()\naborting\n");
		exit(0);
	}

	/*
	g_hMouseEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
 
	if (g_hMouseEvent == NULL) {
		printf("error calling CreateEvent(mouse)()\naborting\n");
		exit(0);

	}
 
	if(FAILED(g_pMouse->SetEventNotification(g_hMouseEvent)))
	{
		printf("error calling SetEventNotification(mouse)()\naborting\n");
		exit(0);

	}
	

	#define SAMPLE_BUFFER_SIZE  16
 
	DIPROPDWORD dipdw;
		// the header
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		// the data
		dipdw.dwData            = SAMPLE_BUFFER_SIZE;

	if(FAILED(g_pMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
	{
		printf("error calling SetProperty(mouse)()\naborting\n");
		exit(0);

	}
	*/

	if(FAILED(g_pMouse->Acquire()))
	{
		printf("error calling Acquire(mouse)()\naborting\n");
		exit(0);
	}



	printf("initialized DirectInput()\n");
}

void InitFMod(void)
{
	if (FSOUND_GetVersion() < FMOD_VERSION)
	{
		printf("Error : You are using the wrong DLL version!  You should be using FMOD %.02f\n", FMOD_VERSION);
		exit(1);
	}

	/*
	    INITIALIZE
	*/

	if (!FSOUND_Init(44100, 32, FSOUND_INIT_GLOBALFOCUS))
	{
		printf("FMod Error: %s\n", FMOD_ErrorString(FSOUND_GetError()));
		//exit(1);
	}

	FSOUND_CD_SetPlayMode(0, FSOUND_CD_PLAYLOOPED);

	printf("initialized fMOD\n");
}


// Program Entry (WinMain)
/*
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application			application;									// Application Structure
	Keys				keys;											// Key Structure
	BOOL				isMessagePumpActive;							// Message Pump Active?
	MSG					msg;											// Window Message Structure
	DWORD				tickCount;										// Used For The Tick Counter

	// Fill Out Application Data
	application.className = "OpenGL";									// Application Class Name
	application.hInstance = hInstance;									// Application Instance

	// Fill Out Window
	//ZeroMemory (&window, sizeof (GL_Window));							// Make Sure Memory Is Zeroed
	window.keys					= &keys;								// Window Key Structure
	window.init.application		= &application;							// Window Application
	window.init.title			= "RCTGL MS 5";							// Window Title
	window.init.width			= 640;									// Window Width
	window.init.height			= 480;									// Window Height
	window.init.bitsPerPixel	= 16;									// Bits Per Pixel
	window.init.isFullScreen	= FALSE;									// Fullscreen? (Set To TRUE)

	//ZeroMemory (&keys, sizeof (Keys));	// Zero keys Structure

	//#ifdef _DEBUG

	RedirectIOToConsole(); 

	//#endif



    
	// Register A Class For Our Window To Use
	if (RegisterWindowClass (&application) == FALSE)					// Did Registering A Class Fail?
	{
		// Failure
		MessageBox (HWND_DESKTOP, "Error Registering Window Class!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;														// Terminate Application
	}

	g_isProgramLooping = TRUE;											// Program Looping Is Set To TRUE
	g_createFullScreen = window.init.isFullScreen;						// g_createFullScreen Is Set To User Default
	while (g_isProgramLooping)											// Loop Until WM_QUIT Is Received
	{
		// Create A Window
		window.init.isFullScreen = g_createFullScreen;					// Set Init Param Of Window Creation To Fullscreen?
		if (CreateWindowGL (&window) == TRUE)							// Was Window Creation Successful?
		{
			// At This Point We Should Have A Window That Is Setup To Render OpenGL
			if (Initialize (&window, &keys) == FALSE)					// Call User Intialization
			{
				// Failure
				TerminateApplication (&window);							// Close Window, This Will Handle The Shutdown
			}
			else														// Otherwise (Start The Message Pump)
			{	// Initialize was a success
				isMessagePumpActive = TRUE;								// Set isMessagePumpActive To TRUE
				while (isMessagePumpActive == TRUE)						// While The Message Pump Is Active
				{
					// Success Creating Window.  Check For Window Messages
					if (PeekMessage (&msg, window.hWnd, 0, 0, PM_REMOVE) != 0)
					{
						// Check For WM_QUIT Message
						if (msg.message != WM_QUIT)						// Is The Message A WM_QUIT Message?
						{
							DispatchMessage (&msg);						// If Not, Dispatch The Message
						}
						else											// Otherwise (If Message Is WM_QUIT)
						{
							isMessagePumpActive = FALSE;				// Terminate The Message Pump
						}
					}
					else												// If There Are No Messages
					{
						if (window.isVisible == FALSE)					// If Window Is Not Visible
						{
							WaitMessage ();								// Application Is Minimized Wait For A Message
						}
						else											// If Window Is Visible
						{
							// Process Application Loop
							tickCount = GetTickCount ();				// Get The Tick Count
							Update (tickCount - window.lastTickCount);	// Update The Counter
							window.lastTickCount = tickCount;			// Set Last Count To Current Count
							Draw ();									// Draw Our Scene

							SwapBuffers (window.hDC);					// Swap Buffers (Double Buffering)
						}
					}
				}														// Loop While isMessagePumpActive == TRUE
			}															// If (Initialize (...

			// Application Is Finished
			Deinitialize ();											// User Defined DeInitialization

			FSOUND_Close();

			DestroyWindowGL (&window);									// Destroy The Active Window
		}
		else															// If Window Creation Failed
		{
			// Error Creating Window
			MessageBox (HWND_DESKTOP, "Error Creating OpenGL Window", "Error", MB_OK | MB_ICONEXCLAMATION);
			g_isProgramLooping = FALSE;									// Terminate The Loop
		}
	}																	// While (isProgramLooping)

	UnregisterClass (application.className, application.hInstance);		// UnRegister Window Class
	return 0;
}																		// End Of WinMain()
*/