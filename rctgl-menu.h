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
	void drawMenu(const pCpw cpw) const;
	void backOneMenu(void);
	bool isExit(void) const;
	bool isMainMenu(void) const;
	RCTGLMenu(const CpwFontFace &fontFace);

private:
	unsigned int m_scrnht;
	unsigned int m_scrnwid;
	menuScreens m_curScreen;
	unsigned int m_curOption;
	CpwFontFace m_menuFont;

	unsigned int m_fileListOffset;

	vector<string> m_fileList;
	vector<string> m_dirList;
	string m_curPath;

	void drawRCTGLLogo(const pCpw cpw) const;
	void drawRCTGLLogo(const pCpw cpw, const string &sideText) const;
	void drawDetailMenu(const pCpw cpw) const;
	void drawFileLoader(const pCpw cpw) const;
	void drawMainMenu(const pCpw cpw) const;
	void populateFileList(const string &path);
	void addToDirList(const string &filename, bool isDir, bool isFile);
	//void sortDirList(void);
};

#endif