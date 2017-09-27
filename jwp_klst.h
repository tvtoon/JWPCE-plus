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
//  This modlule implements a knaji list window.  This is bascially 
//  the same window used for the kana->kanji conversion and for the 
//  results of a kadical lookup conversion.  This is bascially a 
//  horizontal strip of kanji/(kana) compounds seperated by spaces.
//  The routines here implement omost of the functionality of processing
//  window events, and selecting items.  It is left to the derived 
//  classes JWP_conv, and RADICAL_lookup to actually put contents 
//  back into a file, and procedue data.
//

#ifndef jwp_klst_h
#define jwp_klst_h

#include "jwp_file.h"

#ifdef WINELIB
  #define _virt_    virtual
#else
  #define _vert_    
#endif

//===================================================================
//
//  Parameters for routines.
//
// Parameters for KANJI_list::do_select() and JWP_file::convert().
// Shift conversion to right.
#define KANJILIST_RIGHT   0
// Shift conversion to left.
#define KANJILIST_LEFT    1

class KANJI_list {
public:
  KANJI_list (int count = 1000);
  _vert_ ~KANJI_list (void);
// Adjust display parameters.
  void  adjust       (HWND hwnd);
// Clear conversion system
  void  clear        (void);
// Process mouse messages.
  void  do_mouse     (LPARAM lParam);
// Process scroll bar messages.
  void  do_scroll    (int message);
// Do wheel-mouse events.
  void  do_wheel     (WPARAM wParam);
// Render conversion bar.
  void  draw         (HDC hdc);
// Gets info for the selected character.
  void  get_info     (HWND hwnd);
// Returns index of last compound.
  int   last         (void);
// Returns the length of an kanji string.
  int   len          (int pos);
// Get index of next kanji compound.
  int   next         (int pos);
// Put character into the buffer.
  int   put_kanji    (int kanji);
// Get index of previous kanji compound.
  int   prev         (int pos);
// Force redaw of the kanji bar.
  void  redraw       (void);
// Calculate scroll and display parameters.
  void  set_scroll   (int draw);
// Select a kanji conversion and insert into file.
  virtual void select(int s);
// Context for replacement. (used only for convert routines)
  JWP_file    *file;
//
//  Window display parameters.
//
// Window pointer.
  HWND         window;
// Height of the conversion bar.
  short        height;
// display width (pixal).
  short        width;
// Amount of horizontal space to separate entries in the kanji list.
  short        blank_space;
// Y offset for rendering kanji in the bar.
  short        y_offset;
//
//  List parameters.
//
// The list.
  KANJI       *list;
// Size of the list
  short        size;
// Number of characters in the list.
  short        list_len;
// Index of first kanji to be shown.
  short        first;
// Index to selected kanki.
  short        selected;
// Index of character user clicked on.  This is used for kanji info.
  short        sel_char;
// X pixal length of the entire list.
  int          x_total;
// X pixal location of first.
  int          x_first;
// Specifies the location of the invert box for the slected conversion.
  RECT         sel;
private:
// Advance to next character
  int  hadvance      (int x,int ch);
// Advance the first marker.
  int  next_first    (void);
};

typedef class KANJI_list KANJI_list;

#endif
