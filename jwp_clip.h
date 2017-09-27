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
//  This modlue implement most of the clipboard functionaly of the 
//  system.  The clipbard has no class associated witht it, but rather
//  makes use of stuff distrubuted in a number of classes, particuarly
//  Paragraph, and JWP_file.
//

#ifndef jwp_clip_h
#define jwp_clip_h

#include "jwp_file.h"
// Destroy internal clipbaord data.
extern void      clear_clipboard (void);
// Processes system messages associated with the clipboard.
extern void      do_clipboard    (int iMsg,WPARAM wParam);
// Free paste gotten with get_paste().
extern void      free_paste      (JWP_file *paste);
// Get object to paste
extern JWP_file *get_paste       (HWND hwnd);

extern JWP_file *jwp_clipboard;

#endif
