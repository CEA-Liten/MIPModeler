#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------
QT       -= gui

TARGET = libOsiCbc
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../Osi/src/Osi
INCLUDEPATH += ../../../BuildTools/headers
INCLUDEPATH += ../../../CoinUtils/src
INCLUDEPATH += ../../../Clp/src
INCLUDEPATH += ../../../Clp/src/OsiClp
INCLUDEPATH += ../../../Cbc/src

LIBS += ../../../lib/$$(OPTION)/libOsi.lib
LIBS += ../../../lib/$$(OPTION)/libCoinUtils.lib
LIBS += ../../../lib/$$(OPTION)/libClp.lib
LIBS += ../../../lib/$$(OPTION)/libOsiClp.lib
LIBS += ../../../lib/$$(OPTION)/libCbc.lib
LIBS += ../../../lib/$$(OPTION)/libCgl.lib

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
