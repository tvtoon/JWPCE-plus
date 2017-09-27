//===================================================================//
//                                                                   //
//  JWPce Copyright (C) Glenn Rosenthal, 1998-2004, 2005             //
//                                                                   //
//  JWPce is free sotware distributed under the terms of the         //
//  GNU General Public License.                                      //
//                                                                   //
//===================================================================//

#ifndef jwp_main_h
#define jwp_main_h

// Definition of sscanf() is here, but CE does not have this file
#ifndef WINCE
#include <cstdio>
#endif
// Defintions for UNIX WINELIB
#include <cstdlib>
//#include <ctype>
#define stricmp strcasecmp
#define strnicmp strncasecmp
/*
#define CC_ANYCOLOR 0x100
#define CC_SOLIDCOLOR 0x80
#define CF_UNICODETEXT 99
*/

// Necessary to get wheel-mouse defintions.
#ifdef _WINDOWS
//#define _WIN32_WINNT    0x0401
#include <tchar.h>
#include <windows.h>
#endif

// Windows CE stuff
#ifdef WINCE
#include "jwp_wnce.h"
#endif
// Sets some major compile time options.
#include "jwp_options.h"
// Get the resource parameters for everyone
#include "resource.h"

//===================================================================
//
//  Degugging stuff
//

//#define DEBUG_ROUTINES

#ifdef __DEBUG__
extern void dprintf (TCHAR *format,...);
extern void mprintf (TCHAR *format,...);
 #define DPRINTF   dprintf
 #define MPRINTF   mprintf
#else
 #define DPRINTF   (true ? (void) 0 : wsprintf )
 #define MPRINTF   (true ? (void) 0 : wsprintf )
#endif

/* GAMBIT!*/
#ifdef _WIN64
#define GWL_ID GWLP_ID
#define GWL_USERDATA GWLP_USERDATA
#define DWL_USER DWLP_USER
#endif

//===================================================================
//
//  General definitions.
//
// Size of general working character buffer.
#define SIZE_BUFFER     512
// Version special is defined in options and includes special flags.
// Size of a working string (smaller than a buffer).
#define SIZE_WORKING    256
// Define the special ID if not already.  Used for special versions.
#ifndef VERSION_SPECIAL
#define VERSION_SPECIAL
#endif
// Version ID number
#define VERSION_STRING  TEXT("1.50") VERSION_SPECIAL
// Version name.
#define VERSION_NAME    TEXT("JWPce ") VERSION_STRING
// Input modes
// Kanji (kana too)
#define MODE_KANJI      0
// ASCII
#define MODE_ASCII      1
// Japanese ASCII.
#define MODE_JASCII     2
// Toggles between ASCII and kanji.
#define MODE_TOGGLE     10
// Cycles through all modes.
#define MODE_CYCLE      11
// Does the updage associated with a mode change but does not change the mode
#define MODE_NOCHANGE   13
// Windows globals.
// Main window (parent).
extern HWND      main_window;
// Ediging window (main child).
extern HWND      file_window;
// Our instance.
extern HINSTANCE instance;
// Language processor instance.
extern HINSTANCE language;
// Our menu.
extern HMENU     hmenu;
// Our popup menu.
extern HMENU     popup;
// File menu in the button bar.
#ifdef WINCE_POCKETPC
extern HMENU     hmenu2;
#endif
// Various sizes (mostly used in relation to JWP structures).
typedef short           INT16;
typedef unsigned short  UINT16;
typedef UINT16          KANJI;
typedef unsigned short  ushort;
typedef unsigned long   ulong;
typedef const TCHAR     tchar;
// Used to set handles to zero, clarifies memory refferences.
#define null            0

//
//  Menu defintiions, in order (need to be used in both jwpce.cpp, and jwp_file.cpp).
//
#if  (defined(WINCE_PPC) || defined(WINCE_POCKETPC))
// Menu number for File menu.
#define MENU_FILE                         0
// Menu number for recent files list.
#define MENU_RECENT                       10
#elif defined(WINCE_HPC)
// Menu number for File menu.
#define MENU_FILE                         0
// Menu number for recent files list.
#define MENU_RECENT                       9
#else
// Menu number for File menu.
#define MENU_FILE                         0
// Menu number for recent files list.
#define MENU_RECENT                       13
#endif
// Menu number for the Window number
#define MENU_WINDOW                         4
// Menu index for the first file name in the Windows menu.
#define MENU_WINDOW_FILE_BASE               4

//
//  Custom window message values.
//
// Used to set control value for all working windows.
#define WMU_SETWINDOWVALUE  (WM_USER+1)
// Used to get structrues behind windows controls.
#define WMU_GETWINDOWVALUE  (WM_USER+2)
// Message from color box control indicating it is selected.
#define WMU_COLORCHANGE     (WM_USER+3)
// Internal message used to requrest kanji information in mouse handler.
#define WMU_KANJIINFO       (WM_USER+4)
// Request control to load selected data
#define WMU_LOADCONTROL     (WM_USER+5)
// Japanese list box control find beginning of entry.
#define WMU_JLBC_BEGIN      (WM_USER+6)
// Insert data from list box to file.
#define WMU_JLBC_INSERT     (WM_USER+7)
// Set text in a Japanese edit control
#define WMU_SETTEXT         (WM_USER+8)
// Get text from a Japanese edit/list control
#define WMU_GETTEXT         (WM_USER+9)
// Reset a Japanese List control
#define WMU_RESETLIST       (WM_USER+10)
// Set selection in Japanese List control
#define WMU_SETSELECT       (WM_USER+11)
// Set exclusion file used for inserts
#define WMU_SETEXCLUDE      (WM_USER+12)
// Message sent to non-modal dialog boxes before they are destroyed
#define WMU_OKTODESTROY     (WM_USER+13)
// User is typing into the list box.
#define WMU_CHARFROMLIST    (WM_USER+14)
// User has enetered edit commands into the list box.
#define WMU_EDITFROMLIST    (WM_USER+15)
// User is typing text via the IME into the list box.
#define WMU_IMEFROMLIST     (WM_USER+16)
// Set the history used with a Japanese edit control
#define WMU_SETHISTORY      (WM_USER+17)
// Generate a history list for this list.
#define WMU_HISTORYLIST     (WM_USER+18)
// Set the character used for the kanji info (used in single window system)
#define WMU_SETINFOKANJI    (WM_USER+19)

//
//  Timers used.
//
// Timer used for auto-scroll
#define TIMER_AUTOSCROLL    1
// Timer used for mouse hold events.
#define TIMER_MOUSEHOLD     2

#ifndef DOUBLE_X
#define DOUBLE_X  GetSystemMetrics(SM_CXDOUBLECLK)
#endif

#ifndef DOUBLE_Y
#define DOUBLE_Y  GetSystemMetrics(SM_CYDOUBLECLK)
#endif


//===================================================================
//
//  Configuration defintiions
//
// Pointer to configuration used
extern struct cfg *cfg;
// Default config stucture definines the default condition.
extern struct cfg  default_config;

//===================================================================
//
//  Exported routines.
//
// Add a modeless dialog to the system list
extern void add_dialog    (HWND hwnd,int closeable);
// Remove a mdoeless dialog from the system list.
extern void remove_dialog (HWND hwnd);
// Sets the current edit mode.
extern void set_mode      (int mode);

#endif
