PROJECT = JWPCE
MAJVER = 1.5
MINVER = 1
LIBS = ${PROJECT}
PROGS = ${PROJECT}

include make/conf
include make/cpplib
#include make/wine.mk

CFLAGS = -I/usr/local/include/wine/windows -D_WINDOWS -O2 -Wall -Wextra -g -o
#LDFLAGS = -Wl,--subsystem,windows
ELIBFLAGS = -lgdi32 -lcomdlg32 -lodbc32 -lodbccp32 -lcomctl32 -lwsock32
DOCS =
INFOS =
INCLUDES =

SRC = jwp_cach.cpp jwp_clip.cpp jwp_conv.cpp jwp_dict.cpp jwp_edit.cpp
SRC += jwp_file.cpp jwp_find.cpp jwp_flio.cpp jwp_font.cpp jwp_help.cpp
SRC += jwp_info.cpp jwp_inpt.cpp jwp_inst.cpp jwp_jisc.cpp jwp_klst.cpp
SRC += jwp_lkup.cpp jwp_misc.cpp jwp_para.cpp jwp_prnt.cpp jwp_stat.cpp
SRC += jwp_undo.cpp

LIBSRC := ${SRC}
PROGSRC = resource.h jwpce.c

include make/exconf
include make/build

${PROGS}: ${PROGOBJ}

dist-clean: clean

include make/pack
include make/rules
include make/thedep
