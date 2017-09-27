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
//  This modlue manages the status bar and the toolbar
//
#ifndef jwp_stat_h
#define jwp_stat_h

//===================================================================
//
//  class JWP_stat.
//
//  This class manages the status bar.
//

class JWP_stat {
public:
// Height of the status bar.
  short height;
// Adjust size of satus window.
  void  adjust     (HWND hwnd);
// Process mouse commands.
  void  do_mouse   (LPARAM lParam);
// Called only by window proc (actual draw).
  void  draw       (HDC hdc);
// Intialize the status bar.
  int   initialize (WNDCLASS *wclass);
// Invalidate window (force a redraw).
  void  redraw     (void);
// Update text message and force redraw.
  void  update     (char *text);
private:
// Buffer to store text message.
  char  buffer[10];
// Y offset for rendering text.
  short offset;
// X location of the insert/overwrite flag.
  short x_insert;
// X location of mode flag.
  short x_mode;
// X location of the file type.
  short x_type;
// X location of text messages.
  short x_text;
// X vound for mouse events (INS/OVR)
  short x_imouse;
// X bound for mouse events (mode).
  short x_mmouse;
// Made public for Windows CE support.
public:
// Handle for window.
  HWND  window;
};
// Instance of class.
extern class JWP_stat jwp_stat;

//===================================================================
//
//  Begin class JWP_tool.
//
//  This class processes the toolbar used in Windows (not CE). 
//
//  Key to understanding the toolbar is the strage of tool buttons.  Each
//  button is assigned a number (the value of zero is used for separators).
//  The buttons are stored in an array buttons[] in the cfg structre of the 
//  JWP_config class.  The field button_count indicates the number of 
//  buttons.
//
//  If the button_count is zero, the button array is initialize to the
//  default values.  This allows older systems to automatically pick up the 
//  default button bar.
//
//  Whenever the button bar is created, it is created by adding the buttons
//  from the buttons array.  Whenever it is removed, the buttons are read out
//  and stored back in the array.
//
//  The array can currently store 100 buttons (counting seperators).
//
//  The button numbers are stored in the dwData field of the button structrue.
//  This is also used to access the tips for the button (addjusted by a 
//  value of 1).
//
// Button ID's for the buttons, indicates index into buttons array.
#define BUTTON_SEPARATOR    0
#define BUTTON_FILENEW      1
#define BUTTON_FILEOPEN     2
#define BUTTON_FILESAVE     3
#define BUTTON_FILEDELETE   4
#define BUTTON_FILEPRINT    5

#define BUTTON_UNDO         6
#define BUTTON_REDO         7
#define BUTTON_KANJI        8
#define BUTTON_ASCII        9
#define BUTTON_JASCII       10
#define BUTTON_CUT          11
#define BUTTON_COPY         12
#define BUTTON_PASTE        13
#define BUTTON_SEARCH       14
#define BUTTON_REPLACE      15
#define BUTTON_NEXT         16
#define BUTTON_REVERSE      17

#define BUTTON_CONVERT      18
#define BUTTON_GETINFO      19
#define BUTTON_RADLOOKUP    20
#define BUTTON_BUSHULOOKUP  21
#define BUTTON_BSLOOKUP     22
#define BUTTON_SKIPLOOKUP   23
#define BUTTON_HSLOOKUP     24
#define BUTTON_FCLOOKUP     25
#define BUTTON_READLOOKUP   26
#define BUTTON_INDEXLOOKUP  27
#define BUTTON_JISTABLE     28
#define BUTTON_COUNTKANJI   29
#define BUTTON_COLORKANJI   30

#define BUTTON_FORMATFILE   31
#define BUTTON_PARAGRAPH    32
#define BUTTON_PAGELAYOUT   33
#define BUTTON_DICTIONARY   34
#define BUTTON_KANJICONVERT 35
#define BUTTON_OPTIONS      36
// Toolbar is only used for Windows, Wincows CE uses a command bar.
#ifndef WINCE

class JWP_tool {
public:
  inline JWP_tool (void) { window = null; return; }
// Responds to window size changes.
  void adjust     (void);
// Changes the check state of a button
  void check      (int id,int state);
// Invokes the customize toolbar dialog
  void customize  (void);
// Enables/disables a button.
  void enable     (int id,int state);
// System wants information on avaialbe buttons (for customize)
  int  info       (NMHDR *pnmh);
// This process the general creation and destuction fo the tool bar.
  void process    (int exit);
// Set toolbar buttons to the default.
  void reset      (void);
// Get tooltip associated with a button.
  int  tip        (NMHDR *pnmh);
private:
// Pointer to toolbar.
  HWND window;
};
// Class instance.
extern class JWP_tool jwp_tool;

#endif

#endif
