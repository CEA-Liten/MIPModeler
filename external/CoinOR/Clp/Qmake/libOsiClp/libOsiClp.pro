QT       -= gui

TARGET = libOsiClp
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../Clp/src
INCLUDEPATH += ../../../Clp/src/OsiClp
INCLUDEPATH += ../../../Osi/src
INCLUDEPATH += ../../../Osi/src/Osi
INCLUDEPATH += ../../../CoinUtils/src

win32 {
    LIBS        += ../../../lib/$$(OPTION)/libClp.lib
    LIBS        += ../../../lib/$$(OPTION)/libOsi.lib
    LIBS        += ../../../lib/$$(OPTION)/libCoinUtils.lib
}
unix {
    LIBS        += ../../../lib/$$(OPTION)/liblibClp.so
    LIBS        += ../../../lib/$$(OPTION)/liblibOsi.so
    LIBS        += ../../../lib/$$(OPTION)/liblibCoinUtils.so
}

DEFINES += OSI_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _LIB
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE

SOURCES += \
    ../../src/OsiClp/OsiClpSolverInterface.cpp \

HEADERS +=  \
    ../../src/OsiClp/OsiClpSolverInterface.hpp \

DESTDIR = ../../../lib/$$(OPTION)
