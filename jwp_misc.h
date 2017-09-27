//===================================================================//
//                                                                   //
//  JWPce Copyright (C) Glenn Rosenthal, 1998-2004, 2005             //
//                                                                   //
//  JWPce is free sotware distributed under the terms of the         //
//  GNU General Public License.                                      //
//                                                                   //
//===================================================================//

//===================================================================
//
//  This modlue is a collection of micelaeous routines not placed 
//  in any other module.
//
#ifndef jwp_misc_h
#define jwp_misc_h

#include "jwp_cach.h"

//--------------------------------
//
//  Structure used to save the size and location of a dialog.
//
struct size_window {
// Window position.
  int x,y;
// Window size.
  int sx,sy;
};

//--------------------------------
//
//  Class used to process size changes in dialogs.
//
class SIZE_window {
public:
// Contstructor
  SIZE_window    (void);
// Called in WM_INITDIALOG
  void wm_init   (HWND hwnd,int id,struct size_window *init,int buttons,int dfirst,int dlast);
// Called from WM_MOVE
  void wm_move   (void);
// Called from WM_SIZE
  void wm_size   (int wParam);
// Called from WM_SIZING
  void wm_sizing (RECT *rect);
private:
// Check the dynamic controls.
  void   check_controls  (void);
// First and last dynamic buttons.
  short  first,last;
// Indicates IDOK and IDCANCEL controls need to be moved.
  unsigned char   move_buttons;
// Pointer to saved file location (could be NULL)
  struct size_window *save;
// Minimum dialog size (also default)
  int    dlg_xmin,dlg_ymin;
// Minimum list control size.
  int    lst_xmin,lst_ymin;
// Default location of the control buttons
  int    btn_y;
// Pointer to list.
  HWND   list;
// Pointer to dialog.
  HWND   dlg;
};

//--------------------------------
//
//  This class defines a kanji string and the actions that can be done 
//  to it.  The base storage is simply a pointer to a NULL terminated 
//  kanji list.  The pointer is NULL when the string contains no data.
//
typedef class KANJI_string {
public:
  KANJI *kanji;
// Contstructor
  inline  KANJI_string() { kanji = NULL; }
// Destructor.
  inline ~KANJI_string() { free(); }
  inline  void set (class KANJI_string *ks) { set (ks->kanji); }
// Copy string to buffer with limit
  void   copy     (KANJI *string,int limit);
// Deallocate resources.
  void   free     (void);
// Get from edit box.
  void   get      (HWND hwnd,int id);
// Get length
  int    length   (void);
// Put in edit box.
  void   put      (HWND hwnd,int id);
// Read from file
  int    read     (IO_cache *cache);
// Set to specific value.
  void   set      (KANJI *k,int len = -1);
// Write to file.
  int    write    (IO_cache *cache);
// Transfer string without reallocating.
  void   transfer (class KANJI_string *ks);
} KANJI_string;

//--------------------------------
//
//  Scroll info
//
// Scroll Info structure used by allmost
//   all scroll bars in the system.
extern SCROLLINFO scroll_info;

//--------------------------------
//
//  Error & Message Rotuines..
//
// General Error Message.
extern void ErrorMessage (int error,int format,...);
// Out of Memory error.
extern void OutOfMemory  (HWND hwnd);
// Put up a simple yes-no dialog box.
extern int  YesNo        (int format,...);
// Generates a dialog box that terminates at the first button.
extern int  ButtonDialog (HWND hwnd,int idd,tchar *data,int help);
// Version of system routine to generate a non-modal dialog
extern HWND JCreateDialog(int id,HWND hwnd,DLGPROC proc, LPARAM param=0);
// Version of system routien to generate a dialog box.
extern int  JDialogBox   (int id,HWND hwnd,DLGPROC proc, LPARAM param=0);
// Extened version of system message routine.
extern int  JMessageBox  (HWND hwnd,int text,int caption,unsigned int type,...);

//--------------------------------
//
//  Memory allocation.
//
// Duplicate a kanji string in memory.
extern KANJI *kstrdup (KANJI *string,int length);

//--------------------------------
//
//  Tab dialog box controler
//
// Message sent to pages to read values out.
#define WM_GETDLGVALUES (WM_USER+1)
// Defines a page of a Tab Dialog box.
typedef struct TabPage {
// Label for page.
  short   text;
// ID of page template.
  int     id;
// Procedure for this page.
  DLGPROC procedure;
// Help id
  ushort  help;
} TabPage;

// Defines a tab dialog box.
typedef struct TabSetup {
// Pointer to array of TabPage structures.
  TabPage *pages;
// Number of pages in the above array.
  short    count;
// Current page.
  short    page;
// Dialog proc for user buttons on the main page.
  DLGPROC  procedure;
} TabSetup;

extern int TabDialog (int id,TabSetup *setup);

//--------------------------------
//
//  Debugging Routine.
//
// For searching for optimizer bugs.
// This routine is not actually anywhere, 
// so if you need it you need to define it.
extern void do_nothing      (void);

//--------------------------------
//
//  File name routines.
//
// Add part to a file name (used with open-files)
extern TCHAR *add_part   (TCHAR *buffer, TCHAR *part);
// Get a system folder path.
extern TCHAR *get_folder (int id,TCHAR *buffer);
// Check to see if a file exists
extern int    FileExists (tchar *name);

//--------------------------------
//
//  File IO routines.
//
// Generates a null terminate memory image of a file.
extern unsigned char *load_image (tchar *name);

//--------------------------------
//
//  Dialog box Routines.
//
// Get int value from edit control.
extern int  get_int     (HWND hwnd,int id,int min_val,int max_val,int def);
// Get a float value from buffer
extern int  get_float   (HWND hwnd,int id,float min_val,float max_value,float def,int scale,float *value);
// Put float value into a dialog box.
extern void put_float   (HWND hwnd,int id,float value,int scale);

//--------------------------------
//
//  Menu control routines.
//
// Get information from recent files menu
extern long get_menudata (HMENU menu,int item,int position,TCHAR *buffer);

#if    (defined(WINCE_PPC) || defined(WINCE_POCKETPC))
//--------------------------------
//
//  Class that manages the list of recent file names.
//
// Number of items in recent files list (must be 1 more then the actual values)
#define RECENT_MAX  10
// Maximum length of recent file name
#define RECENT_LEN  28
// Single line of the list.
typedef TCHAR RecentLine[256];

class RecentList {
public:
// Constructor
  RecentList::RecentList (void);
// Get an item
  inline TCHAR *get    (int pos) { return (list[pos]); }
// Insert a name into the list.
  void          insert (HMENU menu,int pos,TCHAR *text);
// Remove a name from the list.
  void          remove (HMENU menu,int pos);
private:
// Actual list.
  RecentLine list[RECENT_MAX];
};
// Class instance.
extern class RecentList recent_list;

 #define JInsertMenu(menu,pos,flags,item,text)    recent_list.insert(menu,pos,text)  
 #define JRemoveMenu(menu,pos,flags)              recent_list.remove(menu,pos)
#else
 #define JInsertMenu(menu,pos,flags,item,text)    InsertMenu(menu,pos,flags,item,text)
 #define JRemoveMenu(menu,pos,flags)              RemoveMenu(menu,pos,flags)
#endif


//--------------------------------
//
//  String table manipulation tools.
//
#define GET_STRING(b,id)        LoadString(language,id,b,(sizeof(b)/sizeof(TCHAR)))
#define LOAD_STRING(b,id,s)     LoadString(language,id,b,s)
// Get string and return in a pointer to a static buffer.
extern TCHAR *get_string    (int id);
// Foramt a string based on an
extern TCHAR *format_string (TCHAR *buffer,int id,...);
// Get a string an replace tab characters with ascii 0 (used for requestors).
extern TCHAR *tab_string    (int id,int id2 = 0);

//--------------------------------
//
//  Numerical tools
//
// Round float to integer.
#define NINT(x) ((int) ((x)+0.5))

//-------------------------------------------------------------------
//
//  Graphics IO routins.
//
//      Fills a rectangle with the current background color.
//      This used to be done with direct calls to FillRect,
//      with color arguments, however, Windows CE does not 
//      correctly support these calls, thus I replaced the 
//      calls with this routine.
//
#ifdef WINCE 
 #define BackFillRect(hdc,rect)    { HBRUSH brush; brush = (HBRUSH) SelectObject(hdc,CreateSolidBrush(GetSysColor(COLOR_WINDOW))); FillRect (hdc,rect,brush); DeleteObject(SelectObject(hdc,brush)); }
#else
 #define BackFillRect(hdc,rect)    FillRect (hdc,rect,(HBRUSH) (COLOR_WINDOW+1));
#endif

#endif
