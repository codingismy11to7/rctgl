/***************************************************************************/
/*                                                                         */
/*  cpw_menus.h                                                            */
/*                                                                         */
/*    Window menus.                                                        */
/*                                                                         */
/*  Copyright 2001-2002 by                                                 */
/*  Jim Mathies,                                                           */
/*                                                                         */
/*  This file is part of the Cpw project, and may only be used,            */
/*  modified, and distributed under the terms of the Cpw project           */
/*  license.  By continuing to use, modify, or distribute this file        */
/*  you indicate that you have read the license and understand and         */
/*  accept it fully.                                                       */
/*                                                                         */
/*  File Platform: cross                                                   */
/*                                                                         */
/***************************************************************************/

#ifndef __cpw_menus_h__
#define __cpw_menus_h__

#include "cpw_config.h"
#include "cpw_state.h"
#include "cpw_window.h"

CPW_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /* <Prototypes>                                                          */
  /*    CpwMenuCallback                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Callback function prototype for menu selections.                   */
  /*                                                                       */
  typedef void (*CpwMenuCallback) ( pCpw cpw, uint_32 winid, uint_32 menuid, uint_32 entryid ); 
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwCreateMenu                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Creates a new top level menu and returns an identifier to it.      */
  /*    The menu may be used as a popup or titlebar menu, or both and      */
  /*    can be assigned to multiple windows.                               */
  /*                                                                       */
  CPW_API uint_32 
  cpwCreateMenu( pCpw cpw, 
                 CpwMenuCallback callback );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwCreateSubMenu                                                   */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Creates a new sub menu and returns an identifier for it.           */
  /*    Sub menus are identical to menus except they do not have           */
  /*    a callback associated with them. They are expected to be           */
  /*    embedded within top level menus. The identifier is only            */
  /*    for editing the menu or inserting it into a top level menu.        */
  /*                                                                       */
  CPW_API uint_32 
  cpwCreateSubMenu( pCpw cpw );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDestroyMenu                                                     */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Destroys the resources associated with a menu or sub menu.         */
  /*    (All menu resources are automatically destroyed when Cpw exits.)   */
  /*                                                                       */
  CPW_API bool    
  cpwDestroyMenu( pCpw cpw, 
                  uint_32 menuid );
  /*                                                                       */
  /*************************************************************************/

  /* menu entry manipulation */

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwAddMenuEntry                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Inserts a new entry into a menu. 'entryid' is the value            */
  /*    handed back to the callback when a user selects the entry.         */
  /*    Entries are added to a menu in a top down fashion.                 */
  /*                                                                       */
  CPW_API bool 
  cpwAddMenuEntry( pCpw cpw, 
                   uint_32 menuid, 
                   pChar title, 
                   uint_32 entryid, 
                   bool checked );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwAddMenuSeperator                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Inserts a new seperator into a menu. 'entryid' is the value        */
  /*    used when editing the menu. Seperators can not be 'selected'       */
  /*    and therefore do not generate callbacks.                           */
  /*                                                                       */
  CPW_API bool 
  cpwAddMenuSeperator( pCpw cpw, 
                       uint_32 menuid, 
                       uint_32 entryid );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwAddSubMenu                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Inserts a new sub menu entry into a menu. 'entryid' is the         */
  /*    value used when editing the menu. Sub menu titles can not be       */
  /*    'selected' and therefore do not generate callbacks.                */
  /*                                                                       */
  CPW_API bool 
  cpwAddSubMenu( pCpw cpw, 
                 uint_32 menuid, 
                 pChar title, 
                 uint_32 submenuid, 
                 uint_32 entryid );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwEditMenuItem                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Changes the attributes of an existing menu entry. The call         */
  /*    will override all previous settings. Editing menus is time         */
  /*    consuming, and should not be carried out based on user             */
  /*    actions. To create different menu's based on the current           */
  /*    state of your application, create multiple menus and assigned      */
  /*    them to a window at the appropriate time.                          */
  /*                                                                       */
  CPW_API bool 
  cpwEditMenuItem( pCpw cpw, 
                   uint_32 menu, 
                   uint_32 entryid, 
                   uint_32 newid, 
                   pChar newtitle, 
                   uint_32 newmenu );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwRemoveMenuItem                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Removes a menu entry from a menu. You can not insert a new         */
  /*    entry to replace an entry you have removed. Editing menus          */
  /*    are time consuming, and should not be carried out based on         */
  /*    user actions. To create different menu's based on the current      */
  /*    state of your application, create multiple menus and assigned      */
  /*    them to a window at the appropriate time.                          */
  /*                                                                       */
  CPW_API bool 
  cpwRemoveMenuItem( pCpw cpw, 
                     uint_32 menu, 
                     uint_32 entryid );
  /*                                                                       */
  /*************************************************************************/

  /* assigning menus to windows */

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwAssignMenuToWindow                                              */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Assigns a top level menu to a window's titlebar and displays       */
  /*    it. Once a menu is assigned, menu selections will generate         */
  /*    callbacks. Note that the callback function handler receives        */
  /*    three parameters, the 'windowid', the 'menuid' and the 'entryid'.  */
  /*    The window id is the id of the window the menu was selected in.    */
  /*    (You can assign a single menu to multiple windows.) The menuid     */
  /*    is the menu identifier of the top level menu containing all        */
  /*    entries and sub menus. Sub menu identifiers are not sent to the    */
  /*    callback, only top level menu identifiers. When creating sub       */
  /*    menus, make sure your entry identifiers are unique across all      */
  /*    entries in the top level menu the sub menu is contained within.    */
  /*                                                                       */
  /*    To seamlessly replace an entire menu, assign the new menu to       */
  /*    the window while the old menu is still in place.                   */
  /*                                                                       */
  CPW_API bool 
  cpwAssignMenuToWindow( pCpw cpw, 
                         uint_32 menuid, 
                         uint_32 winid );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwUnassignMenu                                                    */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Removes a titlebar menu from a window. Does not destroy the        */
  /*    resources associated with the menu and it's sub menus.             */
  /*                                                                       */
  CPW_API bool 
  cpwUnassignMenu( pCpw cpw, 
                   uint_32 winid );
  /*                                                                       */
  /*************************************************************************/

  /* attaching menus to buttons */

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwAttachMenuToButton                                              */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Assigns a popup menu to a particular mouse click for the           */
  /*    specified window. Use the standard cpw mouse button constants      */
  /*    for 'button'. 'winid' must be a valid window identifier. You       */
  /*    can attach a single menu to more than one window, and to more      */
  /*    than one mouse click.                                              */
  /*                                                                       */
  CPW_API bool 
  cpwAttachMenuToButton( pCpw cpw, 
                         uint_32 menuid, 
                         uint_32 button, 
                         uint_32 winid );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwDetachMenu                                                      */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Removes a popup menu button assignment for a particular window.    */
  /*                                                                       */
  CPW_API bool 
  cpwDetachMenu( pCpw cpw, 
                 uint_32 button, 
                 uint_32 winid );
  /*                                                                       */
  /*************************************************************************/

  /* item check marks */

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwCheckMenuEntry                                                  */
  /*                                                                       */
  /* <Description>                                                         */
  /*    If the menu entry is not checked, adds a check mark to             */
  /*    the entry. 'menuid' can only be a top level menu identifier.       */ 
  /*    sub menu identifiers will not work.                                */
  /*                                                                       */
  /*    For platforms which do not support checkmarked menus, the          */
  /*    checkmark will not be displayed. The checkmark's state is          */
  /*    tracked internally by Cpw and is valid regardless.                 */
  /*                                                                       */
  CPW_API bool 
  cpwCheckMenuEntry( pCpw cpw, 
                     uint_32 menuid, 
                     uint_32 entryid );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwUncheckMenuEntry                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    If the menu entry is checked, removes a check mark from            */
  /*    the entry. 'menuid' can only be a top level menu identifier.       */
  /*    sub menu identifiers will not work.                                */
  /*                                                                       */
  CPW_API bool 
  cpwUncheckMenuEntry( pCpw cpw, 
                       uint_32 menuid, 
                       uint_32 entryid );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Function>                                                            */
  /*    cpwMenuEntryChecked                                                */
  /*                                                                       */
  /* <Description>                                                         */
  /*    Returns a flag indicating whether or not the entry has a           */
  /*    checkmark. 'menuid' can only be a top level menu identifier.       */
  /*    sub menu identifiers will not work.                                */
  /*                                                                       */
  CPW_API bool 
  cpwMenuEntryChecked( pCpw cpw, 
                       uint_32 menuid, 
                       uint_32 entryid );
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /*   internal functions                                                  */
  /*                                                                       */
  /*************************************************************************/

#ifdef CPW_INTERN

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwMenuEntry                                                       */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A structure used in storing a single menu entry.                   */
  /*                                                                       */
  struct _CpwMenuEntry 
  {
      uint_32 id;
      pStr    title;
      bool    f_seperator;
      bool    f_checked;
      bool    f_submenu;
      pVoid   submenu;
  };
  typedef struct _CpwMenuEntry CpwMenuEntry;
  typedef struct _CpwMenuEntry* pCpwMenuEntry;
  /*                                                                       */
  /*************************************************************************/

  /*************************************************************************/
  /*                                                                       */
  /* <Struct>                                                              */
  /*    CpwMenu                                                            */
  /*                                                                       */
  /* <Description>                                                         */
  /*    A structure used in storing a menu and it's entries.               */
  /*                                                                       */
  struct _CpwMenu
  {
      uint_32         id;
      uint_32         ecount;
      pCpwMenuEntry   entries[CPW_MENUS_MAXENTRIES];
      CpwMenuCallback callback;
  };
  typedef struct _CpwMenu CpwMenu;
  typedef struct _CpwMenu* pCpwMenu;
  /*                                                                       */
  /*************************************************************************/

  /* init and exit */

  bool cpw_menus_init( pCpw cpw );
  void cpw_menus_exit( pCpw cpw );

  /* called by cpw_event when a popup menu should be displayed */

  void cpw_menus_popupselected( pCpw cpw, pCpwWin window, uint_32 menuid, uint_32 x, uint_32 y );

  /* called by cpw_event when a popup menu entry is selected */

  void cpw_menus_popupcallback( pCpw cpw, uint_32 id, uint_32 menuid, uint_32 entryid );

#endif /* CPW_INTERN */

CPW_END_HEADER

#endif
