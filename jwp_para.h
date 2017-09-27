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
//  This modlue contains the paragraph class and some support routines.
//  This was all moved here from the the modlues jwp_file.cpp and 
//  jwpce.cpp to keep it collected.
//
#ifndef jwp_para_h
#define jwp_para_h

#include "jwp_file.h"
//--------------------------------
//
//  Struct line.
//
//  Spefies a line break within a paragraph.
//
// Individual line
typedef struct Line {
// Offset of fist kanji for line.
  int          first;
// Length of line
  int          length;
// Next and previous lines
  struct Line *next,*prev;
} Line;

//--------------------------------
//
//  Class Paragraph.
//
//  Class defines a paragraph (basic unit of editor) and the operations
//  that can be perfomred on it.
//
// Paragraph element
class Paragraph {
friend class Position;
friend class JWP_file;
friend class JWP_search;
public:
// Unquied constructor.
  Paragraph ();
// Destructor.
 ~Paragraph ();
// Fast add a character used only during file reads
  void        add_char   (int ch);
// Delete character from the paragraph.
  void        del_char   (class JWP_file *file,Line *line, int pos);
// Insert character
  void        ins_string (class JWP_file *file,Line *line, int pos, KANJI *string, int len);
  void        rep_char   (class JWP_file *file,Line *line, int pos, int ch);
private:
// include buffer allocation.
  int         alloc      (void);
// Copy part of this paragraph to the clipboard.
  int         add_to_clip(int start,int end);
// Copy entire paragraph to this paragraph.
  int         copy_para  (Paragraph *para);
// Copy formating infomation form aother paragraph.
  void        copy_format(Paragraph *para);
// Pargaraph format.
  void        format     (class JWP_file *file,Line *line,int redraw);
// x-pixal location of the start of a line.
  int         line_start (Line *line);
// Add line pointer to end of file.
  Line       *new_line   (void);
// Set entire text buffer.
  int         set_text   (KANJI *data,int len);
// Pointers to next & previous paragraph.
  class Paragraph *next, *prev;
// First and last line.
  struct Line     *first, *last;
// Actual text for paragraph (all of it).
  KANJI           *text;
// Allocation length of pharagrph buffer.
  int              size;
// Number of characters in text line.
  int              length;
// Line spaceing in units of 100.
  short            spacing;
// Indicates this is a page break.
  unsigned char             page_break;
// Margin settings in KANJI units.
  unsigned char             indent_left, indent_right;
// Offset for first line of paragraph.
  signed char      indent_first;
};

#endif
