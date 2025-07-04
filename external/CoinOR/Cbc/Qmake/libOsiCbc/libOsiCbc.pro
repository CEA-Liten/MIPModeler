QT       -= gui

TARGET = libOsiCbc
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../Osi/src/Osi
INCLUDEPATH += ../../../CoinUtils/src
INCLUDEPATH += ../../../Clp/src
INCLUDEPATH += ../../../Clp/src/OsiClp
INCLUDEPATH += ../../../Cbc/src


win32 {
    LIBS += ../../../lib/$$(OPTION)/libOsi.lib
    LIBS += ../../../lib/$$(OPTION)/libCoinUtils.lib
    LIBS += ../../../lib/$$(OPTION)/libClp.lib
    LIBS += ../../../lib/$$(OPTION)/libOsiClp.lib
    LIBS += ../../../lib/$$(OPTION)/libCbc.lib
    LIBS += ../../../lib/$$(OPTION)/libCgl.lib
}
unix {
    LIBS += ../../../lib/$$(OPTION)/liblibOsi.so
    LIBS += ../../../lib/$$(OPTION)/liblibCoinUtils.so
    LIBS += ../../../lib/$$(OPTION)/liblibClp.so
    LIBS += ../../../lib/$$(OPTION)/liblibOsiClp.so
    LIBS += ../../../lib/$$(OPTION)/liblibCbc.so
    LIBS += ../../../lib/$$(OPTION)/liblibCgl.so
}

DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _NDEBUG
DEFINES += COIN_FAST_CODE
DEFINES += CLP_FAST_CODE
DEFINES += COIN_NO_TEST_DUPLICATE

SOURCES += \
    ../../src/OsiCbc/OsiCbcSolverInterface.cpp \

HEADERS +=  \
    ../../src/OsiCbc/OsiCbcSolverInterface.hpp \

DESTDIR = ../../../lib/$$(OPTION)
