#ifndef RCTGL_MENU_H
#define RCTGL_MENU_H

#include "rctgl.h"
#include "rctgl-park.h"

#include <windows.h>

#include CPWDLL_LOC

#include <vector>
using namespace std;

enum menuScreens {MAINMENU, SELECTFILE, DETAIL, INPUTCONFIG};

extern RCTGLPark *thePark;

class RCTGLMenu
{
public:
	void moveUp(void);
	void moveDown(void);
	void movePageUp(void);
	void movePageDown(void);
	void selectOption(void);
	void restartMenu(void);
	void drawMenu(pCpw cpw);
	void backOneMenu(void);
	bool isExit(void);
	bool isMainMenu(void);
	RCTGLMenu::RCTGLMenu(CpwFontFace fontFace);

private:
	int scrnht;
	int scrnwid;
	menuScreens curScreen;
	int curOption;
	CpwFontFace menuFont;

	int fileListOffset;

	vector <char*> fileList;
	vector <char*> dirList;
	char curPath[1024];

	void drawRCTGLLogo(pCpw cpw);
	void drawRCTGLLogo(pCpw cpw, char *sideText);
	void drawDetailMenu(pCpw cpw);
	void drawFileLoader(pCpw cpw);
	void drawMainMenu(pCpw cpw);
	void populateFileList(char *path);
	void addToDirList(char *filename, bool isDir, bool isFile);
	void sortDirList(void);
};

#endif