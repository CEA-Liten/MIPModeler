QT       -= gui

TARGET = libOsi
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += ../../../CoinUtils/src
INCLUDEPATH += ../../../Osi/src/Osi

LIBS        += ../../../lib/$$(OPTION)/libCoinUtils.lib

DEFINES += OSI_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _LIB
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _CRT_SECURE_NO_DEPRECATE

SOURCES += \
    ../../src/Osi/OsiAuxInfo.cpp \
    ../../src/Osi/OsiBranchingObject.cpp \
    ../../src/Osi/OsiChooseVariable.cpp \
    ../../src/Osi/OsiColCut.cpp \
    ../../src/Osi/OsiCut.cpp \
    ../../src/Osi/OsiCuts.cpp \
    ../../src/Osi/OsiNames.cpp \
    ../../src/Osi/OsiPresolve.cpp \
    ../../src/Osi/OsiRowCut.cpp \
    ../../src/Osi/OsiRowCutDebugger.cpp \
    ../../src/Osi/OsiSolverBranch.cpp \
    ../../src/Osi/OsiSolverInterface.cpp \

HEADERS +=  \
    ../../src/Osi/OsiAuxInfo.hpp \
    ../../src/Osi/OsiBranchingObject.hpp \
    ../../src/Osi/OsiChooseVariable.hpp \
    ../../src/Osi/OsiColCut.hpp \
    ../../src/Osi/OsiCollections.hpp \
    ../../src/Osi/OsiConfig.h \
    ../../src/Osi/OsiCut.hpp \
    ../../src/Osi/OsiCuts.hpp \
#    ../../src/Osi/OsiOpbdpSolve.hpp \
    ../../src/Osi/OsiPresolve.hpp \
    ../../src/Osi/OsiRowCut.hpp \
    ../../src/Osi/OsiRowCutDebugger.hpp \
    ../../src/Osi/OsiSolverBranch.hpp \
    ../../src/Osi/OsiSolverInterface.hpp \
    ../../src/Osi/OsiSolverParameters.hpp \

DESTDIR = ../../../lib/$$(OPTION)
