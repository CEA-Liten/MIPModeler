#-------------------------------------------------
#
# Project created by QtCreator 2016-09-13T09:54:02
#
#-------------------------------------------------
QT       -= gui

TARGET = libCbcSolver
TEMPLATE = lib
#CONFIG += staticlib

INCLUDEPATH += $$(COINOR_HOME)/Cbc/src
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglZeroHalf
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglGMI
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglLandP
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglTwomir
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglMixedIntegerRounding
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglMixedIntegerRounding2
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglFlowCover
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglClique
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglOddHole
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglKnapsackCover
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglGomory
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglPreProcess
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglDuplicateRow
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglRedSplit
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglProbing
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src
INCLUDEPATH += $$(COINOR_HOME)/Clp/src
INCLUDEPATH += $$(COINOR_HOME)/Clp/src/OsiClp
INCLUDEPATH += $$(COINOR_HOME)/Osi/src/Osi
INCLUDEPATH += $$(COINOR_HOME)/CoinUtils/src
INCLUDEPATH += $$(COINOR_HOME)/BuildTools/headers
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglResidualCapacity
INCLUDEPATH += $$(COINOR_HOME)/Cgl/src/CglRedSplit2

LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCbc.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCgl.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libClp.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsiClp.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libOsi.lib
LIBS        += $$(COINOR_HOME)/lib/$$(OPTION)/libCoinUtils.lib

DEFINES += CBC_BUILD
DEFINES += WIN32
DEFINES += NDEBUG
DEFINES += _NDEBUG
DEFINES += COIN_FAST_CODE
DEFINES += CLP_FAST_CODE
DEFINES += COIN_NO_TEST_DUPLICATE
DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += \
    ..\..\src\CbcCbcParam.cpp \
    ..\..\src\CbcLinked.cpp \
    ..\..\src\CbcLinkedUtils.cpp \
    ..\..\src\CbcSolver.cpp \
    ..\..\src\CbcSolverAnalyze.cpp \
    ..\..\src\CbcSolverExpandKnapsack.cpp \
    ..\..\src\CbcSolverHeuristics.cpp \
    ..\..\src\unitTestClp.cpp \

HEADERS +=  \
    ..\..\src\CbcLinked.hpp \
    ..\..\src\CbcSolver.hpp \
    ..\..\src\CbcSolverAnalyze.hpp \
    ..\..\src\CbcSolverExpandKnapsack.hpp \
    ..\..\src\CbcSolverHeuristics.hpp \

DESTDIR = $$(COINOR_HOME)/lib/$$(OPTION)
