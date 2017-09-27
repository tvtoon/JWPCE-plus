//===================================================================//
//                                                                   //
//  JWPce Copyright (C) Glenn Rosenthal, 1998-2004, 2005             //
//                                                                   //
//  JWPce is free sotware distributed under the terms of the         //
//  GNU General Public License.                                      //
//                                                                   //
//===================================================================//

#ifndef jwp_conf_h
#define jwp_conf_h

#include "jwp_prnt.h"
#include "jwp_misc.h"

#ifdef WINCE
// No quiet errors for Windows CE
#define QUIET_ERROR     if (true)
#else
// Block error message if quiet erros has been selected.
#define QUIET_ERROR     if (!jwp_config.quiet_errors)
#endif

#define SIZE_NAME       40
#define SIZE_DATE       20
#define SIZE_AMPM       10

#define OPENREAD(f)     CreateFile (f,GENERIC_READ ,FILE_SHARE_READ,null,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,null)
#define OPENWRITE(f)    CreateFile (f,GENERIC_WRITE,0              ,null,OPEN_ALWAYS  ,FILE_ATTRIBUTE_NORMAL,null)
#define OPENAPPEND(f)   CreateFile (f,GENERIC_WRITE,0              ,null,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,null)
#define OPENNEW(f)      CreateFile (f,GENERIC_WRITE,0              ,null,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,null)

#define OPEN_READ   0
#define OPEN_WRITE  1
#define OPEN_APPEND 2
#define OPEN_NEW    3
// Disables the kanji font coloring.
#define COLORKANJI_OFF      0
// Colors kanji that match the list.
#define COLORKANJI_MATCH    1
// Colors kanji that don't match the list.
#define COLORKANJI_NOMATCH  2
// Open the file as requested.
#define DOUBLE_OPEN         0
// Change to the already open file.
#define DOUBLE_CHANGE       1
// Prompt the user.
#define DOUBLE_PROMPT       2
// Use dynamic width (adjust to screen width).
#define WIDTH_DYNAMIC       0
// Use fixed with mode.
#define WIDTH_FIXED         1
// Use printer width mode.
#define WIDTH_PRINTER       2
// IME is disabled, only JWPce's input system is used.
#define IME_OFF             0
// Mode uses the IME, but ASCII text is pass through JWPce's input processor
#define IME_MIXED           1
// Replace JWPce's input sytem with the IME.
#define IME_ON              2
// Allows extended IME support.
#define IME_FULL            3
// Automatically determine the code page.
#define CODEPAGE_AUTO       0
// Easter Europ code page
#define CODEPAGE_EASTEUROPE 1250
// Cyrillic code page
#define CODEPAGE_CYRILLIC   1251
// USA and Western Europe code page
#define CODEPAGE_USA        1252
// Greek code page
#define CODEPAGE_GREEK      1253
// Turkish code page
#define CODEPAGE_TURKISH    1254
// Hebrew code page
#define CODEPAGE_HEBREW     1255
// Arabic code page
#define CODEPAGE_ARABIC     1256
// Baltic code page
#define CODEPAGE_BALTIC     1257
// Vietnamese code page
#define CODEPAGE_VIETNAMESE 1258

#ifdef WINCE
// Magic ID for JWP config files.
#define CONFIG_MAGIC  0xCE72C536
#else
// Magic ID for JWP config files.
#define CONFIG_MAGIC  0xBE72C536
#endif

//--------------------------------
//
//  Structure for storing font information.
//
struct cfg_font
{
// Name of font
  TCHAR name[SIZE_NAME];
// Size of font
  short size;
// Font is automatically sized.
  unsigned char  automatic;
// Extra unsigned char for who knows what.
  unsigned char  vertical;
};

//--------------------------------
//
//  Configuration for storing in a file.
//
//  Configuration changes for next major revisition:
//
//      1)  Change nokanjibar to kanjibar and move to display section.
//
struct cfg {
  ulong magic;                  // Identifies this as a JWPce config file.
  long  size;                   // Size of structrue.
  PrintSetup page;              // Default printer setup.
  struct cfg_font ascii_font;   // Ascii system font.
  struct cfg_font sys_font;     // System font used for text and a few other places.
  struct cfg_font list_font;    // Font for lists.
  struct cfg_font edit_font;    // Font used for Japanese edit constrols.
  struct cfg_font bar_font;     // Font used for kanji bars.
  struct cfg_font file_font;    // Font used for editing files.
  struct cfg_font big_font;     // Font used for big text.
  struct cfg_font jis_font;     // Font used for JIS table.
  struct cfg_font clip_font;    // Font used for clipboard bitmapps.
  struct cfg_font print_font;   // Font used for printing.
  struct cfg_font extra_font;   // Extra font for later
  struct cfg_font extra_font2;  // Another extra font.
  struct size_window size_dict; // Size of dictionary window.
  struct size_window size_user; // Size of user dictionary window;
  struct size_window size_oount;// Size of count kanji window.
  struct size_window size_cnvrt;// Size of user kana->kanji conversions window.
  struct size_window size_info; // Size of info dialog.
  struct size_window size_more; // Size of more info dialog.
  struct size_window size_fill; // Unused size structure for later
  int   x,y,xs,ys;              // Dimensions of last saved configuration.
  int   dict_buffer;            // Size of dictionary buffer.
  COLORREF info_color;          // Color used for titles in kanji-info box.
  COLORREF colorkanji_color;    // Color to be used with color-kanji.
  long  dict_bits;              // Stores the state of all dictionary bits in one place.
  short alloc;                  // Allocation size for lines.
  short convert_size;           // Number of entires in user conversion table.
  short char_width;             // Character width for formatinning.
  short undo_number;            // Number of levels of undo to keep.
  short font_cache;             // Size of font cache in characters.
  short head_left;              // Position of headers to the left of margins
  short head_right;             // Position of headers to the right of margins.
  short head_top;               // Position of header lines above margins.
  short head_bottom;            // Position of header lines below margins.
  short scroll_speed;           // Determines the scroll speed.
  short history_size;           // Size of history buffer (in characters).
  KANJI date_format[SIZE_DATE]; // Date format string.
  KANJI time_format[SIZE_DATE]; // Time format string.
  KANJI am_format[SIZE_AMPM];   // AM format string.
  KANJI pm_format[SIZE_AMPM];   // PM format string.
  unsigned char  buttons[100];           // Buttons for the button bar.
  unsigned char  kanji_info[60];         // Character Information dialog items
//
//  Dictionary flags.
//
  unsigned char  dict_compress;          // Displays diconary search results in compressed form.
  unsigned char  dict_auto;              // Automatically attempt a search if the user has selected text.
  unsigned char  dict_advanced;          // Use addaptive dictionary search.
  unsigned char  dict_iadj;              // Process i-adjitives.
  unsigned char  dict_always;            // Even if choices are found do an addpative search.
  unsigned char  dict_showall;           // Show all possible choices in an addaptive search.
  unsigned char  dict_advmark;           // Separate advanced search entries.
  unsigned char  dict_watchclip;         // Watch clipboard when dictionary is open
  unsigned char  dict_classical;         // Classical dictionary search
  unsigned char  dict_primaryfirst;      // Move primary entries to the front the dictionary display.
  unsigned char  dict_fullascii;         // Causes first/last to select complete entry for ascii 
  unsigned char  dict_jascii2ascii;      // Treat JASCII as ascii;
//
//  Startup flags
//
  unsigned char  install;                // If set causes check for installed version and file extensions.
  unsigned char  maximize;               // Maximaize the file.
  unsigned char  usedims;                // Use last saved dimensions.
  unsigned char  save_exit;              // Save configuration on exit.     
  unsigned char  reload_files;           // Reload files loaded when we exited.
//
//  Display flags
//
  unsigned char  vscroll,hscroll;        // Vertical and horizontal scroll bar.
  unsigned char  kscroll;                // Activate scroll bar on bar.
  unsigned char  kanjibar_top;           // Places the kanji bar at the top of the screen
  unsigned char  status;                 // Display status bar.
  unsigned char  toolbar;                // Disable the toolbar.
  unsigned char  button_count;           // Number of buttons in the toolbar
//
//  Basic operations flags
//
  unsigned char  confirm_exit;           // Require confirmation of exit on closing last file.
  unsigned char  close_does_file;        // Window close control, closes just current file.
  unsigned char  backup_files;           // Save last version of a file as a backup.
  unsigned char  double_open;            // Determine the action in the case of a double open.
  unsigned char  ime_mode;               // Determines JWPce's interaction with the Microsoft IME
  unsigned char  fill_unused;            // Causes the delete key to delete current kanji conversion instead of text to right (old action).
  unsigned char  auto_scroll;            // Enables or disables the auto-scroll feature.
  unsigned char  page_mode_file;         // Uses page scrolling for the file (PPC only)
  unsigned char  page_mode_list;         // Uses page scrolling for lists (PPC only)
//
//  Clipboard flags
//
  unsigned char  clip_write;             // Clipboard write type.
  unsigned char  clip_read;              // Clipboard read type.
  unsigned char  no_BITMAP;              // Suppress BITMAP clipboard format
  unsigned char  no_UNICODETEXT;         // Suppress UNICODETEXT clipboard format
//
//  Search flags
//
  unsigned char  search_nocase;          // Search: Ignore case
  unsigned char  search_jascii;          // Search: JASCII=ascii
  unsigned char  search_back;            // Search: Move backward (check jwp_find.cpp to see if this is active)
  unsigned char  search_wrap;            // Search: Wrap at end of file. 
  unsigned char  search_all;             // Search: All files.
  unsigned char  search_noconfirm;       // Repalce: Without confirmation. (check jwp_find.cpp to see if this is active)
  unsigned char  keep_find;              // Causes the Search/Replace dialog to remain open during searches.
//
//  Insert to file flags
//
  unsigned char  paste_newpara;          // When pasting back in the file insert extra lines into new paragraph.
//
//  Formatting and printing
//
  unsigned char  relax_punctuation;      // Allow relaxed punctuation.
  unsigned char  relax_smallkana;        // Allow relaxed small kana.
  unsigned char  width_mode;             // Determines how the width of the display is calculated.
  unsigned char  print_justify;          // Justify ASCII text.
  unsigned char  units_cm;               // CM units (or inches).
//
//  Info and Color Kanji flags
//
  unsigned char  info_compress;          // Compress Character information.
  unsigned char  info_titles;            // Puts titles in the kanji-info list box.
  unsigned char  info_onlyone;           // Allows only one info version to open.
  unsigned char  cache_info;             // Fill for later exapnsion
  unsigned char  colorkanji_mode;        // Determines the way color-fonts are suported.
  unsigned char  colorkanji_bitmap;      // Support color kanji in bitmap clipboard format
  unsigned char  colorkanji_print;       // Support color kanji in printing.
//
//  Kanji lookup flags
//
  unsigned char  auto_lookup;            // Should we do auto-lookups in the radical lookup dialog.
  unsigned char  skip_misscodes;         // Search for skip miss-codes.
  unsigned char  bushu_nelson;           // Search for Nelson bushu
  unsigned char  bushu_classical;        // Search for classicla bushu
  unsigned char  index_type;             // Index type for index search.
  unsigned char  reading_type;           // Reading type for reading search
  unsigned char  reading_kun;            // Allow flexable kun readings.
  unsigned char  reading_word;           // Allow flexable word matching.
  unsigned char  no_variants;            // Suppresses showing of variants in radical lookups.
//
//  Font flags
//
  unsigned char  cache_displayfont;      // Should we cache or not cache the display font.
  unsigned char  all_fonts;              // Show all fonts in the font selector
//
//  Added
//
  unsigned char  nokanjibar;             // Diables the kanji bar.
  short code_page;              // Code page used for translations
//
//  Fill
//
  short fill1;
  unsigned char  fill[252];              // Fill for later expansion.
};

//--------------------------------
//
//  Configuration class
//
class JWP_config
{
public:
 struct cfg cfg;
// Pointer to the data on previously loaded files.
 TCHAR *load;
// Insert mode;
 unsigned char  insert;
// Input mode;
 unsigned char  mode;
// Turns local (paragraph) base effects into global (file) base effects.
 unsigned char  global_effect;
// Flag for quiet error processing.
 unsigned char  quiet_errors;
// Height of command bar
 short commandbar_height;
// Flags indicating what is in the kanji info database.
 long  kanji_flags;
private:
// Disk based configuration is valid.
 unsigned char   ok;
// Name of configuration file.
 TCHAR  buffer[256];
// Buffer for network names
 TCHAR  nbuffer[256];
// Pointer to end of buffer base.
 TCHAR *ptr;
// Pointer to end of network name
 TCHAR *nptr;
// Pointer to last name generated.
 const char *last_name;
public:
// Constructor.
 JWP_config         (void);
// Called during exit to write configuration.
 void  done         (void) { if (!ok || cfg.save_exit) write(); }
// Open a file based on configurations settings.
 HANDLE open        ( const char *name,int mode,int net );
// Generate file name.
 const char *name        (const char *file,int mode,int net);
// Get last name generated by program.
 const char inline *name (void) { return (last_name); }
// Reader routine.
 int   read         (void);
// Set a configuration.
 void  set          (struct cfg *new_config);
// Write configuration file
 void  write        (void);
// Write files information to the configuation file.
 void  write_files  (void);
};

extern class JWP_config jwp_config;

#endif
