//===================================================================//
//                                                                   //
//  JWPce Copyright (C) Glenn Rosenthal, 1998-2004, 2005             //
//                                                                   //
//  JWPce is free sotware distributed under the terms of the         //
//  GNU General Public License.                                      //
//                                                                   //
//===================================================================//

#ifndef jwp_prnt_h
#define jwp_prnt_h
#include "jwp_font.h"

//
//  This structure describes the setup of a page.  This includes margins,
//  printing options (vertical, and landscape).  There is such a class
//  assocated with each file, and a general one that is defined as 
//  used for the default settings.
//
typedef class PageSetup {
public:
// Margins in inches.
  float left,right,top,bottom;
// vertical printing
  unsigned char  vertical;
// Landscape page
  unsigned char  landscape;
// Calculate width of printed page in kanji.
  int print_width (void);
} PrintSetup;

//
//  This class describes the context in which printing will occure.
//  The class contains basic elements such as the size of the page,
//  resolution, offset positions, and various other parameters.
//
typedef class PrintContext {
public:
// Physical dimensions of the printer.
  int   xmax,ymax;
// Printer resolution.
  short xdpi,ydpi;
// Printable page area (with margins included)
  int   height,width;
// Character sizes with space around the chracter
  short kwidth,kheight;
// Pixal size of the character font (not space)
  short fwidth,fheight;
// Offsets to get the render potion of the page.
  int   xoffset,yoffset;
// Shift for rendering kanji characters.
  short xshift;
// Width of the page in characters.
  short char_width;
// Kanji font for rednering.
  KANJI_font *font;

  void setup   (HDC hdc,PageSetup *ps);
// Constructor
  PrintContext (void);
} PrintContext;
// Global print context (default settings)
extern PrintContext print_context;
// Intialize printing parameters.
extern void initialize_printer (PageSetup *ps);

#endif
