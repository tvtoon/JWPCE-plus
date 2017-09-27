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
//  This module is the primary processor of keyboard strokes from the 
//  user.  The main entry point is to the routine JWP_file::do_char.
//  This routine processes the key strokes.  For ASCII and JASCII modes,
//  this routine processes the characters directly.  For kanji mode,
//  the routines are passed to the KANA_convert::do_char routine which
//  handles converting the character to kana, and interfacinging with 
//  the kanji conversion rotuines.
//
#ifndef jwp_inpt_h
#define jwp_inpt_h

#include "jwp_file.h"
// Base value for katakana characters.
#define BASE_KATAKANA   0x2500
// Base value for hiragana characters.
#define BASE_HIRAGANA   0x2400
// Page for JASCII
#define BASE_JASCII     0x2300
// Value of first actual kanji
#define BASE_KANJI      0x3000
// Space character in kanji.
#define KANJI_SPACE     0x2121
// Forward slash (Japanese).
#define KANJI_SLASH     0x213F
// ? (Japanese)
#define KANJI_QUESTION  0x2129
// Cama (Japanese)
#define KANJI_CAMA      0x2122
// Center dot (Japanese)
#define KANJI_DOT       0x2126
// Astric (Japanese)
#define KANJI_ASTRIC    0x2176
// Horizontal arrow (use in user conversion editor)
#define KANJI_ARROW     0x222A
// ~ (Japanese)
#define KANJI_TILDE     0x2141
// - (Japanese, not long vawel, just a dash)
#define KANJI_DASH      0x213D
// - (Japanese)
#define KANJI_LONGVOWEL 0x213C
// ( (Japanese)
#define KANJI_LPARAN    0x214A
// ) (Japanese)
#define KANJI_RPARAN    0x214B
// [ (heavy Japanese)
#define KANJI_LBRACKET  0x215A
// ] (heavy Japanese)
#define KANJI_RBRACKET  0x215B
// [ (Japanese)
#define KANJI_LBRACE    0x214E
// ] (Japanese)
#define KANJI_RBRACE    0x214F
// Knaji used for invalid kanji (this is a solid box).
#define KANJI_BAD       0x2223
// Is this a cr or lf
#define ISCRLF(ch)     (((ch) == '\n') || ((ch) == '\r'))
// Is this a space.
#define ISSPACE(ch)    ((ch == ' ') || (ch == '\t') || (ch == 0x2121))
// Is this any ASCII character
#define ISASCII(ch)    (((ch) & 0x7f00) == 0)
// Is this a kanji or kana
#define ISJIS(ch)      (((ch) & 0x7f00) != 0)
// Is this hiragana
#define ISHIRAGANA(ch) (((ch) & 0x7f00) == BASE_HIRAGANA)
// Is this katakana
#define ISKATAKANA(ch) (((ch) & 0x7f00) == BASE_KATAKANA)
// Is this a kana
#define ISKANA(ch)     (ISHIRAGANA(ch) || ISKATAKANA(ch))
#define ISJASCII(ch)   (((ch) & 0x7f00) == BASE_JASCII)
#define ISKANJI(ch)    (((ch)         ) >= BASE_KANJI)

//-------------------------------------------------------------------
//
//  Exported data (romaji->kana converter)
//
struct compound_kana {
// sting pattern to match (embeded in table).
  char string[6];
// Generated kana.  A value of zero in one unsigned char will suppress that kana.
  unsigned char kana  [2];
}; 

#define SIZE_DIRECT 83
// Direct kana (each corresponds to a single value
extern char                  direct_kana[SIZE_DIRECT][4];
// Compound kana list.  Mostly two kana characters, but there are some others.
extern struct compound_kana  compound_kana[];

//-------------------------------------------------------------------
//
//  Exported routines.
//
// Different character classes returned by char_class().
// Kanji character.
#define CLASS_KANJI     0
// ASCII letter or number
#define CLASS_ASCII     1
// Katakana character
#define CLASS_KATAKANA  2
// Hiragana character
#define CLASS_HIRAGANA  3
// JASCII letter or number
#define CLASS_JASCII    4
// Space or tab (includes JASCII space)
#define CLASS_SPACE     5
// ASCII punctuation
#define CLASS_APUNCT    6
// JASCII punctuation.
#define CLASS_KPUNCT    7
// Invalid character
#define CLASS_JUNK      10

// Routine to get the class of a character.
int    char_class    (int ch);
// Convert jascii character to ascii character.
int  jascii_to_ascii (int ch);
// Convert a kana character back to ascii (used in JWP_conv).
char  *kana_to_ascii (int kana);

//-------------------------------------------------------------------
//
//  Class KANA_convert.
//
//  This specialized class simply handles conversion of ascii characters
//  to kana characters, and interfaces with the kanji generation rotuines.
//

typedef class KANA_convert {
public:
// Initialization routine.
  inline KANA_convert () { erase (); }
// Clears state of convert.  Some characters may be output at this time (n,aieuo).
  void        clear    (void);
// Entry level routine, called by client to pass characters to the routinte.
  void        do_char  (JWP_file *file,int ch);
// Clear without outputing characters.
  int         erase    (void);
// Force output buffer to hiragana
  void        force    (void);
private:
// Called to convert accumlated ASCII into KANA.
  void        out_kana (void);
// Exit level routine that puts kana back to the client.
  void        put_kana (int ch);
// Buffer to accumulate characters from client.
  char      buffer[6];
// Pointer into buffer for next character.
  short     index;
// Cureent state (see description of state table).
  short     state;
// Holding a KANA for later conversion.
  unsigned char      pending;
// Set non-zero if first character of ASCII is capital.
  unsigned char      kanji_start;
// File where we were called from.  This lets us know where to put the characters back.
  JWP_file *file;
} KANA_convert;

// Instance of the KANA_convert class.
extern KANA_convert kana_convert;

#endif
