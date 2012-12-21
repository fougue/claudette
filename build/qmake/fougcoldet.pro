# Note: run qmake "CONFIG += dll" build a DLL instead of a static library
CONFIG += debug_and_release build_all

TARGET = fougcoldet

# Create file yout own _local_config.pri to customize build
#   For example add "CONFIG += dll" to build a DLL or change DESTDIR, TARGET, ...
#   Parameter variables:
#      * TARGET_SUFFIX: used to define the suffix of the generated library
!include(_local_config.pri) {
  message(No local config)
}

isEmpty(PREFIX_DIR) {
  PREFIX_DIR = ../..
}

DESTDIR = $$PREFIX_DIR/lib

TEMPLATE = lib

TARGET = $$TARGET$$TARGET_SUFFIX

CONFIG -= qt
QT = # No link to Qt libs

win*:DEFINES += WIN32 COLDET_EXPORTS
unix:DEFINES += GCC
macx:DEFINES += macintosh

HEADERS += \
   ../../src/box.h \
   ../../src/coldet.h \
   ../../src/coldetimpl.h \
   ../../src/math3d.h \
   ../../src/mytritri.h \
   ../../src/sysdep.h

SOURCES += \
   ../../src/box_bld.cpp \
   ../../src/box.cpp \
   ../../src/coldet_bld.cpp \
   ../../src/coldet.cpp \
   ../../src/math3d.cpp \
   ../../src/mytritri.cpp \
   ../../src/sysdep.cpp \
   ../../src/tritri.c

include.path  = $$PREFIX_DIR/include
include.files = ../../src/coldet.h
INSTALLS += include

#VER_MAJ = 0
#VER_MIN = 1
#VER_PAT = 0
