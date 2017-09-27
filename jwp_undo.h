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
//  This modlule implements the undo system.  This system is quite 
//  complex, because of the constraints of a reasonable system.  In 
//  particular, we want the user to be able to undo editing changes, but
//  we want a resonable overhead for the system, and we want thoes 
//  changes to be undoable in a resonalbe increment.  Keeping track of
//  every character typed, and every change is easy, but somewhat 
//  inconvenient for unding a change.  Saving changes too infrequently
//  is also a problem, in that the user cannot undo changes easilly, 
//  without unding a lot of other stuff.  We get arround this in a 
//  number of different ways.  Prinarally we save changes a key intervals
//  and whenever the user moves the cursor.  This means that a string 
//  of delete commands will be saved together, and a string of typing
//  may also be saved together, but if the user types some, deletes some,
//  etc, this generates a resonalbe system.
//
//  See jwp_undo.cpp for a very full description of the system.
//

#ifndef jwp_undo_h
#define jwp_undo_h

#include "jwp_file.h"

#ifdef WINELIB
 #define _vert_ virtual
#else
 #define _vert_    
#endif

//--------------------------------
//
//  We try to accumulate changes into chuncks that are a nice size for
//  the user.  Currently, this is refered to as accumulating changes. 
//  Generally the undo system generates undo data (saves part of the 
//  file) just before a change is made to the file.  When changes are 
//  being accumulated, we say that we have saved the sate of the file
//  before the user started typing, and as long a s the user continues 
//  to simply type we will not save the state of the file thus accumulating
//  a number of changes.  (Basically we count changes as simple typeing,
//  and as deleting text).  These flags are used to indicate the type
//  of changes being accumulated.  There are, however, some special 
//  flags that are used to force generation of undo data in special 
//  cases. 
//
// Not accumulating changes.
#define UNDO_NONE   0x00
// Accumuating deletions.
#define UNDO_DEL    0x01
// Accumulating typing.
#define UNDO_TYPE   0x02
// Special code to accept any type of conversion.
#define UNDO_ANY    0x10
// Special code to push data duing a quing event (see jwp_undo.cpp).
#define UNDO_QUE    0x30

//--------------------------------
//
//  Undo data is stored in a chain of UNDO_??? objects.  Each of these 
//  object stores information necessary to undo a particutlar type of 
//  action.  This is the base class that forms all of the undo actions.
//  Note that this class is virtuall, and cannot be used directly.  
//  Also not that derived classes must deal with the data field, because
//  the destructor will delete that object.
//
// ### If this system is expanded and the simple single data record is
// ###   not sufficient, the destructor should be made virtural so 
// ###   memory can deallocated correctly.
//
class UNDO_action {
public:
// Single linked list.
  class UNDO_action *next;
// Data, actual use is defined in derived class.
  void              *data;
// Destructor.
  _vert_ ~UNDO_action (void);
// The actuall undo function (true virtual function)!!
  void virtual undo (class JWP_file *file) = 0;
};

//--------------------------------
//
//  Undo action associated with deletion of a paragraph.
//
class UNDO_delpara : public UNDO_action {
public:
// Paragraph number for paragraph that was deleted.
  short number;
// REQUIRED: virtual undo function.
  void  undo (class JWP_file *file);
};
// Data field is unused (NULL).

//--------------------------------
//
//  Undo action associated with creation of a paragraph.
//
class UNDO_newpara : public UNDO_action {
public:
// Paragraph number for paragraph that was created (not one before).
  short number;
// REQUIRED: virturla undo function.
  void  undo (class JWP_file *file);
};
// Data field is unused (NULL).

//--------------------------------
//
//  Undo action assocated with chaning a paragraph (by far the most common
//  type of action).
//
class UNDO_para : public UNDO_action {
public:
// Paragraph number for modified paragraph.
  short number;
// Paragraph number for cursor.
  short cursor_para;
// Line number within paragraph for the cursor.
  short cursor_line;
// Position within a line for cursor.
  short cursor_pos;
// Length of paragraph data.
  short length;
// Line spacing times 100.
  short spacing;
// Non-zero indicates this is a page break.
  unsigned char  page_break;
// Left indent.
  unsigned char  indent_left;
// Right indent.
  unsigned char  indent_right;
// First line indent.
  unsigned char  indent_first;
// REQUIRED: virturla undo function.
  void  undo (class JWP_file *file);
};
// Data field points to paragraph data.

//--------------------------------
//
//  Undo action assocated with chaning a file's type and/or name.
//
class UNDO_type : public UNDO_action {
public:
// File type.
  unsigned char  type;
// REQUIRED: virturla undo function.
  void  undo (class JWP_file *file);
};
// Data field holds file name.

//--------------------------------
//
//  Exported Variables
//
// Redo buffer.
extern UNDO_action **redo;

//--------------------------------
//
//  Exported functions
//
// Free an allocated undo list.
extern void          undo_free  (UNDO_action **list,int length);
// Allocate undo data.
extern UNDO_action **undo_alloc (UNDO_action **undo,int old_size);

#endif
