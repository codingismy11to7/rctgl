#include "rctgl-menu.h"
#include "rctgl-displaymodes.h"


//extern RenderModes DisplayMode;
extern displayModes displayMode;

/*
Main Menu

RctGL
Load
Visuals
Exit

Load Menu


Visuals Menu
*/

void RCTGLMenu::drawRCTGLLogo(const pCpw cpw) const
{
	glRasterPos2d( 20, m_scrnht - 50);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 60 );
    cpwDrawFont( cpw, m_menuFont, "RctGL", 1 );
}

void RCTGLMenu::drawRCTGLLogo(const pCpw cpw, const string &sideText) const
{
	glRasterPos2d( 20, m_scrnht - 50);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 60 );
    cpwDrawFont( cpw, m_menuFont, "RctGL", 1 );

	glColor4f(0.75f, 0.75f, 0.75f, 1.0f);
	glRasterPos2d( 250, m_scrnht - 50);

	char *thisSureIsStupidToHaveToDo = new char[1+sideText.size()];
	memcpy( thisSureIsStupidToHaveToDo, sideText.c_str(), sideText.size() + 1 );
	cpwDrawFont( cpw, m_menuFont, thisSureIsStupidToHaveToDo, 1 );
	delete[] thisSureIsStupidToHaveToDo;
}

void RCTGLMenu::drawDetailMenu(pCpw cpw)
{
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 45 );

	float selectedColor[3] = {1.0f, 1.0f, 1.0f};
	float unselectedColor[3] = {0.6f, 0.6f, 0.6f};

	char *option1 = "Detail";
	char *option2 = "Menu";
	char *option3 = "Options";
	char *option4 = "Here";

	if(m_curOption == 0)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, m_scrnht - 150);	
	cpwDrawFont( cpw, m_menuFont, option1, 1 );

	if(m_curOption == 1)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, m_scrnht - 200);	
	cpwDrawFont( cpw, m_menuFont, option2, 1 );

	if(m_curOption == 2)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, m_scrnht - 250);	
	cpwDrawFont( cpw, m_menuFont, option3, 1 );

	if(m_curOption == 3)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);
	
	glRasterPos2d( 20, m_scrnht - 300);	
	cpwDrawFont( cpw, m_menuFont, option4, 1 );

}

/*int strDiff(char *str1, char *str2)
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
}*/


/*void RCTGLMenu::sortDirList(void)
{
	int len = m_fileList.size();

	int i, j;

	for(i=0; i<len - 1; i++)
	{
		for(j=0; j<len - 1; j++)
		{			
			if(strDiff(m_fileList[j], m_fileList[j+1]) > 0 &&
				((m_fileList[j][0] == '<' && m_fileList[j+1][0] == '<')
				|| (m_fileList[j][0] != '<' && m_fileList[j+1][0] != '<')))
			{
				char *tmp;
				tmp = m_fileList[j];
				m_fileList[j] = m_fileList[j+1];
				m_fileList[j+1] = tmp;
			}
		}
	}
}*/


void RCTGLMenu::addToDirList(const string &filename, bool isDir, bool isFile)
{
	string itemElement;
	
	if(isDir)
		itemElement = "<" + filename + ">";
	else
		itemElement = filename;

	DebugLog::writeToLog( string("itemElement = ") + itemElement );
	if( isDir ) DebugLog::writeToLog( "YES dir" );
	else DebugLog::writeToLog( "NO dir" );

	if(!(isDir && filename == "." && filename.size() == 1))
		m_fileList.push_back(itemElement);
}

bool isSV4(const string &testStr)
{
	unsigned int len;
	len = testStr.size();

	if(len <= 4)
		return false;

	if(testStr[len - 1] != '4')
		return false;
	if(toupper(testStr[len - 2]) != 'V')
		return false;
	if(toupper(testStr[len - 3]) != 'S')
		return false;

	return true;
}

void RCTGLMenu::populateFileList(const string &path)
{
	m_fileList.clear();
	m_dirList.clear();

	DebugLog::beginTask( "populateFileList" );

	string tmpStr;

	string tmpPath = path;

	//add ".."
	//strcpy(tmpStr, "<..>");
	//m_fileList.push_back(tmpStr);

	//now add all the directories
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	string dirString = tmpPath + "\\*.*";
	//printf("dirString = %s\n", dirString);

	DebugLog::writeToLog( string( "dirString = " ) + dirString );

	hFind = FindFirstFile(dirString.c_str(), &FindFileData);
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

	DebugLog::writeToLog( "here!" );

	//then add the files
	hFind = FindFirstFile(dirString.c_str(), &FindFileData);
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

	DebugLog::writeToLog( "here2!" );

	//sortDirList();
	sort( m_fileList.begin(), m_fileList.end() );

	//add the drives
	string drivestr = "B:\\";
	DWORD sectors, bytes, clusters, num;
	for(char drive='C'; drive<'Z'; drive++)
	{
		drivestr[0] = drive;

		if(GetDiskFreeSpace(drivestr.c_str(), &sectors, &bytes, &clusters, &num))
			m_fileList.push_back(drivestr);
	}

	DebugLog::writeToLog( "here3!" );

	//printf("m_fileList\n");
	//for(int i=0; i<m_fileList.size(); i++)
	//	printf("- %s\n", m_fileList[i]);

	m_fileListOffset = 0;
	m_curOption = 0;


	//now add all of the sv4 (and sv6) files

	DebugLog::endTask();
}

void RCTGLMenu::drawFileLoader(const pCpw cpw)
{
	
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 15 );

	float selectedColor[3] = {1.0f, 1.0f, 1.0f};
	float unselectedColor[3] = {0.6f, 0.6f, 0.6f};

	char *option1 = new char[1+m_curPath.size()];
	memcpy( option1, m_curPath.c_str(), 1+m_curPath.size() );
	
	glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	glRasterPos2d( 20, m_scrnht - 75);	
	cpwDrawFont( cpw, m_menuFont, option1, 1 );

	delete[] option1;

	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 20 );

	int maxListDisplay;

	if(m_fileListOffset + 15 < m_fileList.size())
		maxListDisplay = m_fileListOffset + 15;
	else
		maxListDisplay = m_fileList.size();

	int offset = 0;

	//printf("min: %d max: %d cur: %d\n", m_fileListOffset, maxListDisplay, m_curOption);

	for(int i=m_fileListOffset; i<maxListDisplay; i++)
	{
		if(m_curOption == i)
			glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
		else
			glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);
		
		glRasterPos2d( 20, m_scrnht - (100 + 25 * offset));

		char *thisSureIsStupidToHaveToDo = new char[1+m_fileList[i].size()];
		memcpy( thisSureIsStupidToHaveToDo, m_fileList[i].c_str(), 1+m_fileList[i].size() );
		cpwDrawFont( cpw, m_menuFont, thisSureIsStupidToHaveToDo, 1 );
		delete[] thisSureIsStupidToHaveToDo;

		offset++;
	}
}

bool RCTGLMenu::isExit(void)
{
	return (m_curScreen == MAINMENU && m_curOption == 3);
}

bool RCTGLMenu::isMainMenu(void)
{
	return (m_curScreen == MAINMENU);
}

void RCTGLMenu::drawMainMenu(pCpw cpw)
{
	cpwFontMode( cpw, CPW_FONTOPT_SIZE, 45 );

	float selectedColor[3] = {1.0f, 1.0f, 1.0f};
	float unselectedColor[3] = {0.6f, 0.6f, 0.6f};

	char *option1 = "Open Park";
	char *option2 = "Visuals";
	char *option3 = "Input";
	char *option4 = "Exit";

	if(m_curOption == 0)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, m_scrnht - 100);	
	cpwDrawFont( cpw, m_menuFont, option1, 1 );

	if(m_curOption == 1)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, m_scrnht - 150);	
	cpwDrawFont( cpw, m_menuFont, option2, 1 );

	if(m_curOption == 2)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);

	glRasterPos2d( 20, m_scrnht - 200);	
	cpwDrawFont( cpw, m_menuFont, option3, 1 );

	if(m_curOption == 3)
		glColor3f(selectedColor[0], selectedColor[1], selectedColor[2]);
	else
		glColor3f(unselectedColor[0], unselectedColor[1], unselectedColor[2]);
	
	glRasterPos2d( 20, m_scrnht - 250);	
	cpwDrawFont( cpw, m_menuFont, option4, 1 );

}

void RCTGLMenu::moveUp(void)
{
	if(m_curScreen == MAINMENU)
	{
		if(m_curOption == 0)
			m_curOption = 3;
		else
			m_curOption--;		
	}
	else if(m_curScreen == SELECTFILE)
	{
		if(m_curOption > 0)
		{
			if(m_curOption == m_fileListOffset)
				m_fileListOffset--;

			m_curOption--;
		}
	}
}

void RCTGLMenu::movePageUp(void)
{
	if(m_curScreen == SELECTFILE)
	{
		if(m_curOption <= 15)
		{
			m_curOption = 0;
			m_fileListOffset = 0;
		}
		else
		{
			//if it's not at the bottom of the screen
			//move it there
			if(m_curOption > m_fileListOffset)
				m_curOption = m_fileListOffset;
			//move the whole screen down
			else if(m_curOption == m_fileListOffset)
			{
				if(m_curOption - 15 > 0)
				{
					//printf("1\n");
					m_fileListOffset -= 15;
					m_curOption -= 15;
				}
				else
				{
					//printf("2\n");
					m_curOption = 0;
					m_fileListOffset = 0;
				}
			}
		}
	}
}

void RCTGLMenu::moveDown(void)
{
	if(m_curScreen == MAINMENU)
	{
		if(m_curOption == 3)
			m_curOption = 0;
		else
			m_curOption++;		
	}
	else if(m_curScreen == SELECTFILE)
	{
		if(m_curOption + 1 < m_fileList.size())
		{
			if(m_curOption == m_fileListOffset + 14)
				m_fileListOffset++;

			m_curOption++;
		}
	}
}


void RCTGLMenu::movePageDown(void)
{
	if(m_curScreen == SELECTFILE)
	{
		if(m_fileList.size() <= 15)
			m_curOption = m_fileList.size();
		else
		{
			//if it's not at the bottom of the screen
			//move it there
			if(m_curOption < m_fileListOffset + 14)
				m_curOption = m_fileListOffset + 14;
			//move the whole screen down
			else if(m_curOption == m_fileListOffset + 14)
			{
				if(m_curOption + 15 < m_fileList.size())
				{
					//printf("1\n");
					m_fileListOffset = m_curOption + 1;
					m_curOption += 15;
				}
				else
				{
					//printf("2\n");
					m_curOption = m_fileList.size() - 1;
					m_fileListOffset = m_curOption - 14;
				}
			}
		}

	}
}

bool isDrive(const string &teststr)
{
	if(teststr.size() == 3)
		if(teststr[0] >= 'C' && teststr[0] <= 'Z')
			if(teststr[1] == ':')
				if(teststr[2] == '\\')
					return true;

	return false;
}

void RCTGLMenu::selectOption(void)
{
	if(m_curScreen == MAINMENU)
	{
		if(m_curOption == 0)
		{
			populateFileList(m_curPath);
			m_curScreen = SELECTFILE;
			//processFileOpenRequest();
		}
		else if(m_curOption == 1)
			m_curScreen = DETAIL;
		else if(m_curOption == 2)
			m_curScreen = INPUTCONFIG;

		m_curOption = 0;
	}
	else if(m_curScreen == SELECTFILE)
	{
		int iii;
		iii=0;
		//check for the ".."
		if(m_fileList[m_curOption] == "<..>")
		{
			/*char *tmp;
			tmp = strrchr(curPath, '\\');
			*tmp = NULL;*/
			//string tmpPath = m_curPath;
			int slash = m_curPath.rfind( '\\' );
			m_curPath.resize( slash );

			populateFileList(m_curPath);
		}
		//switch directories
		else if(m_fileList[m_curOption][0] == '<')
		{
			string tmpOpt = m_fileList[m_curOption].c_str() + 1;
			tmpOpt.resize( tmpOpt.size() - 1 );
			m_curPath += "\\" + tmpOpt;

			populateFileList(m_curPath);

		}
		//switch drives
		else if(isDrive(m_fileList[m_curOption]))
		{
			m_curPath = m_fileList[m_curOption];
			m_curPath.resize( 3 );

			populateFileList(m_curPath);

		}
		//it must be a file
		else
		{
			//change modes
			//displayMode = LOADPARK;
			displayMode = MENU;
			m_curScreen = MAINMENU;



			//initialize all the flags to zero
			UncompressedFile = FALSE;
			LoadedLandscape = FALSE;
			LoadedRides = FALSE;
			LoadedTrees	= FALSE;
			LoadedPaths = FALSE;
			LoadedElements = FALSE;
			LoadedWalls = FALSE;

			//build the string with the file path
			RCTGL_InFile = m_curPath + "\\" + m_fileList[m_curOption];

			//printf("current file is %s\n", &RCTGL_InFile[0]);

			thePark->loadPark(RCTGL_InFile);
		}
	}	
}

void RCTGLMenu::backOneMenu(void)
{
	m_curScreen = MAINMENU;	
	m_curOption = 0;
}

void RCTGLMenu::restartMenu(void)
{
	m_curScreen = MAINMENU;
	m_curOption = 0;
}

void RCTGLMenu::drawMenu(pCpw cpw)
{
	glDisable(GL_TEXTURE_2D);

	if(m_curScreen == MAINMENU)
	{
		drawRCTGLLogo(cpw);
		drawMainMenu(cpw);	
	}
	else if(m_curScreen == SELECTFILE)
	{
		drawRCTGLLogo(cpw, "Open Park");
		drawFileLoader(cpw);		
	}
	else if(m_curScreen == DETAIL)
	{
		drawRCTGLLogo(cpw, "Visuals");
		drawDetailMenu(cpw);		
	}
}

RCTGLMenu::RCTGLMenu(const CpwFontFace &fontFace)
{
	m_menuFont = fontFace;

	m_scrnwid = 640;
	m_scrnht = 480;

	// open the registry to get the location of RCT save files
	HKEY hKey;
	//char szStoragePath[256];
	//char *tmp;
	DWORD dwBufLen;

	m_curPath = "";

	char path[1024];
	if( ( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
	   "SOFTWARE\\Fish Technology Group\\RollerCoaster Tycoon Setup",
	   0, KEY_QUERY_VALUE, &hKey )) != ERROR_SUCCESS)
	{
		GetModuleFileName(NULL, path, 256);
		m_curPath = path;
		m_curPath.resize( m_curPath.size() - 10 );
	}
	else
	{
		RegQueryValueEx( hKey, "Path", NULL, NULL,
			(LPBYTE) path, &dwBufLen);
		RegCloseKey( hKey );
		m_curPath = path;
	}

	//printf("default path = %s\n", curPath);

	restartMenu();
}

