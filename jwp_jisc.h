//===================================================================//
//                                                                   //
//  JWPce Copyright (C) Glenn Rosenthal, 1998-2004, 2005             //
//                                                                   //
//  JWPce is free sotware distributed under the terms of the         //
//  GNU General Public License.                                      //
//                                                                   //
//  The code do do conversion between ECU, JIS, and Shift-JIS        //
//  was taken from jconv.c which is copyright by Ken R. Lunde,       //
//  Adobe Systems Incorporated.  Full copyright notice is cpp file.  //
//                                                                   //
//===================================================================//

//===================================================================
//
//  This module implements the translatin between JWP's internal coding
//  and various other formats.  These formats include various JIS formats,
//  Shift-JIS, EUC, UNICODE, and ASCII.  (ASCII format is only supported
//  as an import format.)
//
//  Note this class is base on the IO_cache class that provides both
//  input and output buffering.  Additionally, the IO_cache class 
//  provides an easy way for this class to operate on both files and 
//  clipboard contents, as well as an easy character counter.  See the 
//  jwp_cach.cpp/h files for informationon the IO_cache class.
//
#ifndef jwp_jisc_h
#define jwp_jisc_h
// Needed because the JIS_convert class is base on the IO_cache class.
#include "jwp_cach.h"

// File types
// Unnamed file (from New).
#define FILETYPE_UNNAMED    0x00
// Auto-detect file type (load only).
#define FILETYPE_AUTODETECT 0x01
// Japanese file types (load only).
#define FILETYPE_JTYPES     0x02
// Ascii file (load only).
#define FILETYPE_ASCII      0x03
// Normal JPWce file type.
#define FILETYPE_NORMAL     0x04
// Normal .JWP file type.
#define FILETYPE_JWP        0x05
// EUC file type.
#define FILETYPE_EUC        0x06
// Shift-JIS file type.
#define FILETYPE_SJS        0x07
// New JIS file type.
#define FILETYPE_JIS        0x08
// Old JIS file type.
#define FILETYPE_OLD        0x09
// NEC JIS file type.
#define FILETYPE_NEC        0x0a
// Unicode file type.
#define FILETYPE_UNICODE    0x0b
// Unicode file type with reverced unsigned char order.
#define FILETYPE_UNICODER   0x2b
// UTF-7 file type.
#define FILETYPE_UTF7       0x0c
// UTF-8 file type.
#define FILETYPE_UTF8       0x0d
// JFC file type (UTF-8 format)
#define FILETYPE_JFC        0x0e
// JFC file type (EUC format)
#define FILETYPE_JFCEUC     0x2e
// Project file
#define FILETYPE_PROJECT    0x0f
// File type has erverce unsigned char order.  Only used for 16-bit formats.
#define FILETYPE_REVERCE    0x20
// Edit control type.
#define FILETYPE_EDIT       0x40
// Working file type (clipboard, etc.)
#define FILETYPE_WORK       0x41
// Working file mask.
#define FILETYPE_WORKMASK   0x40
// Mask to get actual working types for files.
#define FILETYPE_TYPEMASK   0x0f
// Test for working type file
#define IS_WORKFILE(x)  ((x) & FILETYPE_WORKMASK)
// Unicode value representing an error.
#define UNICODE_BAD         0xffff
// UTF-8 encouding values.
// Value for set bits for single unsigned char UTF-8 Code.
#define UTF8_VALUE1     0x00
// Mask (i.e. bits not set by the standard) 0xxxxxxx
#define UTF8_MASK1      0x80
// Mask of bits we cannot allow if we are going to write one unsigned char code
#define UTF8_WRITE1     0xff80
// Two unsigned char codes
#define UTF8_VALUE2     0xc0
// 110xxxxx 10yyyyyy
#define UTF8_MASK2      0xe0
// Mask of mits we cannot allow if we are going to write two unsigned char code
#define UTF8_WRITE2     0xf800
// Three unsigned char codes
#define UTF8_VALUE3     0xe0
// 1110xxxx 10yyyyyy 10zzzzzz
#define UTF8_MASK3      0xf0
// Four unsigned char values
#define UTF8_VALUE4     0xf0
// 11110xxx ----    (These values are not supported by JWPce).
#define UTF8_MASK4      0xf8
// Continueation unsigned char (10xxxxxx).
#define UTF8_VALUEC     0x80
#define UTF8_MASKC      0xc0

// Character markers.
// All other characters are internal
#define JIS_EOF             -1

class JIS_convert : public IO_cache {
public:
// Determine type of an input stream.
  int     find_type     (void);
// Tests to see if object is a Unicode file.
  int     is_unicode    (void);
// Tests for a UTF8 file.
  int     is_utf8       (void);
// Read next kanji from the input stream
  int     input_char    (void);
// Output a character to the buffer.
  void    output_char   (int ch);
// Setup for a conversion.
  void    set_type      (int type);
// Write's UNICODE ID if necessary.
  void    unicode_write (void);
private:
// Convert half width character to full width character.
  void    half2full     (int *p1,int *p2);
// End a JIS escape sequence
  void    put_end       (void);
// Start a JIS escape sequence
  void    put_start     (void);
// Put bits in the bit buffer.
  void    put_bits      (int value,int count);
// Get bits from bit buffer.
  int     get_bits      (int count);
// File type being written or read.
  short   type;
// In two unsigned char JIS escape sequence.
  unsigned char    in_twobyte;
// Need to reverce data unsigned char order (UNICODE only).
  unsigned char    reverce_bytes;
// Bit buffer for UTF-7 format.
  ulong   bit_buffer;
// Number of bits in the buffer.
  short   bits;
};

typedef class JIS_convert JIS_convert;

//===================================================================
//
//  Exported routines.
//
// Convert extended ASCII to UNICODE
extern int  ascii2unicode  (int ch);
// Convert JIS code into Shift-JIS code.
extern int  jis2sjis       (int ch);
// Convert JIS code into Unicode.
extern int  jis2unicode    (int ch);
// Convert Shift-JIS code to JIS code.
extern int  sjis2jis       (int ch);
// Convert Unicode to JIS code.
extern int  unicode2jis    (int ch,int bad);

//
//  Some of functions have been blocked out because they are not yet needed.  They are for when the 
//  code is converted to UNICODE.
//
// Convert JIS code to UTF-8
extern void jis2utf        ( char *&ptr,int ch);
// Convert UTF-8 to JIS code.
extern int  utf2jis        ( char *&ptr);
// Convert UNICODE to UTF-8
//extern void unicode2utf    (unsigned char *&ptr,int ch);
// Convert UTF-8 to UNICODE.
//extern int  utf2unicode    (unsigned char *&ptr);

// Initialize the conversion routines (adjust for code page)
extern void initialize_cp  (void);

#endif
