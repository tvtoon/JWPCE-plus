//===================================================================//
//                                                                   //
//  JWPce Copyright (C) Glenn Rosenthal, 1998-2004, 2005             //
//                                                                   //
//  JWPce is free sotware distributed under the terms of the         //
//  GNU General Public License.                                      //
//                                                                   //
//  The database read by JWPce is dirived directly from KANJIDIC     //
//  database dirived by Jim Breen.  Please see the _cpright.txt file //
//  for additional information.                                      //
//                                                                   //
//===================================================================//

//===================================================================
//
//  This modlue implements various informational routines.  The 
//  principle of these are the character-info (kanji info) and the 
//  kanji-table.  These routines primrally provide information 
//  related to Japanese characters.
//

#ifndef jwp_info_h
#define jwp_info_h

#include "jwp_file.h"
// Size of buffer for reading info lines.
#define SIZE_INFOBUFFER 512

//
//  Fixed structure for data file.
//
//  This is the structure representing the fixed part of the data file
//  that JWPce is expecting.
//
// Structure to be packed at 2 unsigned char boundaries.
// this results is a smaller data size.
#include <pshpack2.h>

//--------------------------------
//
//  Fixed kanji info structure.
//
/* BROKEN */

struct kinfo {
// Radical number (from Nelson).
  ushort bushu      :8;
// Stroke count.
  ushort strokes    :5;
// Number of on-yomi
  ushort on         :3;
// Grade that Japanese learn the kanji
  ushort grade      :4;
// Number of meanings
  ushort imi        :4;
// Skip code: type
  ushort skip_t     :3;
// first number
  ushort skip_1     :5;
// second number
  ushort skip_2     :5;
// Number of PinYin lines (1 or zero).
  ushort pinyin     :1;
// Number of kun-yomi
  ushort kun        :5;
// Number of nanori.
  ushort nan        :5;
// Entry has extended data.
  ushort extra      :1;
// Halpern refference number
  ushort halpern    :15;
// Number of Korean lines (1 or zero)
  ushort korean     :1;
// Nelson reference number
  ushort nelson     :15;
// Index into New Nelson dicitonary (edited by Haig)
  ushort haig;
// Classical bushu (if different from Nelson's)
  ulong  classical  :8;
// File offset to variable part of the data.
  ulong  offset     :24;
};

//--------------------------------
//
//  Extended data structrue.
//
struct extend {
// Morohashi Daikanwajiten long entry
  ushort md_long;
// Morohashi Daikanwajiten short (volume)
  ulong  md_short1  :4;
// Morohashi Daikanwajiten short (kanji)
  ulong  md_short2  :13;
// Spahn & Hadamitzky Dictionary radical stroke count
  ulong  sh_rstroke :5;
// Spahn & Hadamitzky Dictionary radical (a latter)
  ulong  sh_radical :5;
// Spahn & Hadamitzky Dictionary other stroke count
  ulong  sh_ostroke :5;
// Spahn & Hadamitzky Dictionary index of kanji with radical and stroke count
  ulong  sh_index   :6;
// Four corners main entry
  ulong  fc_main    :14;
// Four corners extra entry.
  ulong  fc_index   :4;
// Four corners extra entry (for second code)
  ulong  fc_index2  :4;
// Morohashi Daikanwajiten (original code 'P')
  ulong  md_p       :1;
// Morohashi Daikanwajiten (close code 'X')
  ulong  md_x       :1;
};

#include <poppack.h>

//
//  SKIP Miss-clasification / cross-reference codes:
//
// Position error.
#define SKIP_POSITION   1
// Stroke error.
#define SKIP_STROKE     2
// Both position and stroke error.
#define SKIP_BOTH       3
// Disagreement between Jim Breen and Jack Halpern about the code.
#define SKIP_BREEN      4

//
//  Amount codes passed to get_info().  These determine the amount of information processing
//  that is done.
//
// Get just the fixed information.
#define INFO_FIXED      0
// Get fixed information and the readings/meaning information.
#define INFO_STRINGS    1
// Get fixed extended information.
#define INFO_EXTEND     2
// Get all information.
#define INFO_ALL        3

//
//  Flags for the flag field.  These indicate what fields are included 
//  in the file.
//
// Has pin yin data.
#define KIFLAG_PINYIN   0x0001
// Has Korean data.
#define KIFLAG_KOREAN   0x0002
// Has nanori data.
#define KIFLAG_NANORI   0x0004
// Has extended data filed
#define KIFLAG_EXTRA    0x0008
// Has extended variable data
#define KIFLAG_EVAR     0x0010
// Has cross refference data
#define KIFLAG_XREF     0x0020

//
//  Identifiers for kanji info dialog items.
//
#define INFO_BLANK              0
#define INFO_TYPE               1
#define INFO_JIS                2
#define INFO_SHIFTJIS           3
#define INFO_UNICODE            4
#define INFO_STROKE             5
#define INFO_GRADE              6
#define INFO_NELSON             7
#define INFO_HALPERN            8
#define INFO_SPAHN              9
#define INFO_FOURCORNERS        10
#define INFO_MOROHASHI          11
#define INFO_PINYIN             12
#define INFO_KOREAN             13

#define INFO_FREQUENCY          14
#define INFO_HENSHALL           15
#define INFO_GAKKEN             16
#define INFO_HEISIG             17
#define INFO_ONEILL             18
#define INFO_DEROO              19
#define INFO_KANJILEARN         20
#define INFO_READWRITE          21
#define INFO_TUTTLECARDS        22
#define INFO_KANJIWAY           23
#define INFO_KANJICONTEXT       24
#define INFO_BUSYPEOPLE         25
#define INFO_COMPACTGUIDE       26
// Last info-item code.
#define INFO_MAXITEM INFO_COMPACTGUIDE

//--------------------------------
//
//  KANJI_info class handles acess to the kanji-info file, and generation
//  of the character info dalog box.
//
class KANJI_info {
friend int  initialize_info (WNDCLASS *wclass);
friend void kanji_info (HWND hwnd,int kanji);
public:
  inline KANJI_info (void) { handle = INVALID_HANDLE_VALUE; return; }
// This is the main information block.
  struct kinfo     kinfo;
// Buffer used for holding the extended information
  char             buffer[SIZE_INFOBUFFER];
// Pointer to extended data structure or a NULL.
  struct extend    extend;
// Pointer to pinyin data or a NULL.
  char            *pinyin;
// Pointer to korean data or a NULL.
  char            *korean;
// Pointer to first on-yomi entry.
  char            *on;
// Pointer to first kun-yomi entry.
  char            *kun;
// Pointer to first imi (meaning) entry.
  char            *imi;
// Pointer to first nanori entry.
  char            *nan;
// Start of the cross-reference entries.
  char            *xref;
// Character frequency
  short            freq;
// Spahn and Hadamitzky Kana & Kanji
  short            sh_kana;
// "A Guide To Remembering Japanese Characters" by Kenneth G. Henshall
  short            henshall;
// Gakken Kanji Dictionary ("A  New Dictionary  of Kanji Usage")
  short            gakken;
// "Remembering The Kanji" by James Heisig
  short            heisig;
// "Japanese Names", by P.G. O'Neill
  short            oneill;
// Four-corners secondary code <code><resolution is stroed in the struture>
  short            fc_main2;
// P.G. O'Neill's Essential Kanji (ISBN 0-8348-0222-8).
  short            oneill_ek;
// Jack Halpern in his Kanji Learners Dictionary, published by Kodansha in 1999
  short            halpern_kld;
// Father Joseph De Roo, and published in his book "2001 Kanji"
  short            deroo;
// Number of kanji in the database. (NOT USED AT THIS TIME)
  short            count;
// "A Guide To Reading and Writing Japanese" edited by Florence Sakade.
  short            readwrite;
// Tuttle Kanji Cards, compiled by Alexander Kask.
  short            tuttlecard;
// "The Kanji Way to Japanese Language Power" by Dale Crowley.
  short            kanjiway;
// "Kanji in Context" by Nishiguchi and Kono.
  short            kanjicontext;
// "Kodansha Compact Kanji Guide".
  short            kanjiguide;
// "Japanese For Busy People" vols I-III, published by the AJLT. The codes are the volume.chapter.
  short            busypeople;
// Last JIS value in the database.
  KANJI            last_jis;
// Dialog box procedure
  int  dlg_kanjiinfo (HWND hwnd,unsigned int message,WPARAM wParam,LPARAM lParam);
// Dialog box procedure
  int  dlg_moreinfo  (HWND hwnd,unsigned int message,WPARAM wParam,LPARAM lParam);
// Dialog box procedure
  int  dlg_xrefinfo  (HWND hwnd,unsigned int message,WPARAM wParam,LPARAM lParam);
// Open the kanji-info file.
  int  open_info     (HWND hwnd);
// Get kanji info record for a character.
  void get_info      (int ch,int amount);
// Get stroke count for character (used by the kanji search rotuines)
  int  get_stroke    (int ch);
// Close info
  void close_info    (void);
private:
// Format and place an object in the display.
  void format_line (HWND hwnd,int line,int code);
// Setup dialog box to display a character.
  void setup_char  (HWND hwnd);
// Intialize main character info dialog.
  void init_dialog (HWND hwnd);
// Format the xref.
  void format_xref (HWND hwnd);
// Kanji we are working with.
  KANJI     ch;
// Hanlde for accessing the kanji-info file.
  HANDLE    handle;
// Dialog pointer.
  HWND      dialog;
};

typedef KANJI_info KANJI_info;
// Implements the count kanji feature.
extern void do_kanjicount   (void);
// Free memory allocated for the kanji info.
extern void free_info       (void);
// Open configure kanji-info dialog.
extern void info_config     (HWND hwnd);
// Register classes needed by the info routines.
extern int  initialize_info (WNDCLASS *wclass);
// Get kanji finformation for a character
extern void kanji_info      (HWND hwnd,int kanji);

#endif
