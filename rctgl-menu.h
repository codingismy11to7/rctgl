#ifndef RCTGL_MENU_H
#define RCTGL_MENU_H

#include "rctgl.h"
#include "rctgl-park.h"

#include <algorithm>
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
	RCTGLMenu(const CpwFontFace &fontFace);

private:
	int m_scrnht;
	int m_scrnwid;
	menuScreens m_curScreen;
	int m_curOption;
	CpwFontFace m_menuFont;

	int m_fileListOffset;

	vector<string> m_fileList;
	vector<string> m_dirList;
	string m_curPath;

	void drawRCTGLLogo(const pCpw cpw) const;
	void drawRCTGLLogo(const pCpw cpw, const string &sideText) const;
	void drawDetailMenu(const pCpw cpw);
	void drawFileLoader(const pCpw cpw);
	void drawMainMenu(const pCpw cpw);
	void populateFileList(const string &path);
	void addToDirList(const string &filename, bool isDir, bool isFile);
	//void sortDirList(void);
};

#endif