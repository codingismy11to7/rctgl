#include "vr-menu.h"
#include "vr3d.h"
#include "NeheGL.h"
#include <windows.h>
#include "vr-displaymodes.h"


extern bool UncompressedFile;
extern bool LoadedLandscape;
extern bool LoadedRides;
extern bool LoadedTrees;
extern bool LoadedElements;
extern bool LoadedPaths;
extern bool LoadedWalls;

extern RenderModes DisplayMode;
extern displayModes displayMode;

HWND parentWindow;


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
		10, 10, //nX, nY,
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

	parentWindow = GetParent(hwndDlg);

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

	SetForegroundWindow(parentWindow);

	ShowCursor (FALSE);
}

/*
Main Menu

RctGL
Load
Visuals
Exit

Load Menu


Visuals Menu
*/

void menuClass::drawRCTGLLogo(pCpw cpw)
{
	glRasterPos2d( 20, scrnht - 50);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 60 );
    cpwDrawFont( cpw, menuFont, "RctGL", 1 );
}

void menuClass::drawRCTGLLogo(pCpw cpw, char *sideText)
{
	glRasterPos2d( 20, scrnht - 50);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 60 );
    cpwDrawFont( cpw, menuFont, "RctGL", 1 );

	glColor4f(0.75f, 0.75f, 0.75f, 1.0f);
	glRasterPos2d( 250, scrnht - 50);
	cpwDrawFont( cpw, menuFont, sideText, 1 );
}

void menuClass::drawDetailMenu(pCpw cpw)
{
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 45 );

	float selectedColor[3] = {1.0f, 1.0f, 1.0f};
	float unselectedColor[3] = {0.6f, 0.6f, 0.6f};

	char *option1 = "Detail";
	char *option2 = "Menu";
	char *option3 = "Options";
	char *option4 = "Here";

	if(curOption == 0)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, scrnht - 150);	
	cpwDrawFont( cpw, menuFont, option1, 1 );

	if(curOption == 1)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, scrnht - 200);	
	cpwDrawFont( cpw, menuFont, option2, 1 );

	if(curOption == 2)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, scrnht - 250);	
	cpwDrawFont( cpw, menuFont, option3, 1 );

	if(curOption == 3)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);
	
	glRasterPos2d( 20, scrnht - 300);	
	cpwDrawFont( cpw, menuFont, option4, 1 );

}

int strDiff(char *str1, char *str2)
{
	int len1, len2, maxlen;
	len1 = strlen(str1);
	len2 = strlen(str2);

	if(len1 > len2)
		maxlen = len1;
	else
		maxlen = len2;

	//returns -1 if str1 < str2
	//returns  1 if str1 > str2
	//returns  0 if str1 == str2
	for(int i=0; i<maxlen; i++)
	{
		if(str1[i] == NULL)
			return -1;
		if(str2[i] == NULL)
			return 1;

		if(toupper(str1[i]) > toupper(str2[i]))
			return 1;
		if(toupper(str1[i]) < toupper(str2[i]))
			return -1;
	}

	return 0;
}


void menuClass::sortDirList(void)
{
	int len = fileList.size();

	int i, j;

	for(i=0; i<len - 1; i++)
	{
		for(j=0; j<len - 1; j++)
		{			
			if(strDiff(fileList[j], fileList[j+1]) > 0 &&
				((fileList[j][0] == '<' && fileList[j+1][0] == '<')
				|| (fileList[j][0] != '<' && fileList[j+1][0] != '<')))
			{
				char *tmp;
				tmp = fileList[j];
				fileList[j] = fileList[j+1];
				fileList[j+1] = tmp;
			}
		}
	}
}


void menuClass::addToDirList(char *filename, bool isDir, bool isFile)
{
	char *itemElement;
	itemElement = (char *)malloc(128);
	
	if(isDir)
	{
		itemElement[0] = '<';
		strcpy(&itemElement[1], filename);
		itemElement[strlen(filename) + 1] = '>';
		itemElement[strlen(filename) + 2] = NULL;
	}
	else
		strcpy(&itemElement[0], filename);

	if(!(isDir && *filename == '.' && strlen(filename) == 1))
		fileList.push_back(itemElement);
}

bool isSV4(char *testStr)
{
	int len;
	len = strlen(testStr);

	if(len <= 4)
		return false;

	bool retval = true;

	if(testStr[len - 1] != '4')
		retval = false;
	if(toupper(testStr[len - 2]) != 'V')
		retval = false;
	if(toupper(testStr[len - 3]) != 'S')
		retval = false;

	return retval;
}

void menuClass::populateFileList(char *path)
{
	fileList.clear();
	dirList.clear();

	char *tmpStr;
	tmpStr = (char *)malloc(128);

	char *tmpPath;
	tmpPath = (char *)malloc(256);
	tmpPath = strcpy(tmpPath, path);

	//add ".."
	//strcpy(tmpStr, "<..>");
	//fileList.push_back(tmpStr);

	//now add all the directories
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char *dirString;
	dirString = (char *)malloc(256);
	dirString = strcat(tmpPath, "\\*.*");
	printf("dirString = %s\n", dirString);

	hFind = FindFirstFile(dirString, &FindFileData);
	if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		addToDirList(FindFileData.cFileName, true, false);
	
	bool finished = false;
	
	while(!finished)
	{
		if (!FindNextFile(hFind, &FindFileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
				finished = TRUE; 
		} 
		else 
		{
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				addToDirList(FindFileData.cFileName, true, false);			
		}		
	}

	//then add the files
	hFind = FindFirstFile(dirString, &FindFileData);
	if(isSV4(FindFileData.cFileName))
		addToDirList(FindFileData.cFileName, false, true);


	finished = false;
	
	while(!finished)
	{
		if (!FindNextFile(hFind, &FindFileData)) 
		{
			if (GetLastError() == ERROR_NO_MORE_FILES) 
				finished = TRUE; 
		} 
		else 
		{
			if(isSV4(FindFileData.cFileName))
				addToDirList(FindFileData.cFileName, false, true);
		}		
	}



	sortDirList();

	//add the drives
	char *drivestr;
	DWORD sectors, bytes, clusters, num;
	for(char drive='C'; drive<'Z'; drive++)
	{
		drivestr = (char*)malloc(4);
		*drivestr = drive;
		*(drivestr + 1) = ':';
		*(drivestr + 2) = '\\';
		*(drivestr + 3) = NULL;

		if(GetDiskFreeSpace(drivestr, &sectors, &bytes, &clusters, &num))
			fileList.push_back(drivestr);
	}

	printf("fileList\n");
	for(int i=0; i<fileList.size(); i++)
		printf("- %s\n", fileList[i]);

	fileListOffset = 0;
	curOption = 0;


	//now add all of the sv4 (and sv6) files

}

void menuClass::drawFileLoader(pCpw cpw)
{
	
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 15 );

	float selectedColor[3] = {1.0f, 1.0f, 1.0f};
	float unselectedColor[3] = {0.6f, 0.6f, 0.6f};

	char *option1 = curPath;
	
	glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	glRasterPos2d( 20, scrnht - 75);	
	cpwDrawFont( cpw, menuFont, option1, 1 );

	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 20 );

	int maxListDisplay;

	if(fileListOffset + 15 < fileList.size())
		maxListDisplay = fileListOffset + 15;
	else
		maxListDisplay = fileList.size();

	int offset = 0;

	//printf("min: %d max: %d cur: %d\n", fileListOffset, maxListDisplay, curOption);

	for(int i=fileListOffset; i<maxListDisplay; i++)
	{
		if(curOption == i)
			glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
		else
			glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);
		
		glRasterPos2d( 20, scrnht - (100 + 25 * offset));
		cpwDrawFont( cpw, menuFont, fileList[i], 1 );

		offset++;
	}
}

bool menuClass::isExit(void)
{
	return (curScreen == MAINMENU && curOption == 3);
}

bool menuClass::isMainMenu(void)
{
	return (curScreen == MAINMENU);
}

void menuClass::drawMainMenu(pCpw cpw)
{
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 45 );

	float selectedColor[3] = {1.0f, 1.0f, 1.0f};
	float unselectedColor[3] = {0.6f, 0.6f, 0.6f};

	char *option1 = "Open Park";
	char *option2 = "Visuals";
	char *option3 = "Input";
	char *option4 = "Exit";

	if(curOption == 0)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, scrnht - 100);	
	cpwDrawFont( cpw, menuFont, option1, 1 );

	if(curOption == 1)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, scrnht - 150);	
	cpwDrawFont( cpw, menuFont, option2, 1 );

	if(curOption == 2)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, scrnht - 200);	
	cpwDrawFont( cpw, menuFont, option3, 1 );

	if(curOption == 3)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);
	
	glRasterPos2d( 20, scrnht - 250);	
	cpwDrawFont( cpw, menuFont, option4, 1 );

}

void menuClass::moveUp(void)
{
	if(curScreen == MAINMENU)
	{
		if(curOption == 0)
			curOption = 3;
		else
			curOption--;		
	}
	else if(curScreen == SELECTFILE)
	{
		if(curOption > 0)
		{
			if(curOption == fileListOffset)
				fileListOffset--;

			curOption--;
		}
	}
}

void menuClass::movePageUp(void)
{
	if(curScreen == SELECTFILE)
	{
		if(curOption <= 15)
		{
			curOption = 0;
			fileListOffset = 0;
		}
		else
		{
			//if it's not at the bottom of the screen
			//move it there
			if(curOption > fileListOffset)
				curOption = fileListOffset;
			//move the whole screen down
			else if(curOption == fileListOffset)
			{
				if(curOption - 15 > 0)
				{
					//printf("1\n");
					fileListOffset -= 15;
					curOption -= 15;
				}
				else
				{
					//printf("2\n");
					curOption = 0;
					fileListOffset = 0;
				}
			}
		}
	}
}

void menuClass::moveDown(void)
{
	if(curScreen == MAINMENU)
	{
		if(curOption == 3)
			curOption = 0;
		else
			curOption++;		
	}
	else if(curScreen == SELECTFILE)
	{
		if(curOption + 1 < fileList.size())
		{
			if(curOption == fileListOffset + 14)
				fileListOffset++;

			curOption++;
		}
	}
}


void menuClass::movePageDown(void)
{
	if(curScreen == SELECTFILE)
	{
		if(fileList.size() <= 15)
			curOption = fileList.size();
		else
		{
			//if it's not at the bottom of the screen
			//move it there
			if(curOption < fileListOffset + 14)
				curOption = fileListOffset + 14;
			//move the whole screen down
			else if(curOption == fileListOffset + 14)
			{
				if(curOption + 15 < fileList.size())
				{
					//printf("1\n");
					fileListOffset = curOption + 1;
					curOption += 15;
				}
				else
				{
					//printf("2\n");
					curOption = fileList.size() - 1;
					fileListOffset = curOption - 14;
				}
			}
		}

	}
}

bool isDrive(char *teststr)
{
	if(strlen(teststr) == 3)
		if(teststr[0] >= 'C' && teststr[0] <= 'Z')
			if(teststr[1] == ':')
				if(teststr[2] == '\\')
					return true;

	return false;
}

void menuClass::selectOption(void)
{
	if(curScreen == MAINMENU)
	{
		if(curOption == 0)
		{
			populateFileList(&curPath[0]);
			curScreen = SELECTFILE;
			//processFileOpenRequest();
		}
		else if(curOption == 1)
			curScreen = DETAIL;
		else if(curOption == 2)
			curScreen = INPUTCONFIG;

		curOption = 0;
	}
	else if(curScreen == SELECTFILE)
	{
		int iii;
		iii=0;
		//check for the ".."
		if(strcmp(fileList[curOption], "<..>") == 0)
		{
			char *tmp;
			tmp = strrchr(curPath, '\\');
			*tmp = NULL;

			populateFileList(curPath);
		}
		//switch directories
		else if(fileList[curOption][0] == '<')
		{
			int offset = strlen(curPath);

			curPath[offset++] = '\\';

			for(int i=1; i<strlen(fileList[curOption]); i++)
			{
				printf("fileList[i] = %c\n", fileList[curOption][i]);
				if(fileList[curOption][i] == '>')
				{
					curPath[offset] = NULL;
					break;
				}
				else
					curPath[offset++] = fileList[curOption][i];
			}

			populateFileList(curPath);

		}
		//switch drives
		else if(isDrive(fileList[curOption]))
		{
			strcpy(&curPath[0], fileList[curOption]);

			curPath[2] = NULL;

			populateFileList(curPath);

		}
		//it must be a file
		else
		{
			//change modes
			displayMode = LOADPARK;

			//initialize all the flags to zero
			UncompressedFile = FALSE;
			LoadedLandscape = FALSE;
			LoadedRides = FALSE;
			LoadedTrees	= FALSE;
			LoadedPaths = FALSE;
			LoadedElements = FALSE;
			LoadedWalls = FALSE;

			//build the string with the file path
			strcpy(&RCTGL_InFile[0], &curPath[0]);
			strcat(&RCTGL_InFile[0], "\\");
			strcat(&RCTGL_InFile[0], fileList[curOption]);

			printf("current file is %s\n", &RCTGL_InFile[0]);
		}
	}	
}

void menuClass::backOneMenu(void)
{
	curScreen = MAINMENU;	
	curOption = 0;
}

void menuClass::restartMenu(void)
{
	curScreen = MAINMENU;
	curOption = 0;
}

void menuClass::drawMenu(pCpw cpw)
{
	glDisable(GL_TEXTURE_2D);

	if(curScreen == MAINMENU)
	{
		drawRCTGLLogo(cpw);
		drawMainMenu(cpw);	
	}
	else if(curScreen == SELECTFILE)
	{
		drawRCTGLLogo(cpw, "Open Park");
		drawFileLoader(cpw);		
	}
	else if(curScreen == DETAIL)
	{
		drawRCTGLLogo(cpw, "Visuals");
		drawDetailMenu(cpw);		
	}
}

menuClass::menuClass(CpwFontFace fontFace)
{
	menuFont = fontFace;

	scrnwid = 640;
	scrnht = 480;

	// open the registry to get the location of RCT save files
	HKEY hKey;
	char szStoragePath[256];
	char *tmp;
	DWORD dwBufLen;

	curPath[0] = NULL;

	RegOpenKeyEx( HKEY_LOCAL_MACHINE,
	   "SOFTWARE\\Fish Technology Group\\RollerCoaster Tycoon Setup",
	   0, KEY_QUERY_VALUE, &hKey );
	RegQueryValueEx( hKey, "Path", NULL, NULL,
	   (LPBYTE) curPath, &dwBufLen);
	RegCloseKey( hKey );

	if(strlen(curPath) == 0)
	{
		GetModuleFileName(NULL, &curPath[0], 256);
		int len;
		len = strlen(&curPath[0]);
		curPath[len - 10] = '\0';
	}

	printf("default path = %s\n", curPath);

	restartMenu();
}

