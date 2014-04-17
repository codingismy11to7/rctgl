#ifndef RCTGL_INPUT_H
#define RCTGL_INPUT_H

#include "rctgl.h"
#include "rctgl-menu.h"

#include CPWDLL_LOC



extern RCTGLMenu *gameMenu;

void keyboardCallback( pCpw cpw, uint_32 windowid, uint_32 asciicode, uint_32 keystate, uint_32 cursorxpos, uint_32 cursorypos );
void systemKeyboardCallback( pCpw cpw, uint_32 windowid, uint_32 asciicode, uint_32 keystate, uint_32 cursorxpos, uint_32 cursorypos );
void mouseClickCallback(pCpw cpw, uint_32 windowid, uint_32 button, uint_32 buttonstate, uint_32 cursorxpos, uint_32 cursorypos);
void mouseDragCallback(pCpw cpw, uint_32 windowid, uint_32 button, int_32 cursorxpos, int_32 cursorypos);
void mouseMoveCallback(pCpw cpw, uint_32 windowid, uint_32 cursorxpos, uint_32 cursorypos);

#endif