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
//  This module implements the search capabilities for the editor.
//  Fundimentally, this is done through the JWP_search class.  This 
//  class is a friend class of JWP_file because it needs access to 
//  the internal strcutres of the file for scanning.
//

#ifndef jwp_find_h
#define jwp_find_h

class JWP_search {
public:
  JWP_search ();
  inline ~JWP_search () { clear (TRUE); }
// Process search and replace dialoge boxes
  int  dlg_search  (HWND hwnd,unsigned int message,int command,int rep,class JWP_list *list);
// Implement the Edit/Find Next function.
  void do_next     (class JWP_list *list);
// Implement the Edit/Replace function.
  void do_replace  (void);
// Implement the Edit/Search function
  void do_search   (class JWP_list *list);
// Error message for not found.
  void not_found   (HWND window,int replace_all);
// Test to see if string matches the search pattern.
  int  test        (KANJI *string);
private:
// Clears the search engine and releases the memory.
  void   clear     (int rep);
// Counter for number of changes.
  int    changes;
// Set to non-zero to do a replace as oposed to search.
  short  is_replace;
// Length of the replace string.
  short  replace_length;
// Repalce kanji string.
  KANJI *replace;
// Search kanji string, working string.
  KANJI *search;
//   (jascii->ascii and case conversions have been done.)
//   This parameter being NULL, implies that this is
//   a fixed case (fast) search.
// Search kanji string entered by the user (saved so we can restore it next time them open the dialoge box.)
  KANJI *search_input;
// Length of the search string.
  short  search_length;
// Pointer to search dialog.
  HWND   search_dlg;
// Pointer to replace dialog.
  HWND   replace_dlg;
};

typedef JWP_search JWP_search;
// Instance of class.
extern JWP_search jwp_search;
// History buffer for seach.
extern JWP_history search_history;
// History buffer for replace.
extern JWP_history replace_history;

#endif
