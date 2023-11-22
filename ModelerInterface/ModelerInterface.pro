QT       -= gui

TARGET = ModelerInterface
TEMPLATE = lib

DEFINES += MODELERINTERFACE_LIB

SOURCES += ModelerFactory.cpp

HEADERS += ModelerFactory.h \
           ModelerInterface.h \
           modelerinterface_global.h

DESTDIR     = ../lib/$$(OPTION)

win32 {
    QMAKE_LFLAGS += /NODEFAULTLIB:LIBCMT
}



