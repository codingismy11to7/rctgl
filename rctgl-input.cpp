#include "rctgl-input.h"

displayModes oldState;

bool escapeDown = false;
bool DownArrowDown = false;
bool UpArrowDown = false;
bool ReturnDown = false;
bool F1Down = false;
bool PgDwnDown = false;
bool PgUpDown = false;
bool plusKeyDown = false;
bool minusKeyDown = false;
bool modeKeyDown = false;

bool menusShown = false;
bool isFullScreen = false;
uint_32 menuID = -1;

void showMenu(pCpw cpw, uint_32 windowID)
{
	oldState = displayMode;
	displayMode = MENU;
	gameMenu->restartMenu();
	menusShown = true;	
}

void hideMenu(pCpw cpw, uint_32 windowID)
{
	displayMode = oldState;	
	menusShown = false;
}

void keyboardCallback( pCpw cpw, uint_32 windowid, uint_32 asciicode, 
                   uint_32 keystate, uint_32 cursorxpos, uint_32 cursorypos )
{

}



void systemKeyboardCallback( pCpw cpw, uint_32 windowid, uint_32 keycode, uint_32 keystate, 
                   uint_32 cursorxpos, uint_32 cursorypos )
{	
	if(keycode ==  CPW_KEY_ESCAPE && keystate == CPW_KEYMOD_DOWN && !escapeDown)
	{
		escapeDown = true;

		if(displayMode == MENU)
		{
			if(gameMenu->isMainMenu())
			{
				hideMenu(cpw, windowid);
				menusShown = false;
			}
			else
				gameMenu->backOneMenu();
		}
		else if(displayMode != MENU)
		{
			showMenu(cpw, windowid);
			menusShown = true;
		}
	}
	else if(keycode ==  CPW_KEY_ESCAPE && keystate == CPW_KEYMOD_UP && escapeDown)
	{
		escapeDown = false;
	}

	if(keycode == CPW_KEY_F1 && keystate == CPW_KEYMOD_DOWN && !F1Down)
	{
		F1Down = true;

		if(isFullScreen)
		{
			isFullScreen = false;
		}
		else
		{
			CpwVideoHints videoHints;
			videoHints.active = true;
			videoHints.depth = 16;
			videoHints.height = 480;
			videoHints.width = 640;
			cpwChangeVideoMode(cpw, videoHints);
			cpwFullscreenWindow(cpw, windowid);

			isFullScreen = true;
		}

	}
	else if(keycode ==  CPW_KEY_F1 && keystate == CPW_KEYMOD_UP && F1Down)
	{
		F1Down = false;
	}

	if(keycode == 14 && keystate == CPW_KEYMOD_DOWN && !UpArrowDown)
	{
		if(displayMode == MENU)
		{
			UpArrowDown = true;
			gameMenu->moveUp();
		}
	}
	else if(keycode ==  14 && keystate == CPW_KEYMOD_UP && UpArrowDown)
	{
		UpArrowDown = false;
	}



	if(keycode == 16 && keystate == CPW_KEYMOD_DOWN && !DownArrowDown)
	{
		if(displayMode == MENU)
		{
			DownArrowDown = true;
			gameMenu->moveDown();
		}
	}
	else if(keycode ==  16 && keystate == CPW_KEYMOD_UP && DownArrowDown)
	{
		DownArrowDown = false;
	}


	if(keycode == 17 && keystate == CPW_KEYMOD_DOWN && !PgUpDown)
	{
		if(displayMode == MENU)
		{
			PgUpDown = true;
			gameMenu->movePageUp();
		}
	}
	else if(keycode ==  17 && keystate == CPW_KEYMOD_UP && PgUpDown)
	{
		PgUpDown = false;
	}


	if(keycode == 18 && keystate == CPW_KEYMOD_DOWN && !PgDwnDown)
	{
		if(displayMode == MENU)
		{
			PgDwnDown = true;
			gameMenu->movePageDown();
		}
	}
	else if(keycode ==  18 && keystate == CPW_KEYMOD_UP && PgDwnDown)
	{
		PgDwnDown = false;
	}


	if(keycode == 30 && keystate == CPW_KEYMOD_DOWN && !ReturnDown)
	{
		if(displayMode == MENU)
		{
			ReturnDown = true;
			if(gameMenu->isExit())
			{
				DebugLog::closeLog();
				exit(0);
			}
			else
				gameMenu->selectOption();
		}
	}
	else if(keycode == 30 && keystate == CPW_KEYMOD_UP && ReturnDown)
	{
		ReturnDown = false;
	}


	if(keycode == 30 && keystate == CPW_KEYMOD_DOWN && !modeKeyDown)
	{
		if(displayMode == GAME)
		{
			modeKeyDown = true;

			if(navMode == PeepMode)
				navMode = FreeMode;
			else
				navMode = PeepMode;			
		}
	}
	else if(keycode == 30 && keystate == CPW_KEYMOD_UP && modeKeyDown)
	{
		modeKeyDown = false;
	}

	bool timeModified = false;

	
	if(keycode == CPW_KEY_ADD && plusKeyDown == false)
	{
		/*
		int tod;
		
		mySkyDome->getTime(&tod);
		mySkyDome->setTime(tod + 15);
		
		plusKeyDown = true;
		
		timeModified = true;
		*/
	}
	else if(keycode == CPW_KEY_ADD && keystate == CPW_KEYMOD_UP && plusKeyDown)
		plusKeyDown = false;

	if(keycode == CPW_KEY_SUBTRACT && minusKeyDown == false)
	{
		/*
		int tod;
		mySkyDome->getTime(&tod);
		mySkyDome->setTime(tod - 15);

		minusKeyDown = true;		
		timeModified = true;
		*/
	}
	else if(keycode == CPW_KEY_SUBTRACT && keystate == CPW_KEYMOD_UP && minusKeyDown)
		minusKeyDown = false;

	/*
	if(timeModified)
	{
		mySkyDome->getAmbientColor(&ambientRValue, &ambientGValue, &ambientBValue);
		mySkyDome->getLightColor(&lightRValue, &lightGValue, &lightBValue);

		double val = calcLightFactor(0.0f, 0.0f, 1.0f);
		float white[3] = {1.0f, 1.0f, 1.0f};
		float r, g, b;
		calcColor(white, val, &edgeLighting[0][0], &edgeLighting[0][1], &edgeLighting[0][2]);
		
		
		val = calcLightFactor(1.0f, 0.0f, 0.0f);
		calcColor(white, val, &edgeLighting[1][0], &edgeLighting[1][1], &edgeLighting[1][2]);

		//changed
		val = calcLightFactor(0.0f, 0.0f, -1.0f);
		calcColor(white, val, &edgeLighting[2][0], &edgeLighting[2][1], &edgeLighting[2][2]);

		val = calcLightFactor(-1.0f, 0.0f, 0.0f);
		calcColor(white, val, &edgeLighting[3][0], &edgeLighting[3][1], &edgeLighting[3][2]);
	}
	

	float moveStep = WALK_SPEED * 0.1f;

	//up arrow, in game
	if(keycode == CPW_KEY_UP && displayMode == GAME)
	{
		ZV+=(float)(-moveStep * cos(XR * M_PI / 180.0f));
		XV-=(float)(-moveStep * sin(XR * M_PI / 180.0f));
	}
	//down arrow, in game
	if(keycode == CPW_KEY_DOWN && displayMode == GAME)
	{
		ZV-=(float)(-moveStep * cos(XR * M_PI / 180.0f));
		XV+=(float)(-moveStep * sin(XR * M_PI / 180.0f));
	}
	//left arrow, in game
	if(keycode == CPW_KEY_LEFT && displayMode == GAME)
	{
		ZV+=(float)(-moveStep * cos((XR - 90.0f) * M_PI / 180.0f));
		XV-=(float)(-moveStep * sin((XR - 90.0f) * M_PI / 180.0f));
	}
	//right arrow, in game
	if(keycode == CPW_KEY_RIGHT && displayMode == GAME)
	{
		ZV+=(float)(-moveStep * cos((XR + 90.0f) * M_PI / 180.0f));
		XV-=(float)(-moveStep * sin((XR + 90.0f) * M_PI / 180.0f));
	}

	//page up
	if(keycode == CPW_KEY_PAGEUP && displayMode == GAME)
		YV += moveStep;
	if(keycode == CPW_KEY_PAGEDOWN && displayMode == GAME)
		YV -= moveStep;
	*/





	//printf("%d\n", keycode);
	
}

void mouseClickCallback(pCpw cpw, uint_32 windowid, uint_32 button, uint_32 buttonstate, 
                   uint_32 cursorxpos, uint_32 cursorypos)
{
}

void mouseDragCallback(pCpw cpw, uint_32 windowid, uint_32 button, int_32 cursorxpos, int_32 cursorypos)
{
}

int lastMouseX = -1;
int lastMouseY = -1;

void mouseMoveCallback(pCpw cpw, uint_32 windowid, uint_32 cursorxpos, uint_32 cursorypos)
{
	/*
	int mouseXDiff=0, mouseYDiff=0;

	if(lastMouseX != -1)
	{
		mouseXDiff = cursorxpos - lastMouseX;
		mouseYDiff = cursorypos - lastMouseY;

		//printf("mousex: %d mousey: %d\n", mouseXDiff, mouseYDiff);
	}

	//put mouse in center of screen
	lastMouseX = 320;
	lastMouseY = 240;
	

	//if(displayMode == GAME) // || DisplayMode == MapMode)
	{
		XR += 0.5f * mouseXDiff;
		YR += 0.5f * mouseYDiff;

		cpwCenterCursor(cpw, windowid);
	}

	if(XR < 0.0f)
		XR += 360.0f;
	else if(XR > 360.0f)
		XR -= 360.0f;

	if(YR < 0.0f)
		YR += 360.0f;
	else if(XR > 360.0f)
		YR -= 360.0f;
	*/
}



