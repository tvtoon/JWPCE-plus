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
//  This module implements a somewhat generaliezed IO buffering cache.
//  This cache has the advantage of speeding up both reads and writes.
//  Additionally, the generalized cache system allows the same code to 
//  be used for input/output from/to either files or the clipboard.
//
#ifndef jwp_cach_h
#define jwp_cach_h
// Used to indicate block read is ok.
#define IO_OK   0
// Used to indicate end of file form a cache read.
#define IO_EOF  -1

class IO_cache
{
friend class JIS_convert;
public:
// Get block from input stream.
  int     get_block    (void *data,int size);
// Get character from input buffer.
  int     get_char     (void);
// Get CR/LF terminated line from buffer.
 char   *get_line     (void);
// Finish a write to an output stream.
  long    flush        (void);
// Initialize to read from clipboard.
  void    input_clip   (HGLOBAL clip);
// Cleanup routine called at the end of inputs.
  void    input_end    (void);
// Intialize a file input stream.
  void    input_file   ( char *buffer,int size,HANDLE file);
// Initilize a memory block as an input stream.
  void    input_memory ( char *buffer);
// Intialize an output stream for the clipboard.
  HGLOBAL output_clip  (long size);
// False output stream that counts the characters.
  void    output_count (void);
// Intialize a file output stream.
  void    output_file  (char *buffer,int size,HANDLE file);
// Put block to output stream.
  void    put_block    (void *data,int size);
// Put character into output buffer.
  void    put_char     (int ch);
// Rewind an input buffer for reuse (used when finding a type).
  void    rewind       (void);
// Set character block size.
  void inline set_size (int cs) { charsize = cs; }
private:
// Reload the input cache (INTERNAL routine).
  int     reload       (void);
// Un-get a character from the input buffer.
  void inline unget_char (void) { position--; }
// Handle used for input and output file streams.
  HANDLE  handle;
// Golobal block for clipboard work.
  HGLOBAL block;
// Pointer to the buffer (both input and output).
  char   *buffer;
// Pointer to count location.
  long    count;
// Size of the buffer (in unsigned chars).
  long    size;
// Current position in the buffer.
  long    position;
// Storage used only for rewind.
  long    bufsize;
// Indidates an error has occured (used only during write).
  short   error;
// Size of character to handle UNICODE and CE.
  short   charsize;
};

typedef IO_cache IO_cache;

#endif
