//===================================================================//
//                                                                   //
//  JWPce Copyright (C) Glenn Rosenthal, 1998-2004, 2005             //
//                                                                   //
//  JWPce is free sotware distributed under the terms of the         //
//  GNU General Public License.                                      //
//                                                                   //
//===================================================================//

//===================================================================//
//
//  This modlues main function is to deal with the system fonts.  
//  There are three fonts used in the system currently.  These are
//  the kana/kanji font.  The user font used in the main edit window,
//  and the system font used in controls, and in the status bar.  
//  Various useful parameters are caclated buy the font system for use
//  by other routines.  The system currenly allows for changes in the 
//  fonts, buf these are relativly limited.  
//
//  Since in the current version, printing is not supported, only the 
//  16x16 kanji font is loaded.  When printing, or higher reslution
//  screens are used, support for additional font can easily be added.
//
#ifndef jwp_font_h
#define jwp_font_h

//#include "jwp_prnt.h"               // We need this for the definition of the print structures

//===================================================================//
//
//  Exported definitons.
//
// This constaint is only defined in Win CE 2.11 and
// up.  We support TrueType fonts for all versions, but
// must check for Japanese fonts.
#ifndef SHIFTJIS_CHARSET
  #define SHIFTJIS_CHARSET 0x80
#endif
// Type for a kanji/kana character.
typedef unsigned short KANJI;
// Allows only the F16X16.F00 kanji font.  This allows some optimizations.
//#define ONLY_16

//-------------------------------------------------------------------
//
//  class KANJI_font.
//
//  This class contains information related direclty to a specific
//  kanji font.
//

//--------------------------------
//
//  This is a virtual font class.  This class cannot be used directly, but must be used
//  to define a veritual class for the type of font that you want.  Because the font 
//  parameters differ so radically, different open versions for each font type are used.
//  The current routine open_bitmap() and open_font() provide uniformed ways to open the
//  fonts.
//
class KANJI_font {
public:
// height and witdth of font
  short width,height;
// Vertial gaps between lines
  short leading;
// Horizontal gaps between characters.
  short spacing;
// Indicates this is a TrueType font.
  unsigned char  truetype;
// Vertical font.
  unsigned char  vertfont;
// Render character
  void  virtual draw       (HDC hdc,int jis,int x,int y) = 0;
// Used to make big kanji.
  void  virtual fill       (HDC hdc,int jis,RECT *rect) = 0;
// Find a kanji.  Load the kanji from disk if necessary
  void          find_color (int jis,HDC hdc,COLORREF &color);
// Convert jis code to font code.
  int   virtual jis_index  (int jis) = 0;
// Deallocate this font and clean up.
  void          remove     (void);
private:
// Close the font
  void  virtual close      (void) = 0;
};

//--------------------------------
//  
//  This dirived class processes bitmaped fonts
//
class BITMAP_KANJI_font : public KANJI_font {
public:
  BITMAP_KANJI_font (void);
// Render character
  void  draw        (HDC hdc,int jis,int x,int y);
// Used to make big kanji.
  void  fill        (HDC hdc,int jis,RECT *rect);
// Convert jis code to font code.
  int   jis_index   (int jis);
// Open the font.
  int   open        (TCHAR *name,int cache,int vertical);
private:
// Closes a font.
  void  close       (void);
// Find a kanji.  Load the kanji from disk if necessary
  int   find_kanji  (int index, HDC hdc, COLORREF &color);
// Indicates font has holes.
  short   holes;
// Shift used in redering characters.
  short   hshift;
// Size of bitmap in memory unsigned chars (per character).
  short   bmsize;
// Size of bitmap in file unsigned chars (per character).
  short   bmfilesize;
// Font's bitmap data
  char   *bitmaps;
// Font cache.
  KANJI  *cache;
// Next bitmap to replace in the font cache.
  short   index;
// Memory HDC used for rendering the bitmaps.
  HDC     hdcmem;
// Pointer to file (used only for cached fonts).
  HANDLE  file;
// CE does not support SetBitmapBits so cannot use this.
#ifndef WINCE
// Bitmap for bit operations
  HBITMAP hbitmap;
#endif
};

//--------------------------------
//
//  This dirived class processes TrueType fonts.
//
class TRUETYPE_KANJI_font : public KANJI_font {
public:
  TRUETYPE_KANJI_font (void);
// Render character
  void  draw          (HDC hdc,int jis,int x,int y);
// Used to make big kanji.
  void  fill          (HDC hdc,int jis,RECT *rect);
// Convert jis code to font code.
  int   jis_index     (int jis);
// Open the font.
  int   open          (HDC hdc,tchar *name,int cache,int vertical);
private:
// Closes a font.
  void  close         (void);
// TrueType font structure.
  HFONT   font;
// Shift used in redering characters.
  short   hshift;
// Vertical shift for rendering characters
  short   vshift;
// Windows CE does not use gylph addressing for TrueType fonts
#ifndef WINCE
// Copy of the cmap structure for this font.
  char   *cmap;
// GSUB structre for this font, used for viertical glyph replacemnt
  char   *gsub;
// Number of entries in the cmap subtable.
  ushort  count;
// Start table for ranges
  ushort *start;
// End table for ranges
  ushort *end;
// Delta table for displacements
  ushort *delta;
// Offest table for entriesinto the glyph table
  ushort *offset;
// Glyph table.
  ushort *glyph;
// Number of vertical replacement glyphs
  ushort  vcount;
// Glphys to be replaced.
  ushort *from;
// replacement glyphs.
  ushort *to;
#endif
};

//-------------------------------------------------------------------
//
//  This is the main class for font work.  Each JFC_font object contains all
//  the information necessary to render text in a particular font.  All spacings
//  and other settings are contained in the class as well as the ASCII font 
//  metrics.  
//
//  Each JFC_font object really constists of a kanji font and an ASCII font pair,
//  plus all the support information.  
//
//  JFC_font objects can contain dupicates of open fonts.  This makes things more
//  efficient.  They are flaged by the duplicate member.
//
class JWP_font {
public:
// Kanji font height
  short height;
// Kanji nominal character-character spcaking.
  short hwidth;
// Top of rectange around kanji font (used a lot in redraw, and selecting).
  short rheight;
// Kanji nominal line-line spacing.
  short vheight;
// Height used in list boxes.
  short lheight;
// Offset for rending line of text in list box.  (Only used once, but pre-calculated for speed)
  short loffset;
// Height of caret (cursor)
  short cheight;
// Vertical extra space measure (framing around window).
  short vspace;
// Horizontal extra space meauser (framing around window).
  short hspace;
// Horizontal offset for rendering text (leaves a small borer on left side). [Parameter used by the JFC_file class]
  short x_offset;
// Vertical offset for rendering of text from top of screen. [Parameter used by the JFC_file class]
  short y_offset;
// Vertical printing font.
  short vertical;
// Indicates that the font is actually a duplicate of another font, so don't deallocate.
  unsigned char  duplicate;
// Ascii font.
  HFONT       ascii;
// Kanji font.
  KANJI_font *kanji;
// Close the font.
  void  close      (void);
// Duplicates a particular font.
  void  copy       (class JWP_font *font);
// Advance a cursor horizontaly by a single character.
  int   hadvance   (int x,int ch);
// Open and initialize the font.
  int   open       (TCHAR *name,int size,int cache,HDC hdc,int vert);
// Open an ascii font.
  HFONT open_ascii (tchar *face);

  inline JWP_font (void) { ascii = NULL; kanji = NULL; duplicate = false; }
private: 
// Holds the char widths in pixels, for the pirmary ASCII.
  short widths[256];
};

//-------------------------------------------------------------------
//
//  class COLOR_kanji.
//
//  Manages the color kanji list.
//
//  The basics of the color kanji list is an array containning one unsigned char for
//  each kanji.  If the unsigned char is set the kanji is in the list.  If it is not 
//  set the kanji is not in the list.
//
// Max number of kanji we allow in the list.
#define MAX_KANJI   6450

class COLOR_kanji {
public:
// Initialize.
  inline COLOR_kanji (void) { clear(); return; }
// Add a character to the list.
  int  add       (int ch);
// Clear the list.
  void clear     (void);
// Count the number of kanji in the list.
  int  count     (void);
// Does the add & remove kanji from list dialog
  void do_adddel (void);
// Is a character in the list.
  int  in        (int ch);
// Add the color kanji into the current file.
  void put       (void);
// Read list from a file.
  void read      (void);
// Remove a character from the color kanji list.
  int  remove    (int ch);
// Write the list to a file.
  int  write     (void);
private:
// One unsigned char for each character.
  unsigned char data[MAX_KANJI+10];
};

//-------------------------------------------------------------------
//
//  Exported data
//
// Font used for posting bitmaps on the clipboard.
extern class JWP_font clip_font;
// Font used for kanji bars.
extern class JWP_font bar_font;
// Font used for file information.
extern class JWP_font file_font;
// Font used for system data (bushu, JIS table, etc).
extern class JWP_font sys_font;
// Font used for line edit
extern class JWP_font edit_font;
// Font used for lists.
extern class JWP_font list_font;
// Height of the system font (used for toolbars).
extern short sysfont_height;

extern class COLOR_kanji color_kanji;

//-------------------------------------------------------------------
//
//  Exported routines.
//
// Draw an ASCII (or extended ASCII character)
extern void        ascii_draw       (HDC hdc,int x,int y,int ch);
// Get width of ASCII character.
extern int         ascii_width      (HDC hdc,int ch);
// Cleanup routine to close all open fonts.
extern void        free_fonts       (void);
// Routine to get the big font.
extern KANJI_font *get_bigfont      (RECT *rect);
// Get font for use in the JIS table
extern KANJI_font *get_jistfont     (void);
// Routine to get a printer font of a given height.
extern KANJI_font *get_printfont    (HDC hdc,int vertical);
// Setup the fonts system and intiailize.
extern int         initialize_fonts (void);

#endif
