#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------
QT       -= gui

TARGET = libOsiClp
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += $$(COINOR_HOME)/Clp/src
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/OsiClp
INCLUDEPATH += $$(COINOR_HOME)/Osi/src
INCLUDEPATH += $$(COINOR_HOME)/Osi/src/Osi
INCLUDEPATH += $$(COINOR_HOME)/CoinUtils/src
INCLUDEPATH += $$(COINOR_HOME)/BuildTools/headers

LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libClp.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsi.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCoinUtils.lib

DEFINES += OSI_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _LIB
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE

SOURCES += \
    ..\..\src\OsiClp\OsiClpSolverInterface.cpp \

HEADERS +=  \
    ..\..\src\OsiClp\OsiClpSolverInterface.hpp \

DESTDIR = $$(COINOR_HOME)/lib/$$(OPTION)
