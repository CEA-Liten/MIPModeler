#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------
QT       -= gui

TARGET = libOsiCbc
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$(COINOR_HOME)/Osi/src/Osi
INCLUDEPATH += $$(COINOR_HOME)/BuildTools/headers
INCLUDEPATH += $$(COINOR_HOME)/CoinUtils/src
INCLUDEPATH += $$(COINOR_HOME)/Clp/src
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/OsiClp
INCLUDEPATH += $$(COINOR_HOME)/Cbc/src

LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsi.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCoinUtils.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libClp.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsiClp.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCbc.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCgl.lib

DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _NDEBUG
DEFINES += COIN_FAST_CODE
DEFINES += CLP_FAST_CODE
DEFINES += COIN_NO_TEST_DUPLICATE

SOURCES += \
    ..\..\src\OsiCbc\OsiCbcSolverInterface.cpp \

HEADERS +=  \
    ..\..\src\OsiCbc\OsiCbcSolverInterface.hpp \

DESTDIR = $$(COINOR_HOME)/lib/$$(OPTION)
