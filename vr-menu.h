#define CPWDLL_EXTERN
#include "basictemplate/cpw.h"
#include <vector>
using namespace std;

enum menuScreens {MAINMENU, SELECTFILE, DETAIL, INPUTCONFIG};

class menuClass
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
	menuClass::menuClass(CpwFontFace fontFace);

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