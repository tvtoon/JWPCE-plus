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
//  This modlue is central to the program.  In this module most of the 
//  basic manipulations on a file are implemented.  This modlue includes 
//  complete implementations of the Paragraph class, Position class, 
//  JWP_view class and a large part of the  JWP_file class.
//
#ifndef jwp_file_h
#define jwp_file_h

#include "jwp_jisc.h"
#include "jwp_misc.h"
#include "jwp_para.h"
#include "jwp_prnt.h"
#include "jwp_undo.h"

//===================================================================
//
//  Begin Class JWP_view.
//
//  Class defines a basic file fiew window.  This is generally associated
//  with a list of JWP_file class, whcih contain the actual files being
//  editied.
// NULL


//===================================================================
//
//  class Position
//
//  Class defines a position within a file and a number of routines
//  that can operate on the class.  Positions are used for the cursor,
//  Upper left corner of the display (view_top), and selected regions
//  of the text.
//
// Position wintin the file
class Position
{
friend class JWP_file;
friend class Paragraph;
friend class JWP_search;
private:
// Pointer to paragraph
  class  Paragraph *para;
// Pointer to line
  struct Line      *line;
// Offset into line
  short             pos;
// Absolute offests of position.
  long              x,y;
// Convert to absolute position.
  void inline abs       (void) { pos += line->first; line = para->first; }
// Get absolute cursor position
  int  inline abs_pos   (void) { return (pos+line->first); }
// Move cursor forward or backward by count.
  void        advance   (int count);
// Align cursor to a specific pixal location.
  void        align     ( int x_pos,int mouse = FALSE);
// Move cursor up through the file.
  int         move_up   (void);
// Move cursor down through the file.
  int         move_down (void);
// Convert to relative position.
  void        rel       (void);
// Inline functions get_char() get character at cursor.  Others 
//   return locational flags, b=begin, e=end, l=line, p=paragraph, f=file
  int  inline get_char  (void) { return ((pos >= para->length) ? 0 : para->text[line->first+pos]); }
  int  inline bof       (void) { return (!pos && (line == para->first) && !para->prev); }
  int  inline eof       (void) { return ((pos >= line->length) && (line == para->last) && !para->next); }
  int  inline bol       (void) { return (!pos); }
  int  inline eol       (void) { return (pos >= line->length); }
  int  inline bop       (void) { return (!line->prev && !pos); }
  int  inline eop       (void) { return (!line->next && (pos >= line->length)); }
};

//===================================================================
//
//  struct Selection.
//
//  Defines the variables associated with the slected region.  This 
//  did not actually have to be separated, but it makes is easier to 
//  tell what is what.
//
// Selection types
// No selection
#define SELECT_NONE     0
// Standard window edit selection.
#define SELECT_EDIT     1
// Kanji conversion selection.
#define SELECT_KANJI    2
// Conversion in process.
#define SELECT_CONVERT  3

// Selection fixed codes.
// Fixed point is pos1
#define SELECT_FIX1     0
// Fixed point is pos2
#define SELECT_FIX2     1

// Size of some arrays.
// Number of lines in the summary.
#define NUMBER_SUMMARY      5
// Number of different headers.
#define NUMBER_HEADERS      4
// Number of positions per header.
#define NUMBER_POSITIONS    3
// Summary names.
#define SUMMARY_TITLE       0
#define SUMMARY_SUBJECT     1
#define SUMMARY_AUTHOR      2
#define SUMMARY_KEYWORDS    3
#define SUMMARY_COMMENT     4
// Flags for JWP_file::find_pos()
// Standard cursor position
#define POS_CURSOR          0
// View point position
#define POS_VIEW            1
// Cursor vertical only position
#define POS_VERT            2
// View point position vertical only
#define POS_VVERT           3
// Character codes for JWP_file::put_char()
// Continue current state.
#define CHAR_CONT           0
// Start kana->kanji conversion
#define CHAR_START          1
// Stop kana->kanji conversion
#define CHAR_STOP           2
// File reading errors
// No errror
#define FILEERR_OK          0
// Fatal file error, cannot be recovered from.
#define FILEERR_FATAL       1
// File has an error but is recoverable
#define FILEERR_ERROR       2
// Special flag indicating selection is with a mouse.
#define SEL_MOUSE           2

#define JWP_FONT    ((filetype == FILETYPE_EDIT) ? edit_font : file_font)
// Information for a selection.
typedef struct
{
// Positions for selection
  class Position pos1, pos2;
// Type marker for selection
  unsigned char           type;
// Indicates which point of the mark is fixed.
  unsigned char           fixed;
} Selection;

//===================================================================
//
//  Begin Class JWP_File.
//
//  This is the basic class that describes a file and all of it's parts.
//

class JWP_file
{
 friend class Position;
 friend class Paragraph;
 friend int close_file (int exit_ok);
 friend class JWP_search;
 friend class UNDO_type;
 friend class UNDO_newpara;
 friend class UNDO_delpara;
public:
// Links to other files
 class  JWP_file  *next,*prev;
// Defined in clipboard support functions
//JWP_file (int format_width);
// Defined in edit-box support routines.
//JWP_file (HWND hwnd);
// Defined in file io support rotuines
//JWP_file (tchar *name,int type);
 ~JWP_file (void);
 HWND  window;
//Process key.
 void        do_key         (int key,int ctrl,int shift);
// Process mouse.
 void        do_mouse       (int iMsg,WPARAM wParam,LPARAM lParam);
// Execute a memue command
 void        do_menu        (int wParam);
// Generate a popup menu.
 void        popup_menu     (int x,int y);
// Main draw routine.
 void        draw_all       (HDC hdc,RECT *bound);
// Process horizontal scroll messages.
 void        h_scroll       (int message);
// Process vertical scroll messages
 void        v_scroll       (int message);
// Move sursor to the left witht or whitout shift.
 void        left           (void);
// Move cursor to the right with or whithout shift.
 void        right          (void);
// File type (disk type).
 unsigned char        filetype;
//
//  Formatting commands.
//
// Adjust file for major changes.
 void        adjust         (void);
// Disable the display caret.
 void inline caret_off      (void) { DestroyCaret(); }
// Enable the display caret.
 void        caret_on       (void);
// Mark file as changed
 void        change         (void);
// Redraw entire file.
 void        redraw_all     (void);
// Redraw from this paragraph forward
 void        redraw_from    (Paragraph *para,Line *line);
// Redraw this paragraph
 void        redraw_para    (Paragraph *para,Line *line);
// Redraw range.
 void        redraw_range   (int pos1,Paragraph *para2,int pos2);
// Reforamt the file.
 void        reformat       (void);
// Set current display title.
 void        title          (void);
// Used to name special files that belong to the editor.
 void        sysname        (int id);
//
//  Routines for support of the the history buffer.
//
// Pointer to the history buffer if there is one.
 class JWP_history *history;
//
//  Undo/redo manipulation rotuines.
//
// Implements the Edit/Undo command.
 void        do_undo        (void);
// Implements the Edit/Redo command.
 void        do_redo        (void);
// End an undo chain.
 void        undo_end       (void);
// Allocates or reallocates an undo buffer for this file
 void        undo_init      (int old_length);
// Key routine that saves changes to a single paragraph.
 void        undo_para      (int id,Paragraph *para = NULL);
// Start an undo chain.
 void        undo_start     (void);
// Fake rotuine used when restoring data from 
 void        undo_undo      (UNDO_para *para);
private:
// Non-zero means that undo is accumulating characters
 unsigned char        undo_accum;
// List of undo lists.
 UNDO_action **undo;
// Convert number to paragraph.
 Paragraph  *number_to_para (int number);
// Convert paragraph to a number.
 int         para_to_number (Paragraph *para);
// Clear the redo buffer.
 void        redo_clear     (void);
// Clear state of accumulated undo if state does not match code.
 void        undo_clear     (int code = UNDO_NONE);
// Add a paragraph deletion undo action to the current chain.
 void        undo_delpara   (Paragraph *para);
// Update the state of the Edit/Undo and Edit/Redo menu items.
 void        undo_menu      (void);
// Generates a new undo chain.
 void        undo_new       (void);
// Add a paragraph additon undo action to the current chain.
 void        undo_newpara   (Paragraph *para);
// Undo an action and pop it from a list.
 void        undo_pop       (UNDO_action **list);
// Push and undo action into the current chain.
 void        undo_push      (UNDO_action *action);
// Save undo information for type/name change.
 void        undo_type      (void);
//
//  Paragraph manipulation rotuines.
//
// Process formmat paragraph dialog box.
public:
 int do_formatpara (HWND hwnd,unsigned int messag,int wParam);
private:
// Make a paragraph as a page break.
 void        set_page       (Paragraph *para,int page);
// Delete a paragraph.
 void        del_paragraph  (Paragraph *para);
// Generate a new paragraph after the indicated one.
 int         new_paragraph  (Paragraph *para);
//
//  Entry points for ascii->kana converter and kana->kanji converter.
//
public:
// Process keys
 void        do_char        (int ch);
// Put character into file from ascii->kana convert.
 void        put_char       (int ch,int code);
// Inserts a character from the IME.
 void        ime_char       (int ch,int unicode);
//
//  Support for Color-kanji (located in jwp_font.cpp)
//
// Does the count part of a kanji count.
 void        kanjicount     (void);
// Generate a kanji list from the current file.
 void        do_kanjilist   (void);
//
//  File IO support routines.
//
// Generall file constructor used for unnamed and named files
 JWP_file (tchar *name,int type,int recent=true);
// Activate this file.
 void        activate       (void);
// Close this file.
 int         close          (int exit_ok);
// Delete disk file associated with the current file.
 void        delete_file    (void);
// Write file to any non-JWP format
 long        export_file    (JIS_convert *cvrt);
// Revert to last loaded file.
 void        revert         (void);
// Save file.
 int         save           (tchar *name);
// Save with requestor
 int         save_as        (void);
// Write JWP file.
 long        write_jwp_file (IO_cache *cache);
private:
// Import file from any non-JWP format
 int         import_file    (JIS_convert *cvrt);
// Page setup dialog
 void        page_setup     (void);
// Print and print-setup.
 void        print          (int setup);
 void        print_heads    (HDC hdc,int head,int y,PrintContext *pc,int *widths,int page);
// Save the project
 int         project_save   (tchar *name);
// Restore the project
 void        project_read   (tchar *name);
// Read JWP file.
 int         read_jwp_file  (IO_cache *cache);
//
//  Support routine for SAVECHECK dialog box.
//
public:
// Get the file name
 TCHAR inline *get_name     (void) { return (name); }
//
//  Support routine for DIALOG BOXES in general.
//
// Used by dialog boxes, to insert back into file.
 void          put_string   (KANJI *kanji,int length);
// Insert a string from a dialog box into a file.with undo
 void          insert_string(KANJI *kanji,int length);
//
//  These fucntions are here to support edit control boxes.
//
// Constructor used for JWP_file object at the heart of the edit control.
 JWP_file (HWND hwnd);
// Initalize an edit control from a JWP_file.
 int           edit_copy    (JWP_file *file);
// Set edit control text.
 void  inline  edit_set     (KANJI *text,int length);
// Get length of edit control
 int   inline  edit_getlen  (void) { return (first->length); }
// Get edit control text.
 KANJI inline *edit_gettext (void) { return (first->text); }
// Replace edit control with clipboard contents
 int           edit_clip    (void);
//
//  Support routines for clipboard functions
//
// This construct is really for the clipboard functions.
 JWP_file (int format_width);
// Copy slected region to clipboard.
 JWP_file   *clip_copy        (void);
// Export clipboard data to bitmap.
 HGLOBAL     export_bitmap    (void);
// Read clipboard data into this file.
 int         import_clip      (void);
private:
// Paste from clipboard.
 void        clip_paste       (int errors);
// Cut text to clipboard.
 void        clip_cut         (void);
//
//  Support for kana->kanji conversion routines.
//
public:
// Put kanji into file from kana->kanji convert.
 void        put_kanji        (KANJI *kanji,int length);
// Dirve conversion commands.
 void        convert          (int direction);
//
//  Selection controls.
//
// Clear the selection.
 void        selection_clear  (void);
// Delete the selection.
 void        selection_delete (void);
// Selection for this file
 Selection  sel;
private:
// Tests if a position in in the selection.
 int         in_selection     (Position *loc);
// General processing routine for making selection my shift-cursor motion.
 void        selection        (int shift);
public:
// Adjust horizontal/vertical scroll to show cursor.
 void        view_check       (void);
// Dtermines the state of elements of the edit-menu.
 void        edit_menu        (void);
// File is changed.
 unsigned char        changed;
private:
// Convert all points to abs.
 void        all_abs          (void);
// Convert all points to relative.
 void        all_rel          (void);
// Clear stored vertical cursor.
 void inline clear_cursor     (void) { x_cursor = 0; }
 void        draw_line        (HDC hdc,Paragraph *para,Line *line,int y,int xmin,int xmax,class JWP_font *font);
// Find the pixal location of a point..
 void        find_pos         (Position *loc,int view = POS_CURSOR);
// Adjust position of scroll bars.
 void        set_scroll       (void);
// Paragraphs for the file.
 class  Paragraph *first,*last;
// Current cursor position
 class  Position   cursor;
// Indicates top-left corner of display.  Control screen scrolling.
 class  Position   view_top;
// X cursor location used in scroll ups and downs (stores pixal locaton at start of up/down).
 short             x_cursor;
// Width of page in characters.
 short             char_pagewidth;
// Total length of the file (int pixls)
 long              total_length;
// Display height.
 short             height;
// Display width.
 short             width;
// Width of display area in kanji characters.
 short             char_width;
// Horizontal scroll in characters width 
 short             hscroll;
// Vertical scroll distance in in pixals (page up/down)
 short             vscroll;
// Vertical offset used for IME composition window.
 short             ime_y;
// Disk file name
 TCHAR            *name;
// Page setup.
 PrintSetup        page;
// No headers & footers on first page.
 unsigned char              no_first;
// Separate odd and even headers and footers.
 unsigned char              odd_even;
// Summary data for file.
 KANJI_string      summary[NUMBER_SUMMARY];
// Header information for this file.
 KANJI_string      headers[NUMBER_HEADERS][NUMBER_POSITIONS];
};

// Pointer to double linked ring of files.
extern class JWP_file *jwp_file;

//===================================================================
//
//  Class to keep track of current files list.  This is the list used
//  to determine where to "Insert to File".
//
// Node structure for list.
typedef struct _FILE_node
{
// Pointer to next node
  _FILE_node *next;
// Pointer to this file
  class  JWP_file  *file;
} FILE_node;

class FILE_list
{
public:
// Intialize the list
  inline FILE_list (void) { list = NULL; }
// Add a file to the list.
  void      add    (JWP_file *file);
// Get current file from list.
  JWP_file *get    (JWP_file *exclude);
// Remove a file from the list.
  void      remove (JWP_file *file);
private:
// List of nodes.
  FILE_node *list;
};
// Actual class instance.
extern FILE_list file_list;
//===================================================================
//
//  Key code for use with do_key().
//
// WINELIB HAD these defined in winuser.h (man would that be helpful!).
//#ifndef WINELIB
#define VK_4    0x34
#define VK_A    0x41
#define VK_B    0x42
#define VK_C    0x43
#define VK_D    0x44
#define VK_E    0x45
#define VK_F    0x46
#define VK_G    0x47
#define VK_H    0x48
#define VK_I    0x49
#define VK_J    0x4a
#define VK_K    0x4b
#define VK_L    0x4c
#define VK_M    0x4d
#define VK_N    0x4e
#define VK_O    0x4f
#define VK_P    0x50
#define VK_Q    0x51
#define VK_R    0x52
#define VK_S    0x53
#define VK_T    0x54
#define VK_U    0x55
#define VK_V    0x56
#define VK_W    0x57
#define VK_X    0x58
#define VK_Y    0x59
#define VK_Z    0x5a
//#endif

#define VK_LT   0xbc
#define VK_GT   0xbe

#endif
